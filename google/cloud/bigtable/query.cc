// Copyright 2025 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "google/cloud/bigtable/query.h"
#include "google/cloud/internal/make_status.h"
#include "google/cloud/log.h"
#include <algorithm>
#include <thread>

namespace google {
namespace cloud {
namespace bigtable {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

std::ostream& operator<<(std::ostream& os, Value const& v) {
  // TODO(sdhart): implement this
  return os;
}

bool operator==(Value const& a, Value const& b) {
  // TODO(sdhart): implement this
  return true;
}

QueryRow::QueryRow()
    : QueryRow({}, std::make_shared<std::vector<std::string>>()) {}

QueryRow::QueryRow(std::vector<Value> values,
                   std::shared_ptr<std::vector<std::string> const> columns)
    : values_(std::move(values)), columns_(std::move(columns)) {
  if (values_.size() != columns_->size()) {
    GCP_LOG(FATAL) << "Row's value and column sizes do not match: "
                   << values_.size() << " vs " << columns_->size();
  }
}

// NOLINTNEXTLINE(readability-identifier-naming)
StatusOr<Value> QueryRow::get(std::size_t pos) const {
  if (pos < values_.size()) return values_[pos];
  return internal::InvalidArgumentError("position out of range",
                                        GCP_ERROR_INFO());
}

// NOLINTNEXTLINE(readability-identifier-naming)
StatusOr<Value> QueryRow::get(std::string const& name) const {
  auto it = std::find(columns_->begin(), columns_->end(), name);
  if (it != columns_->end()) return get(std::distance(columns_->begin(), it));
  return internal::InvalidArgumentError("column name not found",
                                        GCP_ERROR_INFO());
}

bool operator==(QueryRow const& a, QueryRow const& b) {
  return a.values_ == b.values_ && *a.columns_ == *b.columns_;
}

RowStreamIterator::RowStreamIterator() = default;

RowStreamIterator::RowStreamIterator(Source source)
    : source_(std::move(source)) {
  ++*this;
}

RowStreamIterator& RowStreamIterator::operator++() {
  if (!row_ok_) {
    source_ = nullptr;  // Last row was an error; become "end"
    return *this;
  }
  row_ = source_();
  row_ok_ = row_.ok();
  if (row_ && row_->size() == 0) {
    source_ = nullptr;  // No more Rows to consume; become "end"
    return *this;
  }
  return *this;
}

RowStreamIterator RowStreamIterator::operator++(int) {
  auto old = *this;
  ++*this;
  return old;
}

bool operator==(RowStreamIterator const& a, RowStreamIterator const& b) {
  // Input iterators may only be compared to (copies of) themselves and end.
  // See https://en.cppreference.com/w/cpp/named_req/InputIterator. Therefore,
  // by definition, all input iterators are equal unless one is end and the
  // other is not.
  return !a.source_ == !b.source_;
}

bool operator!=(RowStreamIterator const& a, RowStreamIterator const& b) {
  return !(a == b);
}

std::vector<std::string> SqlStatement::ParameterNames() const {
  std::vector<std::string> keys;
  keys.reserve(params_.size());
  for (auto const& p : params_) {
    keys.push_back(p.first);
  }
  return keys;
}

google::cloud::StatusOr<Value> SqlStatement::GetParameter(
    std::string const& parameter_name) const {
  auto iter = params_.find(parameter_name);
  if (iter != params_.end()) {
    return iter->second;
  }
  return internal::NotFoundError("No such parameter: " + parameter_name,
                                 GCP_ERROR_INFO());
}

std::ostream& operator<<(std::ostream& os, SqlStatement const& stmt) {
  os << stmt.statement_;
  for (auto const& param : stmt.params_) {
    os << "\n[param]: {" << param.first << "=" << param.second << "}";
  }
  return os;
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace bigtable

namespace bigtable_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

void PartialResultSetResume::TryCancel() { child_->TryCancel(); }

absl::optional<PartialResultSet> PartialResultSetResume::Read(
    absl::optional<std::string> const& resume_token) {
  bool resumption = false;
  do {
    absl::optional<PartialResultSet> result = child_->Read(resume_token);
    if (result) {
      // Let the caller know if we recreated the PartialResultSetReader using
      // the resume_token so that they might discard any previous results that
      // will be contained in the new stream.
      if (resumption) result->resumption = true;
      return result;
    }
    auto status = Finish();
    if (status.ok()) return {};
    if (!resume_token) {
      // Our caller has requested that we not try to resume the stream,
      // probably because they have already delivered previous results that
      // would otherwise be replayed.
      return {};
    }
    if (idempotency_ == google::cloud::Idempotency::kNonIdempotent ||
        !retry_policy_prototype_->OnFailure(status)) {
      return {};
    }
    std::this_thread::sleep_for(backoff_policy_prototype_->OnCompletion());
    resumption = true;
    last_status_.reset();
    child_ = factory_(*resume_token);
  } while (!retry_policy_prototype_->IsExhausted());
  return {};
}

Status PartialResultSetResume::Finish() {
  // Finish() can be called only once, so cache the last result.
  if (last_status_.has_value()) {
    return *last_status_;
  }
  last_status_ = child_->Finish();
  return *last_status_;
}

StatusOr<std::unique_ptr<PartialResultSourceInterface>>
PartialResultSetSource::Create(std::unique_ptr<PartialResultSetReader> reader) {
  std::cout << __func__ << std::endl;
  std::unique_ptr<PartialResultSetSource> source(
      new PartialResultSetSource(std::move(reader)));

  // Do an initial read from the stream to determine the fate of the factory.
  auto status = source->ReadFromStream();

  // If the initial read finished the stream, and `Finish()` failed, then
  // creating the `PartialResultSetSource` should fail with the same error.
  if (source->state_ == kFinished && !status.ok()) return status;

  // Otherwise we require that the first response contains the metadata.
  // Without it, creating the `PartialResultSetSource` should fail.
  if (!source->metadata_) {
    return internal::InternalError(
        "PartialResultSetSource response contained no metadata",
        GCP_ERROR_INFO());
  }

  return {std::move(source)};
}

PartialResultSetSource::PartialResultSetSource(
    std::unique_ptr<PartialResultSetReader> reader)
    : options_(internal::CurrentOptions()), reader_(std::move(reader)) {
  //  if (options_.has<spanner::StreamingResumabilityBufferSizeOption>()) {
  //    values_space_limit_ =
  //        options_.get<spanner::StreamingResumabilityBufferSizeOption>();
  //  }
}

PartialResultSetSource::~PartialResultSetSource() {
  internal::OptionsSpan span(options_);
  if (state_ == kReading) {
    // Finish() can deadlock if there is still data in the streaming RPC,
    // so before trying to read the final status we need to cancel.
    reader_->TryCancel();
    state_ = kEndOfStream;
  }
  if (state_ == kEndOfStream) {
    // The user didn't iterate over all the data, so finish the stream on
    // their behalf, although we have no way to communicate error status.
    auto status = reader_->Finish();
    if (!status.ok() && status.code() != StatusCode::kCancelled) {
      GCP_LOG(WARNING)
          << "PartialResultSetSource: Finish() failed in destructor: "
          << status;
    }
    state_ = kFinished;
  }
}

StatusOr<bigtable::QueryRow> PartialResultSetSource::NextRow() {
  while (rows_.empty()) {
    if (state_ == kFinished) return bigtable::QueryRow();
    internal::OptionsSpan span(options_);
    auto status = ReadFromStream();
    if (!status.ok()) return status;
  }
  auto row = std::move(rows_.front());
  rows_.pop_front();
  return row;
}

/*
message ExecuteQueryResponse {
  oneof response {
    ResultSetMetadata metadata = 1;
    PartialResultSet results = 2;
  }
}

message ColumnMetadata {
  string name = 1;
  Type type = 2;
}

message ProtoSchema {
  repeated ColumnMetadata columns = 1;
}

message ResultSetMetadata {
  oneof schema {
    ProtoSchema proto_schema = 1;
  }
}

// Rows represented in proto format.
//
// This should be constructed by concatenating the `batch_data` from each
// of the relevant `ProtoRowsBatch` messages and parsing the result as a
// `ProtoRows` message.
message ProtoRows {
  // A proto rows message consists of a list of values. Every N complete values
  // defines a row, where N is equal to the  number of entries in the
  // `metadata.proto_schema.columns` value received in the first response.
  repeated Value values = 2;
}

message ProtoRowsBatch {
  // Part of a serialized `ProtoRows` message.
  // A complete, parseable ProtoRows message is constructed by
  // concatenating `batch_data` from multiple `ProtoRowsBatch` messages. The
  // `PartialResultSet` that contains the last part has `complete_batch` set to
  // `true`.
  bytes batch_data = 1;
}

 message PartialResultSet {
  // Multiple `PartialResultSet` messages may be sent to represent a complete
  // response. The client should buffer data constructed from the fields in
  // `partial_rows` until a non-empty `resume_token` is received. Each
  // sub-message documents the appropriate way to combine results.
  oneof partial_rows {
    // Partial rows in serialized ProtoRows format.
    ProtoRowsBatch proto_rows_batch = 3;
  }

  // CRC32C checksum of concatenated `partial_rows` data for the current batch.
  //
  // When present, the buffered data from `partial_rows` forms a complete
  // parseable message of the appropriate type.
  //
  // The client should mark the end of a parseable message and prepare to
  // receive a new one starting from the next `PartialResultSet` message.
  // Clients must verify the checksum of the serialized batch before yielding it
  // to the caller.
  //
  // This does NOT mean the values can be yielded to the callers since a
  // `resume_token` is required to safely do so.
  //
  // If `resume_token` is non-empty and any data has been received since the
  // last one, this field is guaranteed to be non-empty. In other words, clients
  // may assume that a batch will never cross a `resume_token` boundary.
  optional uint32 batch_checksum = 6;

  // An opaque token sent by the server to allow query resumption and signal
  // that the buffered values constructed from received `partial_rows` can be
  // yielded to the caller. Clients can provide this token in a subsequent
  // request to resume the result stream from the current point.
  //
  // When `resume_token` is non-empty, the buffered values received from
  // `partial_rows` since the last non-empty `resume_token` can be yielded to
  // the callers, provided that the client keeps the value of `resume_token` and
  // uses it on subsequent retries.
  //
  // A `resume_token` may be sent without information in `partial_rows` to
  // checkpoint the progress of a sparse query. Any previous `partial_rows` data
  // should still be yielded in this case, and the new `resume_token` should be
  // saved for future retries as normal.
  //
  // A `resume_token` will only be sent on a boundary where there is either no
  // ongoing result batch, or `batch_checksum` is also populated.
  //
  // The server will also send a sentinel `resume_token` when last batch of
  // `partial_rows` is sent. If the client retries the ExecuteQueryRequest with
  // the sentinel `resume_token`, the server will emit it again without any
  // data in `partial_rows`, then return OK.
  bytes resume_token = 5;

  // If `true`, any data buffered since the last non-empty `resume_token` must
  // be discarded before the other parts of this message, if any, are handled.
  bool reset = 7;

  // Estimated size of the buffer required to hold the next batch of results.
  //
  // This value will be sent with the first `partial_rows` of a batch. That is,
  // on the first `partial_rows` received in a stream, on the first message
  // after a `batch_checksum` message, and any time `reset` is true.
  //
  // The client can use this estimate to allocate a buffer for the next batch of
  // results. This helps minimize the number of allocations required, though the
  // buffer size may still need to be increased if the estimate is too low.
  int32 estimated_batch_size = 4;
}
*/

std::vector<bigtable::QueryRow> ConvertToQueryRows(
    google::bigtable::v2::ResultSetMetadata const& metadata,
    google::bigtable::v2::ProtoRows proto_rows) {
  return {};
}

Status PartialResultSetSource::ReadResultsFromStream(
    google::bigtable::v2::PartialResultSet& results) {
  std::cout << __func__ << std::endl;
  if (results.reset()) {
    rows_.clear();
    read_buffer_.clear();
  }

  if (results.estimated_batch_size() > 0) {
    if (read_buffer_.empty()) {
      read_buffer_.reserve(results.estimated_batch_size());
    }
  }

  if (results.has_proto_rows_batch()) {
    // TODO(sdhart): This seems like an opportunity to use absl::Cord, but I
    //  forget what version of absl it's available in.
    absl::StrAppend(&read_buffer_, results.proto_rows_batch().batch_data());
  }

  if (results.has_batch_checksum() && !read_buffer_.empty()) {
    // perform crc32c checksum on buffer
    // if buffer is valid
    google::bigtable::v2::ProtoRows proto_rows;
    if (proto_rows.ParseFromString(read_buffer_)) {
      read_buffer_.clear();
      std::vector<bigtable::QueryRow> query_rows =
          ConvertToQueryRows(*metadata_, std::move(proto_rows));
      pending_rows_.insert(pending_rows_.end(), query_rows.begin(),
                           query_rows.end());
    }
  }

  if (!results.resume_token().empty()) {
    rows_.insert(rows_.end(), pending_rows_.begin(), pending_rows_.end());
    pending_rows_.clear();
    resume_token_ = results.resume_token();
  }

  return {};
}

Status PartialResultSetSource::ReadFromStream() {
  std::cout << __func__ << std::endl;
  absl::optional<PartialResultSet> result_set;
  if (state_ == kFinished || !rows_.empty()) {
    return internal::InternalError("PartialResultSetSource state error",
                                   GCP_ERROR_INFO());
  }
  if (state_ == kReading) {
    result_set = reader_->Read(resume_token_);
    if (!result_set) state_ = kEndOfStream;
  }
  if (state_ == kEndOfStream) {
    // If we have no buffered data, we're done.
    if (values_.empty()) {
      state_ = kFinished;
      return reader_->Finish();
    }
    // Otherwise, proceed with a `PartialResultSet` using a fake resume
    // token to flush the buffer. The service does not appear to yield
    // a resume token in its final response, despite it completing a row.
    // TODO(sdhart): the above comment is Spanner behavior, determine how
    //   Bigtable populates the resume token in this scenario.
    result_set = PartialResultSet{{}, {}, false};
    if (result_set->results.has_value()) {
      result_set->results->set_resume_token("<end-of-stream>");
    }
  }

  if (result_set->metadata.has_value()) {
    std::cout << __func__ << ": result_set->metadata.has_value()" << std::endl;
    // If we get metadata more than once, log it, but use the first one.
    if (metadata_) {
      GCP_LOG(WARNING) << "PartialResultSetSource: Additional metadata";
    } else {
      metadata_ = std::move(*result_set->metadata);
      // Copy the column names into a vector that will be shared with
      // every Row object returned from NextRow().
      columns_ = std::make_shared<std::vector<std::string>>();
      columns_->reserve(metadata_->proto_schema().columns_size());
      for (auto const& c : metadata_->proto_schema().columns()) {
        columns_->push_back(c.name());
      }
    }
    return {};  // OK
  }

  if (result_set->results.has_value()) {
    return ReadResultsFromStream(*result_set->results);
  }

  return internal::InternalError(
      "ExecuteQueryResponse contains neither metadata nor results",
      GCP_ERROR_INFO());

#if 0
  // If reader_->Read() resulted in a new PartialResultSetReader (i.e., it
  // used the token to resume an interrupted stream), then we must discard
  // any buffered data as it will be replayed.
  if (result_set->resumption) {
    if (!resume_token_) {
      // The reader claims to have resumed the stream even though we said it
      // should not. That leaves us in the untenable position of possibly
      // having returned data that will be replayed, so fail the stream now.
      return internal::InternalError(
          "PartialResultSetSource reader resumed the stream"
          " despite our having asked it not to",
          GCP_ERROR_INFO());
    }
    values_back_incomplete_ = false;
    values_.Clear();
  }

  // If the final value in the previous `PartialResultSet` was incomplete,
  // it must be combined with the first value from the new set. And then
  // we move everything remaining from the new set to the end of `values_`.
  if (result_set->results.has_value()) {
    if (!result_set->results.values().empty()) {
      auto& new_values = *result_set->result.mutable_values();
      int append_start = 0;
      if (values_back_incomplete_) {
        auto& first = *new_values.Mutable(append_start++);
        auto status = MergeChunk(*values_.rbegin(), std::move(first));
        if (!status.ok()) return status;
      }
      ExtractSubrangeAndAppend(new_values, append_start, values_);
      values_back_incomplete_ = result_set->result.chunked_value();
    }
  }

  // Deliver whatever rows we can muster.
  auto const n_values = values_.size() - (values_back_incomplete_ ? 1 : 0);
  auto const n_columns = columns_ ? static_cast<int>(columns_->size()) : 0;
  auto n_rows = n_columns ? n_values / n_columns : 0;
  if (n_columns == 0 && !values_.empty()) {
    return internal::InternalError(
        "PartialResultSetSource metadata is missing row type",
        GCP_ERROR_INFO());
  }

  // If we didn't receive a resume token, and have not exceeded our buffer
  // limit, then we choose to `Read()` again so as to maintain resumability.
  if (result_set->result.resume_token().empty()) {
    if (values_.SpaceUsedExcludingSelfLong() < values_space_limit_) {
      return {};  // OK
    }
  }

  // If we did receive a resume token then everything should be deliverable,
  // and we'll be able to resume the stream at this point after a breakage.
  // Otherwise, if we deliver anything at all, we must disable resumability.
  if (!result_set->result.resume_token().empty()) {
    resume_token_ = result_set->result.resume_token();
    if (n_rows * n_columns != values_.size()) {
      if (state_ != kEndOfStream) {
        return internal::InternalError(
            "PartialResultSetSource reader produced a resume token"
            " that is not on a row boundary",
            GCP_ERROR_INFO());
      }
      if (n_rows == 0) {
        return internal::InternalError(
            "PartialResultSetSource stream ended at a point"
            " that is not on a row boundary",
            GCP_ERROR_INFO());
      }
    }
  } else if (n_rows != 0) {
    resume_token_ = absl::nullopt;
  }

  // Combine the available values into new elements of `rows_`.
  int values_pos = 0;
  std::vector<spanner::Value> values;
  values.reserve(n_columns);
  for (; n_rows != 0; --n_rows) {
    for (auto const& field : metadata_->row_type().fields()) {
      auto& value = *values_.Mutable(values_pos++);
      values.push_back(FromProto(field.type(), std::move(value)));
    }
    rows_.push_back(RowFriend::MakeRow(std::move(values), columns_));
    values.clear();
  }

  // If we didn't combine all the values, leave the remainder for next time.
  auto* rem_values = result_set->result.mutable_values();
  ExtractSubrangeAndAppend(values_, values_pos, *rem_values);
  values_.Swap(rem_values);

  return {};  // OK
#endif
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace bigtable_internal
}  // namespace cloud
}  // namespace google

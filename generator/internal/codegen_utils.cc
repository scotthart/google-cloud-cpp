// Copyright 2019 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "generator/internal/codegen_utils.h"
#include <iostream>
#include <string>

namespace google {
namespace codegen {
namespace internal {

using google::protobuf::Descriptor;
using google::protobuf::FieldDescriptor;
using google::protobuf::MethodDescriptor;

namespace {
const char generator_file_suffix[] = ".gcpcxx.pb";
}  // namespace

std::string GeneratedFileSuffix() { return {generator_file_suffix}; }

std::string LocalInclude(std::string header) {
  return absl::StrCat("\"", header, "\"");
}

std::string SystemInclude(std::string header) {
  return absl::StrCat("<", header, ">");
}

// https://google.aip.dev/client-libraries/4233
bool IsPaginated(google::protobuf::MethodDescriptor const* m) {
    Descriptor const* request_message = m->input_type();
    FieldDescriptor const* page_size = request_message->FindFieldByName("page_size");
    if (page_size && page_size->type() != FieldDescriptor::TYPE_INT32) return false;
    FieldDescriptor const* page_token = request_message->FindFieldByName("page_token");
    if (page_token && page_token->type() != FieldDescriptor::TYPE_STRING) return false;

    Descriptor const* response_message = m->output_type();
    FieldDescriptor const* next_page_token = response_message->FindFieldByName("next_page_token");
    if (next_page_token && next_page_token->type() != FieldDescriptor::TYPE_STRING) return false;

    std::vector<std::tuple<std::string, Descriptor const*, int>> repeated_message_fields;
    for (int i = 0; i < response_message->field_count(); ++i) {
        FieldDescriptor const* field = response_message->field(i);
        if (field->is_repeated() && field->type() == FieldDescriptor::TYPE_MESSAGE) {
            // field_name, message_type, field_number
            repeated_message_fields.push_back(std::make_tuple(field->name(), field->message_type(), field->number()));
            break;
        }
    }

    if (repeated_message_fields.empty()) return false;

    if (repeated_message_fields.size() > 1) {
        auto min_field = std::min_element(repeated_message_fields.begin(), repeated_message_fields.end(),
                [](std::tuple<std::string, Descriptor const*, int> const& lhs,
                        std::tuple<std::string, Descriptor const*, int> const& rhs) {
            return std::get<2>(lhs) < std::get<2>(rhs);
        });
        int min_field_number = std::get<2>(*min_field);
        if (min_field_number != std::get<2>(repeated_message_fields[0])) {
            std::cerr << "Repeated field in paginated response must be first appearing and lowest field number" <<
            m->full_name() << std::endl;
            std::exit(1);
        }
    }
    return true;
}

bool IsNonStreaming(pb::MethodDescriptor const* m) {
  return !m->client_streaming() && !m->server_streaming();
}

bool IsLongrunningOperation(google::protobuf::MethodDescriptor const* m) {
  return m->output_type()->full_name() == "google.longrunning.Operation";
}

bool IsResponseTypeEmpty(google::protobuf::MethodDescriptor const* m) {
  return m->output_type()->full_name() == "google.protobuf.Empty";
}

std::string CamelCaseToSnakeCase(std::string const& input) {
  std::string output;
  for (auto i = 0u; i < input.size(); ++i) {
    if (i + 2 < input.size()) {
      if (std::isupper(input[i + 1]) && std::islower(input[i + 2])) {
        absl::StrAppend(&output, std::string(1, std::tolower(input[i])), "_");
        continue;
      }
    }
    if (i + 1 < input.size()) {
      if ((std::islower(input[i]) || std::isdigit(input[i])) &&
          std::isupper(input[i + 1])) {
        absl::StrAppend(&output, std::string(1, std::tolower(input[i])), "_");
        continue;
      }
    }
    absl::StrAppend(&output, std::string(1, std::tolower(input[i])));
  }
  return output;
}

std::string ServiceNameToFilePath(std::string const& service_name) {
  std::vector<std::string> components = absl::StrSplit(service_name, '.');
  absl::string_view last(components.back());
  absl::ConsumeSuffix(&last, "Service");
  components.back() = std::string(last);
  std::transform(components.begin(), components.end(), components.begin(),
                 CamelCaseToSnakeCase);
  return absl::StrJoin(components, "/");
}

std::string ProtoNameToCppName(std::string const& proto_name) {
  return "::" + absl::StrReplaceAll(proto_name, {{".", "::"}});
}

}  // namespace internal
}  // namespace codegen
}  // namespace google

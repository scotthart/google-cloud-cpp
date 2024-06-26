// Copyright 2022 Google LLC
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

// Generated by the Codegen C++ plugin.
// If you make any local changes, they will be lost.
// source: google/cloud/documentai/v1/document_processor_service.proto

#include "google/cloud/documentai/v1/document_processor_client.h"
#include <memory>
#include <utility>

namespace google {
namespace cloud {
namespace documentai_v1 {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

DocumentProcessorServiceClient::DocumentProcessorServiceClient(
    std::shared_ptr<DocumentProcessorServiceConnection> connection,
    Options opts)
    : connection_(std::move(connection)),
      options_(
          internal::MergeOptions(std::move(opts), connection_->options())) {}
DocumentProcessorServiceClient::~DocumentProcessorServiceClient() = default;

StatusOr<google::cloud::documentai::v1::ProcessResponse>
DocumentProcessorServiceClient::ProcessDocument(std::string const& name,
                                                Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::documentai::v1::ProcessRequest request;
  request.set_name(name);
  return connection_->ProcessDocument(request);
}

StatusOr<google::cloud::documentai::v1::ProcessResponse>
DocumentProcessorServiceClient::ProcessDocument(
    google::cloud::documentai::v1::ProcessRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->ProcessDocument(request);
}

future<StatusOr<google::cloud::documentai::v1::BatchProcessResponse>>
DocumentProcessorServiceClient::BatchProcessDocuments(std::string const& name,
                                                      Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::documentai::v1::BatchProcessRequest request;
  request.set_name(name);
  return connection_->BatchProcessDocuments(request);
}

StatusOr<google::longrunning::Operation>
DocumentProcessorServiceClient::BatchProcessDocuments(ExperimentalTag,
                                                      NoAwaitTag,
                                                      std::string const& name,
                                                      Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::documentai::v1::BatchProcessRequest request;
  request.set_name(name);
  return connection_->BatchProcessDocuments(ExperimentalTag{}, NoAwaitTag{},
                                            request);
}

future<StatusOr<google::cloud::documentai::v1::BatchProcessResponse>>
DocumentProcessorServiceClient::BatchProcessDocuments(
    google::cloud::documentai::v1::BatchProcessRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->BatchProcessDocuments(request);
}

StatusOr<google::longrunning::Operation>
DocumentProcessorServiceClient::BatchProcessDocuments(
    ExperimentalTag, NoAwaitTag,
    google::cloud::documentai::v1::BatchProcessRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->BatchProcessDocuments(ExperimentalTag{}, NoAwaitTag{},
                                            request);
}

future<StatusOr<google::cloud::documentai::v1::BatchProcessResponse>>
DocumentProcessorServiceClient::BatchProcessDocuments(
    ExperimentalTag, google::longrunning::Operation const& operation,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->BatchProcessDocuments(ExperimentalTag{}, operation);
}

StatusOr<google::cloud::documentai::v1::FetchProcessorTypesResponse>
DocumentProcessorServiceClient::FetchProcessorTypes(std::string const& parent,
                                                    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::documentai::v1::FetchProcessorTypesRequest request;
  request.set_parent(parent);
  return connection_->FetchProcessorTypes(request);
}

StatusOr<google::cloud::documentai::v1::FetchProcessorTypesResponse>
DocumentProcessorServiceClient::FetchProcessorTypes(
    google::cloud::documentai::v1::FetchProcessorTypesRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->FetchProcessorTypes(request);
}

StreamRange<google::cloud::documentai::v1::ProcessorType>
DocumentProcessorServiceClient::ListProcessorTypes(std::string const& parent,
                                                   Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::documentai::v1::ListProcessorTypesRequest request;
  request.set_parent(parent);
  return connection_->ListProcessorTypes(request);
}

StreamRange<google::cloud::documentai::v1::ProcessorType>
DocumentProcessorServiceClient::ListProcessorTypes(
    google::cloud::documentai::v1::ListProcessorTypesRequest request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->ListProcessorTypes(std::move(request));
}

StatusOr<google::cloud::documentai::v1::ProcessorType>
DocumentProcessorServiceClient::GetProcessorType(std::string const& name,
                                                 Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::documentai::v1::GetProcessorTypeRequest request;
  request.set_name(name);
  return connection_->GetProcessorType(request);
}

StatusOr<google::cloud::documentai::v1::ProcessorType>
DocumentProcessorServiceClient::GetProcessorType(
    google::cloud::documentai::v1::GetProcessorTypeRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->GetProcessorType(request);
}

StreamRange<google::cloud::documentai::v1::Processor>
DocumentProcessorServiceClient::ListProcessors(std::string const& parent,
                                               Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::documentai::v1::ListProcessorsRequest request;
  request.set_parent(parent);
  return connection_->ListProcessors(request);
}

StreamRange<google::cloud::documentai::v1::Processor>
DocumentProcessorServiceClient::ListProcessors(
    google::cloud::documentai::v1::ListProcessorsRequest request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->ListProcessors(std::move(request));
}

StatusOr<google::cloud::documentai::v1::Processor>
DocumentProcessorServiceClient::GetProcessor(std::string const& name,
                                             Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::documentai::v1::GetProcessorRequest request;
  request.set_name(name);
  return connection_->GetProcessor(request);
}

StatusOr<google::cloud::documentai::v1::Processor>
DocumentProcessorServiceClient::GetProcessor(
    google::cloud::documentai::v1::GetProcessorRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->GetProcessor(request);
}

future<StatusOr<google::cloud::documentai::v1::TrainProcessorVersionResponse>>
DocumentProcessorServiceClient::TrainProcessorVersion(
    std::string const& parent,
    google::cloud::documentai::v1::ProcessorVersion const& processor_version,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::documentai::v1::TrainProcessorVersionRequest request;
  request.set_parent(parent);
  *request.mutable_processor_version() = processor_version;
  return connection_->TrainProcessorVersion(request);
}

StatusOr<google::longrunning::Operation>
DocumentProcessorServiceClient::TrainProcessorVersion(
    ExperimentalTag, NoAwaitTag, std::string const& parent,
    google::cloud::documentai::v1::ProcessorVersion const& processor_version,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::documentai::v1::TrainProcessorVersionRequest request;
  request.set_parent(parent);
  *request.mutable_processor_version() = processor_version;
  return connection_->TrainProcessorVersion(ExperimentalTag{}, NoAwaitTag{},
                                            request);
}

future<StatusOr<google::cloud::documentai::v1::TrainProcessorVersionResponse>>
DocumentProcessorServiceClient::TrainProcessorVersion(
    google::cloud::documentai::v1::TrainProcessorVersionRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->TrainProcessorVersion(request);
}

StatusOr<google::longrunning::Operation>
DocumentProcessorServiceClient::TrainProcessorVersion(
    ExperimentalTag, NoAwaitTag,
    google::cloud::documentai::v1::TrainProcessorVersionRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->TrainProcessorVersion(ExperimentalTag{}, NoAwaitTag{},
                                            request);
}

future<StatusOr<google::cloud::documentai::v1::TrainProcessorVersionResponse>>
DocumentProcessorServiceClient::TrainProcessorVersion(
    ExperimentalTag, google::longrunning::Operation const& operation,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->TrainProcessorVersion(ExperimentalTag{}, operation);
}

StatusOr<google::cloud::documentai::v1::ProcessorVersion>
DocumentProcessorServiceClient::GetProcessorVersion(std::string const& name,
                                                    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::documentai::v1::GetProcessorVersionRequest request;
  request.set_name(name);
  return connection_->GetProcessorVersion(request);
}

StatusOr<google::cloud::documentai::v1::ProcessorVersion>
DocumentProcessorServiceClient::GetProcessorVersion(
    google::cloud::documentai::v1::GetProcessorVersionRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->GetProcessorVersion(request);
}

StreamRange<google::cloud::documentai::v1::ProcessorVersion>
DocumentProcessorServiceClient::ListProcessorVersions(std::string const& parent,
                                                      Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::documentai::v1::ListProcessorVersionsRequest request;
  request.set_parent(parent);
  return connection_->ListProcessorVersions(request);
}

StreamRange<google::cloud::documentai::v1::ProcessorVersion>
DocumentProcessorServiceClient::ListProcessorVersions(
    google::cloud::documentai::v1::ListProcessorVersionsRequest request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->ListProcessorVersions(std::move(request));
}

future<StatusOr<google::cloud::documentai::v1::DeleteProcessorVersionMetadata>>
DocumentProcessorServiceClient::DeleteProcessorVersion(std::string const& name,
                                                       Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::documentai::v1::DeleteProcessorVersionRequest request;
  request.set_name(name);
  return connection_->DeleteProcessorVersion(request);
}

StatusOr<google::longrunning::Operation>
DocumentProcessorServiceClient::DeleteProcessorVersion(ExperimentalTag,
                                                       NoAwaitTag,
                                                       std::string const& name,
                                                       Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::documentai::v1::DeleteProcessorVersionRequest request;
  request.set_name(name);
  return connection_->DeleteProcessorVersion(ExperimentalTag{}, NoAwaitTag{},
                                             request);
}

future<StatusOr<google::cloud::documentai::v1::DeleteProcessorVersionMetadata>>
DocumentProcessorServiceClient::DeleteProcessorVersion(
    google::cloud::documentai::v1::DeleteProcessorVersionRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->DeleteProcessorVersion(request);
}

StatusOr<google::longrunning::Operation>
DocumentProcessorServiceClient::DeleteProcessorVersion(
    ExperimentalTag, NoAwaitTag,
    google::cloud::documentai::v1::DeleteProcessorVersionRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->DeleteProcessorVersion(ExperimentalTag{}, NoAwaitTag{},
                                             request);
}

future<StatusOr<google::cloud::documentai::v1::DeleteProcessorVersionMetadata>>
DocumentProcessorServiceClient::DeleteProcessorVersion(
    ExperimentalTag, google::longrunning::Operation const& operation,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->DeleteProcessorVersion(ExperimentalTag{}, operation);
}

future<StatusOr<google::cloud::documentai::v1::DeployProcessorVersionResponse>>
DocumentProcessorServiceClient::DeployProcessorVersion(std::string const& name,
                                                       Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::documentai::v1::DeployProcessorVersionRequest request;
  request.set_name(name);
  return connection_->DeployProcessorVersion(request);
}

StatusOr<google::longrunning::Operation>
DocumentProcessorServiceClient::DeployProcessorVersion(ExperimentalTag,
                                                       NoAwaitTag,
                                                       std::string const& name,
                                                       Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::documentai::v1::DeployProcessorVersionRequest request;
  request.set_name(name);
  return connection_->DeployProcessorVersion(ExperimentalTag{}, NoAwaitTag{},
                                             request);
}

future<StatusOr<google::cloud::documentai::v1::DeployProcessorVersionResponse>>
DocumentProcessorServiceClient::DeployProcessorVersion(
    google::cloud::documentai::v1::DeployProcessorVersionRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->DeployProcessorVersion(request);
}

StatusOr<google::longrunning::Operation>
DocumentProcessorServiceClient::DeployProcessorVersion(
    ExperimentalTag, NoAwaitTag,
    google::cloud::documentai::v1::DeployProcessorVersionRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->DeployProcessorVersion(ExperimentalTag{}, NoAwaitTag{},
                                             request);
}

future<StatusOr<google::cloud::documentai::v1::DeployProcessorVersionResponse>>
DocumentProcessorServiceClient::DeployProcessorVersion(
    ExperimentalTag, google::longrunning::Operation const& operation,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->DeployProcessorVersion(ExperimentalTag{}, operation);
}

future<
    StatusOr<google::cloud::documentai::v1::UndeployProcessorVersionResponse>>
DocumentProcessorServiceClient::UndeployProcessorVersion(
    std::string const& name, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::documentai::v1::UndeployProcessorVersionRequest request;
  request.set_name(name);
  return connection_->UndeployProcessorVersion(request);
}

StatusOr<google::longrunning::Operation>
DocumentProcessorServiceClient::UndeployProcessorVersion(
    ExperimentalTag, NoAwaitTag, std::string const& name, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::documentai::v1::UndeployProcessorVersionRequest request;
  request.set_name(name);
  return connection_->UndeployProcessorVersion(ExperimentalTag{}, NoAwaitTag{},
                                               request);
}

future<
    StatusOr<google::cloud::documentai::v1::UndeployProcessorVersionResponse>>
DocumentProcessorServiceClient::UndeployProcessorVersion(
    google::cloud::documentai::v1::UndeployProcessorVersionRequest const&
        request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->UndeployProcessorVersion(request);
}

StatusOr<google::longrunning::Operation>
DocumentProcessorServiceClient::UndeployProcessorVersion(
    ExperimentalTag, NoAwaitTag,
    google::cloud::documentai::v1::UndeployProcessorVersionRequest const&
        request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->UndeployProcessorVersion(ExperimentalTag{}, NoAwaitTag{},
                                               request);
}

future<
    StatusOr<google::cloud::documentai::v1::UndeployProcessorVersionResponse>>
DocumentProcessorServiceClient::UndeployProcessorVersion(
    ExperimentalTag, google::longrunning::Operation const& operation,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->UndeployProcessorVersion(ExperimentalTag{}, operation);
}

StatusOr<google::cloud::documentai::v1::Processor>
DocumentProcessorServiceClient::CreateProcessor(
    std::string const& parent,
    google::cloud::documentai::v1::Processor const& processor, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::documentai::v1::CreateProcessorRequest request;
  request.set_parent(parent);
  *request.mutable_processor() = processor;
  return connection_->CreateProcessor(request);
}

StatusOr<google::cloud::documentai::v1::Processor>
DocumentProcessorServiceClient::CreateProcessor(
    google::cloud::documentai::v1::CreateProcessorRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->CreateProcessor(request);
}

future<StatusOr<google::cloud::documentai::v1::DeleteProcessorMetadata>>
DocumentProcessorServiceClient::DeleteProcessor(std::string const& name,
                                                Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::documentai::v1::DeleteProcessorRequest request;
  request.set_name(name);
  return connection_->DeleteProcessor(request);
}

StatusOr<google::longrunning::Operation>
DocumentProcessorServiceClient::DeleteProcessor(ExperimentalTag, NoAwaitTag,
                                                std::string const& name,
                                                Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::documentai::v1::DeleteProcessorRequest request;
  request.set_name(name);
  return connection_->DeleteProcessor(ExperimentalTag{}, NoAwaitTag{}, request);
}

future<StatusOr<google::cloud::documentai::v1::DeleteProcessorMetadata>>
DocumentProcessorServiceClient::DeleteProcessor(
    google::cloud::documentai::v1::DeleteProcessorRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->DeleteProcessor(request);
}

StatusOr<google::longrunning::Operation>
DocumentProcessorServiceClient::DeleteProcessor(
    ExperimentalTag, NoAwaitTag,
    google::cloud::documentai::v1::DeleteProcessorRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->DeleteProcessor(ExperimentalTag{}, NoAwaitTag{}, request);
}

future<StatusOr<google::cloud::documentai::v1::DeleteProcessorMetadata>>
DocumentProcessorServiceClient::DeleteProcessor(
    ExperimentalTag, google::longrunning::Operation const& operation,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->DeleteProcessor(ExperimentalTag{}, operation);
}

future<StatusOr<google::cloud::documentai::v1::EnableProcessorResponse>>
DocumentProcessorServiceClient::EnableProcessor(
    google::cloud::documentai::v1::EnableProcessorRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->EnableProcessor(request);
}

StatusOr<google::longrunning::Operation>
DocumentProcessorServiceClient::EnableProcessor(
    ExperimentalTag, NoAwaitTag,
    google::cloud::documentai::v1::EnableProcessorRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->EnableProcessor(ExperimentalTag{}, NoAwaitTag{}, request);
}

future<StatusOr<google::cloud::documentai::v1::EnableProcessorResponse>>
DocumentProcessorServiceClient::EnableProcessor(
    ExperimentalTag, google::longrunning::Operation const& operation,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->EnableProcessor(ExperimentalTag{}, operation);
}

future<StatusOr<google::cloud::documentai::v1::DisableProcessorResponse>>
DocumentProcessorServiceClient::DisableProcessor(
    google::cloud::documentai::v1::DisableProcessorRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->DisableProcessor(request);
}

StatusOr<google::longrunning::Operation>
DocumentProcessorServiceClient::DisableProcessor(
    ExperimentalTag, NoAwaitTag,
    google::cloud::documentai::v1::DisableProcessorRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->DisableProcessor(ExperimentalTag{}, NoAwaitTag{},
                                       request);
}

future<StatusOr<google::cloud::documentai::v1::DisableProcessorResponse>>
DocumentProcessorServiceClient::DisableProcessor(
    ExperimentalTag, google::longrunning::Operation const& operation,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->DisableProcessor(ExperimentalTag{}, operation);
}

future<
    StatusOr<google::cloud::documentai::v1::SetDefaultProcessorVersionResponse>>
DocumentProcessorServiceClient::SetDefaultProcessorVersion(
    google::cloud::documentai::v1::SetDefaultProcessorVersionRequest const&
        request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->SetDefaultProcessorVersion(request);
}

StatusOr<google::longrunning::Operation>
DocumentProcessorServiceClient::SetDefaultProcessorVersion(
    ExperimentalTag, NoAwaitTag,
    google::cloud::documentai::v1::SetDefaultProcessorVersionRequest const&
        request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->SetDefaultProcessorVersion(ExperimentalTag{},
                                                 NoAwaitTag{}, request);
}

future<
    StatusOr<google::cloud::documentai::v1::SetDefaultProcessorVersionResponse>>
DocumentProcessorServiceClient::SetDefaultProcessorVersion(
    ExperimentalTag, google::longrunning::Operation const& operation,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->SetDefaultProcessorVersion(ExperimentalTag{}, operation);
}

future<StatusOr<google::cloud::documentai::v1::ReviewDocumentResponse>>
DocumentProcessorServiceClient::ReviewDocument(
    std::string const& human_review_config, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::documentai::v1::ReviewDocumentRequest request;
  request.set_human_review_config(human_review_config);
  return connection_->ReviewDocument(request);
}

StatusOr<google::longrunning::Operation>
DocumentProcessorServiceClient::ReviewDocument(
    ExperimentalTag, NoAwaitTag, std::string const& human_review_config,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::documentai::v1::ReviewDocumentRequest request;
  request.set_human_review_config(human_review_config);
  return connection_->ReviewDocument(ExperimentalTag{}, NoAwaitTag{}, request);
}

future<StatusOr<google::cloud::documentai::v1::ReviewDocumentResponse>>
DocumentProcessorServiceClient::ReviewDocument(
    google::cloud::documentai::v1::ReviewDocumentRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->ReviewDocument(request);
}

StatusOr<google::longrunning::Operation>
DocumentProcessorServiceClient::ReviewDocument(
    ExperimentalTag, NoAwaitTag,
    google::cloud::documentai::v1::ReviewDocumentRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->ReviewDocument(ExperimentalTag{}, NoAwaitTag{}, request);
}

future<StatusOr<google::cloud::documentai::v1::ReviewDocumentResponse>>
DocumentProcessorServiceClient::ReviewDocument(
    ExperimentalTag, google::longrunning::Operation const& operation,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->ReviewDocument(ExperimentalTag{}, operation);
}

future<
    StatusOr<google::cloud::documentai::v1::EvaluateProcessorVersionResponse>>
DocumentProcessorServiceClient::EvaluateProcessorVersion(
    std::string const& processor_version, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::documentai::v1::EvaluateProcessorVersionRequest request;
  request.set_processor_version(processor_version);
  return connection_->EvaluateProcessorVersion(request);
}

StatusOr<google::longrunning::Operation>
DocumentProcessorServiceClient::EvaluateProcessorVersion(
    ExperimentalTag, NoAwaitTag, std::string const& processor_version,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::documentai::v1::EvaluateProcessorVersionRequest request;
  request.set_processor_version(processor_version);
  return connection_->EvaluateProcessorVersion(ExperimentalTag{}, NoAwaitTag{},
                                               request);
}

future<
    StatusOr<google::cloud::documentai::v1::EvaluateProcessorVersionResponse>>
DocumentProcessorServiceClient::EvaluateProcessorVersion(
    google::cloud::documentai::v1::EvaluateProcessorVersionRequest const&
        request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->EvaluateProcessorVersion(request);
}

StatusOr<google::longrunning::Operation>
DocumentProcessorServiceClient::EvaluateProcessorVersion(
    ExperimentalTag, NoAwaitTag,
    google::cloud::documentai::v1::EvaluateProcessorVersionRequest const&
        request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->EvaluateProcessorVersion(ExperimentalTag{}, NoAwaitTag{},
                                               request);
}

future<
    StatusOr<google::cloud::documentai::v1::EvaluateProcessorVersionResponse>>
DocumentProcessorServiceClient::EvaluateProcessorVersion(
    ExperimentalTag, google::longrunning::Operation const& operation,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->EvaluateProcessorVersion(ExperimentalTag{}, operation);
}

StatusOr<google::cloud::documentai::v1::Evaluation>
DocumentProcessorServiceClient::GetEvaluation(std::string const& name,
                                              Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::documentai::v1::GetEvaluationRequest request;
  request.set_name(name);
  return connection_->GetEvaluation(request);
}

StatusOr<google::cloud::documentai::v1::Evaluation>
DocumentProcessorServiceClient::GetEvaluation(
    google::cloud::documentai::v1::GetEvaluationRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->GetEvaluation(request);
}

StreamRange<google::cloud::documentai::v1::Evaluation>
DocumentProcessorServiceClient::ListEvaluations(std::string const& parent,
                                                Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::documentai::v1::ListEvaluationsRequest request;
  request.set_parent(parent);
  return connection_->ListEvaluations(request);
}

StreamRange<google::cloud::documentai::v1::Evaluation>
DocumentProcessorServiceClient::ListEvaluations(
    google::cloud::documentai::v1::ListEvaluationsRequest request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->ListEvaluations(std::move(request));
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace documentai_v1
}  // namespace cloud
}  // namespace google

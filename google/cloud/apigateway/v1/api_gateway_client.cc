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
// source: google/cloud/apigateway/v1/apigateway_service.proto

#include "google/cloud/apigateway/v1/api_gateway_client.h"
#include <memory>
#include <utility>

namespace google {
namespace cloud {
namespace apigateway_v1 {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

ApiGatewayServiceClient::ApiGatewayServiceClient(
    std::shared_ptr<ApiGatewayServiceConnection> connection, Options opts)
    : connection_(std::move(connection)),
      options_(
          internal::MergeOptions(std::move(opts), connection_->options())) {}
ApiGatewayServiceClient::~ApiGatewayServiceClient() = default;

StreamRange<google::cloud::apigateway::v1::Gateway>
ApiGatewayServiceClient::ListGateways(std::string const& parent, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::apigateway::v1::ListGatewaysRequest request;
  request.set_parent(parent);
  return connection_->ListGateways(request);
}

StreamRange<google::cloud::apigateway::v1::Gateway>
ApiGatewayServiceClient::ListGateways(
    google::cloud::apigateway::v1::ListGatewaysRequest request, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->ListGateways(std::move(request));
}

StatusOr<google::cloud::apigateway::v1::Gateway>
ApiGatewayServiceClient::GetGateway(std::string const& name, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::apigateway::v1::GetGatewayRequest request;
  request.set_name(name);
  return connection_->GetGateway(request);
}

StatusOr<google::cloud::apigateway::v1::Gateway>
ApiGatewayServiceClient::GetGateway(
    google::cloud::apigateway::v1::GetGatewayRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->GetGateway(request);
}

future<StatusOr<google::cloud::apigateway::v1::Gateway>>
ApiGatewayServiceClient::CreateGateway(
    std::string const& parent,
    google::cloud::apigateway::v1::Gateway const& gateway,
    std::string const& gateway_id, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::apigateway::v1::CreateGatewayRequest request;
  request.set_parent(parent);
  *request.mutable_gateway() = gateway;
  request.set_gateway_id(gateway_id);
  return connection_->CreateGateway(request);
}

StatusOr<google::longrunning::Operation> ApiGatewayServiceClient::CreateGateway(
    NoAwaitTag, std::string const& parent,
    google::cloud::apigateway::v1::Gateway const& gateway,
    std::string const& gateway_id, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::apigateway::v1::CreateGatewayRequest request;
  request.set_parent(parent);
  *request.mutable_gateway() = gateway;
  request.set_gateway_id(gateway_id);
  return connection_->CreateGateway(NoAwaitTag{}, request);
}

future<StatusOr<google::cloud::apigateway::v1::Gateway>>
ApiGatewayServiceClient::CreateGateway(
    google::cloud::apigateway::v1::CreateGatewayRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->CreateGateway(request);
}

StatusOr<google::longrunning::Operation> ApiGatewayServiceClient::CreateGateway(
    NoAwaitTag,
    google::cloud::apigateway::v1::CreateGatewayRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->CreateGateway(NoAwaitTag{}, request);
}

future<StatusOr<google::cloud::apigateway::v1::Gateway>>
ApiGatewayServiceClient::CreateGateway(
    google::longrunning::Operation const& operation, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->CreateGateway(operation);
}

future<StatusOr<google::cloud::apigateway::v1::Gateway>>
ApiGatewayServiceClient::UpdateGateway(
    google::cloud::apigateway::v1::Gateway const& gateway,
    google::protobuf::FieldMask const& update_mask, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::apigateway::v1::UpdateGatewayRequest request;
  *request.mutable_gateway() = gateway;
  *request.mutable_update_mask() = update_mask;
  return connection_->UpdateGateway(request);
}

StatusOr<google::longrunning::Operation> ApiGatewayServiceClient::UpdateGateway(
    NoAwaitTag, google::cloud::apigateway::v1::Gateway const& gateway,
    google::protobuf::FieldMask const& update_mask, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::apigateway::v1::UpdateGatewayRequest request;
  *request.mutable_gateway() = gateway;
  *request.mutable_update_mask() = update_mask;
  return connection_->UpdateGateway(NoAwaitTag{}, request);
}

future<StatusOr<google::cloud::apigateway::v1::Gateway>>
ApiGatewayServiceClient::UpdateGateway(
    google::cloud::apigateway::v1::UpdateGatewayRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->UpdateGateway(request);
}

StatusOr<google::longrunning::Operation> ApiGatewayServiceClient::UpdateGateway(
    NoAwaitTag,
    google::cloud::apigateway::v1::UpdateGatewayRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->UpdateGateway(NoAwaitTag{}, request);
}

future<StatusOr<google::cloud::apigateway::v1::Gateway>>
ApiGatewayServiceClient::UpdateGateway(
    google::longrunning::Operation const& operation, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->UpdateGateway(operation);
}

future<StatusOr<google::cloud::apigateway::v1::OperationMetadata>>
ApiGatewayServiceClient::DeleteGateway(std::string const& name, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::apigateway::v1::DeleteGatewayRequest request;
  request.set_name(name);
  return connection_->DeleteGateway(request);
}

StatusOr<google::longrunning::Operation> ApiGatewayServiceClient::DeleteGateway(
    NoAwaitTag, std::string const& name, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::apigateway::v1::DeleteGatewayRequest request;
  request.set_name(name);
  return connection_->DeleteGateway(NoAwaitTag{}, request);
}

future<StatusOr<google::cloud::apigateway::v1::OperationMetadata>>
ApiGatewayServiceClient::DeleteGateway(
    google::cloud::apigateway::v1::DeleteGatewayRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->DeleteGateway(request);
}

StatusOr<google::longrunning::Operation> ApiGatewayServiceClient::DeleteGateway(
    NoAwaitTag,
    google::cloud::apigateway::v1::DeleteGatewayRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->DeleteGateway(NoAwaitTag{}, request);
}

future<StatusOr<google::cloud::apigateway::v1::OperationMetadata>>
ApiGatewayServiceClient::DeleteGateway(
    google::longrunning::Operation const& operation, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->DeleteGateway(operation);
}

StreamRange<google::cloud::apigateway::v1::Api>
ApiGatewayServiceClient::ListApis(std::string const& parent, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::apigateway::v1::ListApisRequest request;
  request.set_parent(parent);
  return connection_->ListApis(request);
}

StreamRange<google::cloud::apigateway::v1::Api>
ApiGatewayServiceClient::ListApis(
    google::cloud::apigateway::v1::ListApisRequest request, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->ListApis(std::move(request));
}

StatusOr<google::cloud::apigateway::v1::Api> ApiGatewayServiceClient::GetApi(
    std::string const& name, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::apigateway::v1::GetApiRequest request;
  request.set_name(name);
  return connection_->GetApi(request);
}

StatusOr<google::cloud::apigateway::v1::Api> ApiGatewayServiceClient::GetApi(
    google::cloud::apigateway::v1::GetApiRequest const& request, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->GetApi(request);
}

future<StatusOr<google::cloud::apigateway::v1::Api>>
ApiGatewayServiceClient::CreateApi(
    std::string const& parent, google::cloud::apigateway::v1::Api const& api,
    std::string const& api_id, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::apigateway::v1::CreateApiRequest request;
  request.set_parent(parent);
  *request.mutable_api() = api;
  request.set_api_id(api_id);
  return connection_->CreateApi(request);
}

StatusOr<google::longrunning::Operation> ApiGatewayServiceClient::CreateApi(
    NoAwaitTag, std::string const& parent,
    google::cloud::apigateway::v1::Api const& api, std::string const& api_id,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::apigateway::v1::CreateApiRequest request;
  request.set_parent(parent);
  *request.mutable_api() = api;
  request.set_api_id(api_id);
  return connection_->CreateApi(NoAwaitTag{}, request);
}

future<StatusOr<google::cloud::apigateway::v1::Api>>
ApiGatewayServiceClient::CreateApi(
    google::cloud::apigateway::v1::CreateApiRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->CreateApi(request);
}

StatusOr<google::longrunning::Operation> ApiGatewayServiceClient::CreateApi(
    NoAwaitTag, google::cloud::apigateway::v1::CreateApiRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->CreateApi(NoAwaitTag{}, request);
}

future<StatusOr<google::cloud::apigateway::v1::Api>>
ApiGatewayServiceClient::CreateApi(
    google::longrunning::Operation const& operation, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->CreateApi(operation);
}

future<StatusOr<google::cloud::apigateway::v1::Api>>
ApiGatewayServiceClient::UpdateApi(
    google::cloud::apigateway::v1::Api const& api,
    google::protobuf::FieldMask const& update_mask, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::apigateway::v1::UpdateApiRequest request;
  *request.mutable_api() = api;
  *request.mutable_update_mask() = update_mask;
  return connection_->UpdateApi(request);
}

StatusOr<google::longrunning::Operation> ApiGatewayServiceClient::UpdateApi(
    NoAwaitTag, google::cloud::apigateway::v1::Api const& api,
    google::protobuf::FieldMask const& update_mask, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::apigateway::v1::UpdateApiRequest request;
  *request.mutable_api() = api;
  *request.mutable_update_mask() = update_mask;
  return connection_->UpdateApi(NoAwaitTag{}, request);
}

future<StatusOr<google::cloud::apigateway::v1::Api>>
ApiGatewayServiceClient::UpdateApi(
    google::cloud::apigateway::v1::UpdateApiRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->UpdateApi(request);
}

StatusOr<google::longrunning::Operation> ApiGatewayServiceClient::UpdateApi(
    NoAwaitTag, google::cloud::apigateway::v1::UpdateApiRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->UpdateApi(NoAwaitTag{}, request);
}

future<StatusOr<google::cloud::apigateway::v1::Api>>
ApiGatewayServiceClient::UpdateApi(
    google::longrunning::Operation const& operation, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->UpdateApi(operation);
}

future<StatusOr<google::cloud::apigateway::v1::OperationMetadata>>
ApiGatewayServiceClient::DeleteApi(std::string const& name, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::apigateway::v1::DeleteApiRequest request;
  request.set_name(name);
  return connection_->DeleteApi(request);
}

StatusOr<google::longrunning::Operation> ApiGatewayServiceClient::DeleteApi(
    NoAwaitTag, std::string const& name, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::apigateway::v1::DeleteApiRequest request;
  request.set_name(name);
  return connection_->DeleteApi(NoAwaitTag{}, request);
}

future<StatusOr<google::cloud::apigateway::v1::OperationMetadata>>
ApiGatewayServiceClient::DeleteApi(
    google::cloud::apigateway::v1::DeleteApiRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->DeleteApi(request);
}

StatusOr<google::longrunning::Operation> ApiGatewayServiceClient::DeleteApi(
    NoAwaitTag, google::cloud::apigateway::v1::DeleteApiRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->DeleteApi(NoAwaitTag{}, request);
}

future<StatusOr<google::cloud::apigateway::v1::OperationMetadata>>
ApiGatewayServiceClient::DeleteApi(
    google::longrunning::Operation const& operation, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->DeleteApi(operation);
}

StreamRange<google::cloud::apigateway::v1::ApiConfig>
ApiGatewayServiceClient::ListApiConfigs(std::string const& parent,
                                        Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::apigateway::v1::ListApiConfigsRequest request;
  request.set_parent(parent);
  return connection_->ListApiConfigs(request);
}

StreamRange<google::cloud::apigateway::v1::ApiConfig>
ApiGatewayServiceClient::ListApiConfigs(
    google::cloud::apigateway::v1::ListApiConfigsRequest request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->ListApiConfigs(std::move(request));
}

StatusOr<google::cloud::apigateway::v1::ApiConfig>
ApiGatewayServiceClient::GetApiConfig(std::string const& name, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::apigateway::v1::GetApiConfigRequest request;
  request.set_name(name);
  return connection_->GetApiConfig(request);
}

StatusOr<google::cloud::apigateway::v1::ApiConfig>
ApiGatewayServiceClient::GetApiConfig(
    google::cloud::apigateway::v1::GetApiConfigRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->GetApiConfig(request);
}

future<StatusOr<google::cloud::apigateway::v1::ApiConfig>>
ApiGatewayServiceClient::CreateApiConfig(
    std::string const& parent,
    google::cloud::apigateway::v1::ApiConfig const& api_config,
    std::string const& api_config_id, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::apigateway::v1::CreateApiConfigRequest request;
  request.set_parent(parent);
  *request.mutable_api_config() = api_config;
  request.set_api_config_id(api_config_id);
  return connection_->CreateApiConfig(request);
}

StatusOr<google::longrunning::Operation>
ApiGatewayServiceClient::CreateApiConfig(
    NoAwaitTag, std::string const& parent,
    google::cloud::apigateway::v1::ApiConfig const& api_config,
    std::string const& api_config_id, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::apigateway::v1::CreateApiConfigRequest request;
  request.set_parent(parent);
  *request.mutable_api_config() = api_config;
  request.set_api_config_id(api_config_id);
  return connection_->CreateApiConfig(NoAwaitTag{}, request);
}

future<StatusOr<google::cloud::apigateway::v1::ApiConfig>>
ApiGatewayServiceClient::CreateApiConfig(
    google::cloud::apigateway::v1::CreateApiConfigRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->CreateApiConfig(request);
}

StatusOr<google::longrunning::Operation>
ApiGatewayServiceClient::CreateApiConfig(
    NoAwaitTag,
    google::cloud::apigateway::v1::CreateApiConfigRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->CreateApiConfig(NoAwaitTag{}, request);
}

future<StatusOr<google::cloud::apigateway::v1::ApiConfig>>
ApiGatewayServiceClient::CreateApiConfig(
    google::longrunning::Operation const& operation, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->CreateApiConfig(operation);
}

future<StatusOr<google::cloud::apigateway::v1::ApiConfig>>
ApiGatewayServiceClient::UpdateApiConfig(
    google::cloud::apigateway::v1::ApiConfig const& api_config,
    google::protobuf::FieldMask const& update_mask, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::apigateway::v1::UpdateApiConfigRequest request;
  *request.mutable_api_config() = api_config;
  *request.mutable_update_mask() = update_mask;
  return connection_->UpdateApiConfig(request);
}

StatusOr<google::longrunning::Operation>
ApiGatewayServiceClient::UpdateApiConfig(
    NoAwaitTag, google::cloud::apigateway::v1::ApiConfig const& api_config,
    google::protobuf::FieldMask const& update_mask, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::apigateway::v1::UpdateApiConfigRequest request;
  *request.mutable_api_config() = api_config;
  *request.mutable_update_mask() = update_mask;
  return connection_->UpdateApiConfig(NoAwaitTag{}, request);
}

future<StatusOr<google::cloud::apigateway::v1::ApiConfig>>
ApiGatewayServiceClient::UpdateApiConfig(
    google::cloud::apigateway::v1::UpdateApiConfigRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->UpdateApiConfig(request);
}

StatusOr<google::longrunning::Operation>
ApiGatewayServiceClient::UpdateApiConfig(
    NoAwaitTag,
    google::cloud::apigateway::v1::UpdateApiConfigRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->UpdateApiConfig(NoAwaitTag{}, request);
}

future<StatusOr<google::cloud::apigateway::v1::ApiConfig>>
ApiGatewayServiceClient::UpdateApiConfig(
    google::longrunning::Operation const& operation, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->UpdateApiConfig(operation);
}

future<StatusOr<google::cloud::apigateway::v1::OperationMetadata>>
ApiGatewayServiceClient::DeleteApiConfig(std::string const& name,
                                         Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::apigateway::v1::DeleteApiConfigRequest request;
  request.set_name(name);
  return connection_->DeleteApiConfig(request);
}

StatusOr<google::longrunning::Operation>
ApiGatewayServiceClient::DeleteApiConfig(NoAwaitTag, std::string const& name,
                                         Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::apigateway::v1::DeleteApiConfigRequest request;
  request.set_name(name);
  return connection_->DeleteApiConfig(NoAwaitTag{}, request);
}

future<StatusOr<google::cloud::apigateway::v1::OperationMetadata>>
ApiGatewayServiceClient::DeleteApiConfig(
    google::cloud::apigateway::v1::DeleteApiConfigRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->DeleteApiConfig(request);
}

StatusOr<google::longrunning::Operation>
ApiGatewayServiceClient::DeleteApiConfig(
    NoAwaitTag,
    google::cloud::apigateway::v1::DeleteApiConfigRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->DeleteApiConfig(NoAwaitTag{}, request);
}

future<StatusOr<google::cloud::apigateway::v1::OperationMetadata>>
ApiGatewayServiceClient::DeleteApiConfig(
    google::longrunning::Operation const& operation, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->DeleteApiConfig(operation);
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace apigateway_v1
}  // namespace cloud
}  // namespace google

// Copyright 2025 Google LLC
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
// source: google/cloud/licensemanager/v1/licensemanager.proto

#include "google/cloud/licensemanager/v1/license_manager_client.h"
#include <memory>
#include <utility>

namespace google {
namespace cloud {
namespace licensemanager_v1 {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

LicenseManagerClient::LicenseManagerClient(
    std::shared_ptr<LicenseManagerConnection> connection, Options opts)
    : connection_(std::move(connection)),
      options_(
          internal::MergeOptions(std::move(opts), connection_->options())) {}
LicenseManagerClient::~LicenseManagerClient() = default;

StreamRange<google::cloud::licensemanager::v1::Configuration>
LicenseManagerClient::ListConfigurations(std::string const& parent,
                                         Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::licensemanager::v1::ListConfigurationsRequest request;
  request.set_parent(parent);
  return connection_->ListConfigurations(request);
}

StreamRange<google::cloud::licensemanager::v1::Configuration>
LicenseManagerClient::ListConfigurations(
    google::cloud::licensemanager::v1::ListConfigurationsRequest request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->ListConfigurations(std::move(request));
}

StatusOr<google::cloud::licensemanager::v1::Configuration>
LicenseManagerClient::GetConfiguration(std::string const& name, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::licensemanager::v1::GetConfigurationRequest request;
  request.set_name(name);
  return connection_->GetConfiguration(request);
}

StatusOr<google::cloud::licensemanager::v1::Configuration>
LicenseManagerClient::GetConfiguration(
    google::cloud::licensemanager::v1::GetConfigurationRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->GetConfiguration(request);
}

future<StatusOr<google::cloud::licensemanager::v1::Configuration>>
LicenseManagerClient::CreateConfiguration(
    std::string const& parent,
    google::cloud::licensemanager::v1::Configuration const& configuration,
    std::string const& configuration_id, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::licensemanager::v1::CreateConfigurationRequest request;
  request.set_parent(parent);
  *request.mutable_configuration() = configuration;
  request.set_configuration_id(configuration_id);
  return connection_->CreateConfiguration(request);
}

StatusOr<google::longrunning::Operation>
LicenseManagerClient::CreateConfiguration(
    NoAwaitTag, std::string const& parent,
    google::cloud::licensemanager::v1::Configuration const& configuration,
    std::string const& configuration_id, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::licensemanager::v1::CreateConfigurationRequest request;
  request.set_parent(parent);
  *request.mutable_configuration() = configuration;
  request.set_configuration_id(configuration_id);
  return connection_->CreateConfiguration(NoAwaitTag{}, request);
}

future<StatusOr<google::cloud::licensemanager::v1::Configuration>>
LicenseManagerClient::CreateConfiguration(
    google::cloud::licensemanager::v1::CreateConfigurationRequest const&
        request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->CreateConfiguration(request);
}

StatusOr<google::longrunning::Operation>
LicenseManagerClient::CreateConfiguration(
    NoAwaitTag,
    google::cloud::licensemanager::v1::CreateConfigurationRequest const&
        request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->CreateConfiguration(NoAwaitTag{}, request);
}

future<StatusOr<google::cloud::licensemanager::v1::Configuration>>
LicenseManagerClient::CreateConfiguration(
    google::longrunning::Operation const& operation, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->CreateConfiguration(operation);
}

future<StatusOr<google::cloud::licensemanager::v1::Configuration>>
LicenseManagerClient::UpdateConfiguration(
    google::cloud::licensemanager::v1::Configuration const& configuration,
    google::protobuf::FieldMask const& update_mask, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::licensemanager::v1::UpdateConfigurationRequest request;
  *request.mutable_configuration() = configuration;
  *request.mutable_update_mask() = update_mask;
  return connection_->UpdateConfiguration(request);
}

StatusOr<google::longrunning::Operation>
LicenseManagerClient::UpdateConfiguration(
    NoAwaitTag,
    google::cloud::licensemanager::v1::Configuration const& configuration,
    google::protobuf::FieldMask const& update_mask, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::licensemanager::v1::UpdateConfigurationRequest request;
  *request.mutable_configuration() = configuration;
  *request.mutable_update_mask() = update_mask;
  return connection_->UpdateConfiguration(NoAwaitTag{}, request);
}

future<StatusOr<google::cloud::licensemanager::v1::Configuration>>
LicenseManagerClient::UpdateConfiguration(
    google::cloud::licensemanager::v1::UpdateConfigurationRequest const&
        request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->UpdateConfiguration(request);
}

StatusOr<google::longrunning::Operation>
LicenseManagerClient::UpdateConfiguration(
    NoAwaitTag,
    google::cloud::licensemanager::v1::UpdateConfigurationRequest const&
        request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->UpdateConfiguration(NoAwaitTag{}, request);
}

future<StatusOr<google::cloud::licensemanager::v1::Configuration>>
LicenseManagerClient::UpdateConfiguration(
    google::longrunning::Operation const& operation, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->UpdateConfiguration(operation);
}

future<StatusOr<google::cloud::licensemanager::v1::OperationMetadata>>
LicenseManagerClient::DeleteConfiguration(std::string const& name,
                                          Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::licensemanager::v1::DeleteConfigurationRequest request;
  request.set_name(name);
  return connection_->DeleteConfiguration(request);
}

StatusOr<google::longrunning::Operation>
LicenseManagerClient::DeleteConfiguration(NoAwaitTag, std::string const& name,
                                          Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::licensemanager::v1::DeleteConfigurationRequest request;
  request.set_name(name);
  return connection_->DeleteConfiguration(NoAwaitTag{}, request);
}

future<StatusOr<google::cloud::licensemanager::v1::OperationMetadata>>
LicenseManagerClient::DeleteConfiguration(
    google::cloud::licensemanager::v1::DeleteConfigurationRequest const&
        request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->DeleteConfiguration(request);
}

StatusOr<google::longrunning::Operation>
LicenseManagerClient::DeleteConfiguration(
    NoAwaitTag,
    google::cloud::licensemanager::v1::DeleteConfigurationRequest const&
        request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->DeleteConfiguration(NoAwaitTag{}, request);
}

future<StatusOr<google::cloud::licensemanager::v1::OperationMetadata>>
LicenseManagerClient::DeleteConfiguration(
    google::longrunning::Operation const& operation, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->DeleteConfiguration(operation);
}

StreamRange<google::cloud::licensemanager::v1::Instance>
LicenseManagerClient::ListInstances(std::string const& parent, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::licensemanager::v1::ListInstancesRequest request;
  request.set_parent(parent);
  return connection_->ListInstances(request);
}

StreamRange<google::cloud::licensemanager::v1::Instance>
LicenseManagerClient::ListInstances(
    google::cloud::licensemanager::v1::ListInstancesRequest request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->ListInstances(std::move(request));
}

StatusOr<google::cloud::licensemanager::v1::Instance>
LicenseManagerClient::GetInstance(std::string const& name, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::licensemanager::v1::GetInstanceRequest request;
  request.set_name(name);
  return connection_->GetInstance(request);
}

StatusOr<google::cloud::licensemanager::v1::Instance>
LicenseManagerClient::GetInstance(
    google::cloud::licensemanager::v1::GetInstanceRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->GetInstance(request);
}

future<StatusOr<google::cloud::licensemanager::v1::Configuration>>
LicenseManagerClient::DeactivateConfiguration(std::string const& name,
                                              Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::licensemanager::v1::DeactivateConfigurationRequest request;
  request.set_name(name);
  return connection_->DeactivateConfiguration(request);
}

StatusOr<google::longrunning::Operation>
LicenseManagerClient::DeactivateConfiguration(NoAwaitTag,
                                              std::string const& name,
                                              Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::licensemanager::v1::DeactivateConfigurationRequest request;
  request.set_name(name);
  return connection_->DeactivateConfiguration(NoAwaitTag{}, request);
}

future<StatusOr<google::cloud::licensemanager::v1::Configuration>>
LicenseManagerClient::DeactivateConfiguration(
    google::cloud::licensemanager::v1::DeactivateConfigurationRequest const&
        request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->DeactivateConfiguration(request);
}

StatusOr<google::longrunning::Operation>
LicenseManagerClient::DeactivateConfiguration(
    NoAwaitTag,
    google::cloud::licensemanager::v1::DeactivateConfigurationRequest const&
        request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->DeactivateConfiguration(NoAwaitTag{}, request);
}

future<StatusOr<google::cloud::licensemanager::v1::Configuration>>
LicenseManagerClient::DeactivateConfiguration(
    google::longrunning::Operation const& operation, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->DeactivateConfiguration(operation);
}

future<StatusOr<google::cloud::licensemanager::v1::Configuration>>
LicenseManagerClient::ReactivateConfiguration(std::string const& name,
                                              Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::licensemanager::v1::ReactivateConfigurationRequest request;
  request.set_name(name);
  return connection_->ReactivateConfiguration(request);
}

StatusOr<google::longrunning::Operation>
LicenseManagerClient::ReactivateConfiguration(NoAwaitTag,
                                              std::string const& name,
                                              Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::licensemanager::v1::ReactivateConfigurationRequest request;
  request.set_name(name);
  return connection_->ReactivateConfiguration(NoAwaitTag{}, request);
}

future<StatusOr<google::cloud::licensemanager::v1::Configuration>>
LicenseManagerClient::ReactivateConfiguration(
    google::cloud::licensemanager::v1::ReactivateConfigurationRequest const&
        request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->ReactivateConfiguration(request);
}

StatusOr<google::longrunning::Operation>
LicenseManagerClient::ReactivateConfiguration(
    NoAwaitTag,
    google::cloud::licensemanager::v1::ReactivateConfigurationRequest const&
        request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->ReactivateConfiguration(NoAwaitTag{}, request);
}

future<StatusOr<google::cloud::licensemanager::v1::Configuration>>
LicenseManagerClient::ReactivateConfiguration(
    google::longrunning::Operation const& operation, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->ReactivateConfiguration(operation);
}

StatusOr<
    google::cloud::licensemanager::v1::QueryConfigurationLicenseUsageResponse>
LicenseManagerClient::QueryConfigurationLicenseUsage(
    std::string const& name, google::protobuf::Timestamp const& start_time,
    google::protobuf::Timestamp const& end_time, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::licensemanager::v1::QueryConfigurationLicenseUsageRequest
      request;
  request.set_name(name);
  *request.mutable_start_time() = start_time;
  *request.mutable_end_time() = end_time;
  return connection_->QueryConfigurationLicenseUsage(request);
}

StatusOr<
    google::cloud::licensemanager::v1::QueryConfigurationLicenseUsageResponse>
LicenseManagerClient::QueryConfigurationLicenseUsage(
    google::cloud::licensemanager::v1::
        QueryConfigurationLicenseUsageRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->QueryConfigurationLicenseUsage(request);
}

StreamRange<google::cloud::licensemanager::v1::Usage>
LicenseManagerClient::AggregateUsage(
    std::string const& name, google::protobuf::Timestamp const& start_time,
    google::protobuf::Timestamp const& end_time, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::licensemanager::v1::AggregateUsageRequest request;
  request.set_name(name);
  *request.mutable_start_time() = start_time;
  *request.mutable_end_time() = end_time;
  return connection_->AggregateUsage(request);
}

StreamRange<google::cloud::licensemanager::v1::Usage>
LicenseManagerClient::AggregateUsage(
    google::cloud::licensemanager::v1::AggregateUsageRequest request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->AggregateUsage(std::move(request));
}

StreamRange<google::cloud::licensemanager::v1::Product>
LicenseManagerClient::ListProducts(std::string const& parent, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::licensemanager::v1::ListProductsRequest request;
  request.set_parent(parent);
  return connection_->ListProducts(request);
}

StreamRange<google::cloud::licensemanager::v1::Product>
LicenseManagerClient::ListProducts(
    google::cloud::licensemanager::v1::ListProductsRequest request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->ListProducts(std::move(request));
}

StatusOr<google::cloud::licensemanager::v1::Product>
LicenseManagerClient::GetProduct(std::string const& name, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::cloud::licensemanager::v1::GetProductRequest request;
  request.set_name(name);
  return connection_->GetProduct(request);
}

StatusOr<google::cloud::licensemanager::v1::Product>
LicenseManagerClient::GetProduct(
    google::cloud::licensemanager::v1::GetProductRequest const& request,
    Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->GetProduct(request);
}

StreamRange<google::cloud::location::Location>
LicenseManagerClient::ListLocations(
    google::cloud::location::ListLocationsRequest request, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->ListLocations(std::move(request));
}

StatusOr<google::cloud::location::Location> LicenseManagerClient::GetLocation(
    google::cloud::location::GetLocationRequest const& request, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->GetLocation(request);
}

StreamRange<google::longrunning::Operation>
LicenseManagerClient::ListOperations(std::string const& name,
                                     std::string const& filter, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::longrunning::ListOperationsRequest request;
  request.set_name(name);
  request.set_filter(filter);
  return connection_->ListOperations(request);
}

StreamRange<google::longrunning::Operation>
LicenseManagerClient::ListOperations(
    google::longrunning::ListOperationsRequest request, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->ListOperations(std::move(request));
}

StatusOr<google::longrunning::Operation> LicenseManagerClient::GetOperation(
    std::string const& name, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::longrunning::GetOperationRequest request;
  request.set_name(name);
  return connection_->GetOperation(request);
}

StatusOr<google::longrunning::Operation> LicenseManagerClient::GetOperation(
    google::longrunning::GetOperationRequest const& request, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->GetOperation(request);
}

Status LicenseManagerClient::DeleteOperation(std::string const& name,
                                             Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::longrunning::DeleteOperationRequest request;
  request.set_name(name);
  return connection_->DeleteOperation(request);
}

Status LicenseManagerClient::DeleteOperation(
    google::longrunning::DeleteOperationRequest const& request, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->DeleteOperation(request);
}

Status LicenseManagerClient::CancelOperation(std::string const& name,
                                             Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  google::longrunning::CancelOperationRequest request;
  request.set_name(name);
  return connection_->CancelOperation(request);
}

Status LicenseManagerClient::CancelOperation(
    google::longrunning::CancelOperationRequest const& request, Options opts) {
  internal::OptionsSpan span(internal::MergeOptions(std::move(opts), options_));
  return connection_->CancelOperation(request);
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace licensemanager_v1
}  // namespace cloud
}  // namespace google

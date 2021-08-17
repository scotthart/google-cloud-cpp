// Copyright 2021 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "google/cloud/internal/rest_client.h"
#include "google/cloud/internal/absl_str_cat_quiet.h"
#include "google/cloud/internal/generic_request.h"
#include "absl/strings/match.h"

namespace google {
namespace cloud {
inline namespace GOOGLE_CLOUD_CPP_NS {
namespace internal {

using internal::CurlHandleFactory;

namespace {
std::shared_ptr<CurlHandleFactory> CreateHandleFactory(Options const& options) {
  auto const pool_size = options.get<ConnectionPoolSizeOption>();
  if (pool_size == 0) {
    return std::make_shared<DefaultCurlHandleFactory>(options);
  }
  return std::make_shared<PooledCurlHandleFactory>(pool_size, options);
}

template <typename Request>
void SetupBuilderUserIp(CurlRequestBuilder& builder, Request const& request) {
  if (request.template HasOption<UserIp>()) {
    std::string value = request.template GetOption<UserIp>().value();
    if (value.empty()) {
      value = builder.LastClientIpAddress();
    }
    if (!value.empty()) {
      builder.AddQueryParameter(UserIp::name(), value);
    }
  }
}

}  // namespace

std::string HostHeader(Options const& options, std::string const& service) {
  // If this function returns an empty string libcurl will fill out the `Host: `
  // header based on the URL. In most cases this is the correct value. The main
  // exception are applications using `VPC-SC`:
  //     https://cloud.google.com/vpc/docs/configure-private-google-access
  // In those cases the application would target an URL like
  // `https://restricted.googleapis.com`, or `https://private.googleapis.com`,
  // or their own proxy, and need to provide the target's service host.
  auto const& endpoint = options.get<RestEndpointOption>();
  if (absl::StrContains(endpoint, "googleapis.com")) {
    return absl::StrCat("Host: ", service, ".googleapis.com");
  }
  return {};
}

RestEndpoint::RestEndpoint(std::string endpoint, std::string service,
                           google::cloud::Options options)
    : options_(std::move(options)),
      endpoint_(std::move(endpoint)),
      service_(std::move(service)),
      xml_enabled_(options_.has<XmlPayloadOption>()),
      generator_(google::cloud::internal::MakeDefaultPRNG()),
      handle_factory_(CreateHandleFactory(options_)) {
  CurlInitializeOnce(options_);
}

template <typename Request>
StatusOr<RequestBuilder> RestEndpoint::CreateRequestBuilder(
    std::string http_method, std::string const& path, Request const& request) {
  CurlRequestBuilder builder(endpoint_ + path, handle_factory_);
  auto status = SetupBuilder(builder, request, http_method);
  if (!status.ok()) {
    return status;
  }
  return builder;
}

Status RestEndpoint::SetupBuilderCommon(CurlRequestBuilder& builder,
                                        std::string const& http_method) {
  auto auth_header =
      options_.get<Oauth2CredentialsOption>()->AuthorizationHeader();
  if (!auth_header.ok()) {
    return std::move(auth_header).status();
  }
  builder.SetMethod(http_method)
      .ApplyClientOptions(options_)
      .AddHeader(auth_header.value())
      .AddHeader(HostHeader(options_, service_))
      .AddHeader(x_goog_api_client());
  return Status();
}

template <typename Request>
Status RestEndpoint::SetupBuilder(CurlRequestBuilder& builder,
                                  Request const& request,
                                  std::string const& http_method) {
  auto status = SetupBuilderCommon(builder, http_method);
  if (!status.ok()) {
    return status;
  }
  request.AddOptionsToHttpRequest(builder);
  SetupBuilderUserIp(builder, request);
  return Status();
}

}  // namespace internal
}  // namespace GOOGLE_CLOUD_CPP_NS
}  // namespace cloud
}  // namespace google

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

#ifndef GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_INTERNAL_REST_CLIENT_H
#define GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_INTERNAL_REST_CLIENT_H

#include "google/cloud/internal/curl_handle_factory.h"
#include "google/cloud/internal/curl_request_builder.h"
#include "google/cloud/internal/rest_options.h"
#include "google/cloud/options.h"
#include <memory>
#include <string>

namespace google {
namespace cloud {
inline namespace GOOGLE_CLOUD_CPP_NS {
namespace internal {

class RestEndpoint : public std::enable_shared_from_this<RestEndpoint> {
 public:
  static std::shared_ptr<RestEndpoint> Create(std::string endpoint,
                                              std::string service,
                                              Options options) {
    // Cannot use std::make_shared because the constructor is private.
    return std::shared_ptr<RestEndpoint>(new RestEndpoint(
        std::move(endpoint), std::move(service), std::move(options)));
  }

  RestEndpoint(RestEndpoint const& rhs) = delete;
  RestEndpoint(RestEndpoint&& rhs) = delete;
  RestEndpoint& operator=(RestEndpoint const& rhs) = delete;
  RestEndpoint& operator=(RestEndpoint&& rhs) = delete;

  template <typename Request>
  StatusOr<RequestBuilder> CreateRequestBuilder(std::string http_method,
                                                std::string const& path,
                                                Request const& request);

 private:
  RestEndpoint(std::string endpoint, std::string service,
               google::cloud::Options options);

  /// Setup the configuration parameters that do not depend on the request.
  Status SetupBuilderCommon(CurlRequestBuilder& builder,
                            std::string const& http_method);

  /// Applies the common configuration parameters to @p builder.
  template <typename Request>
  Status SetupBuilder(CurlRequestBuilder& builder, Request const& request,
                      std::string const& method);

  google::cloud::Options options_;
  std::string const endpoint_;
  std::string const service_;
  bool const xml_enabled_;
  std::mutex mu_;
  google::cloud::internal::DefaultPRNG generator_;  // GUARDED_BY(mu_);
  std::shared_ptr<google::cloud::internal::CurlHandleFactory> handle_factory_;
};

}  // namespace internal
}  // namespace GOOGLE_CLOUD_CPP_NS
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_INTERNAL_REST_CLIENT_H

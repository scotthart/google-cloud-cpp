// Copyright 2022 Google LLC
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

#ifndef GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_REST_OPTIONS_H
#define GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_REST_OPTIONS_H

#include "google/cloud/common_options.h"
#include "google/cloud/options.h"
#include "google/cloud/tracing_options.h"
#include "google/cloud/version.h"
#include "absl/types/optional.h"
#include <chrono>
#include <string>

namespace google {
namespace cloud {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

/**
 * Timeout for the server to finish processing the request. This system param
 * only applies to REST APIs for which client-side timeout is not applicable.
 *
 * @ingroup rest-options
 */
struct ServerTimeoutOption {
  using Type = std::chrono::milliseconds;
};

/**
 * The `TracingOptions` to use when printing REST transport http messages.
 *
 * @ingroup options
 */
struct RestTracingOptionsOption {
  using Type = TracingOptions;
};

/**
 * Stores the client SSL certificate along with any other needed values to
 * access the certificate.
 *
 * The data in this class is used to set various options in libcurl:
 *  - ssl_client_cert_file: CURLOPT_SSLCERT
 *  - ssl_key_file: CURLOPT_SSLKEY
 *  - ssl_key_file_password: CURLOPT_KEYPASSWD
 *  - ssl_cert_type: CURLOPT_SSLCERTTYPE - defaults to PEM
 *
 *  Please see https://curl.se/libcurl/c/easy_setopt_options.html for more
 *  detailed information on the behavior of setting these options.
 */
class SslCertificate {
 public:
  enum class SslCertType { kPEM, kDER, kP12 };

  SslCertificate() = default;
  explicit SslCertificate(std::string ssl_client_cert_file);
  SslCertificate(std::string ssl_client_cert, std::string ssl_key_file,
                 std::string ssl_key_file_password);

  std::string ssl_client_cert_file() const;

  absl::optional<std::string> ssl_key_file() const;
  absl::optional<std::string> ssl_key_file_password() const;

  SslCertType ssl_cert_type() const;

  SslCertificate& set_cert_type(SslCertType ssl_cert_type);

  static std::string ToString(SslCertType type);

 private:
  struct SslKeyFile {
    std::string ssl_key_file;
    std::string ssl_key_file_password;
  };
  std::string ssl_client_cert_file_;
  absl::optional<SslKeyFile> ssl_key_file_ = absl::nullopt;
  SslCertType ssl_cert_type_ = SslCertType::kPEM;
};

/**
 * Used to override the default client SSL certificate.
 */
struct SslCertificateOption {
  using Type = SslCertificate;
};

/// The complete list of options accepted by `CurlRestClient`
using RestOptionList =
    ::google::cloud::OptionList<QuotaUserOption, RestTracingOptionsOption,
                                ServerTimeoutOption, SslCertificateOption,
                                UserIpOption>;

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_REST_OPTIONS_H

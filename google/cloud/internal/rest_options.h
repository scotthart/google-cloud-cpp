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

#ifndef GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_INTERNAL_REST_OPTIONS_H
#define GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_INTERNAL_REST_OPTIONS_H

#include "google/cloud/internal/oauth2/credentials.h"
//#include "google/cloud/storage/options.h"
#include "google/cloud/backoff_policy.h"
#include "google/cloud/common_options.h"
#include "google/cloud/credentials.h"
#include "google/cloud/options.h"
#include "google/cloud/status_or.h"
#include "google/cloud/version.h"
#include <chrono>
#include <memory>
#include <string>

namespace google {
namespace cloud {
inline namespace GOOGLE_CLOUD_CPP_NS {
class RestOptions;
namespace internal {
/**
 * Set the HTTP version used by the client.
 *
 * If this option is not provided, or is set to `default` then the library uses
 * [libcurl's default], typically HTTP/2 with SSL. Possible settings include:
 * - "1.0": use HTTP/1.0, this is not recommended as would require a new
 *   connection for each request.
 * - "1.1": use HTTP/1.1, this may be useful when the overhead of HTTP/2 is
 *   unacceptable. Note that this may require additional connections.
 * - "2TLS": use HTTP/2 with TLS
 * - "2.0": use HTTP/2 with our without TLS.
 *
 * [libcurl's default]: https://curl.se/libcurl/c/CURLOPT_HTTP_VERSION.html
 */
struct HttpVersionOption {
  using Type = std::string;
};

/// This is only intended for testing against staging or development versions
/// of the service. It is not for public use.
struct TargetApiVersionOption {
  using Type = std::string;
};

/// This is only intended for testing. It is not for public use.
struct CAPathOption {
  using Type = std::string;
};

/// Configure the REST endpoint for the GCS client library.
struct RestEndpointOption {
  using Type = std::string;
};

/// Configure the IAM endpoint for the GCS client library.
struct IamEndpointOption {
  using Type = std::string;
};

/// Configure oauth2::Credentials for the GCS client library.
struct Oauth2CredentialsOption {
  using Type = std::shared_ptr<oauth2::Credentials>;
};

/// Set the Google Cloud Platform project id.
struct ProjectIdOption {
  using Type = std::string;
};

struct XmlPayloadOption {
  using Type = bool;
};

/**
 * Set the maximum connection pool size.
 *
 * The C++ client library uses this value to limit the growth of the
 * connection pool. Once an operation (a RPC or a download) completes the
 * connection used for that operation is returned to the pool. If the pool is
 * full the connection is immediately released. If the pool has room the
 * connection is cached for the next RPC or download.
 *
 * @note The behavior of this pool may change in the future, depending on the
 * low-level implementation details of the library.
 *
 * @note The library does not create connections proactively, setting a high
 * value may result in very few connections if your application does not need
 * them.
 *
 * @warning The library may create more connections than this option configures,
 * for example if your application requests many simultaneous downloads.
 */
struct ConnectionPoolSizeOption {
  using Type = std::size_t;
};

/**
 * Control the formatted I/O download buffer.
 *
 * When using formatted I/O operations (typically `operator>>(std::istream&...)`
 * this option controls the size of the in-memory buffer kept to satisfy any I/O
 * requests.
 *
 * Applications seeking optional performance for downloads should avoid
 * formatted I/O, and prefer using `std::istream::read()`. This option has no
 * effect in that case.
 */
struct DownloadBufferSizeOption {
  using Type = std::size_t;
};

/**
 * Control the formatted I/O upload buffer.
 *
 * When using formatted I/O operations (typically `operator<<(std::istream&...)`
 * this option controls the size of the in-memory buffer kept before a chunk is
 * uploaded. Note that GCS only accepts chunks in multiples of 256KiB, so this
 * option is always rounded up to the next such multiple.
 *
 * Applications seeking optional performance for downloads should avoid
 * formatted I/O, and prefer using `std::istream::write()`. This option has no
 * effect in that case.
 */
struct UploadBufferSizeOption {
  using Type = std::size_t;
};

/**
 * Defines the threshold to switch from simple to resumable uploads for files.
 *
 * When uploading small files the faster approach is to use a simple upload. For
 * very large files this is not feasible, as the whole file may not fit in
 * memory (we are ignoring memory mapped files in this discussion). The library
 * automatically switches to resumable upload for files larger than this
 * threshold.
 */
struct MaximumSimpleUploadSizeOption {
  using Type = std::size_t;
};

/**
 * Disables automatic OpenSSL locking.
 *
 * With older versions of OpenSSL any locking must be provided by locking
 * callbacks in the application or intermediate libraries. The C++ client
 * library automatically provides the locking callbacks. If your application
 * already provides such callbacks, and you prefer to use them, set this option
 * to `false`.
 *
 * @note This option is only useful for applications linking against
 * OpenSSL 1.0.2.
 */
struct EnableCurlSslLockingOption {
  using Type = bool;
};

/**
 * Disables automatic OpenSSL sigpipe handler.
 *
 * With some versions of OpenSSL it might be necessary to setup a SIGPIPE
 * handler. If your application already provides such a handler, set this option
 * to `false` to disable the handler in the GCS C++ client library.
 */
struct EnableCurlSigpipeHandlerOption {
  using Type = bool;
};

/**
 * Control the maximum socket receive buffer.
 *
 * The default is to let the operating system pick a value. Applications that
 * perform multiple downloads in parallel may need to use smaller receive
 * buffers to avoid exhausting the OS resources dedicated to TCP buffers.
 */
struct MaximumCurlSocketRecvSizeOption {
  using Type = std::size_t;
};

/**
 * Control the maximum socket send buffer.
 *
 * The default is to let the operating system pick a value, this is almost
 * always a good choice.
 */
struct MaximumCurlSocketSendSizeOption {
  using Type = std::size_t;
};

/**
 * Sets the "stall" timeout.
 *
 * If the download "stalls", i.e., no bytes are received for a significant
 * period, it may be better to restart the download as this may indicate a
 * network glitch.
 */
struct DownloadStallTimeoutOption {
  using Type = std::chrono::seconds;
};

#if 0
/// Set the retry policy for a GCS client.
struct RetryPolicyOption {
  using Type = std::shared_ptr<RetryPolicy>;
};

/// Set the backoff policy for a GCS client.
struct BackoffPolicyOption {
  using Type = std::shared_ptr<BackoffPolicy>;
};

/// Set the idempotency policy for a GCS client.
struct IdempotencyPolicyOption {
  using Type = std::shared_ptr<IdempotencyPolicy>;
};
#endif

/// The complete list of options accepted by `storage::Client`.
using RestOptionList = ::google::cloud::OptionList<
    XmlPayloadOption, RestEndpointOption, IamEndpointOption,
    Oauth2CredentialsOption, ProjectIdOption, ProjectIdOption,
    ConnectionPoolSizeOption, DownloadBufferSizeOption, UploadBufferSizeOption,
    EnableCurlSslLockingOption, EnableCurlSigpipeHandlerOption,
    MaximumCurlSocketRecvSizeOption, MaximumCurlSocketSendSizeOption,
    DownloadStallTimeoutOption, CARootsFilePathOption, HttpVersionOption>;

std::string JsonEndpoint(Options const&);
std::string JsonUploadEndpoint(Options const&);
std::string XmlEndpoint(Options const&);
std::string IamEndpoint(Options const&);

Options MakeOptions(RestOptions);

RestOptions MakeBackwardsCompatibleRestOptions(Options);
#if 0
Options ApplyPolicy(Options opts, RetryPolicy const& p);
Options ApplyPolicy(Options opts, BackoffPolicy const& p);
Options ApplyPolicy(Options opts, IdempotencyPolicy const& p);
#endif
inline Options ApplyPolicies(Options opts) { return opts; }

template <typename P, typename... Policies>
Options ApplyPolicies(Options opts, P&& head, Policies&&... tail) {
  opts = ApplyPolicy(std::move(opts), std::forward<P>(head));
  return ApplyPolicies(std::move(opts), std::forward<Policies>(tail)...);
}

Options DefaultOptions(std::shared_ptr<oauth2::Credentials> credentials,
                       Options opts);
Options DefaultOptionsWithCredentials(Options opts);

/**
 * Describes the configuration for low-level connection features.
 *
 * Some applications may want to use a different SSL root of trust for their
 * connections, for example, containerized applications might store the
 * certificate authority certificates in a hard-coded location.
 *
 * This is a separate class, as it is used to configure both the normal
 * connections to GCS and the connections used to obtain OAuth2 access
 * tokens.
 */
class ChannelOptions {
 public:
  std::string ssl_root_path() const { return ssl_root_path_; }

  ChannelOptions& set_ssl_root_path(std::string ssl_root_path) {
    ssl_root_path_ = std::move(ssl_root_path);
    return *this;
  }

 private:
  std::string ssl_root_path_;
};

/**
 * Describes the configuration for a `storage::Client` object.
 *
 * By default, several environment variables are read to configure the client:
 *
 * - `CLOUD_STORAGE_EMULATOR_ENDPOINT`: if set, use this http endpoint to
 *   make all http requests instead of the production GCS service. Also,
 *   if set, the `CreateDefaultRestOptions()` function will use an
 *   `AnonymousCredentials` object instead of loading Application Default
 *   %Credentials.
 * - `CLOUD_STORAGE_ENABLE_CLOG`: if set, enable std::clog as a backend for
 *   `google::cloud::LogSink`.
 * - `CLOUD_STORAGE_ENABLE_TRACING`: if set, this is the list of components that
 *   will have logging enabled, the component this is:
 *   - `http`: trace all http request / responses.
 */
class RestOptions {
 public:
  explicit RestOptions(std::shared_ptr<oauth2::Credentials> credentials)
      : RestOptions(std::move(credentials), {}) {}
  RestOptions(std::shared_ptr<oauth2::Credentials> credentials,
              ChannelOptions channel_options);

  /**
   * Creates a `RestOptions` with Google Application Default %Credentials.
   *
   * If Application Default %Credentials could not be loaded, this returns a
   * `Status` with failure details.  If the `CLOUD_STORAGE_EMULATOR_ENDPOINT`
   * environment variable is set, this function instead uses an
   * `AnonymousCredentials` to configure the client.
   */
  static StatusOr<RestOptions> CreateDefaultRestOptions();
  static StatusOr<RestOptions> CreateDefaultRestOptions(
      ChannelOptions const& channel_options);

  std::shared_ptr<oauth2::Credentials> credentials() const {
    return opts_.get<Oauth2CredentialsOption>();
  }
  RestOptions& set_credentials(std::shared_ptr<oauth2::Credentials> c) {
    opts_.set<Oauth2CredentialsOption>(std::move(c));
    return *this;
  }

  std::string const& endpoint() const {
    return opts_.get<RestEndpointOption>();
  }
  RestOptions& set_endpoint(std::string endpoint) {
    opts_.set<RestEndpointOption>(std::move(endpoint));
    return *this;
  }

  std::string const& iam_endpoint() const {
    return opts_.get<IamEndpointOption>();
  }
  RestOptions& set_iam_endpoint(std::string endpoint) {
    opts_.set<IamEndpointOption>(std::move(endpoint));
    return *this;
  }

  std::string const& version() const {
    return opts_.get<internal::TargetApiVersionOption>();
  }
  RestOptions& set_version(std::string version) {
    opts_.set<internal::TargetApiVersionOption>(std::move(version));
    return *this;
  }

  bool enable_http_tracing() const;
  RestOptions& set_enable_http_tracing(bool enable);

  bool enable_raw_client_tracing() const;
  RestOptions& set_enable_raw_client_tracing(bool enable);

  std::string const& project_id() const { return opts_.get<ProjectIdOption>(); }
  RestOptions& set_project_id(std::string v) {
    opts_.set<ProjectIdOption>(std::move(v));
    return *this;
  }

  std::size_t connection_pool_size() const {
    return opts_.get<ConnectionPoolSizeOption>();
  }
  RestOptions& set_connection_pool_size(std::size_t size) {
    opts_.set<ConnectionPoolSizeOption>(size);
    return *this;
  }

  std::size_t download_buffer_size() const {
    return opts_.get<DownloadBufferSizeOption>();
  }
  RestOptions& SetDownloadBufferSize(std::size_t size);

  std::size_t upload_buffer_size() const {
    return opts_.get<UploadBufferSizeOption>();
  }
  RestOptions& SetUploadBufferSize(std::size_t size);

  std::string const& user_agent_prefix() const { return user_agent_prefix_; }
  RestOptions& add_user_agent_prefix(std::string prefix) {
    opts_.lookup<UserAgentProductsOption>().push_back(prefix);
    if (!user_agent_prefix_.empty()) {
      prefix += ' ';
      prefix += user_agent_prefix_;
    }
    user_agent_prefix_ = std::move(prefix);
    return *this;
  }
  /// @deprecated use `add_user_agent_prefix()` instead.
  RestOptions& add_user_agent_prefx(std::string const& v) {
    return add_user_agent_prefix(v);
  }

  std::size_t maximum_simple_upload_size() const {
    return opts_.get<MaximumSimpleUploadSizeOption>();
  }
  RestOptions& set_maximum_simple_upload_size(std::size_t v) {
    opts_.set<MaximumSimpleUploadSizeOption>(v);
    return *this;
  }

  /**
   * If true and using OpenSSL 1.0.2 the library configures the OpenSSL
   * callbacks for locking.
   */
  bool enable_ssl_locking_callbacks() const {
    return opts_.get<EnableCurlSslLockingOption>();
  }
  RestOptions& set_enable_ssl_locking_callbacks(bool v) {
    opts_.set<EnableCurlSslLockingOption>(v);
    return *this;
  }

  bool enable_sigpipe_handler() const {
    return opts_.get<EnableCurlSigpipeHandlerOption>();
  }
  RestOptions& set_enable_sigpipe_handler(bool v) {
    opts_.set<EnableCurlSigpipeHandlerOption>(v);
    return *this;
  }

  std::size_t maximum_socket_recv_size() const {
    return opts_.get<MaximumCurlSocketRecvSizeOption>();
  }
  RestOptions& set_maximum_socket_recv_size(std::size_t v) {
    opts_.set<MaximumCurlSocketRecvSizeOption>(v);
    return *this;
  }

  std::size_t maximum_socket_send_size() const {
    return opts_.get<MaximumCurlSocketSendSizeOption>();
  }
  RestOptions& set_maximum_socket_send_size(std::size_t v) {
    opts_.set<MaximumCurlSocketSendSizeOption>(v);
    return *this;
  }

  ChannelOptions& channel_options() { return channel_options_; }
  ChannelOptions const& channel_options() const { return channel_options_; }

  //@{
  /**
   * Control the maximum amount of time allowed for "stalls" during a download.
   *
   * A download that receives no data is considered "stalled". If the download
   * remains stalled for more than the time set in this option then the download
   * is aborted.
   *
   * The default value is 2 minutes. Can be disabled by setting the value to 0.
   */
  std::chrono::seconds download_stall_timeout() const {
    return opts_.get<DownloadStallTimeoutOption>();
  }
  RestOptions& set_download_stall_timeout(std::chrono::seconds v) {
    opts_.set<DownloadStallTimeoutOption>(std::move(v));
    return *this;
  }
  //@}

 private:
  friend Options MakeOptions(RestOptions);
  //  friend RestOptions internal::MakeBackwardsCompatibleRestOptions(Options);

  explicit RestOptions(Options o);

  Options opts_;

  // Used for backwards compatibility. The value here is merged with the values
  // in `opts_` by internal::MakeOptions(RestOptions const&);
  ChannelOptions channel_options_;

  // Only used for backwards compatibility, the value in `opts_.
  std::string user_agent_prefix_;
};

}  // namespace internal
}  // namespace GOOGLE_CLOUD_CPP_NS
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_INTERNAL_REST_OPTIONS_H

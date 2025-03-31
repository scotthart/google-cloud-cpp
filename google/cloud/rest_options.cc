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

#include "google/cloud/rest_options.h"
#include <cstring>
#include <string>

namespace google {
namespace cloud {

SslCertificate::SslCertificate(std::string ssl_client_cert_filename)
    : ssl_client_cert_filename_(std::move(ssl_client_cert_filename)) {}
SslCertificate::SslCertificate(std::string ssl_client_cert_filename,
                               std::string ssl_key_filename,
                               std::string ssl_key_file_password)
    : ssl_client_cert_filename_(std::move(ssl_client_cert_filename)),
      ssl_key_file_(SslKeyFile{std::move(ssl_key_filename),
                               std::move(ssl_key_file_password)}) {}

SslCertificate::SslCertificate(std::string ssl_cert_blob,
                               std::string ssl_key_blob) {
  ssl_blob_ = SslBlob{};
  ssl_blob_->ssl_cert_blob.reserve(ssl_cert_blob.size());
  std::memcpy(&(ssl_blob_->ssl_cert_blob[0]), ssl_cert_blob.data(),  // NOLINT
              ssl_cert_blob.size());

  ssl_blob_->ssl_key_blob.reserve(ssl_key_blob.size());
  std::memcpy(&(ssl_blob_->ssl_key_blob[0]), ssl_key_blob.data(),  // NOLINT
              ssl_key_blob.size());
}

std::string SslCertificate::ssl_client_cert_filename() const {
  return ssl_client_cert_filename_;
}

absl::optional<std::string> SslCertificate::ssl_key_filename() const {
  if (ssl_key_file_.has_value()) return ssl_key_file_->ssl_key_filename;
  return absl::nullopt;
}

absl::optional<std::string> SslCertificate::ssl_key_file_password() const {
  if (ssl_key_file_.has_value()) return ssl_key_file_->ssl_key_file_password;
  return absl::nullopt;
}

SslCertificate::SslCertType SslCertificate::ssl_cert_type() const {
  return ssl_cert_type_;
}

SslCertificate& SslCertificate::set_cert_type(SslCertType ssl_cert_type) {
  ssl_cert_type_ = ssl_cert_type;
  return *this;
}

std::string SslCertificate::ToString(SslCertType type) {
  switch (type) {
    case SslCertType::kPEM:
      return "PEM";
    case SslCertType::kDER:
      return "DER";
    case SslCertType::kP12:
      return "P12";
  }
  return "";
}

std::vector<char>& SslCertificate::ssl_cert_blob() {
  return ssl_blob_->ssl_cert_blob;
}

std::vector<char>& SslCertificate::ssl_key_blob() {
  return ssl_blob_->ssl_key_blob;
}

}  // namespace cloud
}  // namespace google

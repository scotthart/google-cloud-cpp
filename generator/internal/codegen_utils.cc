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

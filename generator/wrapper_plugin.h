// Copyright 2024 Google LLC
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

#ifndef GOOGLE_CLOUD_CPP_GENERATOR_WRAPPER_PLUGIN_H
#define GOOGLE_CLOUD_CPP_GENERATOR_WRAPPER_PLUGIN_H

#include <google/protobuf/compiler/code_generator.h>
#include <google/protobuf/descriptor.h>
#include <string>

namespace google {
namespace cloud {
namespace generator {

/**
 * C++ protobuf wrapper plugin entry point.
 *
 * Command line arguments can be passed from the protoc command line via:
 * '--cpp_wrapper_opt=key=value'. This can be specified multiple times to
 * pass various key,value pairs.
 *
 * @par Example:
 * @code
 * protoc \
 *   --proto_path=${MY_PROTO_PATH} \
 *   --plugin=protoc-gen-cpp_wrapper=${PLUGIN_BIN_PATH}/protoc-gen-cpp_wrapper \
 *   --cpp_wrapper_out=. \
 *   --cpp_wrapper_opt=copyright_year=2020
 * @endcode
 */
class WrapperPlugin : public google::protobuf::compiler::CodeGenerator {
 public:
  bool Generate(google::protobuf::FileDescriptor const* file,
                std::string const& parameter,
                google::protobuf::compiler::GeneratorContext* generator_context,
                std::string* error) const override;

  uint64_t GetSupportedFeatures() const override {
    return FEATURE_PROTO3_OPTIONAL;
  }
};

}  // namespace generator
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_GENERATOR_WRAPPER_PLUGIN_H

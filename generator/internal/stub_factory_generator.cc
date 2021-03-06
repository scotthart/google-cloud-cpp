// Copyright 2020 Google LLC
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

#include "generator/internal/stub_factory_generator.h"
#include "generator/internal/codegen_utils.h"
#include "generator/internal/printer.h"
#include <google/api/client.pb.h>
#include <google/protobuf/descriptor.h>

namespace google {
namespace cloud {
namespace generator_internal {

StubFactoryGenerator::StubFactoryGenerator(
    google::protobuf::ServiceDescriptor const* service_descriptor,
    VarsDictionary service_vars,
    std::map<std::string, VarsDictionary> service_method_vars,
    google::protobuf::compiler::GeneratorContext* context)
    : ServiceCodeGenerator("stub_factory_header_path", "stub_factory_cc_path",
                           service_descriptor, std::move(service_vars),
                           std::move(service_method_vars), context) {}

Status StubFactoryGenerator::GenerateHeader() {
  HeaderPrint(CopyrightLicenseFileHeader());
  HeaderPrint(  // clang-format off
    "// Generated by the Codegen C++ plugin.\n"
    "// If you make any local changes, they will be lost.\n"
    "// source: $proto_file_name$\n"
    "#ifndef $header_include_guard$\n"
    "#define $header_include_guard$\n"
    "\n");
  // clang-format on

  // includes
  HeaderLocalIncludes({vars("connection_header_path"), vars("stub_header_path"),
                       "google/cloud/version.h"});
  HeaderSystemIncludes({"memory"});
  HeaderPrint("\n");

  auto result = HeaderOpenNamespaces(NamespaceType::kInternal);
  if (!result.ok()) return result;

  HeaderPrint(  // clang-format off
    "std::shared_ptr<$stub_class_name$>\n"
    "CreateDefault$stub_class_name$($product_namespace$::$connection_options_name$ const& options);\n\n");
  // clang-format on

  HeaderCloseNamespaces();
  // close header guard
  HeaderPrint(  // clang-format off
    "#endif  // $header_include_guard$\n");
  // clang-format on
  return {};
}

Status StubFactoryGenerator::GenerateCc() {
  CcPrint(CopyrightLicenseFileHeader());
  CcPrint(  // clang-format off
    "// Generated by the Codegen C++ plugin.\n"
    "// If you make any local changes, they will be lost.\n"
    "// source: $proto_file_name$\n\n");
  // clang-format on

  // includes
  CcLocalIncludes({vars("stub_factory_header_path"),
                   vars("logging_header_path"), vars("metadata_header_path"),
                   vars("stub_header_path"), "google/cloud/log.h"});
  CcSystemIncludes({"memory"});
  CcPrint("\n");

  auto result = CcOpenNamespaces(NamespaceType::kInternal);
  if (!result.ok()) return result;

  // factory function implementation
  CcPrint(  // clang-format off
    "std::shared_ptr<$stub_class_name$>\n"
    "CreateDefault$stub_class_name$($product_namespace$::$connection_options_name$ const& options) {\n"
    "  auto channel =\n"
    "      grpc::CreateCustomChannel(options.endpoint(), options.credentials(),\n"
    "                                options.CreateChannelArguments());\n"
    "  auto service_grpc_stub =\n"
    "      $grpc_stub_fqn$::NewStub(channel);\n");
  if (HasLongrunningMethod()) {
    CcPrint(  // clang-format off
    "  auto longrunning_grpc_stub =\n"
    "      google::longrunning::Operations::NewStub(channel);\n"
    "\n");
            // clang-format on
  }
  CcPrint(  // clang-format off
    "  std::shared_ptr<$stub_class_name$> stub =\n"
    "      std::make_shared<Default$stub_class_name$>(\n"
    "          std::move(service_grpc_stub)");
            // clang-format on
  if (HasLongrunningMethod()) {
    CcPrint(  // clang-format off
    ", std::move(longrunning_grpc_stub));\n");
              // clang-format on
  } else {
    CcPrint(  // clang-format off
    ");\n");
    // clang-format on
  }
  CcPrint(  // clang-format off
    "\n"
    "  stub = std::make_shared<$metadata_class_name$>(std::move(stub));\n"
    "\n"
    "  if (options.tracing_enabled(\"rpc\")) {\n"
    "    GCP_LOG(INFO) << \"Enabled logging for gRPC calls\";\n"
    "    stub = std::make_shared<$logging_class_name$>(std::move(stub),\n"
    "                                                  options.tracing_options(),\n"
    "                                                  options.components());\n"
    "  }\n"
    "  return stub;\n"
    "}\n\n");
  // clang-format on

  CcCloseNamespaces();
  return {};
}

}  // namespace generator_internal
}  // namespace cloud
}  // namespace google

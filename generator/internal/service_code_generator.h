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

#ifndef GOOGLE_CLOUD_CPP_GENERATOR_INTERNAL_SERVICE_CODE_GENERATOR_H
#define GOOGLE_CLOUD_CPP_GENERATOR_INTERNAL_SERVICE_CODE_GENERATOR_H

#include "generator/generator_config.pb.h"
#include "generator/internal/codegen_utils.h"
#include "generator/internal/descriptor_utils.h"
#include "generator/internal/generator_interface.h"
#include "generator/internal/mixin_utils.h"
#include "generator/internal/printer.h"
#include "google/cloud/status.h"
#include <google/protobuf/descriptor.h>

namespace google {
namespace cloud {
namespace generator_internal {

class ServiceCodeGenerator : public GeneratorInterface {
 public:
  ServiceCodeGenerator(
      std::string const& header_path_key, std::string const& cc_path_key,
      google::protobuf::ServiceDescriptor const* service_descriptor,
      VarsDictionary service_vars,
      std::map<std::string, VarsDictionary> service_method_vars,
      google::protobuf::compiler::GeneratorContext* context,
      std::vector<MixinMethod> const& mixin_methods);

  ServiceCodeGenerator(
      std::string const& header_path_key,
      google::protobuf::ServiceDescriptor const* service_descriptor,
      VarsDictionary service_vars,
      std::map<std::string, VarsDictionary> service_method_vars,
      google::protobuf::compiler::GeneratorContext* context,
      std::vector<MixinMethod> const& mixin_methods);

  ~ServiceCodeGenerator() override = default;

  ServiceCodeGenerator(ServiceCodeGenerator const&) = delete;
  ServiceCodeGenerator& operator=(ServiceCodeGenerator const&) = delete;
  ServiceCodeGenerator(ServiceCodeGenerator&&) = default;
  ServiceCodeGenerator& operator=(ServiceCodeGenerator&&) = default;

  Status Generate() override;

 protected:
  using MethodDescriptorList = std::vector<
      std::reference_wrapper<google::protobuf::MethodDescriptor const>>;
  using ServiceConfiguration =
      google::cloud::cpp::generator::ServiceConfiguration;

  virtual Status GenerateHeader() = 0;
  virtual Status GenerateCc() = 0;

  VarsDictionary const& vars() const;
  std::string vars(std::string const& key) const;
  MethodDescriptorList const& methods() const { return methods_; }
  MethodDescriptorList const& async_methods() const { return async_methods_; }
  void SetVars(absl::string_view header_path);
  VarsDictionary MergeServiceAndMethodVars(
      google::protobuf::MethodDescriptor const& method) const;

  void HeaderLocalIncludes(std::vector<std::string> const& local_includes);
  void CcLocalIncludes(std::vector<std::string> const& local_includes);
  void HeaderSystemIncludes(std::vector<std::string> const& system_includes);
  void CcSystemIncludes(std::vector<std::string> const& system_includes);

  void HeaderProtobufGenCodeIncludes(
      std::vector<std::string> const& pb_h_includes);
  void CcProtobufGenCodeIncludes(std::vector<std::string> const& pb_h_includes);

  Status HeaderOpenNamespaces(NamespaceType ns_type = NamespaceType::kNormal);
  Status HeaderOpenForwardingNamespaces(
      NamespaceType ns_type = NamespaceType::kNormal,
      std::string const& ns_documentation = "");
  void HeaderCloseNamespaces();
  Status CcOpenNamespaces(NamespaceType ns_type = NamespaceType::kNormal);
  Status CcOpenForwardingNamespaces(
      NamespaceType ns_type = NamespaceType::kNormal);
  void CcCloseNamespaces();

  void HeaderPrint(std::string const& text);
  void HeaderPrint(std::vector<PredicatedFragment<void>> const& text);
  Status HeaderPrintMethod(google::protobuf::MethodDescriptor const& method,
                           std::vector<MethodPattern> const& patterns,
                           char const* file, int line);
  void HeaderPrintMethod(google::protobuf::MethodDescriptor const& method,
                         char const* file, int line, std::string const& text);

  void CcPrint(std::string const& text);
  void CcPrint(std::vector<PredicatedFragment<void>> const& text);
  Status CcPrintMethod(google::protobuf::MethodDescriptor const& method,
                       std::vector<MethodPattern> const& patterns,
                       char const* file, int line);
  void CcPrintMethod(google::protobuf::MethodDescriptor const& method,
                     char const* file, int line, std::string const& text);

  /**
   * How the endpoint for the service might depend upon its location.
   */
  ServiceConfiguration::EndpointLocationStyle EndpointLocationStyle() const;

  /**
   * Whether a service is experimental. If true, we add the `ExperimentalTag` to
   * certain APIs.
   */
  bool IsExperimental() const;

  /**
   * Determines if the service contains at least one method that requires
   * LRO handling. This could be AIP-151 compatible or something custom.
   */
  bool HasLongrunningMethod() const;

  /**
   * Determines if the service contains at least one method that returns a
   * google::longrunning::Operation.
   */
  bool HasGRPCLongrunningOperation() const;

  /**
   * Determines if any async methods are generated for the service.
   */
  bool HasAsyncMethod() const;

  /**
   * Determines if the service contains at least one method that is paginated
   * per https://google.aip.dev/client-libraries/4233.
   */
  bool HasPaginatedMethod() const;

  /**
   * Determines if the service contains at least one rpc whose request or
   * response contains a field of the proto map type.
   */
  bool HasMessageWithMapField() const;

  /**
   * Determines if the service contains at least once rpc with a stream
   * response.
   */
  bool HasStreamingReadMethod() const;

  /**
   * Determines if we need to generate at least one asynchronous streaming read
   * RPC.
   */
  bool HasAsynchronousStreamingReadMethod() const;

  /**
   * Determines if we need to generate at least one asynchronous streaming write
   * RPC.
   */
  bool HasAsynchronousStreamingWriteMethod() const;

  /**
   * Determines if the service contains at least once rpc with a stream
   * request.
   */
  bool HasStreamingWriteMethod() const;

  /**
   * Determines if the service contains at least one bidir streaming RPC
   */
  bool HasBidirStreamingMethod() const;

  /**
   * Determines if the service contains at least one RPC with a
   * google.api.routing annotation.
   */
  bool HasExplicitRoutingMethod() const;

  /**
   * Determines if REST transport is enabled for the service.
   */
  bool HasGenerateRestTransport() const;

  /**
   * Determines if gRPC transport is enabled for the service.
   */
  bool HasGenerateGrpcTransport() const;

  /// Determine if any of the methods has an autopopulated `request_id`-like
  /// field.
  bool HasRequestId() const;

  /// Determine if @p method has an auto-populated `request_id`-like field.
  bool HasRequestId(google::protobuf::MethodDescriptor const& method) const;

  /// Determine if the `google.api.api_version` option is specified.
  bool HasApiVersion() const;

  /**
   * Determines if any of the method signatures has any Protocol Buffer
   * Well-Known Types per
   * https://developers.google.com/protocol-buffers/docs/reference/google.protobuf
   * and provides the necessary include path.
   */
  std::vector<std::string> MethodSignatureWellKnownProtobufTypeIncludes() const;

  /**
   * Determines if any emitted method signature uses a deprecated field.
   */
  bool MethodSignatureUsesDeprecatedField() const;

  /**
   * Method signatures are omitted if they contain deprecated fields, or if the
   * overload set conflicts with a previous method signature.
   */
  bool OmitMethodSignature(google::protobuf::MethodDescriptor const& method,
                           int method_signature_number) const;

  /**
   * If gRPC transport is enabled return the appropriate grpc.pb.h file.
   * Otherwise, return the appropriate pb.h file.
   */
  std::string GetPbIncludeByTransport() const;

  /**
   * If gRPC transport is enabled return the appropriate mixin grpc.pb.h files.
   * Otherwise, return the appropriate mixin pb.h files.
   */
  std::vector<std::string> GetMixinPbIncludeByTransport() const;

  /**
   * If the service defining protos are produced from a REST Discovery Document.
   */
  bool IsDiscoveryDocumentProto() const;

  std::vector<MixinMethod> const& MixinMethods() const;

  /**
   * If the service is defined with `option deprecated = true;`.
   */
  bool IsDeprecated() const;

 private:
  void SetMethods();

  enum class FileType { kHeaderFile, kCcFile };
  static void GenerateLocalIncludes(Printer& p,
                                    std::vector<std::string> local_includes,
                                    FileType file_type);
  static void GenerateSystemIncludes(Printer& p,
                                     std::vector<std::string> system_includes);

  Status OpenNamespaces(Printer& p, NamespaceType ns_type,
                        std::string const& product_path_var,
                        std::string const& ns_documentation = "");
  void CloseNamespaces(Printer& p,
                       bool define_backwards_compatibility_namespace_alias);

  google::protobuf::ServiceDescriptor const* service_descriptor_;
  VarsDictionary service_vars_;
  std::map<std::string, VarsDictionary> service_method_vars_;
  std::string namespace_;
  bool define_backwards_compatibility_namespace_alias_ = false;
  bool pb_h_system_includes_ = true;
  MethodDescriptorList methods_;
  MethodDescriptorList async_methods_;
  Printer header_;
  Printer cc_;
  std::vector<MixinMethod> mixin_methods_;
};

}  // namespace generator_internal
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_GENERATOR_INTERNAL_SERVICE_CODE_GENERATOR_H

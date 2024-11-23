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

#include "generator/internal/wrapper_generator.h"
#include "generator/internal/codegen_utils.h"
#include "generator/internal/longrunning.h"
#include "generator/internal/pagination.h"
#include "generator/internal/printer.h"
#include "generator/internal/request_id.h"
#include "google/cloud/internal/absl_str_cat_quiet.h"
#include "google/cloud/internal/absl_str_join_quiet.h"
#include "google/cloud/internal/absl_str_replace_quiet.h"
#include "google/cloud/internal/algorithm.h"
#include "google/cloud/internal/make_status.h"
#include "google/cloud/log.h"
#include "absl/strings/str_split.h"
#include "absl/strings/strip.h"
#include <google/api/annotations.pb.h>
#include <google/api/client.pb.h>
#include <google/api/field_behavior.pb.h>
#include <google/api/routing.pb.h>
#include <google/protobuf/descriptor.h>
#include <algorithm>
#include <unordered_map>

namespace google {
namespace cloud {
namespace generator_internal {
namespace {

#if 0
absl::optional<std::string> IncludePathForWellKnownProtobufType(
    google::protobuf::FieldDescriptor const& parameter) {
  // This hash is not intended to be comprehensive. Problematic types and their
  // includes should be added as needed.
  static auto const* const kTypeIncludeMap =
      new std::unordered_map<std::string, std::string>(
          {{"google.protobuf.Duration", "google/protobuf/duration.pb.h"}});
  if (parameter.type() == google::protobuf::FieldDescriptor::TYPE_MESSAGE) {
    auto iter = kTypeIncludeMap->find(parameter.message_type()->full_name());
    if (iter != kTypeIncludeMap->end()) {
      return iter->second;
    }
  }
  return {};
}
#endif
}  // namespace

WrapperGenerator::WrapperGenerator(
    google::protobuf::FileDescriptor const* file,
    google::protobuf::compiler::GeneratorContext* context,
    google::cloud::generator_internal::VarsDictionary file_vars,
    std::map<std::string, VarsDictionary> message_vars)
    : file_(file),
      context_(context),
      header_(context, file_vars["header_file_path"]),
      cc_(context, file_vars["cc_file_path"]),
      file_vars_(std::move(file_vars)),
      message_vars_(std::move(message_vars)) {}

void WrapperGenerator::HeaderPrint(std::string const& text) {
  header_.Print(file_vars_, text);
}

void WrapperGenerator::HeaderPrint(VarsDictionary const& vars,
                                   std::string const& text) {
  VarsDictionary merged{file_vars_};
  merged.insert(vars.begin(), vars.end());
  header_.Print(merged, text);
}

void WrapperGenerator::CcPrint(std::string const& text) {
  cc_.Print(file_vars_, text);
}

void WrapperGenerator::CcPrint(VarsDictionary const& vars,
                               std::string const& text) {
  VarsDictionary merged{file_vars_};
  merged.insert(vars.begin(), vars.end());
  cc_.Print(merged, text);
}

Status WrapperGenerator::Generate() {
  auto result = GenerateHeader();
  //  return {};
  if (!result.ok()) return result;
  return GenerateCc();
}

std::string WrapperFilePath(google::protobuf::FileDescriptor const& file,
                            absl::string_view product_path) {
  std::vector<std::string> parts =
      absl::StrSplit(absl::StripSuffix(file.name(), ".proto"), "/");
  return absl::StrCat(product_path, parts.back());
}

void WrapperGenerator::HeaderLocalIncludes(
    std::vector<std::string> const& local_includes) {
  GenerateLocalIncludes(header_, local_includes);
}

void WrapperGenerator::CcLocalIncludes(
    std::vector<std::string> const& local_includes) {
  GenerateLocalIncludes(cc_, local_includes, FileType::kCcFile);
}

void WrapperGenerator::HeaderSystemIncludes(
    std::vector<std::string> const& system_includes) {
  GenerateSystemIncludes(header_, system_includes);
}

void WrapperGenerator::CcSystemIncludes(
    std::vector<std::string> const& system_includes) {
  GenerateSystemIncludes(cc_, system_includes);
}

Status WrapperGenerator::HeaderOpenNamespaces(NamespaceType ns_type) {
  auto namespace_value =
      OpenNamespaces(header_, ns_type, "product_path", file_vars_);
  if (!namespace_value.ok()) return std::move(namespace_value).status();
  namespace_ = *namespace_value;
  return {};
}

void WrapperGenerator::HeaderCloseNamespaces() {
  CloseNamespaces(header_, false, namespace_);
}

Status WrapperGenerator::CcOpenNamespaces(NamespaceType ns_type) {
  auto namespace_value =
      OpenNamespaces(cc_, ns_type, "product_path", file_vars_);
  if (!namespace_value.ok()) return std::move(namespace_value).status();
  namespace_ = *namespace_value;
  return {};
}

void WrapperGenerator::CcCloseNamespaces() {
  CloseNamespaces(cc_, false, namespace_);
}

bool WrapperGenerator::HasRepeatedField() const {
  if (has_repeated_field_.has_value()) return *has_repeated_field_;
  has_repeated_field_ = false;
  for (int i = 0; i < file_->message_type_count(); ++i) {
    auto message = file_->message_type(i);
    for (int j = 0; j < message->field_count(); ++j) {
      if (message->field(j)->is_repeated() && !message->field(j)->is_map()) {
        has_repeated_field_ = true;
        return *has_repeated_field_;
      }
    }
  }
  return *has_repeated_field_;
}

StatusOr<std::map<std::string, VarsDictionary>> CreateMessageVars(
    google::protobuf::FileDescriptor const& file,
    VarsDictionary const& file_vars) {
  std::map<std::string, VarsDictionary> message_vars;

  for (auto i = 0; i < file.message_type_count(); ++i) {
    auto const* message = file.message_type(i);
    VarsDictionary vars;

    vars["class_name"] = ProtoNameToCppName(message->name());
    vars["message_full_name"] = ProtoNameToCppName(message->full_name());

    message_vars[message->name()] = std::move(vars);
  }

  return message_vars;
}

StatusOr<VarsDictionary> CreateFileVars(
    google::protobuf::FileDescriptor const& file,
    std::vector<std::pair<std::string, std::string>> const& initial_values) {
  VarsDictionary vars(initial_values.begin(), initial_values.end());
  if (vars.count("product_path") < 1) {
    return internal::FailedPreconditionError("product_path not specified",
                                             GCP_ERROR_INFO());
  }

  vars["cc_file_path"] =
      absl::StrCat(WrapperFilePath(file, vars["product_path"]), ".cc");
  vars["header_file_path"] =
      absl::StrCat(WrapperFilePath(file, vars["product_path"]), ".h");
  vars["header_include_guard"] =
      FormatHeaderIncludeGuard(vars["header_file_path"]);
  vars["product_namespace"] = Namespace(vars["product_path"]);
  vars["product_internal_namespace"] =
      Namespace(vars["product_path"], NamespaceType::kInternal);
  vars["proto_file_name"] = file.name();
  vars["proto_header_path"] =
      absl::StrCat(absl::StripSuffix(file.name(), ".proto"), ".pb.h");

  return vars;
}

std::string FieldCppType(google::protobuf::FieldDescriptor const& field) {
  static auto* const kSupportedWellKnownValueTypes = [] {
    auto types_map =
        std::make_unique<std::unordered_map<std::string, std::string>>();
    types_map->emplace("google::protobuf::BoolValue", "bool");
    types_map->emplace("google::protobuf::DoubleValue", "double");
    types_map->emplace("google::protobuf::FloatValue", "float");
    types_map->emplace("google::protobuf::Int32Value", "std::int32_t");
    types_map->emplace("google::protobuf::Int64Value", "std::int64_t");
    types_map->emplace("google::protobuf::StringValue", "std::string");
    types_map->emplace("google::protobuf::UInt32Value", "std::uint32_t");
    types_map->emplace("google::protobuf::UInt64Value", "std::uint64_t");
    return types_map.release();
  }();

  auto return_type = CppTypeToString(field);
  auto iter = kSupportedWellKnownValueTypes->find(return_type);
  if (iter != kSupportedWellKnownValueTypes->end()) {
    return_type = iter->second;
  }

  return return_type;
}

bool IsPod(google::protobuf::FieldDescriptor const& field) {
  static auto* const kSupportedWellKnownValueTypes = [] {
    auto types_set = std::make_unique<std::unordered_set<std::string>>();
    types_set->insert("google.protobuf.BoolValue");
    types_set->insert("google.protobuf.DoubleValue");
    types_set->insert("google.protobuf.FloatValue");
    types_set->insert("google.protobuf.Int32Value");
    types_set->insert("google.protobuf.Int64Value");
    types_set->insert("google.protobuf.StringValue");
    types_set->insert("google.protobuf.UInt32Value");
    types_set->insert("google.protobuf.UInt64Value");
    return types_set.release();
  }();

  bool is_pod =
      field.cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_MESSAGE &&
      field.cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_STRING;
  if (field.cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_MESSAGE) {
    std::cerr << __func__
              << ": field_type=" << field.message_type()->full_name() << "\n";
  }
  if (field.cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_MESSAGE &&
      internal::Contains(*kSupportedWellKnownValueTypes,
                         field.message_type()->full_name())) {
    is_pod = true;
  }

  return is_pod;
}

StatusOr<std::string> FormatAccessors(
    google::protobuf::FieldDescriptor const& field,
    absl::string_view field_cpp_name) {
  std::vector<std::string> accessor_text;
  auto field_cpp_type = FieldCppType(field);
  bool const is_pod = IsPod(field);

  if (field.is_map()) {
  } else if (field.is_repeated()) {
    accessor_text.push_back(
        absl::StrFormat("  %s const& %s(std::size_t index) const;",
                        field_cpp_type, field_cpp_name));
    std::string repeated_cpp_type;
    if (is_pod) {
      repeated_cpp_type =
          absl::StrCat("google::cloud::RepeatedField<", field_cpp_type, ">");
    } else {
      repeated_cpp_type =
          absl::StrCat("google::cloud::RepeatedPtrField<", field_cpp_type, ">");
    }
    accessor_text.push_back(absl::StrFormat("  %s const& %s() const ABSL_ATTRIBUTE_LIFETIME_BOUND;",
                                            repeated_cpp_type, field_cpp_name));
  } else {
    accessor_text.push_back(
        absl::StrFormat("  %s %s() const;", field_cpp_type, field_cpp_name));
  }

  return absl::StrJoin(accessor_text, "\n");
}

StatusOr<std::string> FormatMutators(
    google::protobuf::FieldDescriptor const& field,
    absl::string_view field_cpp_name) {
  std::vector<std::string> mutator_text;
  auto field_cpp_type = FieldCppType(field);
  bool const is_pod = IsPod(field);

  if (field.is_map()) {
  } else if (field.is_repeated()) {
    mutator_text.push_back(
        absl::StrFormat("  %s& Append%s();", field_cpp_type,
                        CapitalizeFirstLetter(field.camelcase_name())));
    mutator_text.push_back(
        absl::StrFormat("  $class_name$& Append%s(%s const& %s);",
                        CapitalizeFirstLetter(field.camelcase_name()),
                        field_cpp_type, field_cpp_name));
    mutator_text.push_back(
        absl::StrFormat("  $class_name$& Append%s(%s && %s);",
                        CapitalizeFirstLetter(field.camelcase_name()),
                        field_cpp_type, field_cpp_name));
    std::string repeated_cpp_type;
    if (is_pod) {
      repeated_cpp_type =
          absl::StrCat("google::protobuf::RepeatedField<", field_cpp_type, ">");
    } else {
      repeated_cpp_type = absl::StrCat("google::protobuf::RepeatedPtrField<",
                                       field_cpp_type, ">");
    }
    mutator_text.push_back(absl::StrFormat("  %s& mutable_%s();",
                                           repeated_cpp_type, field_cpp_name));
  } else {
    if (is_pod) {
      mutator_text.push_back(absl::StrFormat("  $class_name$& set_%s(%s %s);",
                                             field_cpp_name, field_cpp_type,
                                             field_cpp_name));
    } else {
      mutator_text.push_back(
          absl::StrFormat("  $class_name$& set_%s(%s const& %s);",
                          field_cpp_name, field_cpp_type, field_cpp_name));
      mutator_text.push_back(
          absl::StrFormat("  $class_name$& set_%s(%s && %s);", field_cpp_name,
                          field_cpp_type, field_cpp_name));
    }
  }

  return absl::StrJoin(mutator_text, "\n");
}

StatusOr<std::string> HeaderWrapField(
    google::protobuf::FieldDescriptor const& field) {
  std::vector<std::string> message_text;
  auto field_cpp_name = ProtoNameToCppName(field.name());
  message_text.push_back(absl::StrCat("\n  // ", field_cpp_name));
  auto accessors = FormatAccessors(field, field_cpp_name);
  if (!accessors) return std::move(accessors).status();
  message_text.push_back(*accessors);

  auto field_behavior =
      field.options().GetRepeatedExtension(google::api::field_behavior);
  if (!internal::Contains(field_behavior,
                          google::api::FieldBehavior::OUTPUT_ONLY)) {
    auto mutators = FormatMutators(field, field_cpp_name);
    if (!mutators) return std::move(mutators).status();
    message_text.push_back(*mutators);
  }

  return absl::StrJoin(message_text, "\n");
}

StatusOr<std::pair<VarsDictionary, std::string>> HeaderWrapMessage(
    google::protobuf::Descriptor const& message) {
  std::vector<std::string> text;
  VarsDictionary vars;
  //  vars["class_name"] = ProtoNameToCppName(message.name());
  //  vars["message_full_name"] = ProtoNameToCppName(message.full_name());

  text.push_back(R"""(
class $class_name$ {
 public:
  $class_name$() = default;
  // converting constructors
  $class_name$($message_full_name$ const& message);
  $class_name$($message_full_name$ && message);
  // conversion operators
  operator $message_full_name$() const&;
  operator $message_full_name$() &&;)""");

  for (int i = 0; i < message.field_count(); ++i) {
    auto const* field = message.field(i);
    auto field_text = HeaderWrapField(*field);
    if (!field_text) return std::move(field_text).status();
    text.push_back(std::move(*field_text));
  }

  text.push_back(R"""(
 private:
  $message_full_name$ message_;
};)""");

  return {{vars, absl::StrJoin(text, "\n")}};
}

Status WrapperGenerator::GenerateHeader() {
  HeaderPrint(CopyrightLicenseFileHeader());
  HeaderPrint(R"""(
// Generated by the Codegen C++ plugin.
// If you make any local changes, they will be lost.
// source: $proto_file_name$

#ifndef $header_include_guard$
#define $header_include_guard$

)""");

  HeaderLocalIncludes(
      {"google/cloud/version.h",
       HasRepeatedField() ? "google/cloud/repeated_field.h" : ""});
  HeaderSystemIncludes({file_vars_["proto_header_path"]});

  auto result = HeaderOpenNamespaces(NamespaceType::kNormal);
  if (!result.ok()) return result;

  for (int i = 0; i < file_->message_type_count(); ++i) {
    auto const* message = file_->message_type(i);
    auto text = HeaderWrapMessage(*message);
    //    auto message = file->message_type(i);
    //    p.Print(message->full_name());
    HeaderPrint(message_vars_[message->name()], text->second);
    HeaderPrint("\n");
  }

  HeaderCloseNamespaces();
  HeaderPrint(R"""(
#endif  // $header_include_guard$
)""");

  return {};
}

Status WrapperGenerator::GenerateCc() {
  CcPrint(CopyrightLicenseFileHeader());
  CcPrint(R"""(
// Generated by the Codegen C++ plugin.
// If you make any local changes, they will be lost.
// source: $proto_file_name$

)""");

  CcLocalIncludes({file_vars_["header_file_path"], "google/cloud/version.h"});
  CcSystemIncludes({});

  auto result = CcOpenNamespaces(NamespaceType::kNormal);
  if (!result.ok()) return result;

  CcCloseNamespaces();

  return {};
}

StatusOr<WrapperGenerator> MakeWrapperGenerator(
    google::protobuf::FileDescriptor const* file,
    google::protobuf::compiler::GeneratorContext* context,
    std::vector<std::pair<std::string, std::string>> const& initial_values) {
  auto file_vars = CreateFileVars(*file, initial_values);
  if (!file_vars.ok()) return std::move(file_vars).status();

  auto message_vars = CreateMessageVars(*file, *file_vars);
  if (!message_vars.ok()) return std::move(message_vars).status();

  return WrapperGenerator{file, context, *std::move(file_vars),
                          *std::move(message_vars)};
}

#if 0
ServiceCodeGenerator::ServiceCodeGenerator(
    std::string const& header_path_key, std::string const& cc_path_key,
    google::protobuf::ServiceDescriptor const* service_descriptor,
    VarsDictionary service_vars,
    std::map<std::string, VarsDictionary> service_method_vars,
    google::protobuf::compiler::GeneratorContext* context,
    std::vector<MixinMethod> const& mixin_methods)
    : service_descriptor_(service_descriptor),
      service_vars_(std::move(service_vars)),
      service_method_vars_(std::move(service_method_vars)),
      header_(context, service_vars_[header_path_key]),
      cc_(context, service_vars_[cc_path_key]),
      mixin_methods_(mixin_methods) {
  assert(service_descriptor != nullptr);
  assert(context != nullptr);
  SetVars(service_vars_[header_path_key]);
  SetMethods();
  auto e = service_vars_.find("backwards_compatibility_namespace_alias");
  define_backwards_compatibility_namespace_alias_ =
      (e != service_vars_.end() && e->second == "true");
}

ServiceCodeGenerator::ServiceCodeGenerator(
    std::string const& header_path_key,
    google::protobuf::ServiceDescriptor const* service_descriptor,
    VarsDictionary service_vars,
    std::map<std::string, VarsDictionary> service_method_vars,
    google::protobuf::compiler::GeneratorContext* context,
    std::vector<MixinMethod> const& mixin_methods)
    : service_descriptor_(service_descriptor),
      service_vars_(std::move(service_vars)),
      service_method_vars_(std::move(service_method_vars)),
      header_(context, service_vars_[header_path_key]),
      mixin_methods_(mixin_methods) {
  assert(service_descriptor != nullptr);
  assert(context != nullptr);
  SetVars(service_vars_[header_path_key]);
  SetMethods();
}

ServiceCodeGenerator::ServiceConfiguration::EndpointLocationStyle
ServiceCodeGenerator::EndpointLocationStyle() const {
  auto endpoint_location_style = ServiceConfiguration::LOCATION_INDEPENDENT;
  ServiceConfiguration::EndpointLocationStyle_Parse(
      vars("endpoint_location_style"), &endpoint_location_style);
  return endpoint_location_style;
}

bool ServiceCodeGenerator::IsExperimental() const {
  auto iter = vars().find("experimental");
  return iter != vars().end() && iter->second == "true";
}

bool ServiceCodeGenerator::HasLongrunningMethod() const {
  return std::any_of(methods_.begin(), methods_.end(),
                     [](google::protobuf::MethodDescriptor const& m) {
                       return IsLongrunningOperation(m);
                     });
}

bool ServiceCodeGenerator::HasGRPCLongrunningOperation() const {
  return std::any_of(methods_.begin(), methods_.end(),
                     [](google::protobuf::MethodDescriptor const& m) {
                       return IsGRPCLongrunningOperation(m);
                     });
}

bool ServiceCodeGenerator::HasAsyncMethod() const {
  return !async_methods_.empty() || HasLongrunningMethod();
}

bool ServiceCodeGenerator::HasPaginatedMethod() const {
  return std::any_of(methods_.begin(), methods_.end(),
                     [](google::protobuf::MethodDescriptor const& m) {
                       return IsPaginated(m);
                     });
}

bool ServiceCodeGenerator::HasMessageWithMapField() const {
  for (auto method : methods_) {
    auto const* const request = method.get().input_type();
    auto const* const response = method.get().output_type();
    for (int j = 0; j < request->field_count(); ++j) {
      if (request->field(j)->is_map()) {
        return true;
      }
    }
    for (int k = 0; k < response->field_count(); ++k) {
      if (response->field(k)->is_map()) {
        return true;
      }
    }
  }
  return false;
}

bool ServiceCodeGenerator::HasStreamingReadMethod() const {
  return std::any_of(methods_.begin(), methods_.end(),
                     [](google::protobuf::MethodDescriptor const& m) {
                       return IsStreamingRead(m);
                     });
}

bool ServiceCodeGenerator::HasAsynchronousStreamingReadMethod() const {
  return std::any_of(async_methods_.begin(), async_methods_.end(),
                     [](google::protobuf::MethodDescriptor const& m) {
                       return IsStreamingRead(m);
                     });
}

bool ServiceCodeGenerator::HasAsynchronousStreamingWriteMethod() const {
  return std::any_of(async_methods_.begin(), async_methods_.end(),
                     [](google::protobuf::MethodDescriptor const& m) {
                       return IsStreamingWrite(m);
                     });
}

bool ServiceCodeGenerator::HasStreamingWriteMethod() const {
  return std::any_of(methods_.begin(), methods_.end(),
                     [](google::protobuf::MethodDescriptor const& m) {
                       return IsStreamingWrite(m);
                     });
}

bool ServiceCodeGenerator::HasBidirStreamingMethod() const {
  return std::any_of(methods_.begin(), methods_.end(),
                     [](google::protobuf::MethodDescriptor const& m) {
                       return IsBidirStreaming(m);
                     });
}

bool ServiceCodeGenerator::HasExplicitRoutingMethod() const {
  return std::any_of(methods_.begin(), methods_.end(),
                     [](google::protobuf::MethodDescriptor const& m) {
                       return m.options().HasExtension(google::api::routing);
                     });
}

bool ServiceCodeGenerator::HasGenerateRestTransport() const {
  auto const generate_rest_transport =
      service_vars_.find("generate_rest_transport");
  return generate_rest_transport != service_vars_.end() &&
         generate_rest_transport->second == "true";
}

bool ServiceCodeGenerator::HasGenerateGrpcTransport() const {
  auto const generate_grpc_transport =
      service_vars_.find("generate_grpc_transport");
  return generate_grpc_transport != service_vars_.end() &&
         generate_grpc_transport->second == "true";
}

bool ServiceCodeGenerator::HasRequestId() const {
  return std::any_of(service_method_vars_.begin(), service_method_vars_.end(),
                     [](auto const& kv) {
                       return kv.second.find("request_id_field_name") !=
                              kv.second.end();
                     });
}

bool ServiceCodeGenerator::HasRequestId(
    google::protobuf::MethodDescriptor const& method) const {
  auto mv = service_method_vars_.find(method.full_name());
  if (mv == service_method_vars_.end()) return false;
  auto const& method_vars = mv->second;
  return method_vars.find("request_id_field_name") != method_vars.end();
}

bool ServiceCodeGenerator::HasApiVersion() const {
  auto iter = service_vars_.find("api_version");
  return iter != service_vars_.end() && !iter->second.empty();
}

std::vector<std::string>
ServiceCodeGenerator::MethodSignatureWellKnownProtobufTypeIncludes() const {
  std::vector<std::string> include_paths;
  for (auto method : methods_) {
    auto method_signature_extension =
        method.get().options().GetRepeatedExtension(
            google::api::method_signature);
    google::protobuf::Descriptor const* input_type = method.get().input_type();
    for (auto const& extension : method_signature_extension) {
      std::vector<std::string> parameters =
          absl::StrSplit(extension, ',', absl::SkipEmpty());
      for (auto& parameter : parameters) {
        absl::StripAsciiWhitespace(&parameter);
        auto path = IncludePathForWellKnownProtobufType(
            *input_type->FindFieldByName(parameter));
        if (path) include_paths.push_back(*path);
      }
    }
  }
  return include_paths;
}

bool ServiceCodeGenerator::MethodSignatureUsesDeprecatedField() const {
  return std::any_of(
      service_method_vars_.begin(), service_method_vars_.end(),
      [](auto const& method_vars) {
        return method_vars.second.find("uses_deprecated_field") !=
               method_vars.second.end();
      });
}

bool ServiceCodeGenerator::OmitMethodSignature(
    google::protobuf::MethodDescriptor const& method,
    int method_signature_number) const {
  auto method_vars = service_method_vars_.find(method.full_name());
  if (method_vars == service_method_vars_.end()) {
    GCP_LOG(FATAL) << method.full_name()
                   << " not found in service_method_vars_\n";
  }
  return method_vars->second.find("method_signature" +
                                  std::to_string(method_signature_number)) ==
         method_vars->second.end();
}

VarsDictionary const& ServiceCodeGenerator::vars() const {
  return service_vars_;
}

std::string ServiceCodeGenerator::vars(std::string const& key) const {
  auto iter = service_vars_.find(key);
  if (iter == service_vars_.end()) {
    GCP_LOG(FATAL) << key << " not found in service_vars_\n";
  }
  return iter->second;
}

VarsDictionary ServiceCodeGenerator::MergeServiceAndMethodVars(
    google::protobuf::MethodDescriptor const& method) const {
  auto vars = service_vars_;
  vars.insert(service_method_vars_.at(method.full_name()).begin(),
              service_method_vars_.at(method.full_name()).end());
  return vars;
}

void ServiceCodeGenerator::HeaderLocalIncludes(
    std::vector<std::string> const& local_includes) {
  GenerateLocalIncludes(header_, local_includes);
}

void ServiceCodeGenerator::CcLocalIncludes(
    std::vector<std::string> const& local_includes) {
  GenerateLocalIncludes(cc_, local_includes, FileType::kCcFile);
}

void ServiceCodeGenerator::HeaderSystemIncludes(
    std::vector<std::string> const& system_includes) {
  GenerateSystemIncludes(header_, system_includes);
}

void ServiceCodeGenerator::CcSystemIncludes(
    std::vector<std::string> const& system_includes) {
  GenerateSystemIncludes(cc_, system_includes);
}

Status ServiceCodeGenerator::HeaderOpenNamespaces(NamespaceType ns_type) {
  return OpenNamespaces(header_, ns_type, "product_path");
}

Status ServiceCodeGenerator::HeaderOpenForwardingNamespaces(
    NamespaceType ns_type, std::string const& ns_documentation) {
  return OpenNamespaces(header_, ns_type, "forwarding_product_path",
                        ns_documentation);
}

void ServiceCodeGenerator::HeaderCloseNamespaces() {
  CloseNamespaces(header_, define_backwards_compatibility_namespace_alias_);
}

Status ServiceCodeGenerator::CcOpenNamespaces(NamespaceType ns_type) {
  return OpenNamespaces(cc_, ns_type, "product_path");
}

Status ServiceCodeGenerator::CcOpenForwardingNamespaces(NamespaceType ns_type) {
  return OpenNamespaces(cc_, ns_type, "forwarding_product_path");
}

void ServiceCodeGenerator::CcCloseNamespaces() { CloseNamespaces(cc_, false); }

void ServiceCodeGenerator::HeaderPrint(std::string const& text) {
  header_.Print(service_vars_, text);
}

void ServiceCodeGenerator::HeaderPrint(
    std::vector<PredicatedFragment<void>> const& text) {
  for (auto const& fragment : text) {
    header_.Print(service_vars_, fragment());
  }
}

Status ServiceCodeGenerator::HeaderPrintMethod(
    google::protobuf::MethodDescriptor const& method,
    std::vector<MethodPattern> const& patterns, char const* file, int line) {
  return PrintMethod(method, header_, MergeServiceAndMethodVars(method),
                     patterns, file, line);
}

void ServiceCodeGenerator::HeaderPrintMethod(
    google::protobuf::MethodDescriptor const& method, char const* file,
    int line, std::string const& text) {
  header_.Print(line, file, MergeServiceAndMethodVars(method), text);
}

void ServiceCodeGenerator::CcPrint(std::string const& text) {
  cc_.Print(service_vars_, text);
}

void ServiceCodeGenerator::CcPrint(
    std::vector<PredicatedFragment<void>> const& text) {
  for (auto const& fragment : text) {
    cc_.Print(service_vars_, fragment());
  }
}

Status ServiceCodeGenerator::CcPrintMethod(
    google::protobuf::MethodDescriptor const& method,
    std::vector<MethodPattern> const& patterns, char const* file, int line) {
  return PrintMethod(method, cc_, MergeServiceAndMethodVars(method), patterns,
                     file, line);
}

void ServiceCodeGenerator::CcPrintMethod(
    google::protobuf::MethodDescriptor const& method, char const* file,
    int line, std::string const& text) {
  cc_.Print(line, file, MergeServiceAndMethodVars(method), text);
}

void ServiceCodeGenerator::GenerateLocalIncludes(
    Printer& p, std::vector<std::string> local_includes, FileType file_type) {
  if (file_type == FileType::kCcFile) {
    std::sort(local_includes.begin() + 1, local_includes.end());
  } else {
    std::sort(local_includes.begin(), local_includes.end());
  }
  for (auto const& include : local_includes) {
    p.Print(LocalInclude(include));
  }
}

void ServiceCodeGenerator::GenerateSystemIncludes(
    Printer& p, std::vector<std::string> system_includes) {
  std::sort(system_includes.begin(), system_includes.end());
  for (auto const& include : system_includes) {
    p.Print(SystemInclude(include));
  }
}

Status ServiceCodeGenerator::OpenNamespaces(
    Printer& p, NamespaceType ns_type, std::string const& product_path_var,
    std::string const& ns_documentation) {
  auto result = service_vars_.find(product_path_var);
  if (result == service_vars_.end()) {
    return internal::InternalError(product_path_var + " not found in vars",
                                   GCP_ERROR_INFO());
  }
  namespace_ = Namespace(service_vars_[product_path_var], ns_type);
  p.Print(R"""(
namespace google {
namespace cloud {)""");
  p.Print(service_vars_, ns_documentation);
  p.Print(R"""(
namespace $namespace$ {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN
)""",
          "namespace", namespace_);
  return {};
}

void ServiceCodeGenerator::CloseNamespaces(
    Printer& p, bool define_backwards_compatibility_namespace_alias) {
  p.Print(R"""(
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END)""");
  // TODO(#7463) - remove backwards compatibility namespaces
  if (define_backwards_compatibility_namespace_alias) {
    p.Print(R"""(
namespace gcpcxxV1 = GOOGLE_CLOUD_CPP_NS; // NOLINT(misc-unused-alias-decls))""");
  }
  p.Print(R"""(
}  // namespace $namespace$
}  // namespace cloud
}  // namespace google
)""",
          "namespace", namespace_);
}

Status ServiceCodeGenerator::Generate() {
  auto result = GenerateHeader();
  if (!result.ok()) return result;
  return GenerateCc();
}

void ServiceCodeGenerator::SetVars(absl::string_view header_path) {
  service_vars_["header_include_guard"] = FormatHeaderIncludeGuard(header_path);
}

void ServiceCodeGenerator::SetMethods() {
  auto split_arg = [this](std::string const& arg) -> std::set<std::string> {
    auto l = service_vars_.find(arg);
    if (l == service_vars_.end()) return {};
    std::vector<std::string> s = absl::StrSplit(l->second, ',');
    for (auto& a : s) a = SafeReplaceAll(a, "@", ",");
    return {s.begin(), s.end()};
  };
  auto const omitted_rpcs = split_arg("omitted_rpcs");
  auto const gen_async_rpcs = split_arg("gen_async_rpcs");

  auto service_name = service_descriptor_->name();
  for (int i = 0; i < service_descriptor_->method_count(); ++i) {
    auto const* method = service_descriptor_->method(i);
    auto method_name = method->name();
    auto qualified_method_name = absl::StrCat(service_name, ".", method_name);
    auto any_match = [&](std::string const& v) {
      return v == method_name || v == qualified_method_name;
    };
    bool omit_rpc = internal::ContainsIf(omitted_rpcs, any_match);
    if (!omit_rpc) methods_.emplace_back(*method);
    if (internal::ContainsIf(gen_async_rpcs, any_match)) {
      // We still generate the async API for omitted (and possibly
      // deprecated) RPCs when they appear in gen_async_rpcs.
      async_methods_.emplace_back(*method);
    }
  }

  for (auto const& mixin_method : mixin_methods_) {
    methods_.emplace_back(mixin_method.method.get());
  }
}

std::string ServiceCodeGenerator::GetPbIncludeByTransport() const {
  if (HasGenerateGrpcTransport()) return vars("proto_grpc_header_path");
  return vars("proto_header_path");
}

std::vector<std::string> ServiceCodeGenerator::GetMixinPbIncludeByTransport()
    const {
  std::string const& mixin_pb_header_paths =
      HasGenerateGrpcTransport() ? vars("mixin_proto_grpc_header_paths")
                                 : vars("mixin_proto_header_paths");

  return absl::StrSplit(mixin_pb_header_paths, ',');
}

bool ServiceCodeGenerator::IsDiscoveryDocumentProto() const {
  auto iter = service_vars_.find("proto_file_source");
  return (iter != service_vars_.end() && iter->second == "discovery_document");
}

std::vector<MixinMethod> const& ServiceCodeGenerator::MixinMethods() const {
  return mixin_methods_;
}
#endif

}  // namespace generator_internal
}  // namespace cloud
}  // namespace google

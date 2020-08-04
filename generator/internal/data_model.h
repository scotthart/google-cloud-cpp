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
#ifndef GENERATOR_INTERNAL_DATA_MODEL_H_
#define GENERATOR_INTERNAL_DATA_MODEL_H_

#include "absl/strings/str_cat.h"
#include "absl/strings/str_join.h"
#include "absl/strings/str_replace.h"
#include "absl/strings/str_split.h"
#include "generator/internal/codegen_utils.h"
#include "generator/internal/printer.h"
#include "google/api/client.pb.h"
#include "google/api/http.pb.h"
#include "google/longrunning/operations.pb.h"
#include <google/protobuf/compiler/code_generator.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/descriptor.pb.h>
#include <algorithm>
#include <cctype>
#include <functional>
#include <map>
#include <regex>
#include <string>

namespace pb = google::protobuf;

namespace google {
namespace codegen {
namespace internal {
using google::protobuf::FieldDescriptor;

inline std::string CppTypeToString(
    google::protobuf::FieldDescriptor const* field) {
  switch (field->cpp_type()) {
    case FieldDescriptor::CPPTYPE_INT32:
    case FieldDescriptor::CPPTYPE_INT64:
    case FieldDescriptor::CPPTYPE_UINT32:
    case FieldDescriptor::CPPTYPE_UINT64:
    case FieldDescriptor::CPPTYPE_DOUBLE:
    case FieldDescriptor::CPPTYPE_FLOAT:
    case FieldDescriptor::CPPTYPE_BOOL:
    case FieldDescriptor::CPPTYPE_ENUM:
    case FieldDescriptor::CPPTYPE_STRING:
      return std::string("std::") + std::string(field->cpp_type_name());
    case FieldDescriptor::CPPTYPE_MESSAGE:
      return internal::ProtoNameToCppName(field->message_type()->full_name());
  }
  return "oops";
}

struct DataModel {
  static void SetServiceVars(pb::ServiceDescriptor const* service,
                             std::map<std::string, std::string>& vars) {
    vars["class_name"] = service->name();
    vars["stub_class_name"] = absl::StrCat(service->name(), "Stub");
    vars["metadata_class_name"] = absl::StrCat(service->name(), "Metadata");
    vars["logging_class_name"] = absl::StrCat(service->name(), "Logging");
    vars["proto_file_name"] = service->file()->name();
    vars["header_include_guard_const"] = absl::StrCat(service->name(), "_H_");
    vars["stub_header_include_guard_const"] =
        absl::StrCat(service->name(), "_STUB", "_H_");
    vars["metadata_header_include_guard_const"] =
        absl::StrCat(service->name(), "_METADATA", "_H_");
    vars["logging_header_include_guard_const"] =
        absl::StrCat(service->name(), "_LOGGING", "_H_");
    vars["class_comment_block"] = "// TODO: pull in comments";
    vars["grpc_stub_fqn"] = internal::ProtoNameToCppName(service->full_name());
    vars["service_endpoint"] =
        service->options().GetExtension(google::api::default_host);
  }

  static void SetMethodVars(pb::MethodDescriptor const* method,
                            std::map<std::string, std::string>& vars) {
    vars["method_name"] = method->name();
    vars["method_name_snake"] = CamelCaseToSnakeCase(method->name());
    vars["request_type"] =
        internal::ProtoNameToCppName(method->input_type()->full_name());
    vars["response_type"] =
        internal::ProtoNameToCppName(method->output_type()->full_name());
    //    vars["return_type"] = method->output_type()->full_name() ==
    //    "google.protobuf.Empty" ?
    //        "Status" :
    //        "StatusOr<" +
    //        internal::ProtoNameToCppName(method->output_type()->full_name()) +
    //        ">";
    if (method->output_type()->full_name() == "google.longrunning.Operation") {
      auto operation_info =
          method->options().GetExtension(google::longrunning::operation_info);
      vars["longrunning_metadata_type"] =
          internal::ProtoNameToCppName(operation_info.metadata_type());
      vars["longrunning_response_type"] =
          internal::ProtoNameToCppName(operation_info.response_type());
      if (vars["longrunning_response_type"] == "::Backup") {
        vars["longrunning_response_type"] =
            "::google::spanner::admin::database::v1::Backup";
      }

      // TODO(sdhart): determine if this is the correct behavior for
      // response_type Empty.
      vars["longrunning_deduced_response_type"] =
          operation_info.response_type() == "google.protobuf.Empty"
              ? internal::ProtoNameToCppName(operation_info.metadata_type())
              : internal::ProtoNameToCppName(operation_info.response_type());
      if (vars["longrunning_deduced_response_type"] == "::Backup") {
        vars["longrunning_deduced_response_type"] =
            "::google::spanner::admin::database::v1::Backup";
      }
    }

    if (IsPaginated(method)) {
      vars["range_output_field_name"] = DeterminePagination(method)->first;
      vars["range_output_type"] =
          internal::ProtoNameToCppName(DeterminePagination(method)->second);
    }

    auto method_signature =
        method->options().GetRepeatedExtension(google::api::method_signature);
    if (!method_signature.empty()) {
      google::protobuf::Descriptor const* input_type = method->input_type();
      std::vector<std::string> parameters =
          absl::StrSplit(method_signature[0], ",");
      std::string method_signature;
      for (unsigned int i = 0; i < parameters.size() - 1; ++i) {
        google::protobuf::FieldDescriptor const* parameter =
            input_type->FindFieldByName(parameters[i]);
        method_signature += CppTypeToString(parameter);
        method_signature += " const& ";
        method_signature += parameters[i];
        method_signature += ", ";
      }
      google::protobuf::FieldDescriptor const* parameter =
          input_type->FindFieldByName(parameters[parameters.size() - 1]);
      method_signature += CppTypeToString(parameter);
      method_signature += " const& ";
      method_signature += parameters[parameters.size() - 1];

      vars["method_signature"] = method_signature;
    }

    google::api::HttpRule http_rule =
        method->options().GetExtension(google::api::http);
    vars["method_request_param"] = "foo";
    std::string url_pattern;
    switch (http_rule.pattern_case()) {
      case google::api::HttpRule::kGet:
        url_pattern = http_rule.get();
        break;
      case google::api::HttpRule::kPut:
        url_pattern = http_rule.put();
        break;
      case google::api::HttpRule::kPost:
        url_pattern = http_rule.post();
        break;
      case google::api::HttpRule::kDelete:
        url_pattern = http_rule.delete_();
        break;
      case google::api::HttpRule::kPatch:
        url_pattern = http_rule.patch();
        break;
      default:
        std::cerr << __FILE__ << ":" << __LINE__
                  << ": google::api::HttpRule not handled" << std::endl;
        std::exit(1);
    }
    std::regex url_pattern_regex(R"(.*\{(.*)=.*\}.*)");
    std::smatch match;
    std::regex_match(url_pattern, match, url_pattern_regex);
    std::string param = match[1];
    //    std::cerr << param << "\n";
    vars["method_request_param_key"] = param;
    std::vector<std::string> chunks = absl::StrSplit(param, std::string("."));
    if (chunks.size() > 1) {
      std::string value;
      unsigned int i = 0;
      for (; i < chunks.size() - 1; ++i) {
        value += chunks[i] + "().";
      }
      value += chunks[i] + "()";
      vars["method_request_param_value"] = value;
    } else {
      vars["method_request_param_value"] = param + "()";
    }
  }

  // PrintMethods should only iterate over service methods once.
  // Currently, each different template is passed to a call of PrintMethods,
  // which attempts to generate each methods regardless if it has already been
  // generated.
  // Furthermore, we need to be able to determine if there are multiple matches
  // for a method (an error) or no matches for a method (also an error).
  // All the different tmplt+predicate need to be put in a container in an
  // class along with having vars as a member.
  static void PrintMethods(
      pb::ServiceDescriptor const* service,
      std::map<std::string, std::string> vars, Printer& p, char const* tmplt,
      std::function<bool(pb::MethodDescriptor const*)> predicate =
          [](pb::MethodDescriptor const*) { return true; }) {
    for (int i = 0; i < service->method_count(); i++) {
      const pb::MethodDescriptor* method = service->method(i);
      if (predicate(method)) {
        SetMethodVars(method, vars);
        p->Print(vars, tmplt);
      }
    }
  }

  static void PrintMethods(
      pb::ServiceDescriptor const* service,
      std::map<std::string, std::string> vars, Printer& p,
      std::vector<PredicatedFragment<google::protobuf::MethodDescriptor>>
          fragments,
      std::function<bool(pb::MethodDescriptor const*)> predicate =
          [](pb::MethodDescriptor const*) { return true; }) {
    for (int i = 0; i < service->method_count(); i++) {
      const pb::MethodDescriptor* method = service->method(i);
      if (predicate(method)) {
        SetMethodVars(method, vars);
        for (auto const& f : fragments) {
          p->Print(vars, f(method).c_str());
        }
      }
    }
  }
};

}  // namespace internal
}  // namespace codegen
}  // namespace google

#endif  // GENERATOR_INTERNAL_DATA_MODEL_H_

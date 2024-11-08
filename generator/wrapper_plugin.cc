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

#include "generator/wrapper_plugin.h"
#include "generator/internal/codegen_utils.h"
#include "generator/internal/descriptor_utils.h"
#include "generator/internal/generator_interface.h"
#include "generator/internal/make_generators.h"
#include "google/cloud/internal/absl_str_cat_quiet.h"
#include "google/cloud/internal/algorithm.h"
#include "google/cloud/internal/filesystem.h"
#include "google/cloud/status_or.h"
#include "absl/strings/str_split.h"
#include "absl/strings/str_join.h"
#include <google/api/client.pb.h>
#include <future>
#include <string>
#include <vector>

namespace google {
namespace cloud {
namespace generator {


void HeaderWrapField(google::protobuf::FieldDescriptor const& field) {

}

StatusOr<std::pair<generator_internal::VarsDictionary, std::string>> HeaderWrapMessage(
    google::protobuf::Descriptor const& message) {
  std::vector<std::string> text;
  generator_internal::VarsDictionary vars;
  vars["class_name"] = generator_internal::ProtoNameToCppName(message.name());
  vars["message_full_name"] = generator_internal::ProtoNameToCppName(message.full_name());

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
    HeaderWrapField(*field);

  }

  text.push_back(R"""(
 private:
  $message_full_name$ message_;
};)""");

  return {{vars, absl::StrJoin(text, "\n")}};

}

bool WrapperPlugin::Generate(google::protobuf::FileDescriptor const* file,
                         std::string const& parameters,
                         google::protobuf::compiler::GeneratorContext* context,
                         std::string* error) const {

  StatusOr<std::vector<std::pair<std::string, std::string>>> command_line_args =
      generator_internal::ProcessWrapperCommandLineArgs(parameters);
  if (!command_line_args.ok()) {
    *error = command_line_args.status().message();
    return false;
  }

  generator_internal::Printer p(context, file->name() + ".wrapper.h");
  for (int i = 0; i < file->message_type_count(); ++i) {
    auto text = HeaderWrapMessage(*file->message_type(i));
//    auto message = file->message_type(i);
//    p.Print(message->full_name());
    p.Print(text->first, text->second);
    p.Print("\n");

  }

  return true;

#if 0
  using ServiceGenerator =
      std::vector<std::unique_ptr<generator_internal::GeneratorInterface>>;

  if (file->options().cc_generic_services()) {
    *error =
        "cpp codegen proto compiler plugin does not work with generic "
        "services. To generate cpp codegen APIs, please set \""
        "cc_generic_service = false\".";
    return false;
  }

  StatusOr<std::vector<std::pair<std::string, std::string>>> command_line_args =
      generator_internal::ProcessCommandLineArgs(parameters);
  if (!command_line_args.ok()) {
    *error = command_line_args.status().message();
    return false;
  }

  std::vector<std::string> omitted_services;
  for (auto const& arg : *command_line_args) {
    if (arg.first == "omitted_services") {
      omitted_services = absl::StrSplit(arg.second, ',');
    }
  }

  YAML::Node service_config;
  for (auto const& arg : *command_line_args) {
    if (arg.first != "service_config_yaml") continue;
    auto status = google::cloud::internal::status(arg.second);
    if (!exists(status)) continue;
    service_config = YAML::LoadFile(arg.second);
  }

  std::vector<ServiceGenerator> services;
  services.reserve(file->service_count());
  for (int i = 0; i < file->service_count(); ++i) {
    auto const* service = file->service(i);
    if (!internal::Contains(omitted_services, service->name())) {
      services.push_back(generator_internal::MakeGenerators(
          service, context, service_config, *command_line_args));
    }
  }

  std::vector<std::future<Status>> tasks;
  for (auto const& code_generators : services) {
    for (auto const& c : code_generators) {
      tasks.push_back(
          std::async(std::launch::async, [&c]() { return c->Generate(); }));
    }
  }

  std::string error_message;
  for (auto& t : tasks) {
    auto result = t.get();
    if (!result.ok()) {
      absl::StrAppend(&error_message, result.message(), "\n");
    }
  }

  if (!error_message.empty()) {
    *error = error_message;
    return false;
  }
  return true;
#endif
}

}  // namespace generator
}  // namespace cloud
}  // namespace google

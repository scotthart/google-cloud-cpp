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
#include <google/protobuf/compiler/plugin.h>

int main(int argc, char** argv) {
  google::cloud::generator::WrapperPlugin wrapper_plugin;
  return google::protobuf::compiler::PluginMain(argc, argv, &wrapper_plugin);
}

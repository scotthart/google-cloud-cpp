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

#include "google/cloud/internal/http_header.h"
#include <gmock/gmock.h>

namespace google {
namespace cloud {
namespace rest_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN
namespace {

//using ::testing::ElementsAre;
using ::testing::Eq;

TEST(HttpHeader, ConstructionAndFormatting) {
  HttpHeader empty;
  EXPECT_THAT(std::string(empty), Eq(""));

  HttpHeader no_value("key");
  EXPECT_THAT(std::string(no_value), Eq("key:"));

  HttpHeader single_value("key", "value");
  EXPECT_THAT(std::string(single_value), Eq("key: value"));

  HttpHeader multi_value("key", std::vector<std::string>{"value1", "value2"});
  EXPECT_THAT(std::string(multi_value), Eq("key: value1,value2"));
}

}  // namespace
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace rest_internal
}  // namespace cloud
}  // namespace google

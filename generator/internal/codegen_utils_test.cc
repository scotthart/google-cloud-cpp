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
#include <gtest/gtest.h>
#include <string>
#include <utility>
#include <vector>

namespace google {
namespace codegen {
namespace internal {
namespace {

TEST(CodegenUtils, CamelCaseToSnakeCase) {
  std::vector<std::pair<std::string, std::string>> test_cases{
      {"abc", "abc"},        {"Abc", "abc"},
      {"AbcDef", "abc_def"}, {"abcDef", "abc_def"},
      {"ABc", "a_bc"},       {"ABcDEf", "a_bc_d_ef"},
      {"Abc1De", "abc1_de"}, {"Abc1de", "abc1de"},
      {"A1B", "a1_b"},       {"SNMPParse", "snmp_parse"}};

  for (auto const& test_case : test_cases) {
    std::string actual = CamelCaseToSnakeCase(test_case.first);
    std::string expected = test_case.second;
    EXPECT_EQ(expected, actual);
  }
}

TEST(CodegenUtils, ServiceNameToFilePath) {
  auto result =
      ServiceNameToFilePath("google.example.library.v1.LibraryService");
  EXPECT_EQ(result, "google/example/library/v1/library");
}

bool PredicateTrue(int const*) { return true; }
bool PredicateFalse(int const*) { return false; }

TEST(CodegenUtils, GenericNot) {
  int bar;
  EXPECT_TRUE(GenericNot<int>(PredicateFalse)(&bar));
  EXPECT_FALSE(GenericNot<int>(PredicateTrue)(&bar));
}

TEST(CodegenUtils, GenericAnd) {
  int bar;
  EXPECT_TRUE(GenericAnd<int>(PredicateTrue, PredicateTrue)(&bar));
  EXPECT_FALSE(GenericAnd<int>(PredicateFalse, PredicateTrue)(&bar));
  EXPECT_FALSE(GenericAnd<int>(PredicateTrue, PredicateFalse)(&bar));
  EXPECT_FALSE(GenericAnd<int>(PredicateFalse, PredicateFalse)(&bar));

  EXPECT_TRUE(
      GenericAnd<int>(PredicateTrue, GenericNot<int>(PredicateFalse))(&bar));
  EXPECT_TRUE(
      GenericAnd<int>(GenericNot<int>(PredicateFalse), PredicateTrue)(&bar));
  EXPECT_TRUE(
      GenericNot<int>(GenericAnd<int>(PredicateTrue, PredicateFalse))(&bar));
}

TEST(CodegenUtils, GenericOr) {
  int bar;
  EXPECT_TRUE(GenericOr<int>(PredicateTrue, PredicateTrue)(&bar));
  EXPECT_TRUE(GenericOr<int>(PredicateFalse, PredicateTrue)(&bar));
  EXPECT_TRUE(GenericOr<int>(PredicateTrue, PredicateFalse)(&bar));
  EXPECT_FALSE(GenericOr<int>(PredicateFalse, PredicateFalse)(&bar));
}

TEST(CodegenUtils, GenericAll) {
  int bar;
  EXPECT_TRUE(GenericAll<int>(PredicateTrue)(&bar));
  EXPECT_FALSE(GenericAll<int>(PredicateFalse)(&bar));
  EXPECT_FALSE(GenericAll<int>(PredicateFalse, PredicateFalse)(&bar));
  EXPECT_TRUE(GenericAll<int>(PredicateTrue, PredicateTrue)(&bar));
  EXPECT_TRUE(
      GenericAll<int>(PredicateTrue, PredicateTrue, PredicateTrue)(&bar));
  EXPECT_FALSE(
      GenericAll<int>(PredicateFalse, PredicateTrue, PredicateTrue)(&bar));
  EXPECT_FALSE(
      GenericAll<int>(PredicateTrue, PredicateFalse, PredicateTrue)(&bar));
  EXPECT_FALSE(
      GenericAll<int>(PredicateFalse, PredicateFalse, PredicateFalse)(&bar));

  EXPECT_FALSE(GenericAll<int>(
      PredicateFalse, GenericOr<int>(PredicateFalse, PredicateTrue))(&bar));
}

TEST(CodegenUtils, GenericAny) {
  int bar;
  EXPECT_TRUE(GenericAny<int>(PredicateTrue)(&bar));
  EXPECT_FALSE(GenericAny<int>(PredicateFalse)(&bar));
  EXPECT_FALSE(GenericAny<int>(PredicateFalse, PredicateFalse)(&bar));
  EXPECT_TRUE(GenericAny<int>(PredicateTrue, PredicateTrue)(&bar));
  EXPECT_TRUE(
      GenericAny<int>(PredicateTrue, PredicateTrue, PredicateTrue)(&bar));
  EXPECT_TRUE(
      GenericAny<int>(PredicateFalse, PredicateTrue, PredicateTrue)(&bar));
  EXPECT_TRUE(
      GenericAny<int>(PredicateTrue, PredicateFalse, PredicateTrue)(&bar));
  EXPECT_FALSE(
      GenericAny<int>(PredicateFalse, PredicateFalse, PredicateFalse)(&bar));
}

}  // namespace
}  // namespace internal
}  // namespace codegen
}  // namespace google

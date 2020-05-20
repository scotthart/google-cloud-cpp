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
#ifndef GENERATOR_INTERNAL_GAPIC_UTILS_H_
#define GENERATOR_INTERNAL_GAPIC_UTILS_H_

#include "absl/strings/str_cat.h"
#include "absl/strings/str_join.h"
#include "absl/strings/str_replace.h"
#include "absl/strings/str_split.h"
#include <google/protobuf/descriptor.h>
#include <algorithm>
#include <cctype>
#include <functional>
#include <string>

namespace google {
namespace codegen {
namespace internal {

namespace pb = google::protobuf;

std::string GeneratedFileSuffix();

bool IsNonStreaming(google::protobuf::MethodDescriptor const* m);
bool IsLongrunningOperation(google::protobuf::MethodDescriptor const* m);
bool IsResponseTypeEmpty(google::protobuf::MethodDescriptor const* m);

class And {
 public:
  And(std::function<bool(google::protobuf::MethodDescriptor const* m)> lhs,
      std::function<bool(google::protobuf::MethodDescriptor const* m)> rhs)
      : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}
  bool operator()(google::protobuf::MethodDescriptor const* m) const {
    return lhs_(m) && rhs_(m);
  }

 private:
  std::function<bool(google::protobuf::MethodDescriptor const* m)> lhs_;
  std::function<bool(google::protobuf::MethodDescriptor const* m)> rhs_;
};

class Or {
 public:
  Or(std::function<bool(google::protobuf::MethodDescriptor const* m)> lhs,
     std::function<bool(google::protobuf::MethodDescriptor const* m)> rhs)
      : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}
  bool operator()(google::protobuf::MethodDescriptor const* m) const {
    return lhs_(m) || rhs_(m);
  }

 private:
  std::function<bool(google::protobuf::MethodDescriptor const* m)> lhs_;
  std::function<bool(google::protobuf::MethodDescriptor const* m)> rhs_;
};

class Not {
 public:
  Not(std::function<bool(google::protobuf::MethodDescriptor const* m)> lhs)
      : lhs_(std::move(lhs)) {}
  bool operator()(google::protobuf::MethodDescriptor const* m) const {
    return !lhs_(m);
  }

 private:
  std::function<bool(google::protobuf::MethodDescriptor const* m)> lhs_;
};

template <typename T>
class PredicatedFragment {
 public:
  using PredicateFn = std::function<bool(T const*)>;

  PredicatedFragment(PredicateFn predicate, std::string fragment_if_true,
                     std::string fragment_if_false)
      : predicate_(predicate),
        fragment_if_true_(std::move(fragment_if_true)),
        fragment_if_false_(std::move(fragment_if_false)) {}

  PredicatedFragment(std::string fragment_always_true)
      : predicate_([](T const*) { return true; }),
        fragment_if_true_(std::move(fragment_always_true)),
        fragment_if_false_({}) {}

  std::string operator()(T const* descriptor) const {
    if (predicate_(descriptor)) {
      return fragment_if_true_;
    }
    return fragment_if_false_;
  }

 private:
  PredicateFn predicate_;
  std::string fragment_if_true_;
  std::string fragment_if_false_;
};

// Convenience functions for wrapping include headers with the correct
// delimiting characters (either <> or "")
std::string LocalInclude(std::string header);
std::string SystemInclude(std::string header);

/**
 * Convert a CamelCase string to snake_case.
 */
std::string CamelCaseToSnakeCase(std::string const& input);

/**
 * Convert a service name to a file path.
 *
 * service_name should consist of CamelCase pieces and "." separators.
 * Each component of service_name will become part of the path, except
 * the last component, which will become the file name. Components will
 * be converted from CamelCase to snake_case.
 *
 * Example: "google.LibraryService" -> "google/library_service"
 */
std::string ServiceNameToFilePath(std::string const& service_name);

/**
 * Convert a protobuf name to a fully qualified C++ name.
 *
 * proto_name should be a "." separated name, which we convert to a
 * "::" separated C++ fully qualified name.
 */
std::string ProtoNameToCppName(std::string const& proto_name);

}  // namespace internal
}  // namespace codegen
}  // namespace google

#endif  // GENERATOR_INTERNAL_GAPIC_UTILS_H_

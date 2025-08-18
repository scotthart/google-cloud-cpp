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

#ifndef GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_BIGTABLE_QUERY_H
#define GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_BIGTABLE_QUERY_H

#include "google/cloud/bigtable/retry_policy.h"
#include "google/cloud/backoff_policy.h"
#include "google/cloud/idempotency.h"
#include "google/cloud/internal/make_status.h"
#include "google/cloud/options.h"
#include "google/cloud/status_or.h"
#include "google/cloud/version.h"
#include <google/bigtable/v2/bigtable.pb.h>
#include <google/bigtable/v2/types.pb.h>
#include <google/protobuf/struct.pb.h>
#include <google/protobuf/util/message_differencer.h>
#include <string>
#include <unordered_map>
#include <vector>

namespace google {
namespace cloud {
namespace bigtable_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN
// The implementation for `IsTuple<T>` (below).
template <typename T>
struct IsTupleImpl : std::false_type {};
template <typename... Ts>
struct IsTupleImpl<std::tuple<Ts...>> : std::true_type {};

// Decays the given type `T` and determines whether it is a `std::tuple<...>`.
//
// Example:
//
//     using Type = std::tuple<...>;
//     static_assert(IsTuple<Type>::value, "");
//
template <typename T>
using IsTuple = IsTupleImpl<std::decay_t<T>>;

// Decays the tuple `T` and returns its size as in the ::value member.
template <typename T>
using TupleSize = std::tuple_size<std::decay_t<T>>;

// Base case of `ForEach` that is called at the end of iterating a tuple.
// See the docs for the next overload to see how to use `ForEach`.
template <std::size_t I = 0, typename T, typename F, typename... Args>
std::enable_if_t<I == TupleSize<T>::value, void> ForEach(T&&, F&&, Args&&...) {}

// This function template iterates the elements of a tuple, calling the given
// functor with each of the tuple's elements as well as any additional
// (optional) caller-provided arguments. The given functor should be able to
// accept each type in the container. All arguments are perfect-forwarded to
// the functor, so the functor may choose to accept the tuple arguments by
// value, const-ref, or even non-const reference, in which case the elements
// inside the tuple may be modified.
//
// Example:
//
//     struct Stringify {
//       template <typename T>
//       void operator()(T& t, std::vector<std::string>& out) const {
//         out.push_back(std::to_string(t));
//       }
//     };
//     auto tup = std::make_tuple(true, 42);
//     std::vector<std::string> v;
//     internal::ForEach(tup, Stringify{}, v);
//     EXPECT_THAT(v, testing::ElementsAre("1", "42"));
//
template <std::size_t I = 0, typename T, typename F, typename... Args>
std::enable_if_t<(I < TupleSize<T>::value), void> ForEach(T&& t, F&& f,
                                                          Args&&... args) {
  auto&& e = std::get<I>(std::forward<T>(t));
  std::forward<F>(f)(std::forward<decltype(e)>(e), std::forward<Args>(args)...);
  ForEach<I + 1>(std::forward<T>(t), std::forward<F>(f),
                 std::forward<Args>(args)...);
}
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace bigtable_internal

namespace bigtable_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN
struct ValueInternals;
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace bigtable_internal

namespace bigtable {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

class Value {
 public:
  /**
   * Constructs a `Value` that holds nothing.
   *
   * All calls to `get<T>()` will return an error.
   */
  Value() = default;

  // Copy and move.
  Value(Value const&) = default;
  Value(Value&&) = default;
  Value& operator=(Value const&) = default;
  Value& operator=(Value&&) = default;

  /// Constructs an instance with the specified type and value.
  explicit Value(bool v) : Value(PrivateConstructor{}, v) {}
  /// @copydoc Value(bool)
  explicit Value(std::int64_t v) : Value(PrivateConstructor{}, v) {}
  /// @copydoc Value(bool)
  explicit Value(float v) : Value(PrivateConstructor{}, v) {}
  /// @copydoc Value(bool)
  explicit Value(double v) : Value(PrivateConstructor{}, v) {}
  /// @copydoc Value(bool)
  explicit Value(std::string v) : Value(PrivateConstructor{}, std::move(v)) {}
  //  /// @copydoc Value(bool)
  //  explicit Value(Bytes v) : Value(PrivateConstructor{}, std::move(v)) {}
  //  /// @copydoc Value(bool)
  //  explicit Value(Json v) : Value(PrivateConstructor{}, std::move(v)) {}
  //  /// @copydoc Value(bool)
  //  explicit Value(JsonB v) : Value(PrivateConstructor{}, std::move(v)) {}
  //  /// @copydoc Value(bool)
  //  explicit Value(Numeric v) : Value(PrivateConstructor{}, std::move(v)) {}
  //  /// @copydoc Value(bool)
  //  explicit Value(PgNumeric v) : Value(PrivateConstructor{}, std::move(v)) {}
  //  /// @copydoc Value(bool)
  //  explicit Value(PgOid v) : Value(PrivateConstructor{}, std::move(v)) {}
  //  /// @copydoc Value(bool)
  //  explicit Value(Timestamp v) : Value(PrivateConstructor{}, std::move(v)) {}
  //  /// @copydoc Value(bool)
  //  explicit Value(CommitTimestamp v)
  //      : Value(PrivateConstructor{}, std::move(v)) {}
  //  /// @copydoc Value(bool)
  //  explicit Value(absl::CivilDay v)
  //      : Value(PrivateConstructor{}, std::move(v)) {}
  //  /// @copydoc Value(bool)
  //  explicit Value(Interval v) : Value(PrivateConstructor{}, std::move(v)) {}
  //  /// @copydoc Value(bool)
  //  template <typename E>
  //  explicit Value(ProtoEnum<E> v) : Value(PrivateConstructor{}, std::move(v))
  //  {}
  //  /// @copydoc Value(bool)
  //  template <typename M>
  //  explicit Value(ProtoMessage<M> v)
  //      : Value(PrivateConstructor{}, std::move(v)) {}

  /**
   * Constructs an instance from common C++ literal types that closely, though
   * not exactly, match supported Spanner types.
   *
   * An integer literal in C++ is of type `int`, which is not exactly an
   * allowed Spanner type. This will be allowed but it will be implicitly up
   * converted to a `std::int64_t`. Similarly, a C++ string literal will be
   * implicitly converted to a `std::string`. For example:
   *
   * @code
   * spanner::Value v1(42);
   * assert(42 == *v1.get<std::int64_t>());
   *
   * spanner::Value v2("hello");
   * assert("hello" == *v2.get<std::string>());
   * @endcode
   */
  explicit Value(int v) : Value(PrivateConstructor{}, v) {}
  /// @copydoc Value(int)
  explicit Value(char const* v) : Value(PrivateConstructor{}, v) {}

  /**
   * Constructs a non-null instance if `opt` has a value, otherwise constructs
   * a null instance with the specified type `T`.
   */
  template <typename T>
  explicit Value(absl::optional<T> opt)
      : Value(PrivateConstructor{}, std::move(opt)) {}

  /**
   * Constructs an instance from a Spanner ARRAY of the specified type and
   * values.
   *
   * The type `T` may be any valid type shown above, except vectors of vectors
   * are not allowed.
   *
   * @warning If `T` is a `std::tuple` with field names (i.e., at least one of
   *   its element types is a `std::pair<std::string, T>`) then, all of the
   *   vector's elements must have exactly the same field names. Any mismatch
   *   in in field names results in undefined behavior.
   */
  template <typename T>
  explicit Value(std::vector<T> v) : Value(PrivateConstructor{}, std::move(v)) {
    static_assert(!IsVector<std::decay_t<T>>::value,
                  "vector of vector not allowed. See value.h documentation.");
  }

  /**
   * Constructs an instance from a Spanner STRUCT with a type and values
   * matching the given `std::tuple`.
   *
   * Any STRUCT field may optionally have a name, which is specified as
   * `std::pair<std::string, T>`.
   */
  template <typename... Ts>
  explicit Value(std::tuple<Ts...> tup)
      : Value(PrivateConstructor{}, std::move(tup)) {}

  friend bool operator==(Value const& a, Value const& b);
  friend bool operator!=(Value const& a, Value const& b) { return !(a == b); }

  /**
   * Returns the contained value wrapped in a `google::cloud::StatusOr<T>`.
   *
   * Returns a non-OK status IFF:
   *
   * * The contained value is "null", and `T` is not an `absl::optional`.
   * * There is an error converting the contained value to `T`.
   *
   * @par Example
   *
   * @code
   * spanner::Value v{3.14};
   * StatusOr<double> d = v.get<double>();
   * if (d) {
   *   std::cout << "d=" << *d;
   * }
   *
   * // Now using a "null" std::int64_t
   * v = spanner::MakeNullValue<std::int64_t>();
   * StatusOr<std::int64_t> i = v.get<std::int64_t>();
   * if (!i) {
   *   std::cerr << "Could not get integer: " << i.status();
   * }
   * StatusOr<absl::optional<std::int64_t>> j =
   *     v.get<absl::optional<std::int64_t>>();
   * assert(j.ok());  // Since we know the types match in this example
   * assert(!v->has_value());  // Since we know v was null in this example
   * @endcode
   */
  template <typename T>
  StatusOr<T> get() const& {
    if (!TypeProtoIs(T{}, type_))
      return google::cloud::internal::UnknownError("wrong type",
                                                   GCP_ERROR_INFO());
    if (value_.kind_case() == google::protobuf::Value::kNullValue) {
      if (IsOptional<T>::value) return T{};
      return google::cloud::internal::UnknownError("null value",
                                                   GCP_ERROR_INFO());
    }
    return GetValue(T{}, value_, type_);
  }

  /// @copydoc get()
  template <typename T>
  StatusOr<T> get() && {
    if (!TypeProtoIs(T{}, type_))
      return google::cloud::internal::UnknownError("wrong type",
                                                   GCP_ERROR_INFO());
    if (value_.kind_case() == google::protobuf::Value::kNullValue) {
      if (IsOptional<T>::value) return T{};
      return google::cloud::internal::UnknownError("null value",
                                                   GCP_ERROR_INFO());
    }
    auto tag = T{};  // Works around an odd msvc issue
    return GetValue(std::move(tag), std::move(value_), type_);
  }

  /**
   * Outputs string representation of a given Value to the provided stream.
   *
   * @warning This is intended for debugging and human consumption only, not
   *     machine consumption, as the output format may change without notice.
   *
   * @par Example:
   * @code
   *   spanner::Value v{42};
   *   std::cout << v << "\n";
   * @endcode
   */
  friend std::ostream& operator<<(std::ostream& os, Value const& v);

  /**
   * Prints the same output as `operator<<`.
   *
   * @warning DO NOT CALL. This function will be removed in a future release.
   *     Use `operator<<` instead.
   */
  friend void PrintTo(Value const& v, std::ostream* os) { *os << v; }

 private:
  // Metafunction that returns true if `T` is an `absl::optional<U>`
  template <typename T>
  struct IsOptional : std::false_type {};
  template <typename T>
  struct IsOptional<absl::optional<T>> : std::true_type {};

  // Metafunction that returns true if `T` is a std::vector<U>
  template <typename T>
  struct IsVector : std::false_type {};
  template <typename... Ts>
  struct IsVector<std::vector<Ts...>> : std::true_type {};

  // Tag-dispatch overloads to check if a C++ type matches the type specified
  // by the given `Type` proto.
  static bool TypeProtoIs(bool, google::bigtable::v2::Type const&);
  static bool TypeProtoIs(std::int64_t, google::bigtable::v2::Type const&);
  static bool TypeProtoIs(float, google::bigtable::v2::Type const&);
  static bool TypeProtoIs(double, google::bigtable::v2::Type const&);
  //  static bool TypeProtoIs(Timestamp, google::bigtable::v2::Type const&);
  //  static bool TypeProtoIs(CommitTimestamp, google::bigtable::v2::Type
  //  const&); static bool TypeProtoIs(absl::CivilDay,
  //  google::bigtable::v2::Type const&); static bool TypeProtoIs(Interval,
  //  google::bigtable::v2::Type const&); static bool TypeProtoIs(std::string
  //  const&, google::bigtable::v2::Type const&); static bool TypeProtoIs(Bytes
  //  const&, google::bigtable::v2::Type const&); static bool TypeProtoIs(Json
  //  const&, google::bigtable::v2::Type const&); static bool TypeProtoIs(JsonB
  //  const&, google::bigtable::v2::Type const&); static bool
  //  TypeProtoIs(Numeric const&, google::bigtable::v2::Type const&); static
  //  bool TypeProtoIs(PgNumeric const&, google::bigtable::v2::Type const&);
  //  static bool TypeProtoIs(PgOid const&, google::bigtable::v2::Type const&);
  //  template <typename E>
  //  static bool TypeProtoIs(ProtoEnum<E> const&,
  //                          google::bigtable::v2::Type const& type) {
  //    return type.code() == google::bigtable::v2::TypeCode::ENUM &&
  //           type.proto_type_fqn() == ProtoEnum<E>::TypeName();
  //  }
  //  template <typename M>
  //  static bool TypeProtoIs(ProtoMessage<M> const&,
  //                          google::bigtable::v2::Type const& type) {
  //    return type.code() == google::bigtable::v2::TypeCode::PROTO &&
  //           type.proto_type_fqn() == ProtoMessage<M>::TypeName();
  //  }
  template <typename T>
  static bool TypeProtoIs(absl::optional<T>,
                          google::bigtable::v2::Type const& type) {
    return TypeProtoIs(T{}, type);
  }
  //  template <typename T>
  //  static bool TypeProtoIs(std::vector<T> const&,
  //                          google::bigtable::v2::Type const& type) {
  //    return type.code() == google::bigtable::v2::TypeCode::ARRAY &&
  //           TypeProtoIs(T{}, type.array_element_type());
  //  }
  //  template <typename... Ts>
  //  static bool TypeProtoIs(std::tuple<Ts...> const& tup,
  //                          google::bigtable::v2::Type const& type) {
  //    bool ok = type.code() == google::bigtable::v2::TypeCode::STRUCT;
  //    ok = ok && type.struct_type().fields().size() == sizeof...(Ts);
  //    bigtable_internal::ForEach(tup, IsStructTypeProto{ok, 0},
  //                               type.struct_type());
  //    return ok;
  //  }

  // A functor to be used with internal::ForEach to check if a StructType proto
  // matches the types in a std::tuple.
  //  struct IsStructTypeProto {
  //    bool& ok;
  //    int field;
  //    template <typename T>
  //    void operator()(T const&, google::spanner::v1::StructType const& type) {
  //      ok = ok && TypeProtoIs(T{}, type.fields(field).type());
  //      ++field;
  //    }
  //    template <typename T>
  //    void operator()(std::pair<std::string, T> const&,
  //                    google::spanner::v1::StructType const& type) {
  //      operator()(T{}, type);
  //    }
  //  };

  // Tag-dispatch overloads to convert a C++ type to a `Type` protobuf. The
  // argument type is the tag, the argument value is ignored.
  static google::bigtable::v2::Type MakeTypeProto(bool);
  static google::bigtable::v2::Type MakeTypeProto(std::int64_t);
  static google::bigtable::v2::Type MakeTypeProto(float);
  static google::bigtable::v2::Type MakeTypeProto(double);
  static google::bigtable::v2::Type MakeTypeProto(std::string const&);
  //  static google::bigtable::v2::Type MakeTypeProto(Bytes const&);
  //  static google::bigtable::v2::Type MakeTypeProto(Json const&);
  //  static google::bigtable::v2::Type MakeTypeProto(JsonB const&);
  //  static google::bigtable::v2::Type MakeTypeProto(Numeric const&);
  //  static google::bigtable::v2::Type MakeTypeProto(PgNumeric const&);
  //  static google::bigtable::v2::Type MakeTypeProto(PgOid const&);
  //  static google::bigtable::v2::Type MakeTypeProto(Timestamp);
  //  static google::bigtable::v2::Type MakeTypeProto(CommitTimestamp);
  //  static google::bigtable::v2::Type MakeTypeProto(absl::CivilDay);
  //  static google::bigtable::v2::Type MakeTypeProto(Interval);
  //  template <typename E>
  //  static google::bigtable::v2::Type MakeTypeProto(ProtoEnum<E>) {
  //    google::bigtable::v2::Type t;
  //    t.set_code(google::bigtable::v2::TypeCode::ENUM);
  //    t.set_proto_type_fqn(ProtoEnum<E>::TypeName());
  //    return t;
  //  }
  //  template <typename M>
  //  static google::bigtable::v2::Type MakeTypeProto(ProtoMessage<M>) {
  //    google::bigtable::v2::Type t;
  //    t.set_code(google::bigtable::v2::TypeCode::PROTO);
  //    t.set_proto_type_fqn(ProtoMessage<M>::TypeName());
  //    return t;
  //  }
  static google::bigtable::v2::Type MakeTypeProto(int);
  static google::bigtable::v2::Type MakeTypeProto(char const*);
  template <typename T>
  static google::bigtable::v2::Type MakeTypeProto(absl::optional<T> const&) {
    return MakeTypeProto(T{});
  }
  //  template <typename T>
  //  static google::bigtable::v2::Type MakeTypeProto(std::vector<T> const& v) {
  //    google::bigtable::v2::Type t;
  //    t.set_code(google::bigtable::v2::TypeCode::ARRAY);
  //    *t.mutable_array_element_type() = MakeTypeProto(v.empty() ? T{} : v[0]);
  //    // Checks that vector elements have exactly the same proto Type, which
  //    // includes field names. This is documented UB.
  //    for (auto&& e : v) {
  //      if (!google::protobuf::util::MessageDifferencer::Equals(
  //              MakeTypeProto(e), t.array_element_type())) {
  //        google::cloud::internal::ThrowInvalidArgument("Mismatched types");
  //      }
  //    }
  //    return t;
  //  }
  //  template <typename... Ts>
  //  static google::bigtable::v2::Type MakeTypeProto(
  //      std::tuple<Ts...> const& tup) {
  //    google::bigtable::v2::Type t;
  //    t.set_code(google::bigtable::v2::TypeCode::STRUCT);
  //    bigtable_internal::ForEach(tup, AddStructTypes{},
  //    *t.mutable_struct_type()); return t;
  //  }
  //
  //  // A functor to be used with internal::ForEach to add type protos for all
  //  the
  //  // elements of a tuple.
  //  struct AddStructTypes {
  //    template <typename T>
  //    void operator()(T const& t,
  //                    google::spanner::v1::StructType& struct_type) const {
  //      auto* field = struct_type.add_fields();
  //      *field->mutable_type() = MakeTypeProto(t);
  //    }
  //    template <
  //        typename S, typename T,
  //        std::enable_if_t<std::is_convertible<S, std::string>::value, int> =
  //        0>
  //    void operator()(std::pair<S, T> const& p,
  //                    google::spanner::v1::StructType& struct_type) const {
  //      auto* field = struct_type.add_fields();
  //      field->set_name(p.first);
  //      *field->mutable_type() = MakeTypeProto(p.second);
  //    }
  //  };

  // Encodes the argument as a protobuf according to the rules described in
  // https://github.com/googleapis/googleapis/blob/master/google/spanner/v1/type.proto
  static google::protobuf::Value MakeValueProto(bool b);
  static google::protobuf::Value MakeValueProto(std::int64_t i);
  static google::protobuf::Value MakeValueProto(float f);
  static google::protobuf::Value MakeValueProto(double d);
  static google::protobuf::Value MakeValueProto(std::string s);
  //  static google::protobuf::Value MakeValueProto(Bytes b);
  //  static google::protobuf::Value MakeValueProto(Json j);
  //  static google::protobuf::Value MakeValueProto(JsonB j);
  //  static google::protobuf::Value MakeValueProto(Numeric n);
  //  static google::protobuf::Value MakeValueProto(PgNumeric n);
  //  static google::protobuf::Value MakeValueProto(PgOid n);
  //  static google::protobuf::Value MakeValueProto(Timestamp ts);
  //  static google::protobuf::Value MakeValueProto(CommitTimestamp ts);
  //  static google::protobuf::Value MakeValueProto(absl::CivilDay d);
  //  static google::protobuf::Value MakeValueProto(Interval intvl);
  //  template <typename E>
  //  static google::protobuf::Value MakeValueProto(ProtoEnum<E> e) {
  //    return MakeValueProto(std::int64_t{E{e}});
  //  }
  //  template <typename M>
  //  static google::protobuf::Value MakeValueProto(ProtoMessage<M> m) {
  //    internal::Base64Encoder encoder;
  //    for (auto c : std::string{m}) encoder.PushBack(c);
  //    return MakeValueProto(std::move(encoder).FlushAndPad());
  //  }
  static google::protobuf::Value MakeValueProto(int i);
  static google::protobuf::Value MakeValueProto(char const* s);
  template <typename T>
  static google::protobuf::Value MakeValueProto(absl::optional<T> opt) {
    if (opt.has_value()) return MakeValueProto(*std::move(opt));
    google::protobuf::Value v;
    v.set_null_value(google::protobuf::NullValue::NULL_VALUE);
    return v;
  }
  template <typename T>
  static google::protobuf::Value MakeValueProto(std::vector<T> vec) {
    google::protobuf::Value v;
    auto& list = *v.mutable_list_value();
    for (auto&& e : vec) {
      *list.add_values() = MakeValueProto(std::move(e));
    }
    return v;
  }
  template <typename... Ts>
  static google::protobuf::Value MakeValueProto(std::tuple<Ts...> tup) {
    google::protobuf::Value v;
    bigtable_internal::ForEach(tup, AddStructValues{}, *v.mutable_list_value());
    return v;
  }

  // A functor to be used with internal::ForEach to add Value protos for all
  // the elements of a tuple.
  struct AddStructValues {
    template <typename T>
    void operator()(T& t, google::protobuf::ListValue& list_value) const {
      *list_value.add_values() = MakeValueProto(std::move(t));
    }
    template <
        typename S, typename T,
        std::enable_if_t<std::is_convertible<S, std::string>::value, int> = 0>
    void operator()(std::pair<S, T> p,
                    google::protobuf::ListValue& list_value) const {
      *list_value.add_values() = MakeValueProto(std::move(p.second));
    }
  };

  // Tag-dispatch overloads to extract a C++ value from a `Value` protobuf. The
  // first argument type is the tag, its value is ignored.
  static StatusOr<bool> GetValue(bool, google::protobuf::Value const&,
                                 google::bigtable::v2::Type const&);
  static StatusOr<std::int64_t> GetValue(std::int64_t,
                                         google::protobuf::Value const&,
                                         google::bigtable::v2::Type const&);
  static StatusOr<float> GetValue(float, google::protobuf::Value const&,
                                  google::bigtable::v2::Type const&);
  static StatusOr<double> GetValue(double, google::protobuf::Value const&,
                                   google::bigtable::v2::Type const&);
  static StatusOr<std::string> GetValue(std::string const&,
                                        google::protobuf::Value const&,
                                        google::bigtable::v2::Type const&);
  static StatusOr<std::string> GetValue(std::string const&,
                                        google::protobuf::Value&&,
                                        google::bigtable::v2::Type const&);
  //  static StatusOr<Bytes> GetValue(Bytes const&, google::protobuf::Value
  //  const&,
  //                                  google::bigtable::v2::Type const&);
  //  static StatusOr<Json> GetValue(Json const&, google::protobuf::Value
  //  const&,
  //                                 google::bigtable::v2::Type const&);
  //  static StatusOr<JsonB> GetValue(JsonB const&, google::protobuf::Value
  //  const&,
  //                                  google::bigtable::v2::Type const&);
  //  static StatusOr<Numeric> GetValue(Numeric const&,
  //                                    google::protobuf::Value const&,
  //                                    google::bigtable::v2::Type const&);
  //  static StatusOr<PgNumeric> GetValue(PgNumeric const&,
  //                                      google::protobuf::Value const&,
  //                                      google::bigtable::v2::Type const&);
  //  static StatusOr<PgOid> GetValue(PgOid const&, google::protobuf::Value
  //  const&,
  //                                  google::bigtable::v2::Type const&);
  //  static StatusOr<Timestamp> GetValue(Timestamp, google::protobuf::Value
  //  const&,
  //                                      google::bigtable::v2::Type const&);
  //  static StatusOr<CommitTimestamp> GetValue(CommitTimestamp,
  //                                            google::protobuf::Value const&,
  //                                            google::bigtable::v2::Type
  //                                            const&);
  //  static StatusOr<absl::CivilDay> GetValue(absl::CivilDay,
  //                                           google::protobuf::Value const&,
  //                                           google::bigtable::v2::Type
  //                                           const&);
  //  static StatusOr<Interval> GetValue(Interval, google::protobuf::Value
  //  const&,
  //                                     google::bigtable::v2::Type const&);
  //  template <typename E>
  //  static StatusOr<ProtoEnum<E>> GetValue(ProtoEnum<E>,
  //                                         google::protobuf::Value const& pv,
  //                                         google::bigtable::v2::Type const&
  //                                         pt) {
  //    if (pv.kind_case() != google::protobuf::Value::kStringValue) {
  //      return internal::UnknownError("missing ENUM", GCP_ERROR_INFO());
  //    }
  //    auto value = GetValue(std::int64_t{}, pv, pt);
  //    if (!value) return std::move(value).status();
  //    if (static_cast<typename std::underlying_type_t<E>>(*value) != *value) {
  //      return Status(StatusCode::kUnknown,
  //                    "Value out of range: " + pv.string_value());
  //    }
  //    return ProtoEnum<E>(static_cast<E>(*std::move(value)));
  //  }
  //  template <typename M>
  //  static StatusOr<ProtoMessage<M>> GetValue(ProtoMessage<M>,
  //                                            google::protobuf::Value const&
  //                                            pv, google::bigtable::v2::Type
  //                                            const&) {
  //    if (pv.kind_case() != google::protobuf::Value::kStringValue) {
  //      return internal::UnknownError("missing PROTO", GCP_ERROR_INFO());
  //    }
  //    auto bytes = internal::Base64DecodeToBytes(pv.string_value());
  //    if (!bytes) return std::move(bytes).status();
  //    return ProtoMessage<M>(std::string(bytes->begin(), bytes->end()));
  //  }
  template <typename T, typename V>
  static StatusOr<absl::optional<T>> GetValue(
      absl::optional<T> const&, V&& pv, google::bigtable::v2::Type const& pt) {
    if (pv.kind_case() == google::protobuf::Value::kNullValue) {
      return absl::optional<T>{};
    }
    auto value = GetValue(T{}, std::forward<V>(pv), pt);
    if (!value) return std::move(value).status();
    return absl::optional<T>{*std::move(value)};
  }
  //  template <typename T, typename V>
  //  static StatusOr<std::vector<T>> GetValue(
  //      std::vector<T> const&, V&& pv, google::bigtable::v2::Type const& pt) {
  //    if (pv.kind_case() != google::protobuf::Value::kListValue) {
  //      return internal::UnknownError("missing ARRAY", GCP_ERROR_INFO());
  //    }
  //    std::vector<T> v;
  //    for (int i = 0; i < pv.list_value().values().size(); ++i) {
  //      auto&& e = GetProtoListValueElement(std::forward<V>(pv), i);
  //      using ET = decltype(e);
  //      auto value = GetValue(T{}, std::forward<ET>(e),
  //      pt.array_element_type()); if (!value) return
  //      std::move(value).status(); v.push_back(*std::move(value));
  //    }
  //    return v;
  //  }
  //  template <typename V, typename... Ts>
  //  static StatusOr<std::tuple<Ts...>> GetValue(
  //      std::tuple<Ts...> const&, V&& pv, google::bigtable::v2::Type const&
  //      pt) {
  //    if (pv.kind_case() != google::protobuf::Value::kListValue) {
  //      return internal::UnknownError("missing STRUCT", GCP_ERROR_INFO());
  //    }
  //    std::tuple<Ts...> tup;
  //    Status status;  // OK
  //    ExtractTupleValues<V> f{status, 0, std::forward<V>(pv), pt};
  //    bigtable_internal::ForEach(tup, f);
  //    if (!status.ok()) return status;
  //    return tup;
  //  }

  // A functor to be used with internal::ForEach to extract C++ types from a
  // ListValue proto and store then in a tuple.
  template <typename V>
  struct ExtractTupleValues {
    Status& status;
    int i;
    V&& pv;
    google::bigtable::v2::Type const& type;
    template <typename T>
    void operator()(T& t) {
      auto&& e = GetProtoListValueElement(std::forward<V>(pv), i);
      using ET = decltype(e);
      auto value = GetValue(T{}, std::forward<ET>(e), type);
      ++i;
      if (!value) {
        status = std::move(value).status();
      } else {
        t = *std::move(value);
      }
    }
    //    template <typename T>
    //    void operator()(std::pair<std::string, T>& p) {
    //      p.first = type.struct_type().fields(i).name();
    //      auto&& e = GetProtoListValueElement(std::forward<V>(pv), i);
    //      using ET = decltype(e);
    //      auto value = GetValue(T{}, std::forward<ET>(e), type);
    //      ++i;
    //      if (!value) {
    //        status = std::move(value).status();
    //      } else {
    //        p.second = *std::move(value);
    //      }
    //    }
  };

  // Protocol buffers are not friendly to generic programming, because they use
  // different syntax and different names for mutable and non-mutable
  // functions. To make GetValue(vector<T>, ...) (above) work, we need split
  // the different protobuf syntaxes into overloaded functions.
  static google::protobuf::Value const& GetProtoListValueElement(
      google::protobuf::Value const& pv, int pos) {
    return pv.list_value().values(pos);
  }
  static google::protobuf::Value&& GetProtoListValueElement(
      google::protobuf::Value&& pv, int pos) {
    return std::move(*pv.mutable_list_value()->mutable_values(pos));
  }

  // A private templated constructor that is called by all the public
  // constructors to set the type_ and value_ members. The `PrivateConstructor`
  // type is used so that this overload is never chosen for
  // non-member/non-friend callers. Otherwise, since visibility restrictions
  // apply after overload resolution, users could get weird error messages if
  // this constructor matched their arguments best.
  struct PrivateConstructor {};
  template <typename T>
  Value(PrivateConstructor, T&& t)
      : type_(MakeTypeProto(t)), value_(MakeValueProto(std::forward<T>(t))) {}

  Value(google::bigtable::v2::Type t, google::protobuf::Value v)
      : type_(std::move(t)), value_(std::move(v)) {}

  friend struct bigtable_internal::ValueInternals;

  google::bigtable::v2::Type type_;
  google::protobuf::Value value_;
};

/**
 * Factory to construct a "null" Value of the specified type `T`.
 *
 * This is equivalent to passing an `absl::optional<T>` without a value to
 * the constructor, though this factory may be easier to invoke and result
 * in clearer code at the call site.
 */
template <typename T>
Value MakeNullValue() {
  return Value(absl::optional<T>{});
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace bigtable

namespace bigtable_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

struct ValueInternals {
  static bigtable::Value FromProto(google::bigtable::v2::Type t,
                                   google::protobuf::Value v) {
    return bigtable::Value(std::move(t), std::move(v));
  }

  static std::pair<google::bigtable::v2::Type, google::protobuf::Value> ToProto(
      bigtable::Value v) {
    return std::make_pair(std::move(v.type_), std::move(v.value_));
  }
};

inline bigtable::Value FromProto(google::bigtable::v2::Type t,
                                 google::protobuf::Value v) {
  return ValueInternals::FromProto(std::move(t), std::move(v));
}

inline std::pair<google::bigtable::v2::Type, google::protobuf::Value> ToProto(
    bigtable::Value v) {
  return ValueInternals::ToProto(std::move(v));
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace bigtable_internal

namespace bigtable {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

class QueryRow;

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace bigtable

namespace bigtable_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN
struct RowFriend {
  static bigtable::QueryRow MakeRow(
      std::vector<bigtable::Value>,
      std::shared_ptr<std::vector<std::string> const>);
};
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace bigtable_internal

namespace bigtable {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

class QueryRow {
 public:
  /// Default constructs an empty row with no columns nor values.
  QueryRow();

  /// @name Copy and move.
  ///@{
  QueryRow(QueryRow const&) = default;
  QueryRow& operator=(QueryRow const&) = default;
  QueryRow(QueryRow&&) = default;
  QueryRow& operator=(QueryRow&&) = default;
  ///@}

  /// Returns the number of columns in the row.
  std::size_t size() const { return columns_->size(); }

  /// Returns the column names for the row.
  std::vector<std::string> const& columns() const { return *columns_; }

  /// Returns the `Value` objects in the given row.
  std::vector<Value> const& values() const& { return values_; }

  /// Returns the `Value` objects in the given row.
  std::vector<Value>&& values() && { return std::move(values_); }

  /// Returns the `Value` at the given @p pos.
  StatusOr<Value> get(std::size_t pos) const;

  /// Returns the `Value` in the column with @p name
  StatusOr<Value> get(std::string const& name) const;

  /**
   * Returns the native C++ value at the given position or column name.
   *
   * @tparam T the native C++ type, e.g., std::int64_t or std::string
   * @tparam Arg a deduced parameter convertible to a std::size_t or std::string
   */
  template <typename T, typename Arg>
  StatusOr<T> get(Arg&& arg) const {
    auto v = get(std::forward<Arg>(arg));
    if (v) return v->template get<T>();
    return v.status();
  }

  /**
   * Returns all the native C++ values for the whole row in a `std::tuple` with
   * the specified type.
   *
   * @tparam Tuple the `std::tuple` type that the whole row must unpack into.
   */
  template <typename Tuple>
  StatusOr<Tuple> get() const& {
    if (size() != std::tuple_size<Tuple>::value) {
      auto constexpr kMsg = "Tuple has the wrong number of elements";
      return google::cloud::internal::InvalidArgumentError(kMsg,
                                                           GCP_ERROR_INFO());
    }
    Tuple tup;
    auto it = values_.begin();
    Status status;
    bigtable_internal::ForEach(tup, ExtractValue{status}, it);
    if (!status.ok()) return status;
    return tup;
  }

  /**
   * Returns all the native C++ values for the whole row in a `std::tuple` with
   * the specified type.
   *
   * @tparam Tuple the `std::tuple` type that the whole row must unpack into.
   */
  template <typename Tuple>
  StatusOr<Tuple> get() && {
    if (size() != std::tuple_size<Tuple>::value) {
      auto constexpr kMsg = "Tuple has the wrong number of elements";
      return Status(StatusCode::kInvalidArgument, kMsg);
    }
    Tuple tup;
    auto it = std::make_move_iterator(values_.begin());
    Status status;
    bigtable_internal::ForEach(tup, ExtractValue{status}, it);
    if (!status.ok()) return status;
    return tup;
  }

  /// @name Equality
  ///@{
  friend bool operator==(QueryRow const& a, QueryRow const& b);
  friend bool operator!=(QueryRow const& a, QueryRow const& b) {
    return !(a == b);
  }
  ///@}

 private:
  friend struct bigtable_internal::RowFriend;
  struct ExtractValue {
    Status& status;
    template <typename T, typename It>
    void operator()(T& t, It& it) const {
      auto x = it++->template get<T>();
      if (!x) {
        status = std::move(x).status();
      } else {
        t = *std::move(x);
      }
    }
  };

  /**
   * Constructs a `Row` with the given @p values and @p columns.
   *
   * @note columns must not be nullptr
   * @note columns.size() must equal values.size()
   */
  QueryRow(std::vector<Value> values,
           std::shared_ptr<std::vector<std::string> const> columns);

  std::vector<Value> values_;
  std::shared_ptr<std::vector<std::string> const> columns_;
};

class RowStreamIterator {
 public:
  /**
   * A function that returns a sequence of `StatusOr<Row>` objects. Returning
   * an empty `Row` indicates that there are no more rows to be returned.
   */
  using Source = std::function<StatusOr<QueryRow>()>;

  /// @name Iterator type aliases
  ///@{
  using iterator_category = std::input_iterator_tag;
  using value_type = StatusOr<QueryRow>;
  using difference_type = std::ptrdiff_t;
  using pointer = value_type*;
  using reference = value_type&;
  using const_pointer = value_type const*;
  using const_reference = value_type const&;
  ///@}

  /// Default constructs an "end" iterator.
  RowStreamIterator();

  /**
   * Constructs a `RowStreamIterator` that will consume rows from the given
   * @p source, which must not be `nullptr`.
   */
  explicit RowStreamIterator(Source source);

  reference operator*() { return row_; }
  pointer operator->() { return &row_; }

  const_reference operator*() const { return row_; }
  const_pointer operator->() const { return &row_; }

  RowStreamIterator& operator++();
  RowStreamIterator operator++(int);

  friend bool operator==(RowStreamIterator const&, RowStreamIterator const&);
  friend bool operator!=(RowStreamIterator const&, RowStreamIterator const&);

 private:
  bool row_ok_{true};
  value_type row_{QueryRow{}};
  Source source_;  // nullptr means "end"
};

class ResultSourceInterface {
 public:
  virtual ~ResultSourceInterface() = default;
  virtual StatusOr<bigtable::QueryRow> NextRow() = 0;
  virtual absl::optional<google::bigtable::v2::ResultSetMetadata>
  Metadata() = 0;
};

class RowStream {
 public:
  RowStream() = default;
  explicit RowStream(std::unique_ptr<ResultSourceInterface> source)
      : source_(std::move(source)) {}

  // This class is movable but not copyable.
  RowStream(RowStream&&) = default;
  RowStream& operator=(RowStream&&) = default;

  /// Returns a `RowStreamIterator` defining the beginning of this range.
  RowStreamIterator begin() {
    return RowStreamIterator([this]() mutable { return source_->NextRow(); });
  }

  /// Returns a `RowStreamIterator` defining the end of this range.
  // NOLINTNEXTLINE(readability-convert-member-functions-to-static)
  RowStreamIterator end() { return {}; }

  /// Returns the number of rows modified by a DML statement.
  std::int64_t RowsModified() const;

  /**
   * Retrieves the timestamp at which the read occurred.
   *
   * @note Only available if a read-only transaction was used.
   */
  //  absl::optional<Timestamp> ReadTimestamp() const;

 private:
  std::unique_ptr<ResultSourceInterface> source_;
};

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace bigtable

namespace bigtable_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

struct PartialResultSet {
  // TODO(sdhart): consider refactoring individual metadata and result fields
  //  into variant
  absl::optional<google::bigtable::v2::ResultSetMetadata> metadata;
  absl::optional<google::bigtable::v2::PartialResultSet> results;
  bool resumption;
};

class PartialResultSetReader {
 public:
  virtual ~PartialResultSetReader() = default;
  virtual void TryCancel() = 0;
  virtual absl::optional<PartialResultSet> Read(
      absl::optional<std::string> const& resume_token) = 0;
  virtual Status Finish() = 0;
};

using PartialResultSetReaderFactory =
    std::function<std::unique_ptr<PartialResultSetReader>(std::string)>;

class PartialResultSetResume : public PartialResultSetReader {
 public:
  PartialResultSetResume(
      PartialResultSetReaderFactory factory,
      google::cloud::Idempotency idempotency,
      std::unique_ptr<bigtable::DataRetryPolicy> retry_policy,
      std::unique_ptr<BackoffPolicy> backoff_policy)
      : factory_(std::move(factory)),
        idempotency_(idempotency),
        retry_policy_prototype_(std::move(retry_policy)),
        backoff_policy_prototype_(std::move(backoff_policy)),
        child_(factory_(std::string{})) {}

  ~PartialResultSetResume() override = default;

  void TryCancel() override;
  absl::optional<PartialResultSet> Read(
      absl::optional<std::string> const& resume_token) override;
  Status Finish() override;

 private:
  PartialResultSetReaderFactory factory_;
  google::cloud::Idempotency idempotency_;
  std::unique_ptr<bigtable::DataRetryPolicy> retry_policy_prototype_;
  std::unique_ptr<BackoffPolicy> backoff_policy_prototype_;
  std::unique_ptr<PartialResultSetReader> child_;
  absl::optional<Status> last_status_;
};

class PartialResultSourceInterface : public bigtable::ResultSourceInterface {};

class PartialResultSetSource : public PartialResultSourceInterface {
 public:
  /// Factory method to create a PartialResultSetSource.
  static StatusOr<std::unique_ptr<PartialResultSourceInterface>> Create(
      std::unique_ptr<PartialResultSetReader> reader);

  ~PartialResultSetSource() override;

  StatusOr<bigtable::QueryRow> NextRow() override;

  absl::optional<google::bigtable::v2::ResultSetMetadata> Metadata() override {
    return metadata_;
  }

 private:
  explicit PartialResultSetSource(
      std::unique_ptr<PartialResultSetReader> reader);

  Status ReadFromStream();

  Status ReadResultsFromStream(google::bigtable::v2::PartialResultSet&);

  std::string read_buffer_;

  Options options_;
  std::unique_ptr<PartialResultSetReader> reader_;

  // The `PartialResultSet.metadata` we received in the first response, and
  // the column names it contained (which will be shared between rows).
  absl::optional<google::bigtable::v2::ResultSetMetadata> metadata_;
  std::shared_ptr<std::vector<std::string>> columns_;

  std::deque<bigtable::QueryRow> pending_rows_;
  // `Row`s ready to be returned by `NextRow()`.
  std::deque<bigtable::QueryRow> rows_;

  // When engaged, the token we can use to resume the stream immediately after
  // any data in (or previously in) `rows_`. When disengaged, we have already
  // delivered data that would be replayed, so resumption is disabled until we
  // see a new token.
  absl::optional<std::string> resume_token_ = "";

  // `Value`s that could be combined into `rows_` when we have enough to fill
  // an entire row, plus a token that would resume the stream after such rows.
  google::protobuf::RepeatedPtrField<google::protobuf::Value> values_;

  // Should the space used by `values_` get larger than this limit, we will
  // move complete rows into `rows_` and disable resumption until we see a
  // new token. During this time, an error in the stream will be returned by
  // `NextRow()`. No individual row in a result set can exceed 100 MiB, so we
  // set the default limit to twice that.
  std::size_t values_space_limit_ = 2 * 100 * (std::size_t{1} << 20);

  // `*values_.rbegin()` exists, but it is incomplete. The rest of the value
  // will be sent in subsequent `PartialResultSet` messages.
  bool values_back_incomplete_ = false;

  // The state of our PartialResultSetReader.
  enum : char {
    // `Read()` has yet to return nullopt.
    kReading,
    // `Read()` has returned nullopt, but we are yet to call `Finish()`.
    kEndOfStream,
    // `Finish()` has been called, which means `NextRow()` has returned
    // either an empty row or an error status.
    kFinished,
  } state_ = kReading;
};

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace bigtable_internal

namespace bigtable {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

/**
 * Represents a potentially parameterized SQL statement.
 *
 * Details on case sensitivity for SQL statements and string values can be
 * found here: [Case
 * Sensitivity](https://cloud.google.com/spanner/docs/lexical#case-sensitivity)
 *
 * @note `SqlStatement` equality comparisons are case-sensitive.
 *
 * Parameter placeholders are specified by `@<param name>` in the SQL string.
 * Values for parameters are a collection of `std::pair<std::string const,
 * google::cloud:spanner::Value>`.
 * @par Example
 * @snippet samples.cc spanner-sql-statement-params
 */
class SqlStatement {
 public:
  /// Type alias for parameter collection.
  using ParamType = std::unordered_map<std::string, Value>;

  SqlStatement() = default;
  /// Constructs a SqlStatement without parameters.
  explicit SqlStatement(std::string statement)
      : statement_(std::move(statement)) {}
  /// Constructs a SqlStatement with specified parameters.
  SqlStatement(std::string statement, ParamType params)
      : statement_(std::move(statement)), params_(std::move(params)) {}

  /// Copy and move.
  SqlStatement(SqlStatement const&) = default;
  SqlStatement(SqlStatement&&) = default;
  SqlStatement& operator=(SqlStatement const&) = default;
  SqlStatement& operator=(SqlStatement&&) = default;

  /**
   * Returns the SQL statement.
   * No parameter substitution is performed in the statement string.
   */
  std::string const& sql() const { return statement_; }

  /**
   * Returns the collection of parameters.
   * @return If no parameters were specified, the container will be empty.
   */
  ParamType const& params() const { return params_; }

  /**
   * Returns the names of all the parameters.
   */
  std::vector<std::string> ParameterNames() const;

  /**
   * Returns the value of the requested parameter.
   * @param parameter_name name of requested parameter.
   * @return `StatusCode::kNotFound` returned for invalid names.
   */
  google::cloud::StatusOr<Value> GetParameter(
      std::string const& parameter_name) const;

  friend bool operator==(SqlStatement const& a, SqlStatement const& b) {
    return a.statement_ == b.statement_ && a.params_ == b.params_;
  }
  friend bool operator!=(SqlStatement const& a, SqlStatement const& b) {
    return !(a == b);
  }

  /**
   * Outputs a string representation of the given @p stmt to the given @p os.
   *
   * @warning This is intended for debugging and human consumption only, not
   *     machine consumption, as the output format may change without notice.
   */
  friend std::ostream& operator<<(std::ostream& os, SqlStatement const& stmt);

 private:
  std::string statement_;
  ParamType params_;
};

class BoundQuery {
 public:
 private:
};

class PreparedQuery {
 public:
  StatusOr<BoundQuery> Bind() { return BoundQuery{}; }

 private:
};

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace bigtable
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_BIGTABLE_QUERY_H

// Copyright 2024 Google LLC
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

#ifndef GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_REPEATED_FIELD_H
#define GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_REPEATED_FIELD_H

#include "google/cloud/status_or.h"
#include "google/cloud/version.h"
#include "absl/base/attributes.h"
#include "absl/types/variant.h"
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/repeated_ptr_field.h>

namespace google {
namespace cloud {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

namespace internal {
template <typename Element>
class RepeatedIterator;

template <typename It>
class RepeatedPtrIterator;
}  // namespace internal

template <typename Element>
class RepeatedField {
 public:
  RepeatedField(google::protobuf::RepeatedField<Element>& repeated_field)
      : repeated_field_(std::move(repeated_field)) {}

  using reference = Element&;
  using const_reference = Element const&;
  using iterator = internal::RepeatedIterator<Element>;
  using const_iterator = internal::RepeatedIterator<Element const>;

  bool empty() const;
  int size() const;

  const_reference operator[](int index) const ABSL_ATTRIBUTE_LIFETIME_BOUND;
  reference operator[](int index) ABSL_ATTRIBUTE_LIFETIME_BOUND;

  iterator begin() ABSL_ATTRIBUTE_LIFETIME_BOUND;
  const_iterator begin() const ABSL_ATTRIBUTE_LIFETIME_BOUND;
  const_iterator cbegin() const ABSL_ATTRIBUTE_LIFETIME_BOUND;
  iterator end() ABSL_ATTRIBUTE_LIFETIME_BOUND;
  const_iterator end() const ABSL_ATTRIBUTE_LIFETIME_BOUND;
  const_iterator cend() const ABSL_ATTRIBUTE_LIFETIME_BOUND;

 private:
  google::protobuf::RepeatedField<Element>& repeated_field_;
};

template <typename Element>
class RepeatedPtrField {
 public:
  RepeatedPtrField(google::protobuf::RepeatedPtrField<Element>& repeated_field)
      : repeated_field_(std::move(repeated_field)) {}

 private:
  google::protobuf::RepeatedPtrField<Element>& repeated_field_;
};

// STL-like iterator implementation for RepeatedField.  You should not
// refer to this class directly; use RepeatedField<T>::iterator instead.
namespace internal {
template <typename Element>
class RepeatedIterator {
 private:
  using traits =
      std::iterator_traits<typename std::remove_const<Element>::type*>;

 public:
  // Note: value_type is never cv-qualified.
  using value_type = typename traits::value_type;
  using difference_type = typename traits::difference_type;
  using pointer = Element*;
  using reference = Element&;
  using iterator_category = typename traits::iterator_category;
  //  using iterator_concept = typename IteratorConceptSupport<traits>::tag;

  constexpr RepeatedIterator() noexcept : it_(nullptr) {}

  // Allows "upcasting" from RepeatedIterator<T**> to
  // RepeatedIterator<const T*const*>.
  template <typename OtherElement,
            typename std::enable_if<std::is_convertible<
                OtherElement*, pointer>::value>::type* = nullptr>
  constexpr RepeatedIterator(RepeatedIterator<OtherElement>& other) noexcept
      : it_(other.it_) {}

  // dereferenceable
  constexpr reference operator*() const noexcept { return *it_; }
  constexpr pointer operator->() const noexcept { return it_; }

 private:
  // Helper alias to hide the internal type.
  using iterator = RepeatedIterator<Element>;

 public:
  // {inc,dec}rementable
  iterator& operator++() noexcept {
    ++it_;
    return *this;
  }
  iterator operator++(int) noexcept { return iterator(it_++); }
  iterator& operator--() noexcept {
    --it_;
    return *this;
  }
  iterator operator--(int) noexcept { return iterator(it_--); }

  // equality_comparable
  friend constexpr bool operator==(iterator& x, iterator& y) noexcept {
    return x.it_ == y.it_;
  }
  friend constexpr bool operator!=(iterator& x, iterator& y) noexcept {
    return x.it_ != y.it_;
  }

  // less_than_comparable
  friend constexpr bool operator<(iterator& x, iterator& y) noexcept {
    return x.it_ < y.it_;
  }
  friend constexpr bool operator<=(iterator& x, iterator& y) noexcept {
    return x.it_ <= y.it_;
  }
  friend constexpr bool operator>(iterator& x, iterator& y) noexcept {
    return x.it_ > y.it_;
  }
  friend constexpr bool operator>=(iterator& x, iterator& y) noexcept {
    return x.it_ >= y.it_;
  }

  // addable, subtractable
  iterator& operator+=(difference_type d) noexcept {
    it_ += d;
    return *this;
  }
  constexpr iterator operator+(difference_type d) const noexcept {
    return iterator(it_ + d);
  }
  friend constexpr iterator operator+(difference_type d, iterator it) noexcept {
    return it + d;
  }

  iterator& operator-=(difference_type d) noexcept {
    it_ -= d;
    return *this;
  }
  iterator constexpr operator-(difference_type d) const noexcept {
    return iterator(it_ - d);
  }

  // indexable
  constexpr reference operator[](difference_type d) const noexcept {
    return it_[d];
  }

  // random access iterator
  friend constexpr difference_type operator-(iterator it1,
                                             iterator it2) noexcept {
    return it1.it_ - it2.it_;
  }

 private:
  template <typename OtherElement>
  friend class RepeatedIterator;

  // Allow construction from RepeatedField.
  friend class RepeatedField<value_type>;
  explicit RepeatedIterator(pointer it) noexcept : it_(it) {}

  // The internal iterator.
  pointer it_;
};

template <typename Element>
class RepeatedPtrIterator {
 public:
  using iterator = RepeatedPtrIterator<Element>;
  using iterator_category = std::random_access_iterator_tag;
  using value_type = typename std::remove_const<Element>::type;
  using difference_type = std::ptrdiff_t;
  using pointer = Element*;
  using reference = Element&;

  RepeatedPtrIterator() : it_(nullptr) {}
  explicit RepeatedPtrIterator(void* const* it) : it_(it) {}

  // Allows "upcasting" from RepeatedPtrIterator<T**> to
  // RepeatedPtrIterator<const T*const*>.
  template <typename OtherElement,
            typename std::enable_if<std::is_convertible<
                OtherElement*, pointer>::value>::type* = nullptr>
  RepeatedPtrIterator(RepeatedPtrIterator<OtherElement> const& other)
      : it_(other.it_) {}

  // dereferenceable
  reference operator*() const { return *reinterpret_cast<Element*>(*it_); }
  pointer operator->() const { return &(operator*()); }

  // {inc,dec}rementable
  iterator& operator++() {
    ++it_;
    return *this;
  }
  iterator operator++(int) { return iterator(it_++); }
  iterator& operator--() {
    --it_;
    return *this;
  }
  iterator operator--(int) { return iterator(it_--); }

  // equality_comparable
  friend bool operator==(iterator const& x, iterator const& y) {
    return x.it_ == y.it_;
  }
  friend bool operator!=(iterator const& x, iterator const& y) {
    return x.it_ != y.it_;
  }

  // less_than_comparable
  friend bool operator<(iterator const& x, iterator const& y) {
    return x.it_ < y.it_;
  }
  friend bool operator<=(iterator const& x, iterator const& y) {
    return x.it_ <= y.it_;
  }
  friend bool operator>(iterator const& x, iterator const& y) {
    return x.it_ > y.it_;
  }
  friend bool operator>=(iterator const& x, iterator const& y) {
    return x.it_ >= y.it_;
  }

  // addable, subtractable
  iterator& operator+=(difference_type d) {
    it_ += d;
    return *this;
  }
  friend iterator operator+(iterator it, difference_type const d) {
    it += d;
    return it;
  }
  friend iterator operator+(difference_type const d, iterator it) {
    it += d;
    return it;
  }
  iterator& operator-=(difference_type d) {
    it_ -= d;
    return *this;
  }
  friend iterator operator-(iterator it, difference_type d) {
    it -= d;
    return it;
  }

  // indexable
  reference operator[](difference_type d) const { return *(*this + d); }

  // random access iterator
  friend difference_type operator-(iterator it1, iterator it2) {
    return it1.it_ - it2.it_;
  }

 private:
  template <typename OtherElement>
  friend class RepeatedPtrIterator;

  // The internal iterator.
  void* const* it_;
};

}  // namespace internal

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_REPEATED_FIELD_H

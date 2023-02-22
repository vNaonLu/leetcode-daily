#ifndef LEETCODE_LEETCODE_HELPER_H_
#define LEETCODE_LEETCODE_HELPER_H_

#include <cassert>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <unordered_set>

#define LCD_INLINE_VARIABLE inline static

namespace lcd {

template <typename T>
class AllocationCounted;

} // namespace lcd

namespace lcd {

template <typename T>
using Optional = std::optional<T>;

LCD_INLINE_VARIABLE constexpr Optional<int32_t> null = std::nullopt;

template <typename T>
class AllocationCounted {
public:
  AllocationCounted() noexcept;

  virtual ~AllocationCounted() noexcept;

  static size_t CheckRemainRefs() noexcept;

  template <typename S>
  static bool CheckValid(S *node) noexcept;

  template <typename S, typename... Ss>
  requires std::derived_from<S, AllocationCounted<S>>
  static void Release(S *node, Ss... nodes) noexcept;

  static void Release() noexcept;

private:
  LCD_INLINE_VARIABLE std::unordered_set<void *> static_record_;
};

template <typename T>
inline AllocationCounted<T>::AllocationCounted() noexcept {
  if (!static_record_.emplace(reinterpret_cast<void *>(this)).second) {
    assert(false);
  }
}

template <typename T>
inline AllocationCounted<T>::~AllocationCounted() noexcept {
  if (static_record_.erase(reinterpret_cast<void *>(this)) == 0) {
    assert(false);
  }
}

template <typename T>
inline size_t AllocationCounted<T>::CheckRemainRefs() noexcept {
  return static_record_.size();
}

template <typename T>
template <typename S>
inline bool AllocationCounted<T>::CheckValid(S *node) noexcept {
  return static_record_.count(reinterpret_cast<void *>(node));
}

template <typename T>
template <typename S, typename... Ss>
requires std::derived_from<S, AllocationCounted<S>>
inline void AllocationCounted<T>::Release(S *node, Ss... nodes) noexcept {
  std::vector<S *> children = static_cast<S *>(node)->GetChildren();
  if (static_record_.count(reinterpret_cast<void *>(node))) {
    delete node;
  }
  for (auto *ptr : children) {
    if (static_record_.count(reinterpret_cast<void *>(ptr))) {
      delete ptr;
    }
  }
  Release(nodes...);
}

template <typename T>
inline void AllocationCounted<T>::Release() noexcept {
  // just do nothing
}

} // namespace lcd

#endif // LEETCODE_LEETCODE_HELPER_H_

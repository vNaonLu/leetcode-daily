#ifndef LEETCODE_LEETCODE_HELPER_H_
#define LEETCODE_LEETCODE_HELPER_H_

#include <cassert>
#include <concepts>
#include <cstdint>
#include <optional>
#include <unordered_set>

#define LCD_INLINE_VARIABLE inline static

namespace lcd {

template <typename T>
class MemoryChecker;

} // namespace lcd

namespace lcd {

template <typename T>
using Optional = std::optional<T>;

LCD_INLINE_VARIABLE constexpr Optional<int32_t> null = std::nullopt;


template <typename T>
class MemoryChecker {
public:
  MemoryChecker() noexcept;

  virtual ~MemoryChecker() noexcept;

  static bool CheckLeak() noexcept;

  template <typename S, typename... Ss>
  requires std::derived_from<S, MemoryChecker<S>>
  static void Release(S *node, Ss... nodes) noexcept;

  static void Release() noexcept;

private:
  LCD_INLINE_VARIABLE std::unordered_set<void *> static_record_;
};

template <typename T>
inline MemoryChecker<T>::MemoryChecker() noexcept {
  if (!static_record_.emplace(reinterpret_cast<void *>(this)).second) {
    assert(false);
  }
}

template <typename T>
inline MemoryChecker<T>::~MemoryChecker() noexcept {
  if (static_record_.erase(reinterpret_cast<void *>(this)) == 0) {
    assert(false);
  }
}

template <typename T>
inline bool MemoryChecker<T>::CheckLeak() noexcept {
  return !static_record_.empty();
}

template <typename T>
template <typename S, typename... Ss>
requires std::derived_from<S, MemoryChecker<S>>
inline void MemoryChecker<T>::Release(S *node, Ss... nodes) noexcept {
  std::vector<S *> children = static_cast<S *>(node)->GetChildren();
  if (static_record_.erase(reinterpret_cast<void *>(node))) {
    delete node;
  }
  for (auto *ptr : children) {
    if (static_record_.erase(reinterpret_cast<void *>(ptr))) {
      delete ptr;
    }
  }
  Release(nodes...);
}

template <typename T>
inline void MemoryChecker<T>::Release() noexcept {
  // just do nothing
}

} // namespace lcd

#endif // LEETCODE_LEETCODE_HELPER_H_

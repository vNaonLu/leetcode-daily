#ifndef LEETCODE_CONCEPTS_H_
#define LEETCODE_CONCEPTS_H_

#include <concepts>
#include <limits>
#include <type_traits>
#include <vector>

namespace lcd {
template <typename T, typename U>
concept IsSameAs = std::is_same_v<T, U>;

template <typename T>
concept Sortable = requires(T item, typename T::value_type val) {
                     item.begin();
                     item.end();
                     { val < val } -> IsSameAs<bool>;
                   };

template <typename T>
concept LCDNodeType = requires(T object, size_t idx) {
                        { object->GetChild(idx) } -> IsSameAs<T>;
                        { object->GetChildren() } -> IsSameAs<std::vector<T>>;
                      };
} // namespace lcd

#endif // LEETCODE_CONCEPTS_H_
#ifndef TESTING_TEST_HELPER_H_
#define TESTING_TEST_HELPER_H_

#include "gtest/gtest.h"
#include <concepts>
#include <type_traits>

namespace lcd {
class TreeNode;
class ListNode;

namespace detail {

template <typename T, typename U>
concept IsSameAs = std::is_same_v<T, U>;

template <typename T>
concept Sortable = requires(T item, typename T::value_type val) {
                     item.begin();
                     item.end();
                     { val < val } -> IsSameAs<bool>;
                   };
} // namespace detail

void CompareTreeNodePtr(TreeNode const *tree_node_1,
                        TreeNode const *tree_node_2, bool result) noexcept;

void CompareLiseNodePtr(ListNode const *list_node_1,
                        ListNode const *list_node_2, bool result) noexcept;

template <size_t kDepth, detail::Sortable T>
void CompareInAnyOrder(T expect, T actual) noexcept;

} // namespace lcd

#define EXPECT_TREENODE_EQ(tree_node_1, tree_node_2)                           \
  ::lcd::CompareTreeNodePtr(tree_node_1, tree_node_2, true)
#define EXPECT_TREENODE_NE(tree_node_1, tree_node_2)                           \
  ::lcd::CompareTreeNodePtr(tree_node_1, tree_node_2, false)

#define EXPECT_LISTNODE_EQ(list_node_1, list_node_2)                           \
  ::lcd::CompareLiseNodePtr(list_node_1, list_node_2, true)
#define EXPECT_LISTNODE_NE(list_node_1, list_node_2)                           \
  ::lcd::CompareLiseNodePtr(list_node_1, list_node_2, false)

#define EXPECT_ANYORDER_EQ(expect, actual) CompareInAnyOrder<0>(expect, actual)
#define EXPECT_ANYORDER_WITH_DEPTH_EQ(depth, expect, actual)                   \
  CompareInAnyOrder<depth>(expect, actual)

namespace lcd {

namespace detail {

template <size_t kDepth, Sortable T>
void SortItem(T *item) {
  if constexpr (kDepth > 0) {
    for (typename T::value_type &item_in_item : *item) {
      SortItem<kDepth - 1>(&item_in_item);
    }
  }
  std::sort(item->begin(), item->end());
}

} // namespace detail

template <size_t kDepth, detail::Sortable T>
void CompareInAnyOrder(T expect, T actual) noexcept {
  detail::SortItem<kDepth>(&expect);
  detail::SortItem<kDepth>(&actual);
  EXPECT_EQ(expect, actual);
}

} // namespace lcd

#endif // TESTING_TEST_HELPER_H_

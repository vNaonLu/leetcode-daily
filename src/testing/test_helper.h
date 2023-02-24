#ifndef TESTING_TEST_HELPER_H_
#define TESTING_TEST_HELPER_H_

#include "gtest/gtest.h"

namespace lcd {
class TreeNode;
class ListNode;

void CompareTreeNodePtr(TreeNode const *tree_node_1,
                        TreeNode const *tree_node_2) noexcept;

void CompareLiseNodePtr(ListNode const *list_node_1,
                        ListNode const *list_node_2) noexcept;
} // namespace lcd

#define EXPECT_TREENODE_EQ(tree_node_1, tree_node_2)                           \
  ::lcd::CompareTreeNodePtr(tree_node_1, tree_node_2)

#define EXPECT_LISTNODE_EQ(list_node_1, list_node_2)                           \
  ::lcd::CompareLiseNodePtr(list_node_1, list_node_2)

#endif // TESTING_TEST_HELPER_H_

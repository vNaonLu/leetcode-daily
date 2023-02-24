#include "testing/test_helper.h"
#include "leetcode/list_node.h"
#include "leetcode/tree_node.h"

namespace lcd {

void CompareTreeNodePtr(TreeNode const *tree_node_1,
                        TreeNode const *tree_node_2) noexcept {
  // check whether nodes are both nullptr or not.
  ASSERT_EQ(!tree_node_1, !tree_node_2);
  // if passed the pointer check, check their value.
  if (tree_node_1 && tree_node_2) {
    EXPECT_EQ(*tree_node_1, *tree_node_2);
  }
}

void CompareLiseNodePtr(ListNode const *list_node_1,
                        ListNode const *list_node_2) noexcept {
  // check whether nodes are both nullptr or not.
  ASSERT_EQ(!list_node_1, !list_node_2);
  // if passed the pointer check, check their value.
  if (list_node_1 && list_node_2) {
    EXPECT_EQ(*list_node_1, *list_node_2);
  }
}

} // namespace lcd

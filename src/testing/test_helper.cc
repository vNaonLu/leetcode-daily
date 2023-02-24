#include "testing/test_helper.h"
#include "leetcode/list_node.h"
#include "leetcode/tree_node.h"

namespace lcd {

namespace detail {

template <typename T>
void ExpectNodesEqual(T const *expect, T const *actual) {
  // check whether nodes are both nullptr or not.
  ASSERT_EQ(!expect, !actual);
  // if passed the pointer check, check their value.
  if (expect && actual) {
    EXPECT_EQ(*expect, *actual);
  }
}

template <typename T>
void ExpectNodesNotEqual(T const *expect, T const *actual) {
  // if passed the pointer check, check their value.
  if (expect && actual) {
    EXPECT_NE(*expect, *actual);
  }
}

} // namespace detail

void CompareTreeNodePtr(TreeNode const *expect, TreeNode const *actual,
                        bool result) noexcept {
  if (result) {
    detail::ExpectNodesEqual(expect, actual);
  } else {
    detail::ExpectNodesNotEqual(expect, actual);
  }
}

void CompareLiseNodePtr(ListNode const *expect, ListNode const *actual,
                        bool result) noexcept {
  if (result) {
    detail::ExpectNodesEqual(expect, actual);
  } else {
    detail::ExpectNodesNotEqual(expect, actual);
  }
}

} // namespace lcd

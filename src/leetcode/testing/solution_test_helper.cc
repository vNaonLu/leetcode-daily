#include "leetcode/testing/solution_test_helper.h"
#include "leetcode/list_node.h"
#include "leetcode/tree_node.h"

namespace lcd {

namespace detail {

int PopCount(size_t x) {
  int count = 0;
  while (x != 0) {
    if (x & 1) {
      ++count;
    }
    x >>= 1;
  }
  return count;
}

int SolutionDelegate::operator()() {
  Run();
  return 0;
}

void SolutionFixture::SetUp() {
  TreeNode::ReleaseAll();
  ASSERT_EQ(TreeNode::CheckRemainRefs(), 0);
  ListNode::ReleaseAll();
  ASSERT_EQ(ListNode::CheckRemainRefs(), 0);
}

void SolutionFixture::TearDown() {
  EXPECT_EQ(TreeNode::CheckRemainRefs(), 0) << "Dangling TreeNode(s) found.";
  TreeNode::ReleaseAll();
  EXPECT_EQ(ListNode::CheckRemainRefs(), 0) << "Dangling ListNode(s) found.";
  ListNode::ReleaseAll();
}

} // namespace detail

} // namespace lcd
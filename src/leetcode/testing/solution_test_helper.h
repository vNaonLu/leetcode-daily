#ifndef LEETCODE_TESTING_SOLUTION_HELPER_H_
#define LEETCODE_TESTING_SOLUTION_HELPER_H_

#include "leetcode/testing/test_helper.h"
#include "gtest/gtest.h"
#include <memory>

namespace lcd {

namespace detail {

class SolutionWrapper : public ::testing::Test {
private:
  void SetUp() override {
#ifdef LEETCODE_TREE_NODE_H_
    TreeNode::ReleaseAll();
    ASSERT_EQ(TreeNode::CheckRemainRefs(), 0);
#endif
#ifdef LEETCODE_LIST_NODE_H_
    ListNode::ReleaseAll();
    ASSERT_EQ(ListNode::CheckRemainRefs(), 0);
#endif
  }

  void TearDown() override {
#ifdef LEETCODE_TREE_NODE_H_
    EXPECT_EQ(TreeNode::CheckRemainRefs(), 0);
    TreeNode::ReleaseAll();
#endif
#ifdef LEETCODE_LIST_NODE_H_
    EXPECT_EQ(ListNode::CheckRemainRefs(), 0);
    ListNode::ReleaseAll();
#endif
  }
};

} // namespace detail

} // namespace lcd

#define SOLUTION_BEGIN(solution_id, solution_class)                            \
  class solution_id : public ::lcd::detail::SolutionWrapper {                  \
  protected:                                                                   \
    class solution_class

#define SOLUTION_END(solution_id, solution_class)                              \
  template <typename... ArgTypes>                                              \
  std::unique_ptr<solution_class> Get##solution_class(ArgTypes &&...args) {    \
    return std::make_unique<solution_class>(std::forward<ArgTypes>(args)...);  \
  }                                                                            \
  }

#define SOLUTION_TESTCASE(solution_id, test_name) TEST_F(solution_id, test_name)

#endif // TESTING_SOLUTION_HELPER_H_

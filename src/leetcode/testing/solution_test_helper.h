#ifndef LEETCODE_TESTING_SOLUTION_HELPER_H_
#define LEETCODE_TESTING_SOLUTION_HELPER_H_

#include "leetcode/testing/test_helper.h"
#include "gtest/gtest.h"
#include <memory>

namespace lcd {

namespace detail {

class SolutionFixture : public ::testing::Test {
protected:
  virtual void SolutionSetUp() {}
  virtual void SolutionTearDown() {}

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
    SolutionSetUp();
  }

  void TearDown() override {
    SolutionTearDown();
#ifdef LEETCODE_TREE_NODE_H_
    EXPECT_EQ(TreeNode::CheckRemainRefs(), 0) << "Dangling TreeNode(s) found.";
    TreeNode::ReleaseAll();
#endif
#ifdef LEETCODE_LIST_NODE_H_
    EXPECT_EQ(ListNode::CheckRemainRefs(), 0) << "Dangling ListNode(s) found.";
    ListNode::ReleaseAll();
#endif
  }
};

} // namespace detail

} // namespace lcd

#define _LEETCODE_UNITTEST_FIXTURE_NAME(id, name) q##id##_##name

#define LEETCODE_BEGIN_RESOLVING(id, name, solve_class)                        \
  class _LEETCODE_UNITTEST_FIXTURE_NAME(id, name)                              \
      : public ::lcd::detail::SolutionFixture {                                \
  protected:                                                                   \
    class solve_class

#define LEETCODE_END_RESOLVING(solve_class)                                    \
  template <typename... ArgsType>                                              \
  std::unique_ptr<solve_class> Make##solve_class(ArgsType &&...args) {         \
    return std::make_unique<solve_class>(std::forward<ArgsType>(args)...);     \
  }                                                                            \
  }

#define LEETCODE_SOLUTION_UNITTEST(id, name, suite_name)                       \
  TEST_F(_LEETCODE_UNITTEST_FIXTURE_NAME(id, name), suite_name)

#endif // TESTING_SOLUTION_HELPER_H_

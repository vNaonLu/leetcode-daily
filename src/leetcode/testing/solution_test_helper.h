#ifndef LEETCODE_TESTING_SOLUTION_HELPER_H_
#define LEETCODE_TESTING_SOLUTION_HELPER_H_

#include "leetcode/testing/test_helper.h"
#include "gtest/gtest.h"
#include <chrono>
#include <functional>
#include <future>
#include <memory>
#include <thread>

namespace lcd {

namespace detail {

inline int PopCount(size_t x) {
  int count = 0;
  while (x != 0) {
    if (x & 1) {
      ++count;
    }
    x >>= 1;
  }
  return count;
}

class SolutionDelegate {
public:
  virtual void Run() = 0;
  int          operator()() {
    Run();
    return 0;
  }
};

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

#define _LEETCODE_SOLUTION_UNITTEST_DELEGATE_NAME(id, name, suite_name)        \
  q##id##_##name_##suite_name##_delegate

#define LEETCODE_BEGIN_RESOLVING(id, name, solve_class)                        \
  class _LEETCODE_UNITTEST_FIXTURE_NAME(id, name)                              \
      : public ::lcd::detail::SolutionFixture {                                \
  public:                                                                      \
    class __Delegate;                                                          \
                                                                               \
    class __Delegate : public ::lcd::detail::SolutionDelegate {                \
    protected:                                                                 \
      class solve_class;                                                       \
      template <typename... ArgsType>                                          \
      std::unique_ptr<solve_class> Make##solve_class(ArgsType &&...args) {     \
        return std::make_unique<solve_class>(std::forward<ArgsType>(args)...); \
      }

#define LEETCODE_END_RESOLVING(solve_class)                                    \
  }                                                                            \
  ;                                                                            \
  }

#define LEETCODE_SOLUTION_UNITTEST_WITH_TIMED_OUT(id, name, suite_name, time)  \
  class _LEETCODE_SOLUTION_UNITTEST_DELEGATE_NAME(id, name, suite_name)        \
      : public _LEETCODE_UNITTEST_FIXTURE_NAME(id, name)::__Delegate {         \
  protected:                                                                   \
    void Run() override;                                                       \
  };                                                                           \
  TEST_F(_LEETCODE_UNITTEST_FIXTURE_NAME(id, name), suite_name) {              \
    auto delegate =                                                            \
        std::make_unique<_LEETCODE_SOLUTION_UNITTEST_DELEGATE_NAME(            \
            id, name, suite_name)>();                                          \
    std::future<int> timeout =                                                 \
        std::async(std::launch::async,                                         \
                   &_LEETCODE_SOLUTION_UNITTEST_DELEGATE_NAME(                 \
                       id, name, suite_name)::operator(),                      \
                   *delegate);                                                 \
    if (timeout.wait_for(std::chrono::milliseconds(time)) !=                   \
        std::future_status::ready) {                                           \
      FAIL() << "q" << #id << "_" << #name << "." << #suite_name               \
             << " exceeded the time limit: " << #time << "ms";                 \
    }                                                                          \
  }                                                                            \
  void _LEETCODE_SOLUTION_UNITTEST_DELEGATE_NAME(id, name, suite_name)::Run()

#define LEETCODE_SOLUTION_UNITTEST(id, name, suite_name)                       \
  LEETCODE_SOLUTION_UNITTEST_WITH_TIMED_OUT(id, name, suite_name, 1000)

#ifndef __GNUG__

#define __builtin_popcount(x) lcd::detail::PopCount(x)

#define __builtin_popcountll(x) lcd::detail::PopCount(x)

#endif

#endif // TESTING_SOLUTION_HELPER_H_

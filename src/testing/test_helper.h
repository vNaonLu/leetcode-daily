#ifndef TESTING_TEST_HELPER_H_
#define TESTING_TEST_HELPER_H_

#include "gtest/gtest.h"
#include <concepts>
#include <gtest/gtest-printers.h>
#include <gtest/internal/gtest-internal.h>
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

template <size_t kDepth, detail::Sortable T>
bool CompareInAnyOrder(T expect, T actual) noexcept;

template <size_t kDepth, detail::Sortable T, bool Equal>
testing::AssertionResult AssertCompareInAnyOrder(const char *m_expr,
                                                 const char *n_expr, T const &m,
                                                 T const &n) noexcept;

template <typename T>
bool LCDNodeCheck(T const *node_1, T const *node_2) noexcept;

template <typename T, bool Equal>
testing::AssertionResult AssertLCDNodeCheck(const char *m_expr,
                                            const char *n_expr, T const *m,
                                            T const *n) noexcept;

} // namespace lcd

#define EXPECT_TREENODE_EQ(node_1, node_2)                                     \
  EXPECT_PRED_FORMAT2((AssertLCDNodeCheck<::lcd::TreeNode, true>), node_1,     \
                      node_2)
#define EXPECT_TREENODE_NE(node_1, node_2)                                     \
  EXPECT_PRED_FORMAT2((AssertLCDNodeCheck<::lcd::TreeNode, false>), node_1,    \
                      node_2)

#define EXPECT_LISTNODE_EQ(node_1, node_2)                                     \
  EXPECT_PRED_FORMAT2((AssertLCDNodeCheck<::lcd::ListNode, true>), node_1,     \
                      node_2)
#define EXPECT_LISTNODE_NE(node_1, node_2)                                     \
  EXPECT_PRED_FORMAT2((AssertLCDNodeCheck<::lcd::ListNode, false>), node_1,    \
                      node_2)

#define EXPECT_ANYORDER_EQ(expect, actual)                                     \
  EXPECT_PRED_FORMAT2((AssertCompareInAnyOrder<0, decltype(expect), true>),    \
                      expect, actual)
#define EXPECT_ANYORDER_WITH_DEPTH_EQ(depth, expect, actual)                   \
  EXPECT_PRED_FORMAT2(                                                         \
      (AssertCompareInAnyOrder<depth, decltype(expect), true>), expect,        \
      actual)

namespace lcd {

namespace detail {

template <size_t kDepth, Sortable T>
inline void SortItem(T *item) {
  if constexpr (kDepth > 0) {
    for (typename T::value_type &item_in_item : *item) {
      SortItem<kDepth - 1>(&item_in_item);
    }
  }
  std::sort(item->begin(), item->end());
}

} // namespace detail

template <size_t kDepth, detail::Sortable T>
inline bool CompareInAnyOrder(T expect, T actual) noexcept {
  detail::SortItem<kDepth>(&expect);
  detail::SortItem<kDepth>(&actual);
  return expect == actual;
}

template <size_t kDepth, detail::Sortable T, bool Equal>
testing::AssertionResult AssertCompareInAnyOrder(const char *m_expr,
                                                 const char *n_expr, T const &m,
                                                 T const &n) noexcept {
  if constexpr (Equal) {
    if (CompareInAnyOrder<kDepth>(m, n)) {
      return testing::AssertionSuccess();
    }
  } else {
    if (!CompareInAnyOrder<kDepth>(m, n)) {
      return testing::AssertionSuccess();
    }
  }

  auto res = testing::AssertionFailure();
  res      = res << m_expr << " = " << testing::PrintToString(m) << std::endl;
  res      = res << n_expr << " = " << testing::PrintToString(n);
  return res;
}

template <typename T>
inline bool LCDNodeCheck(T const *node_1, T const *node_2) noexcept {
  if (node_1 && node_2) {
    return *node_1 == *node_2;
  } else {
    return !node_1 && !node_2;
  }
}

template <typename T, bool Equal>
inline testing::AssertionResult
AssertLCDNodeCheck(const char *m_expr, const char *n_expr, T const *m,
                   T const *n) noexcept {
  if constexpr (Equal) {
    if (LCDNodeCheck<T>(m, n))
      return testing::AssertionSuccess();
  } else {
    if (!LCDNodeCheck<T>(m, n))
      return testing::AssertionSuccess();
  }

  auto result = testing::AssertionFailure();

  if (m && n) {
    result = result << "neither " << m_expr << " nor " << n_expr
                    << " is |nullptr| where" << std::endl;
    result = result << m_expr << " = " << *m << std::endl;
    result = result << n_expr << " = " << *n;
  } else {
    if (!m) {
      result = result << m_expr << " is |nullptr| while " << n_expr
                      << " is not.";
    } else {
      result = result << n_expr << " is |nullptr| while " << m_expr
                      << " is not.";
    }
  }

  return result;
}

} // namespace lcd

#endif // TESTING_TEST_HELPER_H_

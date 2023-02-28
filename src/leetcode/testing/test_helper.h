#ifndef LEETCODE_TESTING_TEST_HELPER_H_
#define LEETCODE_TESTING_TEST_HELPER_H_

#include "gtest/gtest-printers.h"
#include "gtest/gtest.h"
#include "gtest/internal/gtest-internal.h"
#include <concepts>
#include <sstream>
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

template <typename T>
concept LCDNodeType = requires(T object, size_t idx) {
                        { object->GetChild(idx) } -> IsSameAs<T>;
                        { object->GetChildren() } -> IsSameAs<std::vector<T>>;
                      };

template <typename T, typename S>
class CompareLTHelper;

template <typename T, typename S>
class CompareHelper;

template <typename T, typename S>
class FailureAssertionResult;

} // namespace detail

template <size_t kDepth, detail::Sortable T>
bool CompareInAnyOrder(T lhs, T rhs) noexcept;

template <size_t kDepth, detail::Sortable T, bool Equal>
testing::AssertionResult AssertCompareInAnyOrder(const char *m_expr,
                                                 const char *n_expr, T const &m,
                                                 T const &n) noexcept;

template <typename T, typename S, bool Equal>
testing::AssertionResult AssertLCDCompare(const char *m_expr,
                                          const char *n_expr, T const &m,
                                          S const &n) noexcept;

} // namespace lcd

#define LCD_EXPECT_EQ(node_1, node_2)                                          \
  EXPECT_PRED_FORMAT2(                                                         \
      (AssertLCDCompare<decltype(node_1), decltype(node_2), true>), node_1,    \
      node_2)

#define LCD_EXPECT_NE(node_1, node_2)                                          \
  EXPECT_PRED_FORMAT2(                                                         \
      (AssertLCDCompare<decltype(node_1), decltype(node_2), false>), node_1,   \
      node_2)

#define LCD_ASSERT_EQ(node_1, node_2)                                          \
  ASSERT_PRED_FORMAT2(                                                         \
      (AssertLCDCompare<decltype(node_1), decltype(node_2), true>), node_1,    \
      node_2)

#define LCD_ASSERT_NE(node_1, node_2)                                          \
  ASSERT_PRED_FORMAT2(                                                         \
      (AssertLCDCompare<decltype(node_1), decltype(node_2), false>), node_1,   \
      node_2)

#define EXPECT_TREENODE_EQ(node_1, node_2)                                     \
  EXPECT_PRED_FORMAT2(                                                         \
      (AssertLCDCompare<::lcd::TreeNode *, ::lcd::TreeNode *, true>),        \
      node_1, node_2)
#define EXPECT_TREENODE_NE(node_1, node_2)                                     \
  EXPECT_PRED_FORMAT2(                                                         \
      (AssertLCDCompare<::lcd::TreeNode *, ::lcd::TreeNode *, false>), node_1, \
      node_2)

#define EXPECT_LISTNODE_EQ(node_1, node_2)                                     \
  EXPECT_PRED_FORMAT2(                                                         \
      (AssertLCDCompare<::lcd::ListNode *, ::lcd::ListNode *, true>), node_1,  \
      node_2)
#define EXPECT_LISTNODE_NE(node_1, node_2)                                     \
  EXPECT_PRED_FORMAT2(                                                         \
      (AssertLCDCompare<::lcd::ListNode *, ::lcd::ListNode *, false>), node_1, \
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
  static const CompareLTHelper<typename T::value_type, typename T::value_type>
      content_cmp_lt{};
  if constexpr (kDepth > 0) {
    for (typename T::value_type &item_in_item : *item) {
      SortItem<kDepth - 1>(&item_in_item);
    }
  }

  std::sort(item->begin(), item->end(), content_cmp_lt);
}

template <typename T, typename S>
class CompareLTHelper {
public:
  inline bool operator()(T const &a, S const &b) const { return a < b; }
};

template <typename T, typename S>
requires LCDNodeType<T> && LCDNodeType<S>
class CompareLTHelper<T, S> {
public:
  inline bool operator()(T a, S b) const { return *a < *b; }
};

template <typename T, typename S>
class CompareHelper {
public:
  inline bool operator()(T const &a, S const &b) const { return a == b; }
};

template <typename T, typename S>
requires LCDNodeType<T> && LCDNodeType<S>
class CompareHelper<T, S> {
public:
  inline bool operator()(T a, S b) const {
    if (a && b) {
      return *a == *b;
    } else {
      return !a && !b;
    }
  }
};

template <typename T, typename S>
requires(IsSameAs<T, float> || IsSameAs<T, double>) &&
        (IsSameAs<S, float> || IsSameAs<S, double>)
class CompareHelper<T, S> {
public:
  inline bool operator()(T const &a, T const &b) const {
    const ::testing::internal::FloatingPoint<T> lhs(a);
    const ::testing::internal::FloatingPoint<T> rhs(b);
    return lhs.AlmostEquals(rhs);
  }
};

template <typename T, typename S>
class CompareHelper<std::vector<T>, std::vector<S>> {
public:
  inline bool operator()(std::vector<T> const &a,
                         std::vector<S> const &b) const {
    static const CompareHelper<T, S> content_cmp{};
    if (a.size() != b.size()) {
      return false;
    }

    for (size_t i = 0; i < a.size(); ++i) {
      if (!content_cmp(a[i], b[i])) {
        return false;
      }
    }

    return true;
  }
};

template <typename T, typename S>
class FailureAssertionResult {
public:
  inline std::string operator()(const char *m_expr, const char *n_expr,
                                T const &m, S const &n) {
    std::ostringstream res;
    res << m_expr << " = " << testing::PrintToString(m) << std::endl;
    res << n_expr << " = " << testing::PrintToString(n);
    return res.str();
  }
};

template <typename T, typename S>
requires LCDNodeType<T> && LCDNodeType<S>
class FailureAssertionResult<T, S> {
public:
  inline std::string operator()(const char *m_expr, const char *n_expr,
                                T const &m, S const &n) {
    std::ostringstream res;
    if (m && n) {
      res << "neither " << m_expr << " nor " << n_expr << " is |nullptr| where"
          << std::endl;
      res << m_expr << " = " << *m << std::endl;
      res << n_expr << " = " << *n;
    } else {
      if (!m) {
        res << m_expr << " is |nullptr| while " << n_expr << " is not.";
      } else {
        res << n_expr << " is |nullptr| while " << m_expr << " is not.";
      }
    }
    return res.str();
  }
};

} // namespace detail

template <size_t kDepth, detail::Sortable T>
inline bool CompareInAnyOrder(T lhs, T rhs) noexcept {
  static const detail::CompareHelper<T, T> cmp_helper{};
  detail::SortItem<kDepth>(&lhs);
  detail::SortItem<kDepth>(&rhs);
  return cmp_helper(lhs, rhs);
}

template <size_t kDepth, detail::Sortable T, bool Equal>
testing::AssertionResult AssertCompareInAnyOrder(const char *m_expr,
                                                 const char *n_expr, T const &m,
                                                 T const &n) noexcept {
  static detail::FailureAssertionResult<T, T> assertion{};
  if constexpr (Equal) {
    if (CompareInAnyOrder<kDepth>(m, n)) {
      return testing::AssertionSuccess();
    }
  } else {
    if (!CompareInAnyOrder<kDepth>(m, n)) {
      return testing::AssertionSuccess();
    }
  }
  return testing::AssertionFailure() << assertion(m_expr, n_expr, m, n);
}

template <typename T, typename S, bool Equal>
testing::AssertionResult AssertLCDCompare(const char *m_expr,
                                          const char *n_expr, T const &m,
                                          S const &n) noexcept {
  static detail::CompareHelper<T, S>          lcd_compare{};
  static detail::FailureAssertionResult<T, S> assertion{};
  if constexpr (Equal) {
    if (lcd_compare(m, n))
      return testing::AssertionSuccess();
  } else {
    if (!lcd_compare(m, n))
      return testing::AssertionSuccess();
  }
  return testing::AssertionFailure() << assertion(m_expr, n_expr, m, n);
}

} // namespace lcd

#endif // TESTING_TEST_HELPER_H_

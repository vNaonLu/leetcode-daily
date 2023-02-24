#ifndef LEETCODE_TESTING_TEST_HELPER_H_
#define LEETCODE_TESTING_TEST_HELPER_H_

#include "gtest/gtest-printers.h"
#include "gtest/gtest.h"
#include "gtest/internal/gtest-internal.h"
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

template <typename T>
concept LCDNodeType = requires(T object, size_t idx) {
                        { object->GetChild(idx) } -> IsSameAs<T>;
                        { object->GetChildren() } -> IsSameAs<std::vector<T>>;
                      };

template <typename T>
class CompareLTHelper;

template <typename T>
class CompareHelper;

} // namespace detail

template <size_t kDepth, detail::Sortable T>
bool CompareInAnyOrder(T lhs, T rhs) noexcept;

template <size_t kDepth, detail::Sortable T, bool Equal>
testing::AssertionResult AssertCompareInAnyOrder(const char *m_expr,
                                                 const char *n_expr, T const &m,
                                                 T const &n) noexcept;

template <detail::LCDNodeType T>
bool LCDNodeCheck(T const *node_1, T const *node_2) noexcept;

template <detail::LCDNodeType T, bool Equal>
testing::AssertionResult
AssertLCDNodeCheck(const char *m_expr, const char *n_expr, T m, T n) noexcept;

} // namespace lcd

#define EXPECT_TREENODE_EQ(node_1, node_2)                                     \
  EXPECT_PRED_FORMAT2((AssertLCDNodeCheck<::lcd::TreeNode *, true>), node_1,   \
                      node_2)
#define EXPECT_TREENODE_NE(node_1, node_2)                                     \
  EXPECT_PRED_FORMAT2((AssertLCDNodeCheck<::lcd::TreeNode *, false>), node_1,  \
                      node_2)

#define EXPECT_LISTNODE_EQ(node_1, node_2)                                     \
  EXPECT_PRED_FORMAT2((AssertLCDNodeCheck<::lcd::ListNode *, true>), node_1,   \
                      node_2)
#define EXPECT_LISTNODE_NE(node_1, node_2)                                     \
  EXPECT_PRED_FORMAT2((AssertLCDNodeCheck<::lcd::ListNode *, false>), node_1,  \
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
  static const CompareLTHelper<typename T::value_type> content_cmp_lt{};
  if constexpr (kDepth > 0) {
    for (typename T::value_type &item_in_item : *item) {
      SortItem<kDepth - 1>(&item_in_item);
    }
  }

  std::sort(item->begin(), item->end(), content_cmp_lt);
}

template <typename T>
class CompareLTHelper {
public:
  inline bool operator()(T const &a, T const &b) const { return a < b; }
};

template <typename T>
requires LCDNodeType<T>
class CompareLTHelper<T> {
public:
  inline bool operator()(T a, T b) const { return *a < *b; }
};

template <typename T>
class CompareHelper {
public:
  inline bool operator()(T const &a, T const &b) const { return a == b; }
};

template <typename T>
requires LCDNodeType<T>
class CompareHelper<T> {
public:
  inline bool operator()(T a, T b) const {
    if (a && b) {
      return *a == *b;
    } else {
      return !a && !b;
    }
  }
};

template <typename T>
requires IsSameAs<T, float> || IsSameAs<T, double>
class CompareHelper<T> {
public:
  inline bool operator()(T const &a, T const &b) const {
    const ::testing::internal::FloatingPoint<T> lhs(a);
    const ::testing::internal::FloatingPoint<T> rhs(b);
    return lhs.AlmostEquals(rhs);
  }
};

template <typename T>
class CompareHelper<std::vector<T>> {
public:
  inline bool operator()(std::vector<T> const &a,
                         std::vector<T> const &b) const {
    static const CompareHelper<T> content_cmp{};
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

} // namespace detail

template <size_t kDepth, detail::Sortable T>
inline bool CompareInAnyOrder(T lhs, T rhs) noexcept {
  static const detail::CompareHelper<T> cmp_helper{};
  detail::SortItem<kDepth>(&lhs);
  detail::SortItem<kDepth>(&rhs);
  return cmp_helper(lhs, rhs);
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

template <detail::LCDNodeType T>
inline bool LCDNodeCheck(T node_1, T node_2) noexcept {
  static detail::CompareHelper<T> lcd_compare{};
  return lcd_compare(node_1, node_2);
}

template <detail::LCDNodeType T, bool Equal>
inline testing::AssertionResult
AssertLCDNodeCheck(const char *m_expr, const char *n_expr, T m, T n) noexcept {
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

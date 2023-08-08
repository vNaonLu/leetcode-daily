// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Convert Integer to the Sum of Two No-Zero Integers
//
// https://leetcode.com/problems/convert-integer-to-the-sum-of-two-no-zero-integers/
//
// Question ID: 1317
// Difficult  : Easy
// Solve Date : 2023/08/04 18:58

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1317. Convert Integer to the Sum of Two No-Zero Integers|:
//
// No-Zero integer is a positive integer that does not contain any |0| in its
// decimal representation. Given an integer |n|, return a list of two integers
// |[a, b]| where:
//
//  • |a| and |b| are No-Zero integers.
//
//  • |a + b = n|
// The test cases are generated so that there is at least one valid solution. If
// there are many valid solutions, you can return any of them.
//
//

LEETCODE_BEGIN_RESOLVING(1317, ConvertIntegerToTheSumOfTwoNoZeroIntegers,
                         Solution);

class Solution {
public:
  vector<int> getNoZeroIntegers(int n) {
    int x = 1;
    int y = n - x;
    while (ContainZero(x) || ContainZero(y)) {
      ++x;
      --y;
    }
    return {x, y};
  }

private:
  bool ContainZero(int x) {
    if (x == 0) {
      return true;
    }
    while (x) {
      if (x % 10 == 0) {
        return true;
      }
      x /= 10;
    }
    return false;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= n <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

namespace {
int  Sum(const vector<int> &v) { return v[0] + v[1]; }
bool NotContainZero(const vector<int> &v) {
  return all_of(v.begin(), v.end(), [](auto x) {
    if (x == 0) {
      return true;
    }
    while (x) {
      if (x % 10 == 0) {
        return false;
      }
      x /= 10;
    }
    return true;
  });
}
} // namespace

// [Example #1]
//  Input: n = 2
// Output: [1,1]
//
// Let a = 1 and b = 1.
// Both a and b are no-zero integers, and a + b = 2 = n.

LEETCODE_SOLUTION_UNITTEST(1317, ConvertIntegerToTheSumOfTwoNoZeroIntegers,
                           example_1) {
  auto        solution = MakeSolution();
  int         n        = 2;
  vector<int> actual   = solution->getNoZeroIntegers(n);
  ASSERT_EQ(actual.size(), 2);
  EXPECT_TRUE(NotContainZero(actual));
  LCD_EXPECT_EQ(Sum(actual), n);
}

// [Example #2]
//  Input: n = 11
// Output: [2,9]
//
// Let a = 2 and b = 9.
// Both a and b are no-zero integers, and a + b = 9 = n.
// Note that there are other valid answers as [8, 3] that can be accepted.

LEETCODE_SOLUTION_UNITTEST(1317, ConvertIntegerToTheSumOfTwoNoZeroIntegers,
                           example_2) {
  auto        solution = MakeSolution();
  int         n        = 11;
  vector<int> actual   = solution->getNoZeroIntegers(n);
  ASSERT_EQ(actual.size(), 2);
  EXPECT_TRUE(NotContainZero(actual));
  LCD_EXPECT_EQ(Sum(actual), n);
}

// [Extra Testcase #1]
//  Input: 10000
// Output: [1,9999]
//

LEETCODE_SOLUTION_UNITTEST(1317, ConvertIntegerToTheSumOfTwoNoZeroIntegers,
                           extra_testcase_1) {
  auto        solution = MakeSolution();
  int         n        = 10000;
  vector<int> actual   = solution->getNoZeroIntegers(n);
  ASSERT_EQ(actual.size(), 2);
  EXPECT_TRUE(NotContainZero(actual));
  LCD_EXPECT_EQ(Sum(actual), n);
}

// [Extra Testcase #2]
//  Input: 11
// Output: [2,9]
//

LEETCODE_SOLUTION_UNITTEST(1317, ConvertIntegerToTheSumOfTwoNoZeroIntegers,
                           extra_testcase_2) {
  auto        solution = MakeSolution();
  int         n        = 11;
  vector<int> actual   = solution->getNoZeroIntegers(n);
  ASSERT_EQ(actual.size(), 2);
  EXPECT_TRUE(NotContainZero(actual));
  LCD_EXPECT_EQ(Sum(actual), n);
}

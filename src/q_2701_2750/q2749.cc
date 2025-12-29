// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Minimum Operations to Make the Integer Zero
//
// https://leetcode.com/problems/minimum-operations-to-make-the-integer-zero/
//
// Question ID: 2749
// Difficult  : Medium
// Solve Date : 2025/09/05 18:12

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2749. Minimum Operations to Make the Integer Zero|:
//
// You are given two integers |num1| and |num2|.
// In one operation, you can choose integer |i| in the range |[0, 60]| and
// subtract |2ⁱ + num2| from |num1|. Return the integer denoting the minimum
// number of operations needed to make |num1| equal to |0|. If it is impossible
// to make |num1| equal to |0|, return |-1|.
//
//

LEETCODE_BEGIN_RESOLVING(2749, MinimumOperationsToMakeTheIntegerZero, Solution);

class Solution {
public:
  int makeTheIntegerZero(int num1, int num2) {
    for (int k = 1; k <= 60; k++) {
      long long x = num1 - 1LL * num2 * k;
      if (x < k) {
        return -1;
      }
      if (k >= __builtin_popcountll(x)) {
        return k;
      }
    }
    return -1;
  }
};
LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= num1 <= 10⁹|
// * |-10⁹ <= num2 <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: num1 = 3, num2 = -2
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(2749, MinimumOperationsToMakeTheIntegerZero,
                           example_1) {
  auto solution = MakeSolution();
  int  num1     = 3;
  int  num2     = -2;
  int  expect   = 3;
  int  actual   = solution->makeTheIntegerZero(num1, num2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: num1 = 5, num2 = 7
// Output: -1
//

LEETCODE_SOLUTION_UNITTEST(2749, MinimumOperationsToMakeTheIntegerZero,
                           example_2) {
  auto solution = MakeSolution();
  int  num1     = 5;
  int  num2     = 7;
  int  expect   = -1;
  int  actual   = solution->makeTheIntegerZero(num1, num2);
  LCD_EXPECT_EQ(expect, actual);
}

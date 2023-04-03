// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Get Maximum in Generated Array
//
// https://leetcode.com/problems/get-maximum-in-generated-array/
//
// Question ID: 1646
// Difficult  : Easy
// Solve Date : 2023/04/03 15:29

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1646. Get Maximum in Generated Array|:
//
// You are given an integer |n|. A 0-indexed integer array |nums| of length |n +
// 1| is generated in the following way:
//
//  • |nums[0] = 0|
//
//  • |nums[1] = 1|
//
//  • |nums[2 * i] = nums[i]| when |2 <= 2 * i <= n|
//
//  • |nums[2 * i + 1] = nums[i] + nums[i + 1]| when |2 <= 2 * i + 1 <= n|
// Return the maximum integer in the array |nums|.
//
//

LEETCODE_BEGIN_RESOLVING(1646, GetMaximumInGeneratedArray, Solution);

class Solution {
public:
  int getMaximumGenerated(int n) {
    if (n == 0) {
      return 0;
    }
    int         res = 1;
    vector<int> dp(n + 1);
    dp[0] = 0;
    dp[1] = 1;
    for (int i = 2; i <= n; ++i) {
      if (i & 1) {
        dp[i] = dp[i / 2] + dp[i / 2 + 1];
      } else {
        dp[i] = dp[i / 2];
      }
      res = max(res, dp[i]);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |0 <= n <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 7
// Output: 3
//
// According to the given rules:
//  nums[0] = 0
//  nums[1] = 1
//  nums[(1 * 2) = 2] = nums[1] = 1
//  nums[(1 * 2) + 1 = 3] = nums[1] + nums[2] = 1 + 1 = 2
//  nums[(2 * 2) = 4] = nums[2] = 1
//  nums[(2 * 2) + 1 = 5] = nums[2] + nums[3] = 1 + 2 = 3
//  nums[(3 * 2) = 6] = nums[3] = 2
//  nums[(3 * 2) + 1 = 7] = nums[3] + nums[4] = 2 + 1 = 3
// Hence, nums = [0,1,1,2,1,3,2,3], and the maximum is max(0,1,1,2,1,3,2,3) = 3.

LEETCODE_SOLUTION_UNITTEST(1646, GetMaximumInGeneratedArray, example_1) {
  auto solution = MakeSolution();
  int  n        = 7;
  int  expect   = 3;
  int  actual   = solution->getMaximumGenerated(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 2
// Output: 1
//
// According to the given rules, nums = [0,1,1]. The maximum is max(0,1,1) = 1.

LEETCODE_SOLUTION_UNITTEST(1646, GetMaximumInGeneratedArray, example_2) {
  auto solution = MakeSolution();
  int  n        = 2;
  int  expect   = 1;
  int  actual   = solution->getMaximumGenerated(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: n = 3
// Output: 2
//
// According to the given rules, nums = [0,1,1,2]. The maximum is max(0,1,1,2)
// = 2.

LEETCODE_SOLUTION_UNITTEST(1646, GetMaximumInGeneratedArray, example_3) {
  auto solution = MakeSolution();
  int  n        = 3;
  int  expect   = 2;
  int  actual   = solution->getMaximumGenerated(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: 4
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(1646, GetMaximumInGeneratedArray, extra_testcase_1) {
  auto solution = MakeSolution();
  int  n        = 4;
  int  expect   = 2;
  int  actual   = solution->getMaximumGenerated(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #2]
//  Input: 1
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(1646, GetMaximumInGeneratedArray, extra_testcase_2) {
  auto solution = MakeSolution();
  int  n        = 1;
  int  expect   = 1;
  int  actual   = solution->getMaximumGenerated(n);
  LCD_EXPECT_EQ(expect, actual);
}

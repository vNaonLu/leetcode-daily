// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Unique Binary Search Trees
//
// https://leetcode.com/problems/unique-binary-search-trees/
//
// Question ID: 96
// Difficult  : Medium
// Solve Date : 2021/10/09 16:38

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |96. Unique Binary Search Trees|:
//
// Given an integer |n|, return the number of structurally unique BST's (binary
// search trees) which has exactly |n| nodes of unique values from |1| to |n|.  
//

LEETCODE_BEGIN_RESOLVING(96, UniqueBinarySearchTrees, Solution);

class Solution {
public:
  int numTrees(int n) {
    vector<int> dp(n + 1, 1);
    dp[0] = 0;
    for (int i = 2; i < dp.size(); ++i) {
      dp[i] = 2 * dp[i - 1];
      for (int j = 2; j < i; ++j)
        dp[i] += dp[j - 1] * dp[i - j];
    }
    return dp.back();
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n <= 19|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 3
// Output: 5
//

LEETCODE_SOLUTION_UNITTEST(96, UniqueBinarySearchTrees, example_1) {
  auto solution = MakeSolution();
  int  n        = 3;
  int  expect   = 5;
  int  actual   = solution->numTrees(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 1
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(96, UniqueBinarySearchTrees, example_2) {
  auto solution = MakeSolution();
  int  n        = 1;
  int  expect   = 1;
  int  actual   = solution->numTrees(n);
  LCD_EXPECT_EQ(expect, actual);
}

// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Beautiful Arrangement
//
// https://leetcode.com/problems/beautiful-arrangement/
//
// Question ID: 526
// Difficult  : Medium
// Solve Date : 2024/05/03 20:35

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |526. Beautiful Arrangement|:
//
// Suppose you have |n| integers labeled |1| through |n|. A permutation of those
// |n| integers |perm| (1-indexed) is considered a beautiful arrangement if for
// every |i| ( |1 <= i <= n|), either of the following is true:
//
//  • |perm[i]| is divisible by |i|.
//
//  • |i| is divisible by |perm[i]|.
// Given an integer |n|, return the number of the beautiful arrangements that
// you can construct.
//
//

LEETCODE_BEGIN_RESOLVING(526, BeautifulArrangement, Solution);

class Solution {
public:
  int countArrangement(int n) {
    vector<int> nums;
    int         res = 0;
    for (int i = 1; i <= n; ++i) {
      nums.emplace_back(i);
    }
    helper(nums, 0, &res);
    return res;
  }

private:
  void helper(vector<int> nums, int start, int *res) {
    if (start == nums.size()) {
      ++*res;
      return;
    }
    for (int i = start; i < nums.size(); ++i) {
      swap(nums[start], nums[i]);
      if ((nums[start] % (start + 1)) == 0 ||
          ((start + 1) % nums[start]) == 0) {
        helper(nums, start + 1, res);
      }
    }
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n <= 15|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 2
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(526, BeautifulArrangement, example_1) {
  auto solution = MakeSolution();
  int  n        = 2;
  int  expect   = 2;
  int  actual   = solution->countArrangement(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 1
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(526, BeautifulArrangement, example_2) {
  auto solution = MakeSolution();
  int  n        = 1;
  int  expect   = 1;
  int  actual   = solution->countArrangement(n);
  LCD_EXPECT_EQ(expect, actual);
}

// Copyright 2023 Naon Lu
//
// This file describes the solution of
// 132 Pattern
//
// https://leetcode.com/problems/132-pattern/
//
// Question ID: 456
// Difficult  : Medium
// Solve Date : 2022/05/07 13:30

#include <iosfwd>
#include <set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |456. 132 Pattern|:
//
// Given an array of |n| integers |nums|, a 132 pattern is a subsequence of
// three integers |nums[i]|, |nums[j]| and |nums[k]| such that |i < j < k| and
// |nums[i] < nums[k] < nums[j]|. Return |true| if there is a 132 pattern in
// |nums|, otherwise, return |false|.  
//

LEETCODE_BEGIN_RESOLVING(456, 132Pattern, Solution);

class Solution {
public:
  bool find132pattern(vector<int> &nums) {
    int         n = nums.size();
    vector<int> dp(n, 0);
    dp.front() = nums[0];
    for (int i = 1; i < nums.size(); ++i) {
      dp[i] = min(dp[i - 1], nums[i]);
    }

    set<int> memos;
    memos.insert(nums.back());
    for (int i = n - 2; i > 0; --i) {
      auto l = memos.begin(), r = --memos.end();

      if (*l < nums[i]) {
        if (*r < nums[i]) {
          if (dp[i - 1] < *r) {
            return true;
          }
        } else {
          auto find = --memos.lower_bound(nums[i]);
          if (*find > dp[i - 1]) {
            return true;
          }
        }
      }

      memos.insert(nums[i]);
    }

    return false;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == nums.length|
// * |1 <= n <= 2 * 10⁵|
// * |-10⁹ <= nums[i] <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,3,4]
// Output: false
//
// There is no 132 pattern in the sequence.

LEETCODE_SOLUTION_UNITTEST(456, 132Pattern, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 4};
  bool        expect   = false;
  bool        actual   = solution->find132pattern(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [3,1,4,2]
// Output: true
//
// There is a 132 pattern in the sequence: [1, 4, 2].

LEETCODE_SOLUTION_UNITTEST(456, 132Pattern, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 1, 4, 2};
  bool        expect   = true;
  bool        actual   = solution->find132pattern(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [-1,3,2,0]
// Output: true
//
// There are three 132 patterns in the sequence: [-1, 3, 2], [-1, 3, 0] and [-1,
// 2, 0].

LEETCODE_SOLUTION_UNITTEST(456, 132Pattern, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {-1, 3, 2, 0};
  bool        expect   = true;
  bool        actual   = solution->find132pattern(nums);
  LCD_EXPECT_EQ(expect, actual);
}

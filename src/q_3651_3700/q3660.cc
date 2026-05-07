// Copyright 2026 Naon Lu
//
// This file describes the solution of
// Jump Game IX
//
// https://leetcode.com/problems/jump-game-ix/
//
// Question ID: 3660
// Difficult  : Medium
// Solve Date : 2026/05/07 18:43

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3660. Jump Game IX|:
//
// You are given an integer array |nums|.
// From any index |i|, you can jump to another index |j| under the following
// rules:
//
//  • Jump to index |j| where |j > i| is allowed only if |nums[j] < nums[i]|.
//
//  • Jump to index |j| where |j < i| is allowed only if |nums[j] > nums[i]|.
// For each index |i|, find the maximum value in |nums| that can be reached by
// following any sequence of valid jumps starting at |i|. Return an array |ans|
// where |ans[i]| is the maximum value reachable starting from index |i|.
//
//

LEETCODE_BEGIN_RESOLVING(3660, JumpGameIX, Solution);

class Solution {
public:
  vector<int> maxValue(vector<int> &nums) {
    vector<int> ans(nums.size());
    vector<int> pre(nums.size());
    vector<int> suf(nums.size());
    pre[0] = nums[0];
    for (int i = 1; i < nums.size(); ++i) {
      pre[i] = max(pre[i - 1], nums[i]);
    }
    suf.back() = nums.back();
    for (int i = nums.size() - 2; i >= 0; --i) {
      suf[i] = min(suf[i + 1], nums[i]);
    }
    ans.back() = pre.back();

    for (int i = nums.size() - 2; i >= 0; --i) {
      if (pre[i] > suf[i + 1]) {
        ans[i] = ans[i + 1];
      } else {
        ans[i] = pre[i];
      }
    }

    return ans;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁵|
// * |1 <= nums[i] <= 10⁹​​​​​​​|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [2,1,3]
// Output: [2,2,3]
//

LEETCODE_SOLUTION_UNITTEST(3660, JumpGameIX, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 1, 3};
  vector<int> expect   = {2, 2, 3};
  vector<int> actual   = solution->maxValue(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [2,3,1]
// Output: [3,3,3]
//

LEETCODE_SOLUTION_UNITTEST(3660, JumpGameIX, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 3, 1};
  vector<int> expect   = {3, 3, 3};
  vector<int> actual   = solution->maxValue(nums);
  LCD_EXPECT_EQ(expect, actual);
}

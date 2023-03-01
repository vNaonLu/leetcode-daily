// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Jump Game VI
//
// https://leetcode.com/problems/jump-game-vi/
//
// Question ID: 1696
// Difficult  : Medium
// Solve Date : 2022/07/09 16:44

#include <iosfwd>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1696. Jump Game VI|:
//
// You are given a 0-indexed integer array |nums| and an integer |k|.
// You are initially standing at index |0|. In one move, you can jump at most
// |k| steps forward without going outside the boundaries of the array. That is,
// you can jump from index |i| to any index in the range |[i + 1, min(n - 1, i +
// k)]| inclusive. You want to reach the last index of the array (index |n -
// 1|). Your score is the sum of all |nums[j]| for each index |j| you visited in
// the array. Return the maximum score you can get.
//

LEETCODE_BEGIN_RESOLVING(1696, JumpGameVI, Solution);

class Solution {
public:
  int maxResult(vector<int> &nums, int k) {
    vector<int> dp(nums.size(), 0);
    dp.front() = nums.front();

    priority_queue<pair<int, int>> pq;
    pq.emplace(nums.front(), 0);

    for (int i = 1; i < nums.size(); ++i) {
      while (pq.top().second < i - k) {
        pq.pop();
      }

      dp[i] = nums[i] + pq.top().first;
      pq.emplace(dp[i], i);
    }

    return dp.back();
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length, k <= 10⁵|
// * |-10⁴ <= nums[i] <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,-1,-2,4,-7,3], k = 2
// Output: 7
//
// You can choose your jumps forming the subsequence [1,-1,4,3] (underlined
// above). The sum is 7.

LEETCODE_SOLUTION_UNITTEST(1696, JumpGameVI, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, -1, -2, 4, -7, 3};
  int         k        = 2;
  int         expect   = 7;
  int         actual   = solution->maxResult(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [10,-5,-2,4,0,3], k = 3
// Output: 17
//
// You can choose your jumps forming the subsequence [10,4,3] (underlined
// above). The sum is 17.

LEETCODE_SOLUTION_UNITTEST(1696, JumpGameVI, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {10, -5, -2, 4, 0, 3};
  int         k        = 3;
  int         expect   = 17;
  int         actual   = solution->maxResult(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [1,-5,-20,4,-1,3,-6,-3], k = 2
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(1696, JumpGameVI, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, -5, -20, 4, -1, 3, -6, -3};
  int         k        = 2;
  int         expect   = 0;
  int         actual   = solution->maxResult(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

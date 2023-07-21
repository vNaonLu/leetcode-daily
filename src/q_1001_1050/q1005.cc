// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Maximize Sum Of Array After K Negations
//
// https://leetcode.com/problems/maximize-sum-of-array-after-k-negations/
//
// Question ID: 1005
// Difficult  : Easy
// Solve Date : 2023/07/21 13:21

#include <iosfwd>
#include <numeric>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1005. Maximize Sum Of Array After K Negations|:
//
// Given an integer array |nums| and an integer |k|, modify the array in the
// following way:
//
//  • choose an index |i| and replace |nums[i]| with |-nums[i]|.
// You should apply this process exactly |k| times. You may choose the same
// index |i| multiple times. Return the largest possible sum of the array after
// modifying it in this way.
//
//

LEETCODE_BEGIN_RESOLVING(1005, MaximizeSumOfArrayAfterKNegations, Solution);

class Solution {
public:
  int largestSumAfterKNegations(vector<int> &nums, int k) {
    int res = accumulate(nums.begin(), nums.end(), 0);
    priority_queue<int, vector<int>, greater<int>> pq(nums.begin(), nums.end());

    while (k > 0 && pq.top() < 0) {
      int smallest = pq.top();
      res -= 2 * smallest;
      pq.pop();

      if (-smallest > -pq.top()) {
        pq.emplace(-smallest);
      }
      --k;
    }

    if (k & 1) {
      res -= 2 * pq.top();
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁴|
// * |-100 <= nums[i] <= 100|
// * |1 <= k <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [4,2,3], k = 1
// Output: 5
//
// Choose index 1 and nums becomes [4,-2,3].

LEETCODE_SOLUTION_UNITTEST(1005, MaximizeSumOfArrayAfterKNegations, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {4, 2, 3};
  int         k        = 1;
  int         expect   = 5;
  int         actual   = solution->largestSumAfterKNegations(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [3,-1,0,2], k = 3
// Output: 6
//
// Choose indices (1, 2, 2) and nums becomes [3,1,0,2].

LEETCODE_SOLUTION_UNITTEST(1005, MaximizeSumOfArrayAfterKNegations, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, -1, 0, 2};
  int         k        = 3;
  int         expect   = 6;
  int         actual   = solution->largestSumAfterKNegations(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [2,-3,-1,5,-4], k = 2
// Output: 13
//
// Choose indices (1, 4) and nums becomes [2,3,-1,5,4].

LEETCODE_SOLUTION_UNITTEST(1005, MaximizeSumOfArrayAfterKNegations, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, -3, -1, 5, -4};
  int         k        = 2;
  int         expect   = 13;
  int         actual   = solution->largestSumAfterKNegations(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: [-4,-2]
// 5
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(1005, MaximizeSumOfArrayAfterKNegations,
                           extra_testcase_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {-4, -2};
  int         k        = 5;
  int         expect   = 2;
  int         actual   = solution->largestSumAfterKNegations(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

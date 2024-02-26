// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Divide an Array Into Subarrays With Minimum Cost I
//
// https://leetcode.com/problems/divide-an-array-into-subarrays-with-minimum-cost-i/
//
// Question ID: 3010
// Difficult  : Easy
// Solve Date : 2024/02/23 01:07

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3010. Divide an Array Into Subarrays With Minimum Cost I|:
//
// You are given an array of integers |nums| of length |n|.
// The cost of an array is the value of its first element. For example, the cost
// of |[1,2,3]| is |1| while the cost of |[3,4,1]| is |3|. You need to divide
// |nums| into |3| disjoint contiguous subarrays. Return the minimum possible
// sum of the cost of these subarrays.
//
//

LEETCODE_BEGIN_RESOLVING(3010, DivideAnArrayIntoSubarraysWithMinimumCostI,
                         Solution);

class Solution {
public:
  int minimumCost(vector<int> &nums) {
    int res = nums[0];
    int mn1 = 50;
    int mn2 = 50;
    for (int i = 1; i < nums.size(); ++i) {
      if (mn1 > nums[i]) {
        mn2 = mn1;
        mn1 = nums[i];
      } else if (mn2 > nums[i]) {
        mn2 = nums[i];
      }
    }
    return res + mn1 + mn2;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |3 <= n <= 50|
// * |1 <= nums[i] <= 50|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,3,12]
// Output: 6
//
// The best possible way to form 3 subarrays is: [1], [2], and [3,12] at a total
// cost of 1 + 2 + 3 = 6. The other possible ways to form 3 subarrays are:
// - [1], [2,3], and [12] at a total cost of 1 + 2 + 12 = 15.
// - [1,2], [3], and [12] at a total cost of 1 + 3 + 12 = 16.

LEETCODE_SOLUTION_UNITTEST(3010, DivideAnArrayIntoSubarraysWithMinimumCostI,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 12};
  int         expect   = 6;
  int         actual   = solution->minimumCost(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [5,4,3]
// Output: 12
//
// The best possible way to form 3 subarrays is: [5], [4], and [3] at a total
// cost of 5 + 4 + 3 = 12. It can be shown that 12 is the minimum cost
// achievable.

LEETCODE_SOLUTION_UNITTEST(3010, DivideAnArrayIntoSubarraysWithMinimumCostI,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {5, 4, 3};
  int         expect   = 12;
  int         actual   = solution->minimumCost(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [10,3,1,1]
// Output: 12
//
// The best possible way to form 3 subarrays is: [10,3], [1], and [1] at a total
// cost of 10 + 1 + 1 = 12. It can be shown that 12 is the minimum cost
// achievable.

LEETCODE_SOLUTION_UNITTEST(3010, DivideAnArrayIntoSubarraysWithMinimumCostI,
                           example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {10, 3, 1, 1};
  int         expect   = 12;
  int         actual   = solution->minimumCost(nums);
  LCD_EXPECT_EQ(expect, actual);
}

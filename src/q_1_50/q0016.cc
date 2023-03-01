// Copyright 2023 Naon Lu
//
// This file describes the solution of
// 3Sum Closest
//
// https://leetcode.com/problems/3sum-closest/
//
// Question ID: 16
// Difficult  : Medium
// Solve Date : 2021/11/17 18:17

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |16. 3Sum Closest|:
//
// Given an integer array |nums| of length |n| and an integer |target|, find
// three integers in |nums| such that the sum is closest to |target|. Return the
// sum of the three integers. You may assume that each input would have exactly
// one solution.  
//

LEETCODE_BEGIN_RESOLVING(16, 3SumClosest, Solution);

class Solution {
public:
  int threeSumClosest(vector<int> &nums, int target) {
    int ret  = nums[0] + nums[1] + nums[2];
    int diff = abs(ret - target);
    sort(nums.begin(), nums.end());
    for (int i = 0; i < nums.size() - 2; ++i) {
      if (nums[i] * 3 > target)
        return min(ret, nums[i] + nums[i + 1] + nums[i + 2]);
      int left = i + 1, right = nums.size() - 1;
      while (left < right) {
        int sum     = nums[i] + nums[left] + nums[right];
        int newDiff = abs(sum - target);
        if (diff > newDiff) {
          diff = newDiff;
          ret  = sum;
        }
        if (sum < target)
          ++left;
        else
          --right;
      }
    }
    return ret;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |3 <= nums.length <= 500|
// * |-1000 <= nums[i] <= 1000|
// * |-10⁴ <= target <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [-1,2,1,-4], target = 1
// Output: 2
//
// The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).

LEETCODE_SOLUTION_UNITTEST(16, 3SumClosest, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {-1, 2, 1, -4};
  int         target   = 1;
  int         expect   = 2;
  int         actual   = solution->threeSumClosest(nums, target);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [0,0,0], target = 1
// Output: 0
//
// The sum that is closest to the target is 0. (0 + 0 + 0 = 0).

LEETCODE_SOLUTION_UNITTEST(16, 3SumClosest, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {0, 0, 0};
  int         target   = 1;
  int         expect   = 0;
  int         actual   = solution->threeSumClosest(nums, target);
  LCD_EXPECT_EQ(expect, actual);
}

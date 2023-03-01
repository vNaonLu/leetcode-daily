// Copyright 2023 Naon Lu
//
// This file describes the solution of
// 3Sum
//
// https://leetcode.com/problems/3sum/
//
// Question ID: 15
// Difficult  : Medium
// Solve Date : 2021/09/19 08:00

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |15. 3Sum|:
//
// Given an integer array nums, return all the triplets |[nums[i], nums[j],
// nums[k]]| such that |i != j|, |i != k|, and |j != k|, and |nums[i] + nums[j]
// + nums[k] == 0|. Notice that the solution set must not contain duplicate
// triplets.  
//

LEETCODE_BEGIN_RESOLVING(15, 3Sum, Solution);

class Solution {
public:
  vector<vector<int>> threeSum(vector<int> &nums) {
    vector<vector<int>> res;
    sort(nums.begin(), nums.end());
    for (int k = 0; k < (int)nums.size() - 2; ++k) {
      if (nums[k] > 0)
        break;
      if (k > 0 && nums[k] == nums[k - 1])
        continue;
      int target = 0 - nums[k], i = k + 1, j = (int)nums.size() - 1;
      while (i < j) {
        if (nums[i] + nums[j] == target) {
          res.push_back({nums[k], nums[i], nums[j]});
          while (i < j && nums[i] == nums[i + 1])
            ++i;
          while (i < j && nums[j] == nums[j - 1])
            --j;
          ++i;
          --j;
        } else if (nums[i] + nums[j] < target)
          ++i;
        else
          --j;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |3 <= nums.length <= 3000|
// * |-10⁵ <= nums[i] <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [-1,0,1,2,-1,-4]
// Output: [[-1,-1,2],[-1,0,1]]
//
// nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0.
// nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0.
// nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0.
// The distinct triplets are [-1,0,1] and [-1,-1,2].
// Notice that the order of the output and the order of the triplets does not
// matter.

LEETCODE_SOLUTION_UNITTEST(15, 3Sum, example_1) {
  auto                solution = MakeSolution();
  vector<int>         nums     = {-1, 0, 1, 2, -1, -4};
  vector<vector<int>> expect   = {
      {-1, -1, 2},
      {-1,  0, 1}
  };
  vector<vector<int>> actual = solution->threeSum(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [0,1,1]
// Output: []
//
// The only possible triplet does not sum up to 0.

LEETCODE_SOLUTION_UNITTEST(15, 3Sum, example_2) {
  auto                solution = MakeSolution();
  vector<int>         nums     = {0, 1, 1};
  vector<vector<int>> expect   = {};
  vector<vector<int>> actual   = solution->threeSum(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [0,0,0]
// Output: [[0,0,0]]
//
// The only possible triplet sums up to 0.

LEETCODE_SOLUTION_UNITTEST(15, 3Sum, example_3) {
  auto                solution = MakeSolution();
  vector<int>         nums     = {0, 0, 0};
  vector<vector<int>> expect   = {
      {0, 0, 0}
  };
  vector<vector<int>> actual = solution->threeSum(nums);
  LCD_EXPECT_EQ(expect, actual);
}

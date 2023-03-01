// Copyright 2023 Naon Lu
//
// This file describes the solution of
// 4Sum
//
// https://leetcode.com/problems/4sum/
//
// Question ID: 18
// Difficult  : Medium
// Solve Date : 2021/11/22 18:12

#include <algorithm>
#include <iosfwd>
#include <set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |18. 4Sum|:
//
// Given an array |nums| of |n| integers, return an array of all the unique
// quadruplets |[nums[a], nums[b], nums[c], nums[d]]| such that:
//
//  • |0 <= a, b, c, d < n|
//
//  • |a|, |b|, |c|, and |d| are distinct.
//
//  • |nums[a] + nums[b] + nums[c] + nums[d] == target|
// You may return the answer in any order.
//  
//

LEETCODE_BEGIN_RESOLVING(18, 4Sum, Solution);

class Solution {
public:
  vector<vector<int>> fourSum(vector<int> &nums, int target) {
    set<vector<int>> res;
    sort(nums.begin(), nums.end());
    for (int i = 0; i < int(nums.size() - 3); ++i) {
      for (int j = i + 1; j < int(nums.size() - 2); ++j) {
        if (j > i + 1 && nums[j] == nums[j - 1])
          continue;
        int left = j + 1, right = nums.size() - 1;
        int cur = target - nums[i] - nums[j];
        while (left < right) {
          long sum = nums[left] + nums[right];
          if (sum == cur) {
            vector<int> out{nums[i], nums[j], nums[left], nums[right]};
            res.insert(out);
            ++left;
            --right;
          } else if (sum < cur)
            ++left;
          else
            --right;
        }
      }
    }
    return vector<vector<int>>(res.begin(), res.end());
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 200|
// * |-10⁹ <= nums[i] <= 10⁹|
// * |-10⁹ <= target <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,0,-1,0,-2,2], target = 0
// Output: [[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]
//

LEETCODE_SOLUTION_UNITTEST(18, 4Sum, example_1) {
  auto                solution = MakeSolution();
  vector<int>         nums     = {1, 0, -1, 0, -2, 2};
  int                 target   = 0;
  vector<vector<int>> expect   = {
      {-2, -1, 1, 2},
      {-2,  0, 0, 2},
      {-1,  0, 0, 1}
  };
  vector<vector<int>> actual = solution->fourSum(nums, target);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [2,2,2,2,2], target = 8
// Output: [[2,2,2,2]]
//

LEETCODE_SOLUTION_UNITTEST(18, 4Sum, example_2) {
  auto                solution = MakeSolution();
  vector<int>         nums     = {2, 2, 2, 2, 2};
  int                 target   = 8;
  vector<vector<int>> expect   = {
      {2, 2, 2, 2}
  };
  vector<vector<int>> actual = solution->fourSum(nums, target);
  EXPECT_ANYORDER_EQ(expect, actual);
}

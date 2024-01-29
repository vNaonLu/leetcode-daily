// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Minimum Sum of Mountain Triplets I
//
// https://leetcode.com/problems/minimum-sum-of-mountain-triplets-i/
//
// Question ID: 2908
// Difficult  : Easy
// Solve Date : 2024/01/29 20:18

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2908. Minimum Sum of Mountain Triplets I|:
//
// You are given a 0-indexed array |nums| of integers.
// A triplet of indices |(i, j, k)| is a mountain if:
//
//  • |i < j < k|
//
//  • |nums[i] < nums[j]| and |nums[k] < nums[j]|
// Return the minimum possible sum of a mountain triplet of |nums|. If no such
// triplet exists, return |-1|.
//
//

LEETCODE_BEGIN_RESOLVING(2908, MinimumSumOfMountainTripletsI, Solution);

class Solution {
public:
  int minimumSum(vector<int> &nums) {
    int res = numeric_limits<int>::max();
    for (int i = 0; i < nums.size(); ++i) {
      for (int j = i + 1; j < nums.size(); ++j) {
        for (int k = j + 1; k < nums.size(); ++k) {
          if (nums[j] > nums[i] && nums[k] < nums[j]) {
            res = min(res, nums[i] + nums[j] + nums[k]);
          }
        }
      }
    }
    return res == numeric_limits<int>::max() ? -1 : res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |3 <= nums.length <= 50|
// * |1 <= nums[i] <= 50|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [8,6,1,5,3]
// Output: 9
//
// Triplet (2, 3, 4) is a mountain triplet of sum 9 since:
// - 2 < 3 < 4
// - nums[2] < nums[3] and nums[4] < nums[3]
// And the sum of this triplet is nums[2] + nums[3] + nums[4] = 9. It can be
// shown that there are no mountain triplets with a sum of less than 9.

LEETCODE_SOLUTION_UNITTEST(2908, MinimumSumOfMountainTripletsI, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {8, 6, 1, 5, 3};
  int         expect   = 9;
  int         actual   = solution->minimumSum(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [5,4,8,7,10,2]
// Output: 13
//
// Triplet (1, 3, 5) is a mountain triplet of sum 13 since:
// - 1 < 3 < 5
// - nums[1] < nums[3] and nums[5] < nums[3]
// And the sum of this triplet is nums[1] + nums[3] + nums[5] = 13. It can be
// shown that there are no mountain triplets with a sum of less than 13.

LEETCODE_SOLUTION_UNITTEST(2908, MinimumSumOfMountainTripletsI, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {5, 4, 8, 7, 10, 2};
  int         expect   = 13;
  int         actual   = solution->minimumSum(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [6,5,4,3,4,5]
// Output: -1
//
// It can be shown that there are no mountain triplets in nums.

LEETCODE_SOLUTION_UNITTEST(2908, MinimumSumOfMountainTripletsI, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {6, 5, 4, 3, 4, 5};
  int         expect   = -1;
  int         actual   = solution->minimumSum(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Smallest Missing Integer Greater Than Sequential Prefix Sum
//
// https://leetcode.com/problems/smallest-missing-integer-greater-than-sequential-prefix-sum/
//
// Question ID: 2996
// Difficult  : Easy
// Solve Date : 2024/02/19 21:26

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2996. Smallest Missing Integer Greater Than Sequential Prefix
// Sum|:
//
// You are given a 0-indexed array of integers |nums|.
// A prefix |nums[0..i]| is sequential if, for all |1 <= j <= i|, |nums[j] =
// nums[j - 1] + 1|. In particular, the prefix consisting only of |nums[0]| is
// sequential. Return the smallest integer |x| missing from |nums| such that |x|
// is greater than or equal to the sum of the longest sequential prefix.
//
//

LEETCODE_BEGIN_RESOLVING(2996,
                         SmallestMissingIntegerGreaterThanSequentialPrefixSum,
                         Solution);

class Solution {
public:
  int missingInteger(vector<int> &nums) {
    vector<int> cnt(51, 0);
    int         res = nums.front();
    for (auto x : nums) {
      ++cnt[x];
    }
    for (int i = 1; i < nums.size(); ++i) {
      if (nums[i] != nums[i - 1] + 1) {
        break;
      }
      res += nums[i];
    }
    for (; res < cnt.size(); ++res) {
      if (!cnt[res]) {
        break;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 50|
// * |1 <= nums[i] <= 50|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,3,2,5]
// Output: 6
//
// The longest sequential prefix of nums is [1,2,3] with a sum of 6. 6 is not in
// the array, therefore 6 is the smallest missing integer greater than or equal
// to the sum of the longest sequential prefix.

LEETCODE_SOLUTION_UNITTEST(2996,
                           SmallestMissingIntegerGreaterThanSequentialPrefixSum,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 2, 5};
  int         expect   = 6;
  int         actual   = solution->missingInteger(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [3,4,5,1,12,14,13]
// Output: 15
//
// The longest sequential prefix of nums is [3,4,5] with a sum of 12. 12, 13,
// and 14 belong to the array while 15 does not. Therefore 15 is the smallest
// missing integer greater than or equal to the sum of the longest sequential
// prefix.

LEETCODE_SOLUTION_UNITTEST(2996,
                           SmallestMissingIntegerGreaterThanSequentialPrefixSum,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 4, 5, 1, 12, 14, 13};
  int         expect   = 15;
  int         actual   = solution->missingInteger(nums);
  LCD_EXPECT_EQ(expect, actual);
}

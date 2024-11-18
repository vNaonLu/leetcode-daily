// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Adjacent Increasing Subarrays Detection I
//
// https://leetcode.com/problems/adjacent-increasing-subarrays-detection-i/
//
// Question ID: 3349
// Difficult  : Easy
// Solve Date : 2024/11/17 12:22

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3349. Adjacent Increasing Subarrays Detection I|:
//
// Given an array |nums| of |n| integers and an integer |k|, determine whether
// there exist two adjacent subarrays of length |k| such that both subarrays are
// strictly increasing. Specifically, check if there are two subarrays starting
// at indices |a| and |b| ( |a < b|), where:
//
//  • Both subarrays |nums[a..a + k - 1]| and |nums[b..b + k - 1]| are strictly
//  increasing.
//
//  • The subarrays must be adjacent, meaning |b = a + k|.
// Return |true| if it is possible to find two such subarrays, and |false|
// otherwise.
//
//

LEETCODE_BEGIN_RESOLVING(3349, AdjacentIncreasingSubarraysDetectionI, Solution);

class Solution {
public:
  bool hasIncreasingSubarrays(vector<int> &nums, int k) {
    int n   = nums.size();
    int up  = 1;
    int pre = 0;
    int res = 0;
    for (int i = 1; i < n; ++i) {
      if (nums[i] > nums[i - 1]) {
        ++up;
      } else {
        pre = up;
        up  = 1;
      }
      res = max({res, up / 2, min(pre, up)});
    }
    return res >= k;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= nums.length <= 100|
// * |1 < 2 * k <= nums.length|
// * |-1000 <= nums[i] <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [2,5,7,8,9,2,3,4,3,1], k = 3
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(3349, AdjacentIncreasingSubarraysDetectionI,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 5, 7, 8, 9, 2, 3, 4, 3, 1};
  int         k        = 3;
  bool        expect   = true;
  bool        actual   = solution->hasIncreasingSubarrays(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,2,3,4,4,4,4,5,6,7], k = 5
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(3349, AdjacentIncreasingSubarraysDetectionI,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 4, 4, 4, 4, 5, 6, 7};
  int         k        = 5;
  bool        expect   = false;
  bool        actual   = solution->hasIncreasingSubarrays(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

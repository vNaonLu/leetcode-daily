// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Smallest Range I
//
// https://leetcode.com/problems/smallest-range-i/
//
// Question ID: 908
// Difficult  : Easy
// Solve Date : 2022/11/18 10:09

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |908. Smallest Range I|:
//
// You are given an integer array |nums| and an integer |k|.
// In one operation, you can choose any index |i| where |0 <= i < nums.length|
// and change |nums[i]| to |nums[i] + x| where |x| is an integer from the range
// |[-k, k]|. You can apply this operation at most once for each index |i|. The
// score of |nums| is the difference between the maximum and minimum elements in
// |nums|. Return the minimum score of |nums| after applying the mentioned
// operation at most once for each index in it.
//

LEETCODE_BEGIN_RESOLVING(908, SmallestRangeI, Solution);

class Solution {
public:
  int smallestRangeI(vector<int> &nums, int k) {
    auto mx = *max_element(nums.begin(), nums.end());
    auto mn = *min_element(nums.begin(), nums.end());
    return max(0, mx - mn - k - k);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁴|
// * |0 <= nums[i] <= 10⁴|
// * |0 <= k <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1], k = 0
// Output: 0
//
// The score is max(nums) - min(nums) = 1 - 1 = 0.

LEETCODE_SOLUTION_UNITTEST(908, SmallestRangeI, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1};
  int         k        = 0;
  int         expect   = 0;
  int         actual   = solution->smallestRangeI(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [0,10], k = 2
// Output: 6
//
// Change nums to be [2, 8]. The score is max(nums) - min(nums) = 8 - 2 = 6.

LEETCODE_SOLUTION_UNITTEST(908, SmallestRangeI, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {0, 10};
  int         k        = 2;
  int         expect   = 6;
  int         actual   = solution->smallestRangeI(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [1,3,6], k = 3
// Output: 0
//
// Change nums to be [4, 4, 4]. The score is max(nums) - min(nums) = 4 - 4 = 0.

LEETCODE_SOLUTION_UNITTEST(908, SmallestRangeI, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 3, 6};
  int         k        = 3;
  int         expect   = 0;
  int         actual   = solution->smallestRangeI(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

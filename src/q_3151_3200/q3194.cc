// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Minimum Average of Smallest and Largest Elements
//
// https://leetcode.com/problems/minimum-average-of-smallest-and-largest-elements/
//
// Question ID: 3194
// Difficult  : Easy
// Solve Date : 2024/06/30 12:14

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3194. Minimum Average of Smallest and Largest Elements|:
//
// You have an array of floating point numbers |averages| which is initially
// empty. You are given an array |nums| of |n| integers where |n| is even. You
// repeat the following procedure |n / 2| times:
//
//  • Remove the smallest element, |minElement|, and the largest element
//  |maxElement|, from |nums|.
//
//  • Add |(minElement + maxElement) / 2| to |averages|.
// Return the minimum element in |averages|.
//
//

LEETCODE_BEGIN_RESOLVING(3194, MinimumAverageOfSmallestAndLargestElements,
                         Solution);

class Solution {
public:
  double minimumAverage(vector<int> &nums) {
    sort(nums.begin(), nums.end());
    double res = numeric_limits<double>::max();
    for (int lo = 0, hi = nums.size() - 1; lo < hi; ++lo, --hi) {
      res = min(res, 0.5 * (nums[lo] + nums[hi]));
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= n == nums.length <= 50|
// * |n| is even.
// * |1 <= nums[i] <= 50|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [7,8,3,4,15,13,4,1]
// Output: 5.5
//

LEETCODE_SOLUTION_UNITTEST(3194, MinimumAverageOfSmallestAndLargestElements,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {7, 8, 3, 4, 15, 13, 4, 1};
  double      expect   = 5.5;
  double      actual   = solution->minimumAverage(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,9,8,3,10,5]
// Output: 5.5
//

LEETCODE_SOLUTION_UNITTEST(3194, MinimumAverageOfSmallestAndLargestElements,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 9, 8, 3, 10, 5};
  double      expect   = 5.5;
  double      actual   = solution->minimumAverage(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [1,2,3,7,8,9]
// Output: 5.0
//

LEETCODE_SOLUTION_UNITTEST(3194, MinimumAverageOfSmallestAndLargestElements,
                           example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 7, 8, 9};
  double      expect   = 5.0;
  double      actual   = solution->minimumAverage(nums);
  LCD_EXPECT_EQ(expect, actual);
}

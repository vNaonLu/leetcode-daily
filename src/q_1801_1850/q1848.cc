// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimum Distance to the Target Element
//
// https://leetcode.com/problems/minimum-distance-to-the-target-element/
//
// Question ID: 1848
// Difficult  : Easy
// Solve Date : 2023/09/13 19:20

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1848. Minimum Distance to the Target Element|:
//
// Given an integer array |nums| (0-indexed) and two integers |target| and
// |start|, find an index |i| such that |nums[i] == target| and |abs(i - start)|
// is minimized. Note that |abs(x)| is the absolute value of |x|. Return |abs(i
// - start)|. It is guaranteed that |target| exists in |nums|.
//
//

LEETCODE_BEGIN_RESOLVING(1848, MinimumDistanceToTheTargetElement, Solution);

class Solution {
public:
  int getMinDistance(vector<int> &nums, int target, int start) {
    int res = numeric_limits<int>::max();
    for (int i = 0; i < nums.size(); ++i) {
      if (nums[i] == target) {
        res = min(res, abs(start - i));
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 1000|
// * |1 <= nums[i] <= 10⁴|
// * |0 <= start < nums.length|
// * |target| is in |nums|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,3,4,5], target = 5, start = 3
// Output: 1
//
// nums[4] = 5 is the only value equal to target, so the answer is abs(4 - 3)
// = 1.

LEETCODE_SOLUTION_UNITTEST(1848, MinimumDistanceToTheTargetElement, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 4, 5};
  int         target   = 5;
  int         start    = 3;
  int         expect   = 1;
  int         actual   = solution->getMinDistance(nums, target, start);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1], target = 1, start = 0
// Output: 0
//
// nums[0] = 1 is the only value equal to target, so the answer is abs(0 - 0) =
// 0.

LEETCODE_SOLUTION_UNITTEST(1848, MinimumDistanceToTheTargetElement, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1};
  int         target   = 1;
  int         start    = 0;
  int         expect   = 0;
  int         actual   = solution->getMinDistance(nums, target, start);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [1,1,1,1,1,1,1,1,1,1], target = 1, start = 0
// Output: 0
//
// Every value of nums is 1, but nums[0] minimizes abs(i - start), which is
// abs(0 - 0) = 0.

LEETCODE_SOLUTION_UNITTEST(1848, MinimumDistanceToTheTargetElement, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
  int         target   = 1;
  int         start    = 0;
  int         expect   = 0;
  int         actual   = solution->getMinDistance(nums, target, start);
  LCD_EXPECT_EQ(expect, actual);
}

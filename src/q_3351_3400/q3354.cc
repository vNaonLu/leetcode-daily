// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Make Array Elements Equal to Zero
//
// https://leetcode.com/problems/make-array-elements-equal-to-zero/
//
// Question ID: 3354
// Difficult  : Easy
// Solve Date : 2024/11/18 20:43

#include <iosfwd>
#include <numeric>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3354. Make Array Elements Equal to Zero|:
//
// You are given an integer array |nums|.
// Start by selecting a starting position |curr| such that |nums[curr] == 0|,
// and choose a movement direction of either left or right. After that, you
// repeat the following process:
//
//  • If |curr| is out of the range |[0, n - 1]|, this process ends.
//
//  • If |nums[curr] == 0|, move in the current direction by incrementing |curr|
//  if you are moving right, or decrementing |curr| if you are moving left.
//
//  • Else if |nums[curr] > 0|:
//
//
//    • Decrement |nums[curr]| by 1.
//
//    • Reverse your movement direction (left becomes right and vice versa).
//
//    • Take a step in your new direction.
//
//
// A selection of the initial position |curr| and movement direction is
// considered valid if every element in |nums| becomes 0 by the end of the
// process. Return the number of possible valid selections.
//
//

LEETCODE_BEGIN_RESOLVING(3354, MakeArrayElementsEqualToZero, Solution);

class Solution {
public:
  int countValidSelections(vector<int> &nums) {
    vector<int> sum(nums.size() + 1);
    partial_sum(nums.begin(), nums.end(), sum.begin() + 1);
    int res = 0;
    for (int i = 0; i < nums.size(); ++i) {
      if (nums[i] == 0) {
        if (sum.back() == 2 * sum[i]) {
          res += 2;
        } else if (abs(sum.back() - 2 * sum[i]) == 1) {
          res += 1;
        }
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 100|
// * |0 <= nums[i] <= 100|
// * There is at least one element |i| where |nums[i] == 0|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,0,2,0,3]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(3354, MakeArrayElementsEqualToZero, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 0, 2, 0, 3};
  int         expect   = 2;
  int         actual   = solution->countValidSelections(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [2,3,4,0,4,1,0]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(3354, MakeArrayElementsEqualToZero, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 3, 4, 0, 4, 1, 0};
  int         expect   = 0;
  int         actual   = solution->countValidSelections(nums);
  LCD_EXPECT_EQ(expect, actual);
}

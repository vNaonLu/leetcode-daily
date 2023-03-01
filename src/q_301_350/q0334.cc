// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Increasing Triplet Subsequence
//
// https://leetcode.com/problems/increasing-triplet-subsequence/
//
// Question ID: 334
// Difficult  : Medium
// Solve Date : 2021/09/23 08:00

#include <iosfwd>
#include <limits>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |334. Increasing Triplet Subsequence|:
//
// Given an integer array |nums|, return |true| if there exists a triple of
// indices |(i, j, k)| such that |i < j < k| and |nums[i] < nums[j] < nums[k]|.
// If no such indices exists, return |false|.  
//

LEETCODE_BEGIN_RESOLVING(334, IncreasingTripletSubsequence, Solution);

class Solution {
public:
  bool increasingTriplet(vector<int> &nums) {
    int first = numeric_limits<int>::max(), second = numeric_limits<int>::max();
    for (int i = 0; i < nums.size(); ++i) {
      if (first >= nums[i]) {
        first = nums[i];
      } else if (second >= nums[i]) {
        second = nums[i];
      } else {
        return true;
      }
    }
    return false;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 5 * 10⁵|
// * |-2³¹ <= nums[i] <= 2³¹ - 1|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,3,4,5]
// Output: true
//
// Any triplet where i < j < k is valid.

LEETCODE_SOLUTION_UNITTEST(334, IncreasingTripletSubsequence, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 4, 5};
  bool        expect   = true;
  bool        actual   = solution->increasingTriplet(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [5,4,3,2,1]
// Output: false
//
// No triplet exists.

LEETCODE_SOLUTION_UNITTEST(334, IncreasingTripletSubsequence, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {5, 4, 3, 2, 1};
  bool        expect   = false;
  bool        actual   = solution->increasingTriplet(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [2,1,5,0,4,6]
// Output: true
//
// The triplet (3, 4, 5) is valid because nums[3] == 0 < nums[4] == 4 < nums[5]
// == 6.

LEETCODE_SOLUTION_UNITTEST(334, IncreasingTripletSubsequence, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 1, 5, 0, 4, 6};
  bool        expect   = true;
  bool        actual   = solution->increasingTriplet(nums);
  LCD_EXPECT_EQ(expect, actual);
}

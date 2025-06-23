// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Maximum Difference Between Adjacent Elements in a Circular Array
//
// https://leetcode.com/problems/maximum-difference-between-adjacent-elements-in-a-circular-array/
//
// Question ID: 3423
// Difficult  : Easy
// Solve Date : 2025/06/12 21:24

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3423. Maximum Difference Between Adjacent Elements in a
// Circular Array|:
//
// Given a circular array |nums|, find the maximum absolute difference between
// adjacent elements. Note: In a circular array, the first and last elements are
// adjacent.
//
//

LEETCODE_BEGIN_RESOLVING(
    3423, MaximumDifferenceBetweenAdjacentElementsInACircularArray, Solution);

class Solution {
public:
  int maxAdjacentDistance(vector<int> &nums) {
    int  res = abs(nums.front() - nums.back());
    auto beg = ++nums.begin();
    while (beg != nums.end()) {
      res = max(res, abs(*(beg - 1) - *beg));
      ++beg;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= nums.length <= 100|
// * |-100 <= nums[i] <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,4]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(
    3423, MaximumDifferenceBetweenAdjacentElementsInACircularArray, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 4};
  int         expect   = 3;
  int         actual   = solution->maxAdjacentDistance(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [-5,-10,-5]
// Output: 5
//

LEETCODE_SOLUTION_UNITTEST(
    3423, MaximumDifferenceBetweenAdjacentElementsInACircularArray, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {-5, -10, -5};
  int         expect   = 5;
  int         actual   = solution->maxAdjacentDistance(nums);
  LCD_EXPECT_EQ(expect, actual);
}

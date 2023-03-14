// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Maximum Count of Positive Integer and Negative Integer
//
// https://leetcode.com/problems/maximum-count-of-positive-integer-and-negative-integer/
//
// Question ID: 2529
// Difficult  : Easy
// Solve Date : 2023/03/14 19:00

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2529. Maximum Count of Positive Integer and Negative
// Integer|:
//
// Given an array |nums| sorted in non-decreasing order, return the maximum
// between the number of positive integers and the number of negative integers.
//
//  • In other words, if the number of positive integers in |nums| is |pos| and
//  the number of negative integers is |neg|, then return the maximum of |pos|
//  and |neg|.
// Note that |0| is neither positive nor negative.
//

LEETCODE_BEGIN_RESOLVING(2529, MaximumCountOfPositiveIntegerAndNegativeInteger,
                         Solution);

class Solution {
public:
  int maximumCount(vector<int> &nums) {
    auto neg = lower_bound(nums.begin(), nums.end(), 0);
    auto pos = lower_bound(neg, nums.end(), 1);
    return max(distance(nums.begin(), neg), distance(pos, nums.end()));
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 2000|
// * |-2000 <= nums[i] <= 2000|
// * |nums| is sorted in a non-decreasing order.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [-2,-1,-1,1,2,3]
// Output: 3
//
// There are 3 positive integers and 3 negative integers. The maximum count
// among them is 3.

LEETCODE_SOLUTION_UNITTEST(2529,
                           MaximumCountOfPositiveIntegerAndNegativeInteger,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {-2, -1, -1, 1, 2, 3};
  int         expect   = 3;
  int         actual   = solution->maximumCount(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [-3,-2,-1,0,0,1,2]
// Output: 3
//
// There are 2 positive integers and 3 negative integers. The maximum count
// among them is 3.

LEETCODE_SOLUTION_UNITTEST(2529,
                           MaximumCountOfPositiveIntegerAndNegativeInteger,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {-3, -2, -1, 0, 0, 1, 2};
  int         expect   = 3;
  int         actual   = solution->maximumCount(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [5,20,66,1314]
// Output: 4
//
// There are 4 positive integers and 0 negative integers. The maximum count
// among them is 4.

LEETCODE_SOLUTION_UNITTEST(2529,
                           MaximumCountOfPositiveIntegerAndNegativeInteger,
                           example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {5, 20, 66, 1314};
  int         expect   = 4;
  int         actual   = solution->maximumCount(nums);
  LCD_EXPECT_EQ(expect, actual);
}

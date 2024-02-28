// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Type of Triangle
//
// https://leetcode.com/problems/type-of-triangle/
//
// Question ID: 3024
// Difficult  : Easy
// Solve Date : 2024/02/28 19:05

#include <algorithm>
#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3024. Type of Triangle|:
//
// You are given a 0-indexed integer array |nums| of size |3| which can form the
// sides of a triangle.
//
//  • A triangle is called equilateral if it has all sides of equal length.
//
//  • A triangle is called isosceles if it has exactly two sides of equal
//  length.
//
//  • A triangle is called scalene if all its sides are of different lengths.
// Return a string representing the type of triangle that can be formed or
// |"none"| if it cannot form a triangle.
//
//

LEETCODE_BEGIN_RESOLVING(3024, TypeOfTriangle, Solution);

class Solution {
public:
  string triangleType(vector<int> &nums) {
    sort(nums.begin(), nums.end());
    if (nums[0] + nums[1] <= nums[2]) {
      return "none";
    }

    if (nums[0] == nums[1] && nums[0] == nums[2]) {
      return "equilateral";
    }

    if (nums[0] != nums[1] && nums[0] != nums[2] && nums[2] != nums[1]) {
      return "scalene";
    }

    return "isosceles";
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |nums.length == 3|
// * |1 <= nums[i] <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [3,3,3]
// Output: "equilateral"
//
// Since all the sides are of equal length, therefore, it will form an
// equilateral triangle.

LEETCODE_SOLUTION_UNITTEST(3024, TypeOfTriangle, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 3, 3};
  string      expect   = "equilateral";
  string      actual   = solution->triangleType(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [3,4,5]
// Output: "scalene"
//
// nums[0] + nums[1] = 3 + 4 = 7, which is greater than nums[2] = 5.
// nums[0] + nums[2] = 3 + 5 = 8, which is greater than nums[1] = 4.
// nums[1] + nums[2] = 4 + 5 = 9, which is greater than nums[0] = 3.
// Since the sum of the two sides is greater than the third side for all three
// cases, therefore, it can form a triangle. As all the sides are of different
// lengths, it will form a scalene triangle.

LEETCODE_SOLUTION_UNITTEST(3024, TypeOfTriangle, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 4, 5};
  string      expect   = "scalene";
  string      actual   = solution->triangleType(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Largest Perimeter Triangle
//
// https://leetcode.com/problems/largest-perimeter-triangle/
//
// Question ID: 976
// Difficult  : Easy
// Solve Date : 2022/04/16 11:12

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |976. Largest Perimeter Triangle|:
//
// Given an integer array |nums|, return the largest perimeter of a triangle
// with a non-zero area, formed from three of these lengths. If it is impossible
// to form any triangle of a non-zero area, return |0|.  
//

LEETCODE_BEGIN_RESOLVING(976, LargestPerimeterTriangle, Solution);

class Solution {
private:
  int helper(vector<int> &nums, int i) {
    if (i + 2 >= nums.size()) {
      return 0;
    }
    int sum = nums[i] + nums[i + 1] + nums[i + 2];

    return max(nums[i] + nums[i + 1] > nums[i + 2] &&
                       nums[i + 1] + nums[i + 2] > nums[i] &&
                       nums[i] + nums[i + 2] > nums[i + 1]
                   ? sum
                   : 0,
               helper(nums, i + 1));
  }

public:
  int largestPerimeter(vector<int> &nums) {
    sort(nums.begin(), nums.end());

    return helper(nums, 0);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |3 <= nums.length <= 10⁴|
// * |1 <= nums[i] <= 10⁶|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [2,1,2]
// Output: 5
//
// You can form a triangle with three side lengths: 1, 2, and 2.

LEETCODE_SOLUTION_UNITTEST(976, LargestPerimeterTriangle, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 1, 2};
  int         expect   = 5;
  int         actual   = solution->largestPerimeter(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,2,1,10]
// Output: 0
//
// You cannot use the side lengths 1, 1, and 2 to form a triangle.
// You cannot use the side lengths 1, 1, and 10 to form a triangle.
// You cannot use the side lengths 1, 2, and 10 to form a triangle.
// As we cannot use any three side lengths to form a triangle of non-zero area,
// we return 0.

LEETCODE_SOLUTION_UNITTEST(976, LargestPerimeterTriangle, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 1, 10};
  int         expect   = 0;
  int         actual   = solution->largestPerimeter(nums);
  LCD_EXPECT_EQ(expect, actual);
}

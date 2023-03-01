// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Valid Triangle Number
//
// https://leetcode.com/problems/valid-triangle-number/
//
// Question ID: 611
// Difficult  : Medium
// Solve Date : 2022/07/14 22:39

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |611. Valid Triangle Number|:
//
// Given an integer array |nums|, return the number of triplets chosen from the
// array that can make triangles if we take them as side lengths of a triangle.
//

LEETCODE_BEGIN_RESOLVING(611, ValidTriangleNumber, Solution);

class Solution {
public:
  int triangleNumber(vector<int> &nums) {
    sort(nums.begin(), nums.end());
    int res = 0;

    for (int i = 0; i < (int)nums.size() - 2; ++i) {
      int k = i + 2;
      for (int j = i + 1; j < nums.size() - 1 && nums[i] != 0; ++j) {
        while (k < nums.size() && nums[i] + nums[j] > nums[k]) {
          ++k;
        }
        res += k - j - 1;
      }
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 1000|
// * |0 <= nums[i] <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [2,2,3,4]
// Output: 3
//
// Valid combinations are:
// 2,3,4 (using the first 2)
// 2,3,4 (using the second 2)
// 2,2,3

LEETCODE_SOLUTION_UNITTEST(611, ValidTriangleNumber, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 2, 3, 4};
  int         expect   = 3;
  int         actual   = solution->triangleNumber(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [4,2,3,4]
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(611, ValidTriangleNumber, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {4, 2, 3, 4};
  int         expect   = 4;
  int         actual   = solution->triangleNumber(nums);
  LCD_EXPECT_EQ(expect, actual);
}

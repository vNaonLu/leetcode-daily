// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Transformed Array
//
// https://leetcode.com/problems/transformed-array/
//
// Question ID: 3379
// Difficult  : Easy
// Solve Date : 2024/12/25 19:16

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3379. Transformed Array|:
//
// You are given an integer array |nums| that represents a circular array. Your
// task is to create a new array |result| of the same size, following these
// rules: For each index |i| (where |0 <= i < nums.length|), perform the
// following independent actions:
//
//  • If |nums[i] > 0|: Start at index |i| and move |nums[i]| steps to the right
//  in the circular array. Set |result[i]| to the value of the index where you
//  land.
//
//  • If |nums[i] < 0|: Start at index |i| and move |abs(nums[i])| steps to the
//  left in the circular array. Set |result[i]| to the value of the index where
//  you land.
//
//  • If |nums[i] == 0|: Set |result[i]| to |nums[i]|.
// Return the new array |result|.
// Note: Since |nums| is circular, moving past the last element wraps around to
// the beginning, and moving before the first element wraps back to the end.
//
//

LEETCODE_BEGIN_RESOLVING(3379, TransformedArray, Solution);

class Solution {
public:
  vector<int> constructTransformedArray(vector<int> &nums) {
    vector<int> res = nums;
    int         n   = nums.size();
    for (int i = 0; i < nums.size(); ++i) {
      res[i] = nums[(i + nums[i] % n + n) % n];
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 100|
// * |-100 <= nums[i] <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [3,-2,1,1]
// Output: [1,1,1,3]
//

LEETCODE_SOLUTION_UNITTEST(3379, TransformedArray, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, -2, 1, 1};
  vector<int> expect   = {1, 1, 1, 3};
  vector<int> actual   = solution->constructTransformedArray(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [-1,4,-1]
// Output: [-1,-1,4]
//

LEETCODE_SOLUTION_UNITTEST(3379, TransformedArray, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {-1, 4, -1};
  vector<int> expect   = {-1, -1, 4};
  vector<int> actual   = solution->constructTransformedArray(nums);
  LCD_EXPECT_EQ(expect, actual);
}

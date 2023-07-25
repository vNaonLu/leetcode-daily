// Copyright 2023 Naon Lu
//
// This file describes the solution of
// N-Repeated Element in Size 2N Array
//
// https://leetcode.com/problems/n-repeated-element-in-size-2n-array/
//
// Question ID: 961
// Difficult  : Easy
// Solve Date : 2023/07/20 19:54

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |961. N-Repeated Element in Size 2N Array|:
//
// You are given an integer array |nums| with the following properties:
//
//  • |nums.length == 2 * n|.
//
//  • |nums| contains |n + 1| unique elements.
//
//  • Exactly one element of |nums| is repeated |n| times.
// Return the element that is repeated |n| times.
//
//

LEETCODE_BEGIN_RESOLVING(961, NRepeatedElementInSize2NArray, Solution);

class Solution {
public:
  int repeatedNTimes(vector<int> &nums) {
    int n = nums.size();
    for (int i = 0; i < n - 2; ++i) {
      if (nums[i] == nums[i + 1] || nums[i] == nums[i + 2]) {
        return nums[i];
      }
    }
    return nums.back();
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= n <= 5000|
// * |nums.length == 2 * n|
// * |0 <= nums[i] <= 10⁴|
// * |nums| contains |n + 1| unique elements and one of them is repeated exactly
// |n| times.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,3,3]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(961, NRepeatedElementInSize2NArray, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 3};
  int         expect   = 3;
  int         actual   = solution->repeatedNTimes(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [2,1,2,5,3,2]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(961, NRepeatedElementInSize2NArray, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 1, 2, 5, 3, 2};
  int         expect   = 2;
  int         actual   = solution->repeatedNTimes(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [5,1,5,2,5,3,5,4]
// Output: 5
//

LEETCODE_SOLUTION_UNITTEST(961, NRepeatedElementInSize2NArray, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {5, 1, 5, 2, 5, 3, 5, 4};
  int         expect   = 5;
  int         actual   = solution->repeatedNTimes(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: [9,5,3,3]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(961, NRepeatedElementInSize2NArray,
                           extra_testcase_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {9, 5, 3, 3};
  int         expect   = 3;
  int         actual   = solution->repeatedNTimes(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Smallest Index With Equal Value
//
// https://leetcode.com/problems/smallest-index-with-equal-value/
//
// Question ID: 2057
// Difficult  : Easy
// Solve Date : 2023/01/01 14:48

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2057. Smallest Index With Equal Value|:
//
// Given a 0-indexed integer array |nums|, return the smallest index |i| of
// |nums| such that |i mod 10 == nums[i]|, or |-1| if such index does not exist.
// |x mod y| denotes the remainder when |x| is divided by |y|.
//

LEETCODE_BEGIN_RESOLVING(2057, SmallestIndexWithEqualValue, Solution);

class Solution {
public:
  int smallestEqual(vector<int> &nums) {
    for (int i = 0; i < nums.size(); ++i) {
      if (i % 10 == nums[i]) {
        return i;
      }
    }
    return -1;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 100|
// * |0 <= nums[i] <= 9|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [0,1,2]
// Output: 0
//
// i=0: 0 mod 10 = 0 == nums[0].
// i=1: 1 mod 10 = 1 == nums[1].
// i=2: 2 mod 10 = 2 == nums[2].
// All indices have i mod 10 == nums[i], so we return the smallest index 0.

LEETCODE_SOLUTION_UNITTEST(2057, SmallestIndexWithEqualValue, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {0, 1, 2};
  int         expect   = 0;
  int         actual   = solution->smallestEqual(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [4,3,2,1]
// Output: 2
//
// i=0: 0 mod 10 = 0 != nums[0].
// i=1: 1 mod 10 = 1 != nums[1].
// i=2: 2 mod 10 = 2 == nums[2].
// i=3: 3 mod 10 = 3 != nums[3].
// 2 is the only index which has i mod 10 == nums[i].

LEETCODE_SOLUTION_UNITTEST(2057, SmallestIndexWithEqualValue, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {4, 3, 2, 1};
  int         expect   = 2;
  int         actual   = solution->smallestEqual(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [1,2,3,4,5,6,7,8,9,0]
// Output: -1
//
// No index satisfies i mod 10 == nums[i].

LEETCODE_SOLUTION_UNITTEST(2057, SmallestIndexWithEqualValue, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
  int         expect   = -1;
  int         actual   = solution->smallestEqual(nums);
  LCD_EXPECT_EQ(expect, actual);
}

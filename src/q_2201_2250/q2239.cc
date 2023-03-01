// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Find Closest Number to Zero
//
// https://leetcode.com/problems/find-closest-number-to-zero/
//
// Question ID: 2239
// Difficult  : Easy
// Solve Date : 2023/01/16 16:08

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2239. Find Closest Number to Zero|:
//
// Given an integer array |nums| of size |n|, return the number with the value
// closest to |0| in |nums|. If there are multiple answers, return the number
// with the largest value.
//

LEETCODE_BEGIN_RESOLVING(2239, FindClosestNumberToZero, Solution);

class Solution {
public:
  int findClosestNumber(vector<int> &nums) {
    auto res = nums.front();
    for (auto x : nums) {
      if (abs(res) > abs(x) || (abs(res) == abs(x) && x > res)) {
        res = x;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n <= 1000|
// * |-10⁵ <= nums[i] <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [-4,-2,1,4,8]
// Output: 1
//
// The distance from -4 to 0 is |-4| = 4.
// The distance from -2 to 0 is |-2| = 2.
// The distance from 1 to 0 is |1| = 1.
// The distance from 4 to 0 is |4| = 4.
// The distance from 8 to 0 is |8| = 8.
// Thus, the closest number to 0 in the array is 1.

LEETCODE_SOLUTION_UNITTEST(2239, FindClosestNumberToZero, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {-4, -2, 1, 4, 8};
  int         expect   = 1;
  int         actual   = solution->findClosestNumber(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [2,-1,1]
// Output: 1
//
// 1 and -1 are both the closest numbers to 0, so 1 being larger is returned.

LEETCODE_SOLUTION_UNITTEST(2239, FindClosestNumberToZero, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, -1, 1};
  int         expect   = 1;
  int         actual   = solution->findClosestNumber(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Find the Middle Index in Array
//
// https://leetcode.com/problems/find-the-middle-index-in-array/
//
// Question ID: 1991
// Difficult  : Easy
// Solve Date : 2022/05/21 14:03

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1991. Find the Middle Index in Array|:
//
// Given a 0-indexed integer array |nums|, find the leftmost |middleIndex|
// (i.e., the smallest amongst all the possible ones). A |middleIndex| is an
// index where |nums[0] + nums[1] + ... + nums[middleIndex-1] ==
// nums[middleIndex+1] + nums[middleIndex+2] + ... + nums[nums.length-1]|. If
// |middleIndex == 0|, the left side sum is considered to be |0|. Similarly, if
// |middleIndex == nums.length - 1|, the right side sum is considered to be |0|.
// Return the leftmost |middleIndex| that satisfies the condition, or |-1| if
// there is no such index.
//

LEETCODE_BEGIN_RESOLVING(1991, FindTheMiddleIndexInArray, Solution);

class Solution {
public:
  int findMiddleIndex(vector<int> &nums) {
    vector<int> sum = nums;
    for (int i = 1; i < sum.size(); ++i) {
      sum[i] += sum[i - 1];
    }

    for (int i = 0; i < sum.size(); ++i) {
      if (i == 0) {
        if (sum.back() - sum[i] == 0) {
          return i;
        }

      } else if (i == sum.size() - 1) {
        if (sum[i - 1] == 0) {
          return i;
        }

      } else if (sum[i - 1] == sum.back() - sum[i]) {
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
// * |-1000 <= nums[i] <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [2,3,-1,8,4]
// Output: 3
//
// The sum of the numbers before index 3 is: 2 + 3 + -1 = 4
// The sum of the numbers after index 3 is: 4 = 4

LEETCODE_SOLUTION_UNITTEST(1991, FindTheMiddleIndexInArray, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 3, -1, 8, 4};
  int         expect   = 3;
  int         actual   = solution->findMiddleIndex(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,-1,4]
// Output: 2
//
// The sum of the numbers before index 2 is: 1 + -1 = 0
// The sum of the numbers after index 2 is: 0

LEETCODE_SOLUTION_UNITTEST(1991, FindTheMiddleIndexInArray, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, -1, 4};
  int         expect   = 2;
  int         actual   = solution->findMiddleIndex(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [2,5]
// Output: -1
//
// There is no valid middleIndex.

LEETCODE_SOLUTION_UNITTEST(1991, FindTheMiddleIndexInArray, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 5};
  int         expect   = -1;
  int         actual   = solution->findMiddleIndex(nums);
  LCD_EXPECT_EQ(expect, actual);
}

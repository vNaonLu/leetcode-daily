// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Running Sum of 1d Array
//
// https://leetcode.com/problems/running-sum-of-1d-array/
//
// Question ID: 1480
// Difficult  : Easy
// Solve Date : 2021/11/01 18:23

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1480. Running Sum of 1d Array|:
//
// Given an array |nums|. We define a running sum of an array as  |runningSum[i]
// = sum(nums[0]…nums[i])|.
//
// Return the running sum of |nums|.
//
//  
//

LEETCODE_BEGIN_RESOLVING(1480, RunningSumOf1dArray, Solution);

class Solution {
public:
  vector<int> runningSum(vector<int> &nums) {
    auto res = vector<int>(nums.begin(), nums.end());
    for (auto it = res.begin() + 1; it != res.end(); ++it) {
      *it += *(it - 1);
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 1000|
// * |-10^6 <= nums[i] <= 10^6|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,3,4]
// Output: [1,3,6,10]
//
// Running sum is obtained as follows: [1, 1+2, 1+2+3, 1+2+3+4].

LEETCODE_SOLUTION_UNITTEST(1480, RunningSumOf1dArray, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 4};
  vector<int> expect   = {1, 3, 6, 10};
  vector<int> actual   = solution->runningSum(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,1,1,1,1]
// Output: [1,2,3,4,5]
//
// Running sum is obtained as follows: [1, 1+1, 1+1+1, 1+1+1+1, 1+1+1+1+1].

LEETCODE_SOLUTION_UNITTEST(1480, RunningSumOf1dArray, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 1, 1, 1, 1};
  vector<int> expect   = {1, 2, 3, 4, 5};
  vector<int> actual   = solution->runningSum(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [3,1,2,10,1]
// Output: [3,4,6,16,17]
//

LEETCODE_SOLUTION_UNITTEST(1480, RunningSumOf1dArray, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 1, 2, 10, 1};
  vector<int> expect   = {3, 4, 6, 16, 17};
  vector<int> actual   = solution->runningSum(nums);
  LCD_EXPECT_EQ(expect, actual);
}

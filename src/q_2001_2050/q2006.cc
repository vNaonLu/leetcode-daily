// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Count Number of Pairs With Absolute Difference K
//
// https://leetcode.com/problems/count-number-of-pairs-with-absolute-difference-k/
//
// Question ID: 2006
// Difficult  : Easy
// Solve Date : 2022/05/01 11:21

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2006. Count Number of Pairs With Absolute Difference K|:
//
// Given an integer array |nums| and an integer |k|, return the number of pairs
// |(i, j)| where |i < j| such that ||nums[i] - nums[j]| == k|. The value of
// ||x|| is defined as:
//
//  • |x| if |x >= 0|.
//
//  • |-x| if |x < 0|.
//  
//

LEETCODE_BEGIN_RESOLVING(2006, CountNumberOfPairsWithAbsoluteDifferenceK,
                         Solution);

class Solution {
public:
  int countKDifference(vector<int> &nums, int k) {
    int res = 0;
    for (int i = 0; i < nums.size() - 1; ++i) {
      for (int j = i + 1; j < nums.size(); ++j) {
        if (abs(nums[j] - nums[i]) == k) {
          ++res;
        }
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 200|
// * |1 <= nums[i] <= 100|
// * |1 <= k <= 99|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,2,1], k = 1
// Output: 4
//
// The pairs with an absolute difference of 1 are:
// - [1,2,2,1]
// - [1,2,2,1]
// - [1,2,2,1]
// - [1,2,2,1]

LEETCODE_SOLUTION_UNITTEST(2006, CountNumberOfPairsWithAbsoluteDifferenceK,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 2, 1};
  int         k        = 1;
  int         expect   = 4;
  int         actual   = solution->countKDifference(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,3], k = 3
// Output: 0
//
// There are no pairs with an absolute difference of 3.

LEETCODE_SOLUTION_UNITTEST(2006, CountNumberOfPairsWithAbsoluteDifferenceK,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 3};
  int         k        = 3;
  int         expect   = 0;
  int         actual   = solution->countKDifference(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [3,2,1,5,4], k = 2
// Output: 3
// Explanation: The pairs with an absolute difference of 2 are:
// - [3,2,1,5,4]
// - [3,2,1,5,4]
// - [3,2,1,5,4]
//

LEETCODE_SOLUTION_UNITTEST(2006, CountNumberOfPairsWithAbsoluteDifferenceK,
                           example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 2, 1, 5, 4};
  int         k        = 2;
  int         expect   = 3;
  int         actual   = solution->countKDifference(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Divide Array Into Arrays With Max Difference
//
// https://leetcode.com/problems/divide-array-into-arrays-with-max-difference/
//
// Question ID: 2966
// Difficult  : Medium
// Solve Date : 2024/02/01 18:52

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2966. Divide Array Into Arrays With Max Difference|:
//
// You are given an integer array |nums| of size |n| and a positive integer |k|.
// Divide the array into one or more arrays of size |3| satisfying the following
// conditions:
//
//  • Each element of |nums| should be in exactly one array.
//
//  • The difference between any two elements in one array is less than or equal
//  to |k|.
// Return a 2D array containing all the arrays. If it is impossible to satisfy
// the conditions, return an empty array. And if there are multiple answers,
// return any of them.
//
//

LEETCODE_BEGIN_RESOLVING(2966, DivideArrayIntoArraysWithMaxDifference,
                         Solution);

class Solution {
public:
  vector<vector<int>> divideArray(vector<int> &nums, int k) {
    vector<vector<int>> res;
    sort(nums.begin(), nums.end());
    for (int i = 2; i < nums.size(); i += 3) {
      if (nums[i] - nums[i - 2] > k) {
        return {};
      }

      res.push_back({nums[i - 2], nums[i - 1], nums[i]});
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |n == nums.length|
// * |1 <= n <= 10⁵|
// * |n| is a multiple of |3|.
// * |1 <= nums[i] <= 10⁵|
// * |1 <= k <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,3,4,8,7,9,3,5,1], k = 2
// Output: [[1,1,3],[3,4,5],[7,8,9]]
//
// We can divide the array into the following arrays: [1,1,3], [3,4,5] and
// [7,8,9]. The difference between any two elements in each array is less than
// or equal to 2. Note that the order of elements is not important.

LEETCODE_SOLUTION_UNITTEST(2966, DivideArrayIntoArraysWithMaxDifference,
                           example_1) {
  auto                solution = MakeSolution();
  vector<int>         nums     = {1, 3, 4, 8, 7, 9, 3, 5, 1};
  int                 k        = 2;
  vector<vector<int>> expect   = {
      {1, 1, 3},
      {3, 4, 5},
      {7, 8, 9}
  };
  vector<vector<int>> actual = solution->divideArray(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,3,3,2,7,3], k = 3
// Output: []
//
// It is not possible to divide the array satisfying all the conditions.

LEETCODE_SOLUTION_UNITTEST(2966, DivideArrayIntoArraysWithMaxDifference,
                           example_2) {
  auto                solution = MakeSolution();
  vector<int>         nums     = {1, 3, 3, 2, 7, 3};
  int                 k        = 3;
  vector<vector<int>> expect   = {};
  vector<vector<int>> actual   = solution->divideArray(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

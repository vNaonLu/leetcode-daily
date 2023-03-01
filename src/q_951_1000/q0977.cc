// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Squares of a Sorted Array
//
// https://leetcode.com/problems/squares-of-a-sorted-array/
//
// Question ID: 977
// Difficult  : Easy
// Solve Date : 2021/09/06 08:00

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |977. Squares of a Sorted Array|:
//
// Given an integer array |nums| sorted in non-decreasing order, return an array
// of the squares of each number sorted in non-decreasing order.  
//

LEETCODE_BEGIN_RESOLVING(977, SquaresofaSortedArray, Solution);

class Solution {
public:
  vector<int> sortedSquares(vector<int> &nums) {
    int         k = nums.size();
    vector<int> res(k);
    int         l = 0, r = k - 1;
    while (l <= r) {
      int ls = nums[l] * nums[l];
      int rs = nums[r] * nums[r];
      if (ls > rs) {
        res[--k] = ls;
        ++l;
      } else {
        res[--k] = rs;
        --r;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁴|
// * |-10⁴ <= nums[i] <= 10⁴|
// * |nums| is sorted in non-decreasing order.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [-4,-1,0,3,10]
// Output: [0,1,9,16,100]
//
// After squaring, the array becomes [16,1,0,9,100].
// After sorting, it becomes [0,1,9,16,100].

LEETCODE_SOLUTION_UNITTEST(977, SquaresofaSortedArray, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {-4, -1, 0, 3, 10};
  vector<int> expect   = {0, 1, 9, 16, 100};
  vector<int> actual   = solution->sortedSquares(nums);
  EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [-7,-3,2,3,11]
// Output: [4,9,9,49,121]
//

LEETCODE_SOLUTION_UNITTEST(977, SquaresofaSortedArray, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {-7, -3, 2, 3, 11};
  vector<int> expect   = {4, 9, 9, 49, 121};
  vector<int> actual   = solution->sortedSquares(nums);
  EXPECT_EQ(expect, actual);
}

// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Sum of Unique Elements
//
// https://leetcode.com/problems/sum-of-unique-elements/
//
// Question ID: 1748
// Difficult  : Easy
// Solve Date : 2022/12/16 18:30

#include <iosfwd>
#include <map>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1748. Sum of Unique Elements|:
//
// You are given an integer array |nums|. The unique elements of an array are
// the elements that appear exactly once in the array. Return the sum of all the
// unique elements of |nums|.
//

LEETCODE_BEGIN_RESOLVING(1748, SumOfUniqueElements, Solution);

class Solution {
public:
  int sumOfUnique(vector<int> &nums) {
    auto memo = unordered_map<int, int>();
    auto res  = (int)0;
    for (auto x : nums) {
      ++memo[x];
    }
    for (auto [x, cnt] : memo) {
      if (1 == cnt) {
        res += x;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 100|
// * |1 <= nums[i] <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,3,2]
// Output: 4
//
// The unique elements are [1,3], and the sum is 4.

LEETCODE_SOLUTION_UNITTEST(1748, SumOfUniqueElements, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 2};
  int         expect   = 4;
  int         actual   = solution->sumOfUnique(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,1,1,1,1]
// Output: 0
//
// There are no unique elements, and the sum is 0.

LEETCODE_SOLUTION_UNITTEST(1748, SumOfUniqueElements, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 1, 1, 1, 1};
  int         expect   = 0;
  int         actual   = solution->sumOfUnique(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [1,2,3,4,5]
// Output: 15
//
// The unique elements are [1,2,3,4,5], and the sum is 15.

LEETCODE_SOLUTION_UNITTEST(1748, SumOfUniqueElements, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 4, 5};
  int         expect   = 15;
  int         actual   = solution->sumOfUnique(nums);
  LCD_EXPECT_EQ(expect, actual);
}

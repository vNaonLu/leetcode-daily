// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Number of Good Pairs
//
// https://leetcode.com/problems/number-of-good-pairs/
//
// Question ID: 1512
// Difficult  : Easy
// Solve Date : 2022/12/07 19:34

#include <iosfwd>
#include <map>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1512. Number of Good Pairs|:
//
// Given an array of integers |nums|, return the number of good pairs.
// A pair |(i, j)| is called good if |nums[i] == nums[j]| and |i| < |j|.
//

LEETCODE_BEGIN_RESOLVING(1512, NumberOfGoodPairs, Solution);

class Solution {
public:
  int numIdenticalPairs(vector<int> &nums) {
    auto memo = unordered_map<int, int>();
    auto res  = (int)0;
    for (auto x : nums) {
      auto &cnt = memo[x];
      res += cnt++;
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
//  Input: nums = [1,2,3,1,1,3]
// Output: 4
//
// There are 4 good pairs (0,3), (0,4), (3,4), (2,5) 0-indexed.

LEETCODE_SOLUTION_UNITTEST(1512, NumberOfGoodPairs, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 1, 1, 3};
  int         expect   = 4;
  int         actual   = solution->numIdenticalPairs(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,1,1,1]
// Output: 6
//
// Each pair in the array are good.

LEETCODE_SOLUTION_UNITTEST(1512, NumberOfGoodPairs, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 1, 1, 1};
  int         expect   = 6;
  int         actual   = solution->numIdenticalPairs(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [1,2,3]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(1512, NumberOfGoodPairs, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3};
  int         expect   = 0;
  int         actual   = solution->numIdenticalPairs(nums);
  LCD_EXPECT_EQ(expect, actual);
}

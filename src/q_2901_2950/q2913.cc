// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Subarrays Distinct Element Sum of Squares I
//
// https://leetcode.com/problems/subarrays-distinct-element-sum-of-squares-i/
//
// Question ID: 2913
// Difficult  : Easy
// Solve Date : 2024/01/30 20:09

#include <iosfwd>
#include <map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2913. Subarrays Distinct Element Sum of Squares I|:
//
// You are given a 0-indexed integer array |nums|.
// The distinct count of a subarray of |nums| is defined as:
//
//  • Let |nums[i..j]| be a subarray of |nums| consisting of all the indices
//  from |i| to |j| such that |0 <= i <= j < nums.length|. Then the number of
//  distinct values in |nums[i..j]| is called the distinct count of
//  |nums[i..j]|.
// Return the sum of the squares of distinct counts of all subarrays of |nums|.
// A subarray is a contiguous non-empty sequence of elements within an array.
//
//

LEETCODE_BEGIN_RESOLVING(2913, SubarraysDistinctElementSumOfSquaresI, Solution);

class Solution {
public:
  int sumCounts(vector<int> &nums) {
    map<int, int> mp;
    int           res = 0;
    for (int i = 0; i < nums.size(); ++i) {
      for (int j = i; j < nums.size(); ++j) {
        int a = i;

        while (a <= j) {
          mp[nums[a]];
          ++a;
        }

        res += mp.size() * mp.size();
        mp.clear();
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 100|
// * |1 <= nums[i] <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,1]
// Output: 15
//
// Six possible subarrays are:
// [1]: 1 distinct value
// [2]: 1 distinct value
// [1]: 1 distinct value
// [1,2]: 2 distinct values
// [2,1]: 2 distinct values
// [1,2,1]: 2 distinct values
// The sum of the squares of the distinct counts in all subarrays is equal to 1²
// + 1² + 1² + 2² + 2² + 2² = 15.

LEETCODE_SOLUTION_UNITTEST(2913, SubarraysDistinctElementSumOfSquaresI,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 1};
  int         expect   = 15;
  int         actual   = solution->sumCounts(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,1]
// Output: 3
//
// Three possible subarrays are:
// [1]: 1 distinct value
// [1]: 1 distinct value
// [1,1]: 1 distinct value
// The sum of the squares of the distinct counts in all subarrays is equal to 1²
// + 1² + 1² = 3.

LEETCODE_SOLUTION_UNITTEST(2913, SubarraysDistinctElementSumOfSquaresI,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 1};
  int         expect   = 3;
  int         actual   = solution->sumCounts(nums);
  LCD_EXPECT_EQ(expect, actual);
}

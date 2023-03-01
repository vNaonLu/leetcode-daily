// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Largest Divisible Subset
//
// https://leetcode.com/problems/largest-divisible-subset/
//
// Question ID: 368
// Difficult  : Medium
// Solve Date : 2021/11/15 18:09

#include <algorithm>
#include <iosfwd>
#include <list>
#include <set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |368. Largest Divisible Subset|:
//
// Given a set of distinct positive integers |nums|, return the largest subset
// |answer| such that every pair |(answer[i], answer[j])| of elements in this
// subset satisfies:
//
//  • |answer[i] % answer[j] == 0|, or
//
//  • |answer[j] % answer[i] == 0|
// If there are multiple solutions, return any of them.
//  
//

LEETCODE_BEGIN_RESOLVING(368, LargestDivisibleSubset, Solution);

class Solution {
public:
  vector<int> largestDivisibleSubset(vector<int> &nums) {
    int n = nums.size();
    sort(nums.begin(), nums.end());
    vector<int> list(n, 1);
    vector<int> prev_idx(n, -1);
    int         max = 0, index = 0;
    for (int i = 0; i < n; ++i) {
      for (int j = i - 1; j >= 0; --j) {
        if (list[j] + 1 > list[i] && nums[i] % nums[j] == 0) {
          list[i]     = list[j] + 1;
          prev_idx[i] = j;
        }
      }
    }
    for (int i = 0; i < n; ++i) {
      if (list[i] > max) {
        max   = list[i];
        index = i;
      }
    }
    vector<int> res;
    while (index >= 0) {
      res.emplace_back(nums[index]);
      index = prev_idx[index];
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 1000|
// * |1 <= nums[i] <= 2 * 10⁹|
// * All the integers in |nums| are unique.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,3]
// Output: [1,2]
//
// [1,3] is also accepted.

LEETCODE_SOLUTION_UNITTEST(368, LargestDivisibleSubset, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3};
  vector<int> expect   = {1, 2};
  vector<int> actual   = solution->largestDivisibleSubset(nums);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,2,4,8]
// Output: [1,2,4,8]
//

LEETCODE_SOLUTION_UNITTEST(368, LargestDivisibleSubset, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 4, 8};
  vector<int> expect   = {1, 2, 4, 8};
  vector<int> actual   = solution->largestDivisibleSubset(nums);
  EXPECT_ANYORDER_EQ(expect, actual);
}

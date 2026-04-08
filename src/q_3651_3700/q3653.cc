// Copyright 2026 Naon Lu
//
// This file describes the solution of
// XOR After Range Multiplication Queries I
//
// https://leetcode.com/problems/xor-after-range-multiplication-queries-i/
//
// Question ID: 3653
// Difficult  : Medium
// Solve Date : 2026/04/08 11:57

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3653. XOR After Range Multiplication Queries I|:
//
// You are given an integer array |nums| of length |n| and a 2D integer array
// |queries| of size |q|, where |queries[i] = [lᵢ, rᵢ, kᵢ, vᵢ]|. For each query,
// you must apply the following operations in order:
//
//  • Set |idx = lᵢ|.
//
//  • While |idx <= rᵢ|:
//
//
//    • Update: |nums[idx] = (nums[idx] * vᵢ) % (10⁹ + 7)|
//
//    • Set |idx += kᵢ|.
//
//
// Return the bitwise XOR of all elements in |nums| after processing all
// queries.
//
//

LEETCODE_BEGIN_RESOLVING(3653, XORAfterRangeMultiplicationQueriesI, Solution);

class Solution {
public:
  int xorAfterQueries(vector<int> &nums, vector<vector<int>> &queries) {
    for (auto &q : queries) {
      int l   = q[0];
      int r   = q[1];
      int k   = q[2];
      int v   = q[3];
      int idx = l;
      while (idx <= r) {
        int64_t tmp = nums[idx];
        nums[idx]   = (tmp * v) % kMod;
        idx += k;
      }
    }

    int res = 0;
    for (auto x : nums) {
      res ^= x;
    }
    return res;
  }

private:
  static constexpr int kMod = 1e9 + 7;
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n == nums.length <= 10³|
// * |1 <= nums[i] <= 10⁹|
// * |1 <= q == queries.length <= 10³|
// * |queries[i] = [lᵢ, rᵢ, kᵢ, vᵢ]|
// * |0 <= lᵢ <= rᵢ < n|
// * |1 <= kᵢ <= n|
// * |1 <= vᵢ <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,1,1], queries = [[0,2,1,4]]
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(3653, XORAfterRangeMultiplicationQueriesI,
                           example_1) {
  auto                solution = MakeSolution();
  vector<int>         nums     = {1, 1, 1};
  vector<vector<int>> queries  = {
      {0, 2, 1, 4}
  };
  int expect = 4;
  int actual = solution->xorAfterQueries(nums, queries);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [2,3,1,5,4], queries = [[1,4,2,3],[0,2,1,2]]
// Output: 31
//

LEETCODE_SOLUTION_UNITTEST(3653, XORAfterRangeMultiplicationQueriesI,
                           example_2) {
  auto                solution = MakeSolution();
  vector<int>         nums     = {2, 3, 1, 5, 4};
  vector<vector<int>> queries  = {
      {1, 4, 2, 3},
      {0, 2, 1, 2}
  };
  int expect = 31;
  int actual = solution->xorAfterQueries(nums, queries);
  LCD_EXPECT_EQ(expect, actual);
}

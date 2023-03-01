// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Subsets
//
// https://leetcode.com/problems/subsets/
//
// Question ID: 78
// Difficult  : Medium
// Solve Date : 2021/09/27 13:25

#include <iosfwd>
#include <set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |78. Subsets|:
//
// Given an integer array |nums| of unique elements, return all possible subsets
// (the power set). The solution set must not contain duplicate subsets. Return
// the solution in any order.  
//

LEETCODE_BEGIN_RESOLVING(78, Subsets, Solution);

class Solution {
public:
  vector<vector<int>> subsets(vector<int> &nums) {
    vector<vector<int>> res;
    res.push_back({});
    for (const auto &n : nums) {
      int len = res.size();
      for (int i = 0; i < len; ++i) {
        vector<int> tmp = res[i];
        tmp.push_back(n);
        res.push_back(tmp);
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10|
// * |-10 <= nums[i] <= 10|
// * All the numbers of  |nums| are unique.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,3]
// Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
//

LEETCODE_SOLUTION_UNITTEST(78, Subsets, example_1) {
  auto                solution = MakeSolution();
  vector<int>         nums     = {1, 2, 3};
  vector<vector<int>> expect   = {
      {},
      {1},
      {2},
      {1, 2},
      {3},
      {1, 3},
      {2, 3},
      {1, 2, 3}
  };
  vector<vector<int>> actual = solution->subsets(nums);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [0]
// Output: [[],[0]]
//

LEETCODE_SOLUTION_UNITTEST(78, Subsets, example_2) {
  auto                solution = MakeSolution();
  vector<int>         nums     = {0};
  vector<vector<int>> expect   = {{}, {0}};
  vector<vector<int>> actual   = solution->subsets(nums);
  EXPECT_ANYORDER_EQ(expect, actual);
}

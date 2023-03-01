// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Permutations
//
// https://leetcode.com/problems/permutations/
//
// Question ID: 46
// Difficult  : Medium
// Solve Date : 2021/09/15 08:00

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |46. Permutations|:
//
// Given an array |nums| of distinct integers, return all the possible
// permutations. You can return the answer in any order.  
//

LEETCODE_BEGIN_RESOLVING(46, Permutations, Solution);

class Solution {
private:
  void helper(vector<vector<int>> &r, vector<int> &cur, int size) {
    if (size == 1) {
      r.push_back(cur);
    } else {
      for (int i = 0; i < size; ++i) {
        helper(r, cur, size - 1);
        if (size % 2) {
          swap(cur[0], cur[size - 1]);
        } else {
          swap(cur[i], cur[size - 1]);
        }
      }
    }
  }

public:
  vector<vector<int>> permute(vector<int> &nums) {
    vector<vector<int>> res;
    helper(res, nums, nums.size());
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 6|
// * |-10 <= nums[i] <= 10|
// * All the integers of |nums| are unique.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,3]
// Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
//

LEETCODE_SOLUTION_UNITTEST(46, Permutations, example_1) {
  auto                solution = MakeSolution();
  vector<int>         nums     = {1, 2, 3};
  vector<vector<int>> expect   = {
      {1, 2, 3},
      {1, 3, 2},
      {2, 1, 3},
      {2, 3, 1},
      {3, 1, 2},
      {3, 2, 1}
  };
  vector<vector<int>> actual = solution->permute(nums);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [0,1]
// Output: [[0,1],[1,0]]
//

LEETCODE_SOLUTION_UNITTEST(46, Permutations, example_2) {
  auto                solution = MakeSolution();
  vector<int>         nums     = {0, 1};
  vector<vector<int>> expect   = {
      {0, 1},
      {1, 0}
  };
  vector<vector<int>> actual = solution->permute(nums);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [1]
// Output: [[1]]
//

LEETCODE_SOLUTION_UNITTEST(46, Permutations, example_3) {
  auto                solution = MakeSolution();
  vector<int>         nums     = {1};
  vector<vector<int>> expect   = {{1}};
  vector<vector<int>> actual   = solution->permute(nums);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Combination Sum II
//
// https://leetcode.com/problems/combination-sum-ii/
//
// Question ID: 40
// Difficult  : Medium
// Solve Date : 2021/09/28 10:40

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |40. Combination Sum II|:
//
// Given a collection of candidate numbers (|candidates|) and a target number (
// |target|), find all unique combinations in |candidates| where the candidate
// numbers sum to |target|. Each number in |candidates| may only be used once in
// the combination. Note: The solution set must not contain duplicate
// combinations.  
//

LEETCODE_BEGIN_RESOLVING(40, CombinationSumII, Solution);

class Solution {
  void helper(vector<int> &cand, vector<vector<int>> &r, const int &t,
              vector<int> &c, int &sum, int beg = 0) {
    if (sum == t) {
      r.push_back(c);
    } else if (sum <= t && beg < cand.size()) {
      int i   = beg;
      int num = cand[i];
      while (i < cand.size() && num == cand[i])
        ++i;
      int same = i - beg;
      helper(cand, r, t, c, sum, i);
      for (int j = 0; j < same; ++j) {
        sum += num;
        c.push_back(num);
        helper(cand, r, t, c, sum, i);
      }
      for (int j = 0; j < same; ++j) {
        sum -= num;
        c.pop_back();
      }
    }
  }

public:
  vector<vector<int>> combinationSum2(vector<int> &candidates, int target) {
    sort(candidates.begin(), candidates.end());
    vector<vector<int>> res;
    vector<int>         tmp;
    int                 sum = 0;
    helper(candidates, res, target, tmp, sum, 0);
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= candidates.length <= 100|
// * |1 <= candidates[i] <= 50|
// * |1 <= target <= 30|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: candidates = [10,1,2,7,6,1,5], target = 8
// Output: [
// [1,1,6],
// [1,2,5],
// [1,7],
// [2,6]
// ]
//

LEETCODE_SOLUTION_UNITTEST(40, CombinationSumII, example_1) {
  auto                solution   = MakeSolution();
  vector<int>         candidates = {10, 1, 2, 7, 6, 1, 5};
  int                 target     = 8;
  vector<vector<int>> expect     = {
      {1, 1, 6},
      {1, 2, 5},
      {1, 7},
      {2, 6}
  };
  vector<vector<int>> actual = solution->combinationSum2(candidates, target);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #2]
//  Input: candidates = [2,5,2,1,2], target = 5
// Output: [
// [1,2,2],
// [5]
// ]
//

LEETCODE_SOLUTION_UNITTEST(40, CombinationSumII, example_2) {
  auto                solution   = MakeSolution();
  vector<int>         candidates = {2, 5, 2, 1, 2};
  int                 target     = 5;
  vector<vector<int>> expect     = {
      {1, 2, 2},
      {5}
  };
  vector<vector<int>> actual = solution->combinationSum2(candidates, target);
  EXPECT_ANYORDER_EQ(expect, actual);
}

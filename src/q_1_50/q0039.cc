// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Combination Sum
//
// https://leetcode.com/problems/combination-sum/
//
// Question ID: 39
// Difficult  : Medium
// Solve Date : 2021/09/28 10:15

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |39. Combination Sum|:
//
// Given an array of distinct integers |candidates| and a target integer
// |target|, return a list of all unique combinations of |candidates| where the
// chosen numbers sum to |target|. You may return the combinations in any order.
// The same number may be chosen from |candidates| an unlimited number of times.
// Two combinations are unique if the frequency of at least one of the chosen
// numbers is different. The test cases are generated such that the number of
// unique combinations that sum up to |target| is less than |150| combinations
// for the given input.  
//

LEETCODE_BEGIN_RESOLVING(39, CombinationSum, Solution);

class Solution {
private:
  template <typename Iterator>
  void solve(Iterator beg, Iterator end, vector<vector<int>> &res,
             vector<int> &curr, int curr_sum, int target) {
    if (curr_sum > target) {
      return;
    } else if (curr_sum == target) {
      res.emplace_back(curr.begin(), curr.end());
    } else {
      while (beg != end) {
        curr.emplace_back(*beg);
        solve(beg, end, res, curr, curr_sum + *beg, target);
        curr.pop_back();
        ++beg;
      }
    }
  }

public:
  vector<vector<int>> combinationSum(vector<int> &candidates, int target) {
    auto res = vector<vector<int>>();
    auto tmp = vector<int>();
    solve(candidates.begin(), candidates.end(), res, tmp, 0, target);
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= candidates.length <= 30|
// * |2 <= candidates[i] <= 40|
// * All elements of |candidates| are distinct.
// * |1 <= target <= 40|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: candidates = [2,3,6,7], target = 7
// Output: [[2,2,3],[7]]
//
// 2 and 3 are candidates, and 2 + 2 + 3 = 7. Note that 2 can be used multiple
// times. 7 is a candidate, and 7 = 7. These are the only two combinations.

LEETCODE_SOLUTION_UNITTEST(39, CombinationSum, example_1) {
  auto                solution   = MakeSolution();
  vector<int>         candidates = {2, 3, 6, 7};
  int                 target     = 7;
  vector<vector<int>> expect     = {
      {2, 2, 3},
      {7}
  };
  vector<vector<int>> actual = solution->combinationSum(candidates, target);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #2]
//  Input: candidates = [2,3,5], target = 8
// Output: [[2,2,2,2],[2,3,3],[3,5]]
//

LEETCODE_SOLUTION_UNITTEST(39, CombinationSum, example_2) {
  auto                solution   = MakeSolution();
  vector<int>         candidates = {2, 3, 5};
  int                 target     = 8;
  vector<vector<int>> expect     = {
      {2, 2, 2, 2},
      {2, 3, 3},
      {3, 5}
  };
  vector<vector<int>> actual = solution->combinationSum(candidates, target);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #3]
//  Input: candidates = [2], target = 1
// Output: []
//

LEETCODE_SOLUTION_UNITTEST(39, CombinationSum, example_3) {
  auto                solution   = MakeSolution();
  vector<int>         candidates = {2};
  int                 target     = 1;
  vector<vector<int>> expect     = {};
  vector<vector<int>> actual     = solution->combinationSum(candidates, target);
  EXPECT_ANYORDER_EQ(expect, actual);
}

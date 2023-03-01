// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Non-decreasing Subsequences
//
// https://leetcode.com/problems/non-decreasing-subsequences/
//
// Question ID: 491
// Difficult  : Medium
// Solve Date : 2023/01/20 10:23

#include <iosfwd>
#include <set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |491. Non-decreasing Subsequences|:
//
// Given an integer array |nums|, return all the different possible
// non-decreasing subsequences of the given array with at least two elements.
// You may return the answer in any order.
//

LEETCODE_BEGIN_RESOLVING(491, NonDecreasingSubsequences, Solution);

class Solution {
private:
  template <typename It>
  void dfs(set<vector<int>> &res, vector<int> &curr, It beg, It end) {
    if (curr.size() >= 2) {
      res.emplace(curr);
    }
    while (beg != end) {
      if (curr.empty() || *beg >= curr.back()) {
        curr.emplace_back(*beg);
        dfs(res, curr, beg + 1, end);
        curr.pop_back();
      }
      ++beg;
    }
  }

public:
  vector<vector<int>> findSubsequences(vector<int> &nums) {
    vector<vector<int>> res;
    set<vector<int>>    res_set;
    vector<int>         tmp;
    dfs(res_set, tmp, nums.begin(), nums.end());
    for (auto &v : res_set) {
      res.emplace_back(std::move(v));
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 15|
// * |-100 <= nums[i] <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [4,6,7,7]
// Output: [[4,6],[4,6,7],[4,6,7,7],[4,7],[4,7,7],[6,7],[6,7,7],[7,7]]
//

LEETCODE_SOLUTION_UNITTEST(491, NonDecreasingSubsequences, example_1) {
  auto                solution = MakeSolution();
  vector<int>         nums     = {4, 6, 7, 7};
  vector<vector<int>> expect   = {
      {4, 6},
      {4, 6, 7},
      {4, 6, 7, 7},
      {4, 7},
      {4, 7, 7},
      {6, 7},
      {6, 7, 7},
      {7, 7}
  };
  vector<vector<int>> actual = solution->findSubsequences(nums);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [4,4,3,2,1]
// Output: [[4,4]]
//

LEETCODE_SOLUTION_UNITTEST(491, NonDecreasingSubsequences, example_2) {
  auto                solution = MakeSolution();
  vector<int>         nums     = {4, 4, 3, 2, 1};
  vector<vector<int>> expect   = {
      {4, 4}
  };
  vector<vector<int>> actual = solution->findSubsequences(nums);
  EXPECT_ANYORDER_EQ(expect, actual);
}

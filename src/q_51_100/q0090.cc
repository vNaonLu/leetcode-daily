// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Subsets II
//
// https://leetcode.com/problems/subsets-ii/
//
// Question ID: 90
// Difficult  : Medium
// Solve Date : 2021/09/27 13:40

#include <algorithm>
#include <iosfwd>
#include <set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |90. Subsets II|:
//
// Given an integer array |nums| that may contain duplicates, return all
// possible subsets (the power set). The solution set must not contain duplicate
// subsets. Return the solution in any order.  
//

LEETCODE_BEGIN_RESOLVING(90, SubsetsII, Solution);

class Solution {
public:
  vector<vector<int>> subsetsWithDup(vector<int> &nums) {
    vector<vector<int>> res(1, vector<int>());
    sort(nums.begin(), nums.end());
    int n = nums.size(), last = nums.front();
    int size = 1;
    for (int i = 0; i < n; i++) {
      if (last != nums[i]) {
        last = nums[i];
        size = res.size();
      }
      int len = res.size();
      for (int j = len - size; j < len; ++j) {
        res.push_back(res[j]);
        res.back().push_back(nums[i]);
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
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,2]
// Output: [[],[1],[1,2],[1,2,2],[2],[2,2]]
//

LEETCODE_SOLUTION_UNITTEST(90, SubsetsII, example_1) {
  auto                solution = MakeSolution();
  vector<int>         nums     = {1, 2, 2};
  vector<vector<int>> expect   = {
      {},
      {1},
      {1, 2},
      {1, 2, 2},
      {2},
      {2, 2}
  };
  vector<vector<int>> actual = solution->subsetsWithDup(nums);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [0]
// Output: [[],[0]]
//

LEETCODE_SOLUTION_UNITTEST(90, SubsetsII, example_2) {
  auto                solution = MakeSolution();
  vector<int>         nums     = {0};
  vector<vector<int>> expect   = {{}, {0}};
  vector<vector<int>> actual   = solution->subsetsWithDup(nums);
  EXPECT_ANYORDER_EQ(expect, actual);
}

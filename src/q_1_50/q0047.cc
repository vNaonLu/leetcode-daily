// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Permutations II
//
// https://leetcode.com/problems/permutations-ii/
//
// Question ID: 47
// Difficult  : Medium
// Solve Date : 2021/09/28 09:55

#include <iosfwd>
#include <map>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |47. Permutations II|:
//
// Given a collection of numbers, |nums|, that might contain duplicates, return
// all possible unique permutations in any order.  
//

LEETCODE_BEGIN_RESOLVING(47, PermutationsII, Solution);

class Solution {
private:
  void helper(vector<vector<int>> &r, vector<int> &c,
              unordered_map<int, int> &cnt, const int &size) {
    if (size == c.size()) {
      r.push_back(c);
    } else {
      for (auto it = cnt.begin(); it != cnt.end(); ++it) {
        if (it->second == 0)
          continue;
        --it->second;
        helper(r, c, cnt, size);
        c.push_back(it->first);
        helper(r, c, cnt, size);
        c.pop_back();
        ++it->second;
      }
    }
  }

public:
  vector<vector<int>> permuteUnique(vector<int> &nums) {
    unordered_map<int, int> cnt;
    vector<vector<int>>     res;
    vector<int>             tmp;
    for (const auto &n : nums)
      ++cnt[n];
    helper(res, tmp, cnt, nums.size());
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 8|
// * |-10 <= nums[i] <= 10|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,1,2]
// Output: [[1,1,2],
//  [1,2,1],
//  [2,1,1]]
//

LEETCODE_SOLUTION_UNITTEST(47, PermutationsII, example_1) {
  auto                solution = MakeSolution();
  vector<int>         nums     = {1, 1, 2};
  vector<vector<int>> expect   = {
      {1, 1, 2},
      {1, 2, 1},
      {2, 1, 1}
  };
  vector<vector<int>> actual = solution->permuteUnique(nums);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,2,3]
// Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
//

LEETCODE_SOLUTION_UNITTEST(47, PermutationsII, example_2) {
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
  vector<vector<int>> actual = solution->permuteUnique(nums);
  EXPECT_ANYORDER_EQ(expect, actual);
}

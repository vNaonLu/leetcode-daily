// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Special Array II
//
// https://leetcode.com/problems/special-array-ii/
//
// Question ID: 3152
// Difficult  : Medium
// Solve Date : 2024/12/09 18:54

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3152. Special Array II|:
//
// An array is considered special if every pair of its adjacent elements
// contains two numbers with different parity. You are given an array of integer
// |nums| and a 2D integer matrix |queries|, where for |queries[i] = [fromᵢ,
// toᵢ]| your task is to check that subarray |nums[fromᵢ..toᵢ]| is special or
// not. Return an array of booleans |answer| such that |answer[i]| is |true| if
// |nums[fromᵢ..toᵢ]| is special.
//
//

LEETCODE_BEGIN_RESOLVING(3152, SpecialArrayII, Solution);

class Solution {
public:
  vector<bool> isArraySpecial(vector<int> &nums, vector<vector<int>> &queries) {
    int         n = nums.size();
    vector<int> prefix(n);
    for (int i = 1; i < n; ++i) {
      prefix[i] = prefix[i - 1];
      if ((nums[i - 1] & 1) == (nums[i] & 1)) {
        ++prefix[i];
      }
    }

    vector<bool> res;
    for (auto &q : queries) {
      int lo      = q[0];
      int hi      = q[1];
      int special = prefix[hi] - (lo > 0 ? prefix[lo] : 0);
      res.push_back(!special);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁵|
// * |1 <= nums[i] <= 10⁵|
// * |1 <= queries.length <= 10⁵|
// * |queries[i].length == 2|
// * |0 <= queries[i][0] <= queries[i][1] <= nums.length - 1|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [3,4,1,2,6], queries = [[0,4]]
// Output: [false]
//

LEETCODE_SOLUTION_UNITTEST(3152, SpecialArrayII, example_1) {
  auto                solution = MakeSolution();
  vector<int>         nums     = {3, 4, 1, 2, 6};
  vector<vector<int>> queries  = {
      {0, 4}
  };
  vector<bool> expect = {false};
  vector<bool> actual = solution->isArraySpecial(nums, queries);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [4,3,1,6], queries = [[0,2],[2,3]]
// Output: [false,true]
//

LEETCODE_SOLUTION_UNITTEST(3152, SpecialArrayII, example_2) {
  auto                solution = MakeSolution();
  vector<int>         nums     = {4, 3, 1, 6};
  vector<vector<int>> queries  = {
      {0, 2},
      {2, 3}
  };
  vector<bool> expect = {false, true};
  vector<bool> actual = solution->isArraySpecial(nums, queries);
  LCD_EXPECT_EQ(expect, actual);
}

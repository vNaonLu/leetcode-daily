// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Convert an Array Into a 2D Array With Conditions
//
// https://leetcode.com/problems/convert-an-array-into-a-2d-array-with-conditions/
//
// Question ID: 2610
// Difficult  : Medium
// Solve Date : 2024/01/02 16:26

#include <iosfwd>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2610. Convert an Array Into a 2D Array With Conditions|:
//
// You are given an integer array |nums|. You need to create a 2D array from
// |nums| satisfying the following conditions:
//
//  • The 2D array should contain only the elements of the array |nums|.
//
//  • Each row in the 2D array contains distinct integers.
//
//  • The number of rows in the 2D array should be minimal.
// Return the resulting array. If there are multiple answers, return any of
// them. Note that the 2D array can have a different number of elements on each
// row.
//
//

LEETCODE_BEGIN_RESOLVING(2610, ConvertAnArrayIntoA2DArrayWithConditions,
                         Solution);

class Solution {
public:
  vector<vector<int>> findMatrix(vector<int> &nums) {
    unordered_map<int, int> mp;
    int                     cnt = 0;
    for (auto x : nums) {
      ++mp[x];
      cnt = max(cnt, mp[x]);
    }
    vector<vector<int>> res(cnt);
    for (auto &[num, freq] : mp) {
      for (int i = 0; i < freq; ++i) {
        res[i].emplace_back(num);
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 200|
// * |1 <= nums[i] <= nums.length|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,3,4,1,2,3,1]
// Output: [[1,3,4,2],[1,3],[1]]
//
// We can create a 2D array that contains the following rows:
// - 1,3,4,2
// - 1,3
// - 1
// All elements of nums were used, and each row of the 2D array contains
// distinct integers, so it is a valid answer. It can be shown that we cannot
// have less than 3 rows in a valid array.

LEETCODE_SOLUTION_UNITTEST(2610, ConvertAnArrayIntoA2DArrayWithConditions,
                           example_1) {
  auto                solution = MakeSolution();
  vector<int>         nums     = {1, 3, 4, 1, 2, 3, 1};
  vector<vector<int>> expect   = {
      {2, 4, 3, 1},
      {3, 1},
      {1}
  };
  vector<vector<int>> actual = solution->findMatrix(nums);
  EXPECT_ANYORDER_WITH_DEPTH_EQ(1, expect, actual);
}

// [Example #2]
//  Input: nums = [1,2,3,4]
// Output: [[4,3,2,1]]
//
// All elements of the array are distinct, so we can keep all of them in the
// first row of the 2D array.

LEETCODE_SOLUTION_UNITTEST(2610, ConvertAnArrayIntoA2DArrayWithConditions,
                           example_2) {
  auto                solution = MakeSolution();
  vector<int>         nums     = {1, 2, 3, 4};
  vector<vector<int>> expect   = {
      {4, 3, 2, 1}
  };
  vector<vector<int>> actual = solution->findMatrix(nums);
  EXPECT_ANYORDER_WITH_DEPTH_EQ(1, expect, actual);
}

// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Zero Array Transformation I
//
// https://leetcode.com/problems/zero-array-transformation-i/
//
// Question ID: 3355
// Difficult  : Medium
// Solve Date : 2025/05/20 21:59

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3355. Zero Array Transformation I|:
//
// You are given an integer array |nums| of length |n| and a 2D array |queries|,
// where |queries[i] = [lᵢ, rᵢ]|. For each |queries[i]|:
//
//  • Select a subset of indices within the range |[lᵢ, rᵢ]| in |nums|.
//
//  • Decrement the values at the selected indices by 1.
// A Zero Array is an array where all elements are equal to 0.
// Return |true| if it is possible to transform |nums| into a Zero Array after
// processing all the queries sequentially, otherwise return |false|.
//
//

LEETCODE_BEGIN_RESOLVING(3355, ZeroArrayTransformationI, Solution);

class Solution {
public:
  bool isZeroArray(vector<int> &nums, vector<vector<int>> &queries) {
    vector<int> diff(nums.size() + 1, 0);
    for (auto &q : queries) {
      diff[q[0]]++;
      if (q[1] + 1 < nums.size()) {
        --diff[q[1] + 1];
      }
    }
    int cnt = 0;
    for (int i = 0; i < nums.size(); ++i) {
      cnt += diff[i];
      if (nums[i] > cnt) {
        return false;
      }
    }
    return true;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁵|
// * |0 <= nums[i] <= 10⁵|
// * |1 <= queries.length <= 10⁵|
// * |queries[i].length == 2|
// * |0 <= lᵢ <= rᵢ < nums.length|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,0,1], queries = [[0,2]]
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(3355, ZeroArrayTransformationI, example_1) {
  auto                solution = MakeSolution();
  vector<int>         nums     = {1, 0, 1};
  vector<vector<int>> queries  = {
      {0, 2}
  };
  bool expect = true;
  bool actual = solution->isZeroArray(nums, queries);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [4,3,2,1], queries = [[1,3],[0,2]]
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(3355, ZeroArrayTransformationI, example_2) {
  auto                solution = MakeSolution();
  vector<int>         nums     = {4, 3, 2, 1};
  vector<vector<int>> queries  = {
      {1, 3},
      {0, 2}
  };
  bool expect = false;
  bool actual = solution->isZeroArray(nums, queries);
  LCD_EXPECT_EQ(expect, actual);
}

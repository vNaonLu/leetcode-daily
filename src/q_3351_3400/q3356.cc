// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Zero Array Transformation II
//
// https://leetcode.com/problems/zero-array-transformation-ii/
//
// Question ID: 3356
// Difficult  : Medium
// Solve Date : 2025/03/13 18:00

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3356. Zero Array Transformation II|:
//
// You are given an integer array |nums| of length |n| and a 2D array |queries|
// where |queries[i] = [lᵢ, rᵢ, valᵢ]|. Each |queries[i]| represents the
// following action on |nums|:
//
//  • Decrement the value at each index in the range |[lᵢ, rᵢ]| in |nums| by at
//  most |valᵢ|.
//
//  • The amount by which each value is decremented can be chosen independently
//  for each index.
// A Zero Array is an array with all its elements equal to 0.
// Return the minimum possible non-negative value of |k|, such that after
// processing the first |k| queries in sequence, |nums| becomes a Zero Array. If
// no such |k| exists, return -1.
//
//

LEETCODE_BEGIN_RESOLVING(3356, ZeroArrayTransformationII, Solution);

class Solution {
public:
  int minZeroArray(vector<int> &nums, vector<vector<int>> &queries) {
    int         n   = nums.size();
    int         m   = queries.size();
    int         res = 0;
    int         op  = 0;
    vector<int> freq(n + 1);
    for (int i = 0; i < n; ++i) {
      for (; op < nums[i] - freq[i]; ++res) {
        if (res >= m) {
          return -1;
        }
        int l = queries[res][0];
        int r = queries[res][1];
        int v = queries[res][2];
        if (r < i) {
          continue;
        }

        freq[max(l, i)] += v;
        freq[r + 1] -= v;
      }
      op += freq[i];
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁵|
// * |0 <= nums[i] <= 5 * 10⁵|
// * |1 <= queries.length <= 10⁵|
// * |queries[i].length == 3|
// * |0 <= lᵢ <= rᵢ < nums.length|
// * |1 <= valᵢ <= 5|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [2,0,2], queries = [[0,2,1],[0,2,1],[1,1,3]]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(3356, ZeroArrayTransformationII, example_1) {
  auto                solution = MakeSolution();
  vector<int>         nums     = {2, 0, 2};
  vector<vector<int>> queries  = {
      {0, 2, 1},
      {0, 2, 1},
      {1, 1, 3}
  };
  int expect = 2;
  int actual = solution->minZeroArray(nums, queries);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [4,3,2,1], queries = [[1,3,2],[0,2,1]]
// Output: -1
//

LEETCODE_SOLUTION_UNITTEST(3356, ZeroArrayTransformationII, example_2) {
  auto                solution = MakeSolution();
  vector<int>         nums     = {4, 3, 2, 1};
  vector<vector<int>> queries  = {
      {1, 3, 2},
      {0, 2, 1}
  };
  int expect = -1;
  int actual = solution->minZeroArray(nums, queries);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: [10]
// [[0,0,5],[0,0,3],[0,0,2],[0,0,1],[0,0,4],[0,0,1],[0,0,4],[0,0,5],[0,0,3],[0,0,4],[0,0,1]]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(3356, ZeroArrayTransformationII, extra_testcase_1) {
  auto                solution = MakeSolution();
  vector<int>         nums     = {10};
  vector<vector<int>> queries  = {
      {0, 0, 5},
      {0, 0, 3},
      {0, 0, 2},
      {0, 0, 1},
      {0, 0, 4},
      {0, 0, 1},
      {0, 0, 4},
      {0, 0, 5},
      {0, 0, 3},
      {0, 0, 4},
      {0, 0, 1}
  };
  int expect = 3;
  int actual = solution->minZeroArray(nums, queries);
  LCD_EXPECT_EQ(expect, actual);
}

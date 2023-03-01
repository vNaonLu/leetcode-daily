// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Maximum Side Length of a Square with Sum Less than or Equal to Threshold
//
// https://leetcode.com/problems/maximum-side-length-of-a-square-with-sum-less-than-or-equal-to-threshold/
//
// Question ID: 1292
// Difficult  : Medium
// Solve Date : 2022/07/28 18:17

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1292. Maximum Side Length of a Square with Sum Less than or
// Equal to Threshold|:
//
// Given a |m x n| matrix |mat| and an integer |threshold|, return the maximum
// side-length of a square with a sum less than or equal to |threshold| or
// return |0| if there is no such square.
//

LEETCODE_BEGIN_RESOLVING(
    1292, MaximumSideLengthOfASquareWithSumLessThanOrEqualToThreshold,
    Solution);

class Solution {
private:
  int                     m, n;
  vector<vector<int64_t>> presum;

  bool helper(int x1, int y1, int x2, int y2, int k) {
    auto sum1 = presum[x1][y1];
    auto sum2 = presum[x1][y2];
    auto sum3 = presum[x2][y1];
    auto sum4 = presum[x2][y2];

    return sum1 + sum4 - sum3 - sum2 <= k;
  }

  bool helper(int length, int k) {
    for (int i = length; i <= m; ++i) {
      for (int j = length; j <= n; ++j) {
        if (helper(i - length, j - length, i, j, k)) {
          return true;
        }
      }
    }
    return false;
  }

public:
  int maxSideLength(vector<vector<int>> &mat, int threshold) {
    m      = mat.size();
    n      = mat.front().size();
    presum = vector<vector<int64_t>>(m + 1, vector<int64_t>(n + 1, 0));
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        presum[i + 1][j + 1] =
            mat[i][j] + presum[i + 1][j] + presum[i][j + 1] - presum[i][j];
      }
    }

    int lo = 0, hi = min(m, n);
    int res = 0;
    while (lo + 1 < hi) {
      int mid = lo + (hi - lo) / 2;
      if (helper(mid, threshold)) {
        lo = mid;
      } else {
        hi = mid - 1;
      }
    }

    return helper(hi, threshold) ? hi : lo;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |m == mat.length|
// * |n == mat[i].length|
// * |1 <= m, n <= 300|
// * |0 <= mat[i][j] <= 10⁴|
// * |0 <= threshold <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: mat = [[1,1,3,2,4,3,2],[1,1,3,2,4,3,2],[1,1,3,2,4,3,2]], threshold =
//  4
// Output: 2
//
// The maximum side length of square with sum less than 4 is 2 as shown.

LEETCODE_SOLUTION_UNITTEST(
    1292, MaximumSideLengthOfASquareWithSumLessThanOrEqualToThreshold,
    example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> mat      = {
      {1, 1, 3, 2, 4, 3, 2},
      {1, 1, 3, 2, 4, 3, 2},
      {1, 1, 3, 2, 4, 3, 2}
  };
  int threshold = 4;
  int expect    = 2;
  int actual    = solution->maxSideLength(mat, threshold);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: mat = [[2,2,2,2,2],[2,2,2,2,2],[2,2,2,2,2],[2,2,2,2,2],[2,2,2,2,2]],
//  threshold = 1
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(
    1292, MaximumSideLengthOfASquareWithSumLessThanOrEqualToThreshold,
    example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> mat      = {
      {2, 2, 2, 2, 2},
      {2, 2, 2, 2, 2},
      {2, 2, 2, 2, 2},
      {2, 2, 2, 2, 2},
      {2, 2, 2, 2, 2}
  };
  int threshold = 1;
  int expect    = 0;
  int actual    = solution->maxSideLength(mat, threshold);
  LCD_EXPECT_EQ(expect, actual);
}

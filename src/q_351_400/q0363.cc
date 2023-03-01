// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Max Sum of Rectangle No Larger Than K
//
// https://leetcode.com/problems/max-sum-of-rectangle-no-larger-than-k/
//
// Question ID: 363
// Difficult  : Hard
// Solve Date : 2022/08/27 13:41

#include <iosfwd>
#include <limits>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |363. Max Sum of Rectangle No Larger Than K|:
//
// Given an |m x n| matrix |matrix| and an integer |k|, return the max sum of a
// rectangle in the matrix such that its sum is no larger than |k|. It is
// guaranteed that there will be a rectangle with a sum no larger than |k|.
//

LEETCODE_BEGIN_RESOLVING(363, MaxSumOfRectangleNoLargerThanK, Solution);

class Solution {
private:
  inline auto calcPrefixSum(vector<vector<int>> const &matrix) {
    auto m   = matrix.size();
    auto n   = matrix.front().size();
    auto res = vector<vector<int>>(m + 1, vector<int>(n));
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        res[i + 1][j] = res[i][j] + matrix[i][j];
      }
    }
    return res;
  }

public:
  int maxSumSubmatrix(vector<vector<int>> &matrix, int k) {
    auto m      = matrix.size();
    auto n      = matrix.front().size();
    auto prefix = calcPrefixSum(matrix);
    auto res    = numeric_limits<int>::min();

    for (int i = 0; i < m; ++i) {
      for (int l = i + 1; l <= m; ++l) {
        for (int j = 0; j < n; ++j) {
          auto val = (int)(0);
          for (int t = j; t < n; ++t) {
            val += prefix[l][t] - prefix[i][t];

            if (val < k) {
              res = max(val, res);
            } else if (val == k) {
              return k;
            }
          }
        }
      }
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |m == matrix.length|
// * |n == matrix[i].length|
// * |1 <= m, n <= 100|
// * |-100 <= matrix[i][j] <= 100|
// * |-10⁵ <= k <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: matrix = [[1,0,1],[0,-2,3]], k = 2
// Output: 2
//
// Because the sum of the blue rectangle [[0, 1], [-2, 3]] is 2, and 2 is the
// max number no larger than k (k = 2).

LEETCODE_SOLUTION_UNITTEST(363, MaxSumOfRectangleNoLargerThanK, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> matrix   = {
      {1,  0, 1},
      {0, -2, 3}
  };
  int k      = 2;
  int expect = 2;
  int actual = solution->maxSumSubmatrix(matrix, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: matrix = [[2,2,-1]], k = 3
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(363, MaxSumOfRectangleNoLargerThanK, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> matrix   = {
      {2, 2, -1}
  };
  int k      = 3;
  int expect = 3;
  int actual = solution->maxSumSubmatrix(matrix, k);
  LCD_EXPECT_EQ(expect, actual);
}

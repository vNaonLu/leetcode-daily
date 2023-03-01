// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Number of Submatrices That Sum to Target
//
// https://leetcode.com/problems/number-of-submatrices-that-sum-to-target/
//
// Question ID: 1074
// Difficult  : Hard
// Solve Date : 2022/07/18 18:36

#include <iosfwd>
#include <map>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1074. Number of Submatrices That Sum to Target|:
//
// Given a |matrix|and a |target|, return the number of non-empty submatrices
// that sum to target. A submatrix |x1, y1, x2, y2| is the set of all cells
// |matrix[x][y]| with |x1 <= x <= x2| and |y1 <= y <= y2|. Two submatrices
// |(x1, y1, x2, y2)| and |(x1', y1', x2', y2')| are different if they have some
// coordinatethat is different: for example, if |x1 != x1'|.
//

LEETCODE_BEGIN_RESOLVING(1074, NumberOfSubmatricesThatSumToTarget, Solution);

class Solution {
public:
  int numSubmatrixSumTarget(vector<vector<int>> &matrix, int target) {
    int m = matrix.size(), n = matrix.front().size();
    for (int i = 0; i < m; ++i) {
      for (int j = 1; j < n; ++j) {
        matrix[i][j] += matrix[i][j - 1];
      }
    }

    int res = 0;
    for (int i = 0; i < n; ++i) {
      for (int j = i; j < n; ++j) {
        unordered_map<int, int> cnt = {
            {0, 1}
        };
        int curr = 0;

        for (int k = 0; k < m; ++k) {
          curr += matrix[k][j] - (i == 0 ? 0 : matrix[k][i - 1]);
          auto find = cnt.find(curr - target);
          if (find != cnt.end()) {
            res += find->second;
          }
          ++cnt[curr];
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
// * |1 <= matrix.length <= 100|
// * |1 <= matrix[0].length <= 100|
// * |-1000 <= matrix[i] <= 1000|
// * |-10^8 <= target <= 10^8|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: matrix = [[0,1,0],[1,1,1],[0,1,0]], target = 0
// Output: 4
//
// The four 1x1 submatrices that only contain 0.

LEETCODE_SOLUTION_UNITTEST(1074, NumberOfSubmatricesThatSumToTarget,
                           example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> matrix   = {
      {0, 1, 0},
      {1, 1, 1},
      {0, 1, 0}
  };
  int target = 0;
  int expect = 4;
  int actual = solution->numSubmatrixSumTarget(matrix, target);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: matrix = [[1,-1],[-1,1]], target = 0
// Output: 5
//
// The two 1x2 submatrices, plus the two 2x1 submatrices, plus the 2x2
// submatrix.

LEETCODE_SOLUTION_UNITTEST(1074, NumberOfSubmatricesThatSumToTarget,
                           example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> matrix   = {
      { 1, -1},
      {-1,  1}
  };
  int target = 0;
  int expect = 5;
  int actual = solution->numSubmatrixSumTarget(matrix, target);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: matrix = [[904]], target = 0
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(1074, NumberOfSubmatricesThatSumToTarget,
                           example_3) {
  auto                solution = MakeSolution();
  vector<vector<int>> matrix   = {{904}};
  int                 target   = 0;
  int                 expect   = 0;
  int                 actual = solution->numSubmatrixSumTarget(matrix, target);
  LCD_EXPECT_EQ(expect, actual);
}

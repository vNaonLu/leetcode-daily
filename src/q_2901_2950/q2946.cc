// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Matrix Similarity After Cyclic Shifts
//
// https://leetcode.com/problems/matrix-similarity-after-cyclic-shifts/
//
// Question ID: 2946
// Difficult  : Easy
// Solve Date : 2024/02/07 16:19

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2946. Matrix Similarity After Cyclic Shifts|:
//
// You are given a 0-indexed |m x n| integer matrix |mat| and an integer |k|.
// You have to cyclically right shift odd indexed rows |k| times and cyclically
// left shift even indexed rows |k| times. Return |true| if the initial and
// final matrix are exactly the same and |false| otherwise.
//
//

LEETCODE_BEGIN_RESOLVING(2946, MatrixSimilarityAfterCyclicShifts, Solution);

class Solution {
public:
  bool areSimilar(vector<vector<int>> &mat, int k) {
    for (auto &v : mat) {
      auto beg = v.begin();
      int  idx = k;
      while (beg != v.end()) {
        idx %= v.size();
        if (*beg++ != v[idx++]) {
          return false;
        }
      }
    }
    return true;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= mat.length <= 25|
// * |1 <= mat[i].length <= 25|
// * |1 <= mat[i][j] <= 25|
// * |1 <= k <= 50|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: mat = [[1,2,1,2],[5,5,5,5],[6,3,6,3]], k = 2
// Output: true
//
// ![img](https://assets.leetcode.com/uploads/2023/10/29/similarmatrix.png)
// Initially, the matrix looks like the first figure.
// Second figure represents the state of the matrix after one right and left
// cyclic shifts to even and odd indexed rows. Third figure is the final state
// of the matrix after two cyclic shifts which is similar to the initial matrix.
// Therefore, return true.

LEETCODE_SOLUTION_UNITTEST(2946, MatrixSimilarityAfterCyclicShifts, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> mat      = {
      {1, 2, 1, 2},
      {5, 5, 5, 5},
      {6, 3, 6, 3}
  };
  int  k      = 2;
  bool expect = true;
  bool actual = solution->areSimilar(mat, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: mat = [[2,2],[2,2]], k = 3
// Output: true
//
// As all the values are equal in the matrix, even after performing cyclic
// shifts the matrix will remain the same. Therefeore, we return true.

LEETCODE_SOLUTION_UNITTEST(2946, MatrixSimilarityAfterCyclicShifts, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> mat      = {
      {2, 2},
      {2, 2}
  };
  int  k      = 3;
  bool expect = true;
  bool actual = solution->areSimilar(mat, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: mat = [[1,2]], k = 1
// Output: false
//
// After one cyclic shift, mat = [[2,1]] which is not equal to the initial
// matrix. Therefore we return false.

LEETCODE_SOLUTION_UNITTEST(2946, MatrixSimilarityAfterCyclicShifts, example_3) {
  auto                solution = MakeSolution();
  vector<vector<int>> mat      = {
      {1, 2}
  };
  int  k      = 1;
  bool expect = false;
  bool actual = solution->areSimilar(mat, k);
  LCD_EXPECT_EQ(expect, actual);
}

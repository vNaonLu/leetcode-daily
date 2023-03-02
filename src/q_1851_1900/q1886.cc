// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Determine Whether Matrix Can Be Obtained By Rotation
//
// https://leetcode.com/problems/determine-whether-matrix-can-be-obtained-by-rotation/
//
// Question ID: 1886
// Difficult  : Easy
// Solve Date : 2022/05/02 13:31

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1886. Determine Whether Matrix Can Be Obtained By Rotation|:
//
// Given two |n x n| binary matrices |mat| and |target|, return |true| if it is
// possible to make |mat| equal to |target| by rotating |mat| in 90-degree
// increments, or |false| otherwise.  
//

LEETCODE_BEGIN_RESOLVING(1886, DetermineWhetherMatrixCanBeObtainedByRotation,
                         Solution);

class Solution {
private:
  void rotate(vector<vector<int>> &matrix) {
    int rows = matrix.size();
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < i; j++) {
        swap(matrix[i][j], matrix[j][i]);
      }
    }
    for (auto &row : matrix) {
      reverse(row.begin(), row.end());
    }
  }

public:
  bool findRotation(vector<vector<int>> &mat, vector<vector<int>> &target) {
    for (int i = 0; i < 4; ++i) {
      if (mat == target) {
        return true;
      }

      rotate(mat);
    }
    return false;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == mat.length == target.length|
// * |n == mat[i].length == target[i].length|
// * |1 <= n <= 10|
// * |mat[i][j]| and |target[i][j]| are either |0| or |1|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: mat = [[0,1],[1,0]], target = [[1,0],[0,1]]
// Output: true
//
// We can rotate mat 90 degrees clockwise to make mat equal target.

LEETCODE_SOLUTION_UNITTEST(1886, DetermineWhetherMatrixCanBeObtainedByRotation,
                           example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> mat      = {
      {0, 1},
      {1, 0}
  };
  vector<vector<int>> target = {
      {1, 0},
      {0, 1}
  };
  bool expect = true;
  bool actual = solution->findRotation(mat, target);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: mat = [[0,1],[1,1]], target = [[1,0],[0,1]]
// Output: false
//
// It is impossible to make mat equal to target by rotating mat.

LEETCODE_SOLUTION_UNITTEST(1886, DetermineWhetherMatrixCanBeObtainedByRotation,
                           example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> mat      = {
      {0, 1},
      {1, 1}
  };
  vector<vector<int>> target = {
      {1, 0},
      {0, 1}
  };
  bool expect = false;
  bool actual = solution->findRotation(mat, target);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: mat = [[0,0,0],[0,1,0],[1,1,1]], target = [[1,1,1],[0,1,0],[0,0,0]]
// Output: true
//
// We can rotate mat 90 degrees clockwise two times to make mat equal target.

LEETCODE_SOLUTION_UNITTEST(1886, DetermineWhetherMatrixCanBeObtainedByRotation,
                           example_3) {
  auto                solution = MakeSolution();
  vector<vector<int>> mat      = {
      {0, 0, 0},
      {0, 1, 0},
      {1, 1, 1}
  };
  vector<vector<int>> target = {
      {1, 1, 1},
      {0, 1, 0},
      {0, 0, 0}
  };
  bool expect = true;
  bool actual = solution->findRotation(mat, target);
  LCD_EXPECT_EQ(expect, actual);
}

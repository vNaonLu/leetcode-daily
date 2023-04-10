// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Check if Every Row and Column Contains All Numbers
//
// https://leetcode.com/problems/check-if-every-row-and-column-contains-all-numbers/
//
// Question ID: 2133
// Difficult  : Easy
// Solve Date : 2023/04/07 11:57

#include <algorithm>
#include <cassert>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2133. Check if Every Row and Column Contains All Numbers|:
//
// An |n x n| matrix is valid if every row and every column contains all the
// integers from |1| to |n| (inclusive). Given an |n x n| integer matrix
// |matrix|, return |true| if the matrix is valid. Otherwise, return |false|.
//
//

LEETCODE_BEGIN_RESOLVING(2133, CheckIfEveryRowAndColumnContainsAllNumbers,
                         Solution);

class Solution {
public:
  bool checkValid(vector<vector<int>> &matrix) {
    int n = matrix.size();
    assert(n = matrix[0].size());

    // check rows
    for (int i = 0; i < n; ++i) {
      vector<int> appear(n, 0);
      for (auto x : matrix[i]) {
        ++appear[x - 1];
      }
      if (!all_of(appear.begin(), appear.end(), [](auto x) { return x > 0; })) {
        return false;
      }
    }

    // check cols
    for (int i = 0; i < n; ++i) {
      vector<int> appear(n, 0);
      for (int j = 0; j < n; ++j) {
        ++appear[matrix[j][i] - 1];
      }
      if (!all_of(appear.begin(), appear.end(), [](auto x) { return x > 0; })) {
        return false;
      }
    }

    return true;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == matrix.length == matrix[i].length|
// * |1 <= n <= 100|
// * |1 <= matrix[i][j] <= n|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: matrix = [[1,2,3],[3,1,2],[2,3,1]]
// Output: true
//
// In this case, n = 3, and every row and column contains the numbers 1, 2,
// and 3. Hence, we return true.

LEETCODE_SOLUTION_UNITTEST(2133, CheckIfEveryRowAndColumnContainsAllNumbers,
                           example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> matrix   = {
      {1, 2, 3},
      {3, 1, 2},
      {2, 3, 1}
  };
  bool expect = true;
  bool actual = solution->checkValid(matrix);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: matrix = [[1,1,1],[1,2,3],[1,2,3]]
// Output: false
//
// In this case, n = 3, but the first row and the first column do not contain
// the numbers 2 or 3. Hence, we return false.

LEETCODE_SOLUTION_UNITTEST(2133, CheckIfEveryRowAndColumnContainsAllNumbers,
                           example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> matrix   = {
      {1, 1, 1},
      {1, 2, 3},
      {1, 2, 3}
  };
  bool expect = false;
  bool actual = solution->checkValid(matrix);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: [[1,2,3],[2,1,2],[3,3,1]]
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(2133, CheckIfEveryRowAndColumnContainsAllNumbers,
                           extra_testcase_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> matrix   = {
      {1, 2, 3},
      {2, 1, 2},
      {3, 3, 1}
  };
  bool expect = false;
  bool actual = solution->checkValid(matrix);
  LCD_EXPECT_EQ(expect, actual);
}

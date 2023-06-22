// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Lucky Numbers in a Matrix
//
// https://leetcode.com/problems/lucky-numbers-in-a-matrix/
//
// Question ID: 1380
// Difficult  : Easy
// Solve Date : 2023/06/22 08:03

#include <iosfwd>
#include <numeric>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1380. Lucky Numbers in a Matrix|:
//
// Given an |m x n| matrix of distinct numbers, return all lucky numbers in the
// matrix in any order. A lucky number is an element of the matrix such that it
// is the minimum element in its row and maximum in its column.
//
//

LEETCODE_BEGIN_RESOLVING(1380, LuckyNumbersInAMatrix, Solution);

class Solution {
public:
  vector<int> luckyNumbers(vector<vector<int>> &matrix) {
    vector<int> res;
    for (auto &v : matrix) {
      auto mn     = min_element(v.begin(), v.end());
      auto idx    = distance(v.begin(), mn);
      bool is_max = true;

      for (int i = 0; i < matrix.size() && is_max; ++i) {
        if (matrix[i][idx] > *mn) {
          is_max = false;
        }
      }

      if (is_max) {
        res.emplace_back(*mn);
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |m == mat.length|
// * |n == mat[i].length|
// * |1 <= n, m <= 50|
// * |1 <= matrix[i][j] <= 10⁵|.
// * All elements in the matrix are distinct.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: matrix = [[3,7,8],[9,11,13],[15,16,17]]
// Output: [15]
//
// 15 is the only lucky number since it is the minimum in its row and the
// maximum in its column.

LEETCODE_SOLUTION_UNITTEST(1380, LuckyNumbersInAMatrix, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> matrix   = {
      { 3,  7,  8},
      { 9, 11, 13},
      {15, 16, 17}
  };
  vector<int> expect = {15};
  vector<int> actual = solution->luckyNumbers(matrix);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: matrix = [[1,10,4,2],[9,3,8,7],[15,16,17,12]]
// Output: [12]
//
// 12 is the only lucky number since it is the minimum in its row and the
// maximum in its column.

LEETCODE_SOLUTION_UNITTEST(1380, LuckyNumbersInAMatrix, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> matrix   = {
      { 1, 10,  4,  2},
      { 9,  3,  8,  7},
      {15, 16, 17, 12}
  };
  vector<int> expect = {12};
  vector<int> actual = solution->luckyNumbers(matrix);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: matrix = [[7,8],[1,2]]
// Output: [7]
//
// 7 is the only lucky number since it is the minimum in its row and the maximum
// in its column.

LEETCODE_SOLUTION_UNITTEST(1380, LuckyNumbersInAMatrix, example_3) {
  auto                solution = MakeSolution();
  vector<vector<int>> matrix   = {
      {7, 8},
      {1, 2}
  };
  vector<int> expect = {7};
  vector<int> actual = solution->luckyNumbers(matrix);
  LCD_EXPECT_EQ(expect, actual);
}

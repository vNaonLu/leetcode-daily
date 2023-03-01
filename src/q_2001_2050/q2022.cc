// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Convert 1D Array Into 2D Array
//
// https://leetcode.com/problems/convert-1d-array-into-2d-array/
//
// Question ID: 2022
// Difficult  : Easy
// Solve Date : 2022/12/11 18:54

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2022. Convert 1D Array Into 2D Array|:
//
// You are given a 0-indexed 1-dimensional (1D) integer array |original|, and
// two integers, |m| and |n|. You are tasked with creating a 2-dimensional (2D)
// array with | m| rows and |n| columns using all the elements from |original|.
// The elements from indices |0| to |n - 1| (inclusive) of |original| should
// form the first row of the constructed 2D array, the elements from indices |n|
// to |2 * n - 1| (inclusive) should form the second row of the constructed 2D
// array, and so on. Return an |m x n| 2D array constructed according to the
// above procedure, or an empty 2D array if it is impossible.
//

LEETCODE_BEGIN_RESOLVING(2022, Convert1DArrayInto2DArray, Solution);

class Solution {
public:
  vector<vector<int>> construct2DArray(vector<int> &original, int m, int n) {
    if (m * n != original.size()) {
      return vector<vector<int>>();
    }
    auto res = vector<vector<int>>(m, vector<int>(n, 0));
    auto beg = original.begin();
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        *(res[i].begin() + j) = *beg++;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= original.length <= 5 * 10⁴|
// * |1 <= original[i] <= 10⁵|
// * |1 <= m, n <= 4 * 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: original = [1,2,3,4], m = 2, n = 2
// Output: [[1,2],[3,4]]
//
// The constructed 2D array should contain 2 rows and 2 columns.
// The first group of n=2 elements in original, [1,2], becomes the first row in
// the constructed 2D array. The second group of n=2 elements in original,
// [3,4], becomes the second row in the constructed 2D array.

LEETCODE_SOLUTION_UNITTEST(2022, Convert1DArrayInto2DArray, example_1) {
  auto                solution = MakeSolution();
  vector<int>         original = {1, 2, 3, 4};
  int                 m        = 2;
  int                 n        = 2;
  vector<vector<int>> expect   = {
      {1, 2},
      {3, 4}
  };
  vector<vector<int>> actual = solution->construct2DArray(original, m, n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: original = [1,2,3], m = 1, n = 3
// Output: [[1,2,3]]
//
// The constructed 2D array should contain 1 row and 3 columns.
// Put all three elements in original into the first row of the constructed 2D
// array.

LEETCODE_SOLUTION_UNITTEST(2022, Convert1DArrayInto2DArray, example_2) {
  auto                solution = MakeSolution();
  vector<int>         original = {1, 2, 3};
  int                 m        = 1;
  int                 n        = 3;
  vector<vector<int>> expect   = {
      {1, 2, 3}
  };
  vector<vector<int>> actual = solution->construct2DArray(original, m, n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: original = [1,2], m = 1, n = 1
// Output: []
//
// There are 2 elements in original.
// It is impossible to fit 2 elements in a 1x1 2D array, so return an empty 2D
// array.

LEETCODE_SOLUTION_UNITTEST(2022, Convert1DArrayInto2DArray, example_3) {
  auto                solution = MakeSolution();
  vector<int>         original = {1, 2};
  int                 m        = 1;
  int                 n        = 1;
  vector<vector<int>> expect   = {};
  vector<vector<int>> actual   = solution->construct2DArray(original, m, n);
  LCD_EXPECT_EQ(expect, actual);
}

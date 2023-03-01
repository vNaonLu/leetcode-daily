// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Pascal's Triangle
//
// https://leetcode.com/problems/pascals-triangle/
//
// Question ID: 118
// Difficult  : Easy
// Solve Date : 2021/09/08 08:00

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |118. Pascal's Triangle|:
//
// Given an integer |numRows|, return the first numRows of Pascal's triangle.
// In Pascal's triangle, each number is the sum of the two numbers directly
// above it as shown:
// ![img](https://upload.wikimedia.org/wikipedia/commons/0/0d/PascalTriangleAnimated2.gif)
//  
//

LEETCODE_BEGIN_RESOLVING(118, PascalsTriangle, Solution);

class Solution {
public:
  vector<vector<int>> generate(int numRows) {
    vector<vector<int>> res(numRows);
    for (int i = 0; i < numRows; ++i) {
      res[i].resize(i + 1, 1);
      for (int j = 1; j < i; ++j) {
        res[i][j] = res[i - 1][j - 1] + res[i - 1][j];
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= numRows <= 30|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: numRows = 5
// Output: [[1],[1,1],[1,2,1],[1,3,3,1],[1,4,6,4,1]]
//

LEETCODE_SOLUTION_UNITTEST(118, PascalsTriangle, example_1) {
  auto                solution = MakeSolution();
  int                 numRows  = 5;
  vector<vector<int>> expect   = {
      {1},
      {1, 1},
      {1, 2, 1},
      {1, 3, 3, 1},
      {1, 4, 6, 4, 1}
  };
  vector<vector<int>> actual = solution->generate(numRows);
  EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: numRows = 1
// Output: [[1]]
//

LEETCODE_SOLUTION_UNITTEST(118, PascalsTriangle, example_2) {
  auto                solution = MakeSolution();
  int                 numRows  = 1;
  vector<vector<int>> expect   = {{1}};
  vector<vector<int>> actual   = solution->generate(numRows);
  EXPECT_EQ(expect, actual);
}

// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Pascal's Triangle II
//
// https://leetcode.com/problems/pascals-triangle-ii/
//
// Question ID: 119
// Difficult  : Easy
// Solve Date : 2021/09/21 08:00

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |119. Pascal's Triangle II|:
//
// Given an integer |rowIndex|, return the |rowIndexᵗʰ| (0-indexed) row of the
// Pascal's triangle. In Pascal's triangle, each number is the sum of the two
// numbers directly above it as shown:
// ![img](https://upload.wikimedia.org/wikipedia/commons/0/0d/PascalTriangleAnimated2.gif)
//  
//

LEETCODE_BEGIN_RESOLVING(119, PascalSTriangleII, Solution);

class Solution {
public:
  vector<int> getRow(int rowIndex) {
    vector<int> res(rowIndex + 1, 1);
    for (int i = 1; i < rowIndex; ++i) {
      res[i] = (double)res[i - 1] * (double)(rowIndex - i + 1) / (double)i;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |0 <= rowIndex <= 33|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: rowIndex = 3
// Output: [1,3,3,1]
//

LEETCODE_SOLUTION_UNITTEST(119, PascalSTriangleII, example_1) {
  auto        solution = MakeSolution();
  int         rowIndex = 3;
  vector<int> expect   = {1, 3, 3, 1};
  vector<int> actual   = solution->getRow(rowIndex);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: rowIndex = 0
// Output: [1]
//

LEETCODE_SOLUTION_UNITTEST(119, PascalSTriangleII, example_2) {
  auto        solution = MakeSolution();
  int         rowIndex = 0;
  vector<int> expect   = {1};
  vector<int> actual   = solution->getRow(rowIndex);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: rowIndex = 1
// Output: [1,1]
//

LEETCODE_SOLUTION_UNITTEST(119, PascalSTriangleII, example_3) {
  auto        solution = MakeSolution();
  int         rowIndex = 1;
  vector<int> expect   = {1, 1};
  vector<int> actual   = solution->getRow(rowIndex);
  LCD_EXPECT_EQ(expect, actual);
}

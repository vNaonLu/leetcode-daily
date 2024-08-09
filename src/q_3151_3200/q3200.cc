// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Maximum Height of a Triangle
//
// https://leetcode.com/problems/maximum-height-of-a-triangle/
//
// Question ID: 3200
// Difficult  : Easy
// Solve Date : 2024/08/02 20:06

#include <cmath>
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3200. Maximum Height of a Triangle|:
//
//

LEETCODE_BEGIN_RESOLVING(3200, MaximumHeightOfATriangle, Solution);

class Solution {
public:
  int maxHeightOfTriangle(int red, int blue) {
    int m   = find(red);
    int n   = sqrt(blue);
    int res = m < n ? (m * 2 + 1) : (2 * n);
    n       = sqrt(red);
    m       = find(blue);
    res     = max(res, m < n ? (m * 2 + 1) : (2 * n));
    return res;
  }

private:
  int find(int r) {
    int s = sqrt(r);
    if (s * (s + 1) > r) {
      return s - 1;
    }
    return s;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= red, blue <= 100|
///////////////////////////////////////////////////////////////////////////////

LEETCODE_SOLUTION_UNITTEST(3200, MaximumHeightOfATriangle, example_1) {
  auto solution = MakeSolution();
  int  red      = 2;
  int  blue     = 4;
  int  expect   = 3;
  int  actual   = solution->maxHeightOfTriangle(red, blue);
  LCD_EXPECT_EQ(expect, actual);
}

LEETCODE_SOLUTION_UNITTEST(3200, MaximumHeightOfATriangle, example_2) {
  auto solution = MakeSolution();
  int  red      = 2;
  int  blue     = 1;
  int  expect   = 2;
  int  actual   = solution->maxHeightOfTriangle(red, blue);
  LCD_EXPECT_EQ(expect, actual);
}

LEETCODE_SOLUTION_UNITTEST(3200, MaximumHeightOfATriangle, example_3) {
  auto solution = MakeSolution();
  int  red      = 1;
  int  blue     = 1;
  int  expect   = 1;
  int  actual   = solution->maxHeightOfTriangle(red, blue);
  LCD_EXPECT_EQ(expect, actual);
}

LEETCODE_SOLUTION_UNITTEST(3200, MaximumHeightOfATriangle, example_4) {
  auto solution = MakeSolution();
  int  red      = 10;
  int  blue     = 1;
  int  expect   = 2;
  int  actual   = solution->maxHeightOfTriangle(red, blue);
  LCD_EXPECT_EQ(expect, actual);
}

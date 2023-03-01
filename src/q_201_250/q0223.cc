// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Rectangle Area
//
// https://leetcode.com/problems/rectangle-area/
//
// Question ID: 223
// Difficult  : Medium
// Solve Date : 2022/08/22 16:45

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |223. Rectangle Area|:
//
// Given the coordinates of two rectilinear rectangles in a 2D plane, return the
// total area covered by the two rectangles. The first rectangle is defined by
// its bottom-left corner |(ax1, ay1)| and its top-right corner |(ax2, ay2)|.
// The second rectangle is defined by its bottom-left corner |(bx1, by1)| and
// its top-right corner |(bx2, by2)|.
//

LEETCODE_BEGIN_RESOLVING(223, RectangleArea, Solution);

class Solution {
public:
  int computeArea(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2,
                  int by2) {
    return (ax2 - ax1) * (ay2 - ay1) + (bx2 - bx1) * (by2 - by1) -
           max(0, min(ax2, bx2) - max(ax1, bx1)) *
               max(0, min(ay2, by2) - max(ay1, by1));
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |-10⁴ <= ax1 <= ax2 <= 10⁴|
// * |-10⁴ <= ay1 <= ay2 <= 10⁴|
// * |-10⁴ <= bx1 <= bx2 <= 10⁴|
// * |-10⁴ <= by1 <= by2 <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: ax1 = -3, ay1 = 0, ax2 = 3, ay2 = 4, bx1 = 0, by1 = -1, bx2 = 9, by2
//  = 2
// Output: 45
//

LEETCODE_SOLUTION_UNITTEST(223, RectangleArea, example_1) {
  auto solution = MakeSolution();
  int  ax1      = -3;
  int  ay1      = 0;
  int  ax2      = 3;
  int  ay2      = 4;
  int  bx1      = 0;
  int  by1      = -1;
  int  bx2      = 9;
  int  by2      = 2;
  int  expect   = 45;
  int  actual   = solution->computeArea(ax1, ay1, ax2, ay2, bx1, by1, bx2, by2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: ax1 = -2, ay1 = -2, ax2 = 2, ay2 = 2, bx1 = -2, by1 = -2, bx2 = 2,
//  by2 = 2
// Output: 16
//

LEETCODE_SOLUTION_UNITTEST(223, RectangleArea, example_2) {
  auto solution = MakeSolution();
  int  ax1      = -2;
  int  ay1      = -2;
  int  ax2      = 2;
  int  ay2      = 2;
  int  bx1      = -2;
  int  by1      = -2;
  int  bx2      = 2;
  int  by2      = 2;
  int  expect   = 16;
  int  actual   = solution->computeArea(ax1, ay1, ax2, ay2, bx1, by1, bx2, by2);
  LCD_EXPECT_EQ(expect, actual);
}

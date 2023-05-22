// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Rectangle Overlap
//
// https://leetcode.com/problems/rectangle-overlap/
//
// Question ID: 836
// Difficult  : Easy
// Solve Date : 2023/05/20 11:29

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |836. Rectangle Overlap|:
//
// An axis-aligned rectangle is represented as a list |[x1, y1, x2, y2]|, where
// |(x1, y1)| is the coordinate of its bottom-left corner, and |(x2, y2)| is the
// coordinate of its top-right corner. Its top and bottom edges are parallel to
// the X-axis, and its left and right edges are parallel to the Y-axis. Two
// rectangles overlap if the area of their intersection is positive. To be
// clear, two rectangles that only touch at the corner or edges do not overlap.
// Given two axis-aligned rectangles |rec1| and |rec2|, return |true| if they
// overlap, otherwise return |false|.
//
//

LEETCODE_BEGIN_RESOLVING(836, RectangleOverlap, Solution);

class Solution {
public:
  bool isRectangleOverlap(vector<int> &rec1, vector<int> &rec2) {
    int x1 = rec1[0], y1 = rec1[1], x2 = rec1[2], y2 = rec1[3];
    int x3 = rec2[0], y3 = rec2[1], x4 = rec2[2], y4 = rec2[3];
    return (x1 < x4 && x3 < x2 && y1 < y4 && y3 < y2);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |rec1.length == 4|
// * |rec2.length == 4|
// * |-10⁹ <= rec1[i], rec2[i] <= 10⁹|
// * |rec1| and |rec2| represent a valid rectangle with a non-zero area.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: rec1 = [0,0,2,2], rec2 = [1,1,3,3]
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(836, RectangleOverlap, example_1) {
  auto        solution = MakeSolution();
  vector<int> rec1     = {0, 0, 2, 2};
  vector<int> rec2     = {1, 1, 3, 3};
  bool        expect   = true;
  bool        actual   = solution->isRectangleOverlap(rec1, rec2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: rec1 = [0,0,1,1], rec2 = [1,0,2,1]
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(836, RectangleOverlap, example_2) {
  auto        solution = MakeSolution();
  vector<int> rec1     = {0, 0, 1, 1};
  vector<int> rec2     = {1, 0, 2, 1};
  bool        expect   = false;
  bool        actual   = solution->isRectangleOverlap(rec1, rec2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: rec1 = [0,0,1,1], rec2 = [2,2,3,3]
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(836, RectangleOverlap, example_3) {
  auto        solution = MakeSolution();
  vector<int> rec1     = {0, 0, 1, 1};
  vector<int> rec2     = {2, 2, 3, 3};
  bool        expect   = false;
  bool        actual   = solution->isRectangleOverlap(rec1, rec2);
  LCD_EXPECT_EQ(expect, actual);
}

// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Maximum Area of a Piece of Cake After Horizontal and Vertical Cuts
//
// https://leetcode.com/problems/maximum-area-of-a-piece-of-cake-after-horizontal-and-vertical-cuts/
//
// Question ID: 1465
// Difficult  : Medium
// Solve Date : 2022/07/02 13:25

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1465. Maximum Area of a Piece of Cake After Horizontal and
// Vertical Cuts|:
//
// You are given a rectangular cake of size |h x w| and two arrays of integers
// |horizontalCuts| and |verticalCuts| where:
//
//  • |horizontalCuts[i]| is the distance from the top of the rectangular cake
//  to the |iᵗʰ| horizontal cut and similarly, and
//
//  • |verticalCuts[j]| is the distance from the left of the rectangular cake to
//  the |jᵗʰ| vertical cut.
// Return the maximum area of a piece of cake after you cut at each horizontal
// and vertical position provided in the arrays |horizontalCuts| and
// |verticalCuts|. Since the answer can be a large number, return this modulo
// |10⁹ + 7|.
//

LEETCODE_BEGIN_RESOLVING(
    1465, MaximumAreaOfAPieceOfCakeAfterHorizontalAndVerticalCuts, Solution);

class Solution {
public:
  int maxArea(int h, int w, vector<int> &horizontalCuts,
              vector<int> &verticalCuts) {
    constexpr static int kMod = 1e9 + 7;
    sort(horizontalCuts.begin(), horizontalCuts.end());
    sort(verticalCuts.begin(), verticalCuts.end());
    int64_t max_hori = horizontalCuts.front(), max_vert = verticalCuts.front();
    for (int i = 1; i < horizontalCuts.size(); ++i) {
      max_hori =
          max<int64_t>(max_hori, horizontalCuts[i] - horizontalCuts[i - 1]);
    }
    for (int i = 1; i < verticalCuts.size(); ++i) {
      max_vert = max<int64_t>(max_vert, verticalCuts[i] - verticalCuts[i - 1]);
    }
    max_hori = max<int64_t>(max_hori, h - horizontalCuts.back());
    max_vert = max<int64_t>(max_vert, w - verticalCuts.back());

    return (max_hori * max_vert) % kMod;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |2 <= h, w <= 10⁹|
// * |1 <= horizontalCuts.length <= min(h - 1, 10⁵)|
// * |1 <= verticalCuts.length <= min(w - 1, 10⁵)|
// * |1 <= horizontalCuts[i] < h|
// * |1 <= verticalCuts[i] < w|
// * All the elements in |horizontalCuts| are distinct.
// * All the elements in |verticalCuts| are distinct.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: h = 5, w = 4, horizontalCuts = [1,2,4], verticalCuts = [1,3]
// Output: 4
//
// The figure above represents the given rectangular cake. Red lines are the
// horizontal and vertical cuts. After you cut the cake, the green piece of cake
// has the maximum area.

LEETCODE_SOLUTION_UNITTEST(
    1465, MaximumAreaOfAPieceOfCakeAfterHorizontalAndVerticalCuts, example_1) {
  auto        solution       = MakeSolution();
  int         h              = 5;
  int         w              = 4;
  vector<int> horizontalCuts = {1, 2, 4};
  vector<int> verticalCuts   = {1, 3};
  int         expect         = 4;
  int         actual = solution->maxArea(h, w, horizontalCuts, verticalCuts);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: h = 5, w = 4, horizontalCuts = [3,1], verticalCuts = [1]
// Output: 6
//
// The figure above represents the given rectangular cake. Red lines are the
// horizontal and vertical cuts. After you cut the cake, the green and yellow
// pieces of cake have the maximum area.

LEETCODE_SOLUTION_UNITTEST(
    1465, MaximumAreaOfAPieceOfCakeAfterHorizontalAndVerticalCuts, example_2) {
  auto        solution       = MakeSolution();
  int         h              = 5;
  int         w              = 4;
  vector<int> horizontalCuts = {3, 1};
  vector<int> verticalCuts   = {1};
  int         expect         = 6;
  int         actual = solution->maxArea(h, w, horizontalCuts, verticalCuts);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: h = 5, w = 4, horizontalCuts = [3], verticalCuts = [3]
// Output: 9
//

LEETCODE_SOLUTION_UNITTEST(
    1465, MaximumAreaOfAPieceOfCakeAfterHorizontalAndVerticalCuts, example_3) {
  auto        solution       = MakeSolution();
  int         h              = 5;
  int         w              = 4;
  vector<int> horizontalCuts = {3};
  vector<int> verticalCuts   = {3};
  int         expect         = 9;
  int         actual = solution->maxArea(h, w, horizontalCuts, verticalCuts);
  LCD_EXPECT_EQ(expect, actual);
}

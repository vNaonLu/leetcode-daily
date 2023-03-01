// Copyright 2023 Naon Lu
//
// This file describes the solution of
// The Skyline Problem
//
// https://leetcode.com/problems/the-skyline-problem/
//
// Question ID: 218
// Difficult  : Hard
// Solve Date : 2022/09/30 20:58

#include <algorithm>
#include <iosfwd>
#include <map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |218. The Skyline Problem|:
//
// A city's skyline is the outer contour of the silhouette formed by all the
// buildings in that city when viewed from a distance. Given the locations and
// heights of all the buildings, return the skyline formed by these buildings
// collectively. The geometric information of each building is given in the
// array |buildings| where |buildings[i] = [leftᵢ, rightᵢ, heightᵢ]|:
//
//  • |leftᵢ| is the x coordinate of the left edge of the |iᵗʰ| building.
//
//  • |rightᵢ| is the x coordinate of the right edge of the |iᵗʰ| building.
//
//  • |heightᵢ| is the height of the |iᵗʰ| building.
// You may assume all buildings are perfect rectangles grounded on an absolutely
// flat surface at height |0|. The skyline should be represented as a list of
// "key points" sorted by their x-coordinate in the form
// |[[x₁,y₁],[x₂,y₂],...]|. Each key point is the left endpoint of some
// horizontal segment in the skyline except the last point in the list, which
// always has a y-coordinate |0| and is used to mark the skyline's termination
// where the rightmost building ends. Any ground between the leftmost and
// rightmost buildings should be part of the skyline's contour. Note: There must
// be no consecutive horizontal lines of equal height in the output skyline. For
// instance, |[...,[2 3],[4 5],[7 5],[11 5],[12 7],...]| is not acceptable; the
// three lines of height 5 should be merged into one in the final output as
// such: |[...,[2 3],[4 5],[12 7],...]|
//

LEETCODE_BEGIN_RESOLVING(218, TheSkylineProblem, Solution);

class Solution {
public:
  vector<vector<int>> getSkyline(vector<vector<int>> &buildings) {
    auto coord = vector<pair<int, int>>();
    auto freq  = map<int, int>();
    auto res   = vector<vector<int>>();

    for (auto &v : buildings) {
      /// minus means front
      coord.emplace_back(v[0], -v[2]);
      coord.emplace_back(v[1], v[2]);
    }
    sort(coord.begin(), coord.end());

    freq[0] = 1;
    for (auto [x, y] : coord) {
      if (y < 0) {
        ++freq[-y];
      } else {
        if (--freq[y] == 0) {
          freq.erase(y);
        }
      }

      auto tallest = freq.rbegin()->first;
      if (!res.empty()) {
        auto prev_x = res.back()[0];
        auto prev_y = res.back()[1];

        if (prev_y == tallest) {
          continue;
        }

        if (prev_x == x) {
          res.pop_back();
        }
      }

      res.emplace_back(vector<int>{x, tallest});
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= buildings.length <= 10⁴|
// * |0 <= leftᵢ < rightᵢ <= 2³¹ - 1|
// * |1 <= heightᵢ <= 2³¹ - 1|
// * |buildings| is sorted by |leftᵢ| innon-decreasing order.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: buildings = [[2,9,10],[3,7,15],[5,12,12],[15,20,10],[19,24,8]]
// Output: [[2,10],[3,15],[7,12],[12,0],[15,10],[20,8],[24,0]]
//
// Figure A shows the buildings of the input.
// Figure B shows the skyline formed by those buildings. The red points in
// figure B represent the key points in the output list.

LEETCODE_SOLUTION_UNITTEST(218, TheSkylineProblem, example_1) {
  auto                solution  = MakeSolution();
  vector<vector<int>> buildings = {
      { 2,  9, 10},
      { 3,  7, 15},
      { 5, 12, 12},
      {15, 20, 10},
      {19, 24,  8}
  };
  vector<vector<int>> expect = {
      { 2, 10},
      { 3, 15},
      { 7, 12},
      {12,  0},
      {15, 10},
      {20,  8},
      {24,  0}
  };
  vector<vector<int>> actual = solution->getSkyline(buildings);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: buildings = [[0,2,3],[2,5,3]]
// Output: [[0,3],[5,0]]
//

LEETCODE_SOLUTION_UNITTEST(218, TheSkylineProblem, example_2) {
  auto                solution  = MakeSolution();
  vector<vector<int>> buildings = {
      {0, 2, 3},
      {2, 5, 3}
  };
  vector<vector<int>> expect = {
      {0, 3},
      {5, 0}
  };
  vector<vector<int>> actual = solution->getSkyline(buildings);
  LCD_EXPECT_EQ(expect, actual);
}

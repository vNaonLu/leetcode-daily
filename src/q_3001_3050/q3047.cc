// Copyright 2026 Naon Lu
//
// This file describes the solution of
// Find the Largest Area of Square Inside Two Rectangles
//
// https://leetcode.com/problems/find-the-largest-area-of-square-inside-two-rectangles/
//
// Question ID: 3047
// Difficult  : Medium
// Solve Date : 2026/01/17 12:42

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3047. Find the Largest Area of Square Inside Two Rectangles|:
//
// There exist |n| rectangles in a 2D plane with edges parallel to the x and y
// axis. You are given two 2D integer arrays |bottomLeft| and |topRight| where
// |bottomLeft[i] = [a_i, b_i]| and |topRight[i] = [c_i, d_i]| represent the
// bottom-left and top-right coordinates of the |iᵗʰ| rectangle, respectively.
// You need to find the maximum area of a square that can fit inside the
// intersecting region of at least two rectangles. Return |0| if such a square
// does not exist.
//
//

LEETCODE_BEGIN_RESOLVING(3047, FindTheLargestAreaOfSquareInsideTwoRectangles,
                         Solution);

class Solution {
public:
  long long largestSquareArea(vector<vector<int>> &bottomLeft,
                              vector<vector<int>> &topRight) {
    int64_t res = 0;
    auto    n   = bottomLeft.size();
    for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        int mn_x = max(bottomLeft[i][0], bottomLeft[j][0]);
        int mx_x = min(topRight[i][0], topRight[j][0]);
        int mn_y = max(bottomLeft[i][1], bottomLeft[j][1]);
        int mx_y = min(topRight[i][1], topRight[j][1]);
        if (mn_x < mx_x && mn_y < mx_y) {
          res = max<int>(res, min(mx_x - mn_x, mx_y - mn_y));
        }
      }
    }
    return res * res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |n == bottomLeft.length == topRight.length|
// * |2 <= n <= 10³|
// * |bottomLeft[i].length == topRight[i].length == 2|
// * |1 <= bottomLeft[i][0], bottomLeft[i][1] <= 10⁷|
// * |1 <= topRight[i][0], topRight[i][1] <= 10⁷|
// * |bottomLeft[i][0] < topRight[i][0]|
// * |bottomLeft[i][1] < topRight[i][1]|
///////////////////////////////////////////////////////////////////////////////

LEETCODE_SOLUTION_UNITTEST(3047, FindTheLargestAreaOfSquareInsideTwoRectangles,
                           example_1) {
  auto                solution   = MakeSolution();
  vector<vector<int>> bottomLeft = {
      {1, 1},
      {2, 2},
      {3, 1}
  };
  vector<vector<int>> topRight = {
      {3, 3},
      {4, 4},
      {6, 6}
  };
  int expect = 1;
  int actual = solution->largestSquareArea(bottomLeft, topRight);
  LCD_EXPECT_EQ(expect, actual);
}

LEETCODE_SOLUTION_UNITTEST(3047, FindTheLargestAreaOfSquareInsideTwoRectangles,
                           example_2) {
  auto                solution   = MakeSolution();
  vector<vector<int>> bottomLeft = {
      {1, 1},
      {1, 3},
      {1, 5}
  };
  vector<vector<int>> topRight = {
      {5, 5},
      {5, 7},
      {5, 9}
  };
  int expect = 4;
  int actual = solution->largestSquareArea(bottomLeft, topRight);
  LCD_EXPECT_EQ(expect, actual);
}

LEETCODE_SOLUTION_UNITTEST(3047, FindTheLargestAreaOfSquareInsideTwoRectangles,
                           example_3) {
  auto                solution   = MakeSolution();
  vector<vector<int>> bottomLeft = {
      {1, 1},
      {2, 2},
      {1, 2}
  };
  vector<vector<int>> topRight = {
      {3, 3},
      {4, 4},
      {3, 4}
  };
  int expect = 1;
  int actual = solution->largestSquareArea(bottomLeft, topRight);
  LCD_EXPECT_EQ(expect, actual);
}

LEETCODE_SOLUTION_UNITTEST(3047, FindTheLargestAreaOfSquareInsideTwoRectangles,
                           example_4) {
  auto                solution   = MakeSolution();
  vector<vector<int>> bottomLeft = {
      {1, 1},
      {3, 3},
      {3, 1}
  };
  vector<vector<int>> topRight = {
      {2, 2},
      {4, 4},
      {4, 2}
  };
  int expect = 0;
  int actual = solution->largestSquareArea(bottomLeft, topRight);
  LCD_EXPECT_EQ(expect, actual);
}

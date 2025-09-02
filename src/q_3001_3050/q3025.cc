// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Find the Number of Ways to Place People I
//
// https://leetcode.com/problems/find-the-number-of-ways-to-place-people-i/
//
// Question ID: 3025
// Difficult  : Medium
// Solve Date : 2025/09/02 19:07

#include <algorithm>
#include <iosfwd>
#include <span>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3025. Find the Number of Ways to Place People I|:
//
// You are given a 2D array |points| of size |n x 2| representing integer
// coordinates of some points on a 2D plane, where |points[i] = [xᵢ, yᵢ]|. Count
// the number of pairs of points |(A, B)|, where
//
//  • |A| is on the upper left side of |B|, and
//
//  • there are no other points in the rectangle (or line) they make (including
//  the border).
// Return the count.
//
//

LEETCODE_BEGIN_RESOLVING(3025, FindTheNumberOfWaysToPlacePeopleI, Solution);

class Solution {
public:
  int numberOfPairs(vector<vector<int>> &points) {
    int res = 0;
    sort(points.begin(), points.end(), Cmp{});
    for (int i = 0; i < points.size(); ++i) {
      int yi = points[i][1];
      int y  = 51;
      for (int j = i + 1; j < points.size(); ++j) {
        int yj = points[j][1];
        if (yi <= yj && y > yj) {
          ++res;
          y = yj;
        }
      }
    }
    return res;
  }

private:
  struct Cmp {
    bool operator()(auto const &a, auto const &b) const {
      return a[0] == b[0] ? a[1] < b[1] : a[0] > b[0];
    }
  };

  bool contains(auto const &a, auto const &b, auto const &x) {
    return x[0] >= a[0] && x[0] <= b[0] && x[1] >= a[1] && x[1] <= b[1];
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= n <= 50|
// * |points[i].length == 2|
// * |0 <= points[i][0], points[i][1] <= 50|
// * All |points[i]| are distinct.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: points = [[1,1],[2,2],[3,3]]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(3025, FindTheNumberOfWaysToPlacePeopleI, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> points   = {
      {1, 1},
      {2, 2},
      {3, 3}
  };
  int expect = 0;
  int actual = solution->numberOfPairs(points);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: points = [[6,2],[4,4],[2,6]]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(3025, FindTheNumberOfWaysToPlacePeopleI, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> points   = {
      {6, 2},
      {4, 4},
      {2, 6}
  };
  int expect = 2;
  int actual = solution->numberOfPairs(points);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: points = [[3,1],[1,3],[1,1]]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(3025, FindTheNumberOfWaysToPlacePeopleI, example_3) {
  auto                solution = MakeSolution();
  vector<vector<int>> points   = {
      {3, 1},
      {1, 3},
      {1, 1}
  };
  int expect = 2;
  int actual = solution->numberOfPairs(points);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: [[0,5],[4,5]]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(3025, FindTheNumberOfWaysToPlacePeopleI,
                           extra_testcase_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> points   = {
      {0, 5},
      {4, 5}
  };
  int expect = 1;
  int actual = solution->numberOfPairs(points);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #2]
//  Input: [[0,1],[1,3],[6,1]]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(3025, FindTheNumberOfWaysToPlacePeopleI,
                           extra_testcase_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> points   = {
      {0, 1},
      {1, 3},
      {6, 1}
  };
  int expect = 2;
  int actual = solution->numberOfPairs(points);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #3]
//  Input:
//  [[8,45],[9,13],[48,24],[14,39],[5,26],[26,19],[11,6],[36,38],[42,45],[37,32],[6,18],[24,8],[43,38],[38,27],[31,50],[16,21],[26,16],[31,42],[40,18],[31,38],[20,45],[47,32],[3,0],[43,29],[48,12]]
// Output: 41
//

LEETCODE_SOLUTION_UNITTEST(3025, FindTheNumberOfWaysToPlacePeopleI,
                           extra_testcase_3) {
  auto                solution = MakeSolution();
  vector<vector<int>> points   = {
      { 8, 45},
      { 9, 13},
      {48, 24},
      {14, 39},
      { 5, 26},
      {26, 19},
      {11,  6},
      {36, 38},
      {42, 45},
      {37, 32},
      { 6, 18},
      {24,  8},
      {43, 38},
      {38, 27},
      {31, 50},
      {16, 21},
      {26, 16},
      {31, 42},
      {40, 18},
      {31, 38},
      {20, 45},
      {47, 32},
      { 3,  0},
      {43, 29},
      {48, 12}
  };
  int expect = 41;
  int actual = solution->numberOfPairs(points);
  LCD_EXPECT_EQ(expect, actual);
}

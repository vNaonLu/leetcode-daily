// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Valid Square
//
// https://leetcode.com/problems/valid-square/
//
// Question ID: 593
// Difficult  : Medium
// Solve Date : 2024/04/22 22:47

#include <iosfwd>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |593. Valid Square|:
//
// Given the coordinates of four points in 2D space |p1|, |p2|, |p3| and |p4|,
// return |true| if the four points construct a square. The coordinate of a
// point |pᵢ| is represented as |[xᵢ, yᵢ]|. The input is not given in any order.
// A valid square has four equal sides with positive length and four equal
// angles (90-degree angles).
//
//

LEETCODE_BEGIN_RESOLVING(593, ValidSquare, Solution);

class Solution {
public:
  bool validSquare(vector<int> &p1, vector<int> &p2, vector<int> &p3,
                   vector<int> &p4) {
    vector<vector<int>>     points{p1, p2, p3, p4};
    unordered_map<int, int> cnt;
    int                     side = numeric_limits<int>::max();
    for (int i = 0; i < 4; ++i) {
      for (int j = i + 1; j < 4; ++j) {
        int x   = points[i][0] - points[j][0];
        int y   = points[i][1] - points[j][1];
        int var = x * x + y * y;
        side    = min(side, var);
        ++cnt[var];
      }
    }
    return cnt[side] == 4 && cnt[2 * side] == 2;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |p1.length == p2.length == p3.length == p4.length == 2|
// * |-10⁴ <= xᵢ, yᵢ <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: p1 = [0,0], p2 = [1,1], p3 = [1,0], p4 = [0,1]
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(593, ValidSquare, example_1) {
  auto        solution = MakeSolution();
  vector<int> p1       = {0, 0};
  vector<int> p2       = {1, 1};
  vector<int> p3       = {1, 0};
  vector<int> p4       = {0, 1};
  bool        expect   = true;
  bool        actual   = solution->validSquare(p1, p2, p3, p4);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: p1 = [0,0], p2 = [1,1], p3 = [1,0], p4 = [0,12]
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(593, ValidSquare, example_2) {
  auto        solution = MakeSolution();
  vector<int> p1       = {0, 0};
  vector<int> p2       = {1, 1};
  vector<int> p3       = {1, 0};
  vector<int> p4       = {0, 12};
  bool        expect   = false;
  bool        actual   = solution->validSquare(p1, p2, p3, p4);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: p1 = [1,0], p2 = [-1,0], p3 = [0,1], p4 = [0,-1]
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(593, ValidSquare, example_3) {
  auto        solution = MakeSolution();
  vector<int> p1       = {1, 0};
  vector<int> p2       = {-1, 0};
  vector<int> p3       = {0, 1};
  vector<int> p4       = {0, -1};
  bool        expect   = true;
  bool        actual   = solution->validSquare(p1, p2, p3, p4);
  LCD_EXPECT_EQ(expect, actual);
}

// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Rotating the Box
//
// https://leetcode.com/problems/rotating-the-box/
//
// Question ID: 1861
// Difficult  : Medium
// Solve Date : 2024/11/23 15:39

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1861. Rotating the Box|:
//
// You are given an |m x n| matrix of characters |box| representing a side-view
// of a box. Each cell of the box is one of the following:
//
//
//
//  • A stone |'#'|
//
//  • A stationary obstacle |'*'|
//
//  • Empty |'.'|
//
//
// The box is rotated 90 degrees clockwise, causing some of the stones to fall
// due to gravity. Each stone falls down until it lands on an obstacle, another
// stone, or the bottom of the box. Gravity does not affect the obstacles'
// positions, and the inertia from the box's rotation does not affect the
// stones' horizontal positions.
//
// It is guaranteed that each stone in |box| rests on an obstacle, another
// stone, or the bottom of the box.
//
// Return an |n x m| matrix representing the box after the rotation described
// above.
//
//
//

LEETCODE_BEGIN_RESOLVING(1861, RotatingTheBox, Solution);

class Solution {
public:
  vector<vector<char>> rotateTheBox(vector<vector<char>> &box) {
    int                  m = box.size();
    int                  n = box[0].size();
    vector<vector<char>> res(n, vector<char>(m, '.'));
    for (int i = 0; i < m; ++i) {
      int bottom = n - 1;
      for (int j = n - 1; j >= 0; --j) {
        if (box[i][j] == '#') {
          res[bottom][m - 1 - i] = '#';
          --bottom;
        } else if (box[i][j] == '*') {
          res[j][m - 1 - i] = '*';
          bottom            = j - 1;
        }
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |m == box.length|
// * |n == box[i].length|
// * |1 <= m, n <= 500|
// * |box[i][j]| is either |'#'|, |'*'|, or |'.'|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: box = [["#",".","#"]]
// Output: [["."],
//   ["#"],
//   ["#"]]
//

LEETCODE_SOLUTION_UNITTEST(1861, RotatingTheBox, example_1) {
  auto                 solution = MakeSolution();
  vector<vector<char>> box      = {
      {'#', '.', '#'}
  };
  vector<vector<char>> expect = {{'.'}, {'#'}, {'#'}};
  vector<vector<char>> actual = solution->rotateTheBox(box);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: box = [["#",".","*","."],
//   ["#","#","*","."]]
// Output: [["#","."],
//   ["#","#"],
//   ["*","*"],
//   [".","."]]
//

LEETCODE_SOLUTION_UNITTEST(1861, RotatingTheBox, example_2) {
  auto                 solution = MakeSolution();
  vector<vector<char>> box      = {
      {'#', '.', '*', '.'},
      {'#', '#', '*', '.'}
  };
  vector<vector<char>> expect = {
      {'#', '.'},
      {'#', '#'},
      {'*', '*'},
      {'.', '.'}
  };
  vector<vector<char>> actual = solution->rotateTheBox(box);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: box = [["#","#","*",".","*","."],
//   ["#","#","#","*",".","."],
//   ["#","#","#",".","#","."]]
// Output: [[".","#","#"],
//   [".","#","#"],
//   ["#","#","*"],
//   ["#","*","."],
//   ["#",".","*"],
//   ["#",".","."]]
//

LEETCODE_SOLUTION_UNITTEST(1861, RotatingTheBox, example_3) {
  auto                 solution = MakeSolution();
  vector<vector<char>> box      = {
      {'#', '#', '*', '.', '*', '.'},
      {'#', '#', '#', '*', '.', '.'},
      {'#', '#', '#', '.', '#', '.'}
  };
  vector<vector<char>> expect = {
      {'.', '#', '#'},
      {'.', '#', '#'},
      {'#', '#', '*'},
      {'#', '*', '.'},
      {'#', '.', '*'},
      {'#', '.', '.'}
  };
  vector<vector<char>> actual = solution->rotateTheBox(box);
  LCD_EXPECT_EQ(expect, actual);
}

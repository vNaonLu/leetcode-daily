// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Flood Fill
//
// https://leetcode.com/problems/flood-fill/
//
// Question ID: 733
// Difficult  : Easy
// Solve Date : 2021/09/11 08:00

#include <iosfwd>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |733. Flood Fill|:
//
// An image is represented by an |m x n| integer grid |image| where
// |image[i][j]| represents the pixel value of the image. You are also given
// three integers |sr|, |sc|, and |color|. You should perform a flood fill on
// the image starting from the pixel |image[sr][sc]|. To perform a flood fill,
// consider the starting pixel, plus any pixels connected 4-directionally to the
// starting pixel of the same color as the starting pixel, plus any pixels
// connected 4-directionally to those pixels (also with the same color), and so
// on. Replace the color of all of the aforementioned pixels with |color|.
// Return the modified image after performing the flood fill.
//  
//

LEETCODE_BEGIN_RESOLVING(733, FloodFill, Solution);

class Solution {
private:
  vector<pair<int, int>> dir{
      { 1,  0},
      {-1,  0},
      { 0,  1},
      { 0, -1}
  };

public:
  vector<vector<int>> floodFill(vector<vector<int>> &image, int sr, int sc,
                                int newColor) {
    vector<vector<bool>>  visit(image.size(),
                                vector<bool>(image[0].size(), false));
    queue<pair<int, int>> q;
    int                   color = image[sr][sc];
    q.push({sr, sc});
    while (!q.empty()) {
      auto point = q.front();
      q.pop();
      image[point.first][point.second] = newColor;
      for (int i = 0; i < 4; ++i) {
        pair<int, int> new_p = {point.first + dir[i].first,
                                point.second + dir[i].second};
        if (new_p.first >= 0 && new_p.first < image.size() &&
            new_p.second >= 0 && new_p.second < image[0].size() &&
            !visit[new_p.first][new_p.second] &&
            image[new_p.first][new_p.second] == color) {
          visit[new_p.first][new_p.second] = true;
          q.push(new_p);
        }
      }
    }
    return image;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |m == image.length|
// * |n == image[i].length|
// * |1 <= m, n <= 50|
// * |0 <= image[i][j], color < 2¹⁶|
// * |0 <= sr < m|
// * |0 <= sc < n|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: image = [[1,1,1],[1,1,0],[1,0,1]], sr = 1, sc = 1, color = 2
// Output: [[2,2,2],[2,2,0],[2,0,1]]
//
// From the center of the image with position (sr, sc) = (1, 1) (i.e., the red
// pixel), all pixels connected by a path of the same color as the starting
// pixel (i.e., the blue pixels) are colored with the new color. Note the bottom
// corner is not colored 2, because it is not 4-directionally connected to the
// starting pixel.

LEETCODE_SOLUTION_UNITTEST(733, FloodFill, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> image    = {
      {1, 1, 1},
      {1, 1, 0},
      {1, 0, 1}
  };
  int                 sr     = 1;
  int                 sc     = 1;
  int                 color  = 2;
  vector<vector<int>> expect = {
      {2, 2, 2},
      {2, 2, 0},
      {2, 0, 1}
  };
  vector<vector<int>> actual = solution->floodFill(image, sr, sc, color);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: image = [[0,0,0],[0,0,0]], sr = 0, sc = 0, color = 0
// Output: [[0,0,0],[0,0,0]]
//
// The starting pixel is already colored 0, so no changes are made to the image.

LEETCODE_SOLUTION_UNITTEST(733, FloodFill, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> image    = {
      {0, 0, 0},
      {0, 0, 0}
  };
  int                 sr     = 0;
  int                 sc     = 0;
  int                 color  = 0;
  vector<vector<int>> expect = {
      {0, 0, 0},
      {0, 0, 0}
  };
  vector<vector<int>> actual = solution->floodFill(image, sr, sc, color);
  LCD_EXPECT_EQ(expect, actual);
}

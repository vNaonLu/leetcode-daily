// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Image Smoother
//
// https://leetcode.com/problems/image-smoother/
//
// Question ID: 661
// Difficult  : Easy
// Solve Date : 2022/09/28 17:49

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |661. Image Smoother|:
//
// An image smoother is a filter of the size |3 x 3| that can be applied to each
// cell of an image by rounding down the average of the cell and the eight
// surrounding cells (i.e., the average of the nine cells in the blue smoother).
// If one or more of the surrounding cells of a cell is not present, we do not
// consider it in the average (i.e., the average of the four cells in the red
// smoother).
// ![img](https://assets.leetcode.com/uploads/2021/05/03/smoother-grid.jpg)
// Given an |m x n| integer matrix |img| representing the grayscale of an image,
// return the image after applying the smoother on each cell of it.
//

LEETCODE_BEGIN_RESOLVING(661, ImageSmoother, Solution);

class Solution {
private:
  int avg(vector<vector<int>> &img, int x, int y) {
    auto res = (int)0;
    auto cnt = (int)0;
    auto m   = (int)img.size();
    auto n   = (int)img.front().size();
    for (int i = max(0, x - 1); i <= min(m - 1, x + 1); ++i) {
      for (int j = max(0, y - 1); j <= min(n - 1, y + 1); ++j) {
        res += img[i][j];
        ++cnt;
      }
    }
    return res / cnt;
  }

public:
  vector<vector<int>> imageSmoother(vector<vector<int>> &img) {
    auto m   = img.size();
    auto n   = img.front().size();
    auto res = vector<vector<int>>(m, vector<int>(n));
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        res[i][j] = avg(img, i, j);
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |m == img.length|
// * |n == img[i].length|
// * |1 <= m, n <= 200|
// * |0 <= img[i][j] <= 255|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: img = [[1,1,1],[1,0,1],[1,1,1]]
// Output: [[0,0,0],[0,0,0],[0,0,0]]
//
// For the points (0,0), (0,2), (2,0), (2,2): floor(3/4) = floor(0.75) = 0
// For the points (0,1), (1,0), (1,2), (2,1): floor(5/6) = floor(0.83333333) = 0
// For the point (1,1): floor(8/9) = floor(0.88888889) = 0

LEETCODE_SOLUTION_UNITTEST(661, ImageSmoother, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> img      = {
      {1, 1, 1},
      {1, 0, 1},
      {1, 1, 1}
  };
  vector<vector<int>> expect = {
      {0, 0, 0},
      {0, 0, 0},
      {0, 0, 0}
  };
  vector<vector<int>> actual = solution->imageSmoother(img);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: img = [[100,200,100],[200,50,200],[100,200,100]]
// Output: [[137,141,137],[141,138,141],[137,141,137]]
//
// For the points (0,0), (0,2), (2,0), (2,2): floor((100+200+200+50)/4) =
// floor(137.5) = 137 For the points (0,1), (1,0), (1,2), (2,1):
// floor((200+200+50+200+100+100)/6) = floor(141.666667) = 141 For the point
// (1,1): floor((50+200+200+200+200+100+100+100+100)/9) = floor(138.888889) =
// 138

LEETCODE_SOLUTION_UNITTEST(661, ImageSmoother, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> img      = {
      {100, 200, 100},
      {200,  50, 200},
      {100, 200, 100}
  };
  vector<vector<int>> expect = {
      {137, 141, 137},
      {141, 138, 141},
      {137, 141, 137}
  };
  vector<vector<int>> actual = solution->imageSmoother(img);
  LCD_EXPECT_EQ(expect, actual);
}

// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Image Overlap
//
// https://leetcode.com/problems/image-overlap/
//
// Question ID: 835
// Difficult  : Medium
// Solve Date : 2022/10/27 14:32

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |835. Image Overlap|:
//
// You are given two images, |img1| and |img2|, represented as binary, square
// matrices of size |n x n|. A binary matrix has only |0|s and |1|s as values.
// We translate one image however we choose by sliding all the |1| bits left,
// right, up, and/or down any number of units. We then place it on top of the
// other image. We can then calculate the overlap by counting the number of
// positions that have a |1| in both images. Note also that a translation does
// not include any kind of rotation. Any |1| bits that are translated outside of
// the matrix borders are erased. Return the largest possible overlap.
//

LEETCODE_BEGIN_RESOLVING(835, ImageOverlap, Solution);

class Solution {
private:
  int convolute(vector<vector<int>> &m, vector<vector<int>> &kernel, int xs,
                int ys) {
    auto res = (int)0;
    for (int i = 0; i < m.size(); ++i) {
      for (int j = 0; j < m.size(); ++j) {
        res += m[i][j] * kernel[i + ys][j + xs];
      }
    }
    return res;
  }

public:
  int largestOverlap(vector<vector<int>> &img1, vector<vector<int>> &img2) {
    auto n   = img1.size();
    auto pad = vector<vector<int>>(3 * n - 2, vector<int>(3 * n - 2));
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        pad[i + n - 1][j + n - 1] = img2[i][j];
      }
    }

    auto res = (int)0;
    for (int i = 0; i < 2 * n - 1; ++i) {
      for (int j = 0; j < 2 * n - 1; ++j) {
        res = max(res, convolute(img1, pad, i, j));
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == img1.length == img1[i].length|
// * |n == img2.length == img2[i].length|
// * |1 <= n <= 30|
// * |img1[i][j]| is either |0| or |1|.
// * |img2[i][j]| is either |0| or |1|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: img1 = [[1,1,0],[0,1,0],[0,1,0]], img2 = [[0,0,0],[0,1,1],[0,0,1]]
// Output: 3
//
// We translate img1 to right by 1 unit and down by 1 unit.
// ![img](https://assets.leetcode.com/uploads/2020/09/09/overlap_step1.jpg)
// The number of positions that have a 1 in both images is 3 (shown in red).
// ![img](https://assets.leetcode.com/uploads/2020/09/09/overlap_step2.jpg)

LEETCODE_SOLUTION_UNITTEST(835, ImageOverlap, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> img1     = {
      {1, 1, 0},
      {0, 1, 0},
      {0, 1, 0}
  };
  vector<vector<int>> img2 = {
      {0, 0, 0},
      {0, 1, 1},
      {0, 0, 1}
  };
  int expect = 3;
  int actual = solution->largestOverlap(img1, img2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: img1 = [[1]], img2 = [[1]]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(835, ImageOverlap, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> img1     = {{1}};
  vector<vector<int>> img2     = {{1}};
  int                 expect   = 1;
  int                 actual   = solution->largestOverlap(img1, img2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: img1 = [[0]], img2 = [[0]]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(835, ImageOverlap, example_3) {
  auto                solution = MakeSolution();
  vector<vector<int>> img1     = {{0}};
  vector<vector<int>> img2     = {{0}};
  int                 expect   = 0;
  int                 actual   = solution->largestOverlap(img1, img2);
  LCD_EXPECT_EQ(expect, actual);
}

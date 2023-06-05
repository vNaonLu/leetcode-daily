// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Flipping an Image
//
// https://leetcode.com/problems/flipping-an-image/
//
// Question ID: 832
// Difficult  : Easy
// Solve Date : 2023/06/05 11:21

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |832. Flipping an Image|:
//
// Given an |n x n| binary matrix |image|, flip the image horizontally, then
// invert it, and return the resulting image. To flip an image horizontally
// means that each row of the image is reversed.
//
//  • For example, flipping |[1,1,0]| horizontally results in |[0,1,1]|.
// To invert an image means that each |0| is replaced by |1|, and each |1| is
// replaced by |0|.
//
//  • For example, inverting |[0,1,1]| results in |[1,0,0]|.
//
//

LEETCODE_BEGIN_RESOLVING(832, FlippingAnImage, Solution);

class Solution {
public:
  vector<vector<int>> flipAndInvertImage(vector<vector<int>> &image) {
    for (auto &v : image) {
      reverse(v.begin(), v.end());
      for (auto &c : v) {
        c ^= 1;
      }
    }
    return image;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == image.length|
// * |n == image[i].length|
// * |1 <= n <= 20|
// * |images[i][j]| is either |0| or |1|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: image = [[1,1,0],[1,0,1],[0,0,0]]
// Output: [[1,0,0],[0,1,0],[1,1,1]]
//
// First reverse each row: [[0,1,1],[1,0,1],[0,0,0]].
// Then, invert the image: [[1,0,0],[0,1,0],[1,1,1]]

LEETCODE_SOLUTION_UNITTEST(832, FlippingAnImage, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> image    = {
      {1, 1, 0},
      {1, 0, 1},
      {0, 0, 0}
  };
  vector<vector<int>> expect = {
      {1, 0, 0},
      {0, 1, 0},
      {1, 1, 1}
  };
  vector<vector<int>> actual = solution->flipAndInvertImage(image);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: image = [[1,1,0,0],[1,0,0,1],[0,1,1,1],[1,0,1,0]]
// Output: [[1,1,0,0],[0,1,1,0],[0,0,0,1],[1,0,1,0]]
//
// First reverse each row: [[0,0,1,1],[1,0,0,1],[1,1,1,0],[0,1,0,1]].
// Then invert the image: [[1,1,0,0],[0,1,1,0],[0,0,0,1],[1,0,1,0]]

LEETCODE_SOLUTION_UNITTEST(832, FlippingAnImage, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> image    = {
      {1, 1, 0, 0},
      {1, 0, 0, 1},
      {0, 1, 1, 1},
      {1, 0, 1, 0}
  };
  vector<vector<int>> expect = {
      {1, 1, 0, 0},
      {0, 1, 1, 0},
      {0, 0, 0, 1},
      {1, 0, 1, 0}
  };
  vector<vector<int>> actual = solution->flipAndInvertImage(image);
  LCD_EXPECT_EQ(expect, actual);
}

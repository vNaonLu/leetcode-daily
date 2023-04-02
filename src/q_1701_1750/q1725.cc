// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Number Of Rectangles That Can Form The Largest Square
//
// https://leetcode.com/problems/number-of-rectangles-that-can-form-the-largest-square/
//
// Question ID: 1725
// Difficult  : Easy
// Solve Date : 2023/04/02 16:00

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1725. Number Of Rectangles That Can Form The Largest Square|:
//
// You are given an array |rectangles| where |rectangles[i] = [lᵢ, wᵢ]|
// represents the |iᵗʰ| rectangle of length |lᵢ| and width |wᵢ|.
//
// You can cut the |iᵗʰ| rectangle to form a square with a side length of |k| if
// both |k <= lᵢ| and |k <= wᵢ|. For example, if you have a rectangle |[4,6]|,
// you can cut it to get a square with a side length of at most |4|.
//
// Let |maxLen| be the side length of the largest square you can obtain from any
// of the given rectangles.
//
// Return the number of rectangles that can make a square with a side length of
// |maxLen|.
//
//
//

LEETCODE_BEGIN_RESOLVING(1725, NumberOfRectanglesThatCanFormTheLargestSquare,
                         Solution);

class Solution {
public:
  int countGoodRectangles(vector<vector<int>> &rectangles) {
    int res     = 0;
    int largest = 0;
    for (auto &r : rectangles) {
      largest = max(largest, min(r[0], r[1]));
    }
    for (auto &r : rectangles) {
      if (largest <= min(r[0], r[1])) {
        ++res;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= rectangles.length <= 1000|
// * |rectangles[i].length == 2|
// * |1 <= lᵢ, wᵢ <= 10⁹|
// * |lᵢ != wᵢ|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: rectangles = [[5,8],[3,9],[5,12],[16,5]]
// Output: 3
//
// The largest squares you can get from each rectangle are of lengths [5,3,5,5].
// The largest possible square is of length 5, and you can get it out of 3
// rectangles.

LEETCODE_SOLUTION_UNITTEST(1725, NumberOfRectanglesThatCanFormTheLargestSquare,
                           example_1) {
  auto                solution   = MakeSolution();
  vector<vector<int>> rectangles = {
      { 5,  8},
      { 3,  9},
      { 5, 12},
      {16,  5}
  };
  int expect = 3;
  int actual = solution->countGoodRectangles(rectangles);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: rectangles = [[2,3],[3,7],[4,3],[3,7]]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(1725, NumberOfRectanglesThatCanFormTheLargestSquare,
                           example_2) {
  auto                solution   = MakeSolution();
  vector<vector<int>> rectangles = {
      {2, 3},
      {3, 7},
      {4, 3},
      {3, 7}
  };
  int expect = 3;
  int actual = solution->countGoodRectangles(rectangles);
  LCD_EXPECT_EQ(expect, actual);
}

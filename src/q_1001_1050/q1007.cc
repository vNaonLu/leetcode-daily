// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimum Domino Rotations For Equal Row
//
// https://leetcode.com/problems/minimum-domino-rotations-for-equal-row/
//
// Question ID: 1007
// Difficult  : Medium
// Solve Date : 2022/03/09 18:17

#include <iosfwd>
#include <limits>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1007. Minimum Domino Rotations For Equal Row|:
//
// In a row of dominoes, |tops[i]| and |bottoms[i]| represent the top and bottom
// halves of the |iᵗʰ| domino. (A domino is a tile with two numbers from 1 to 6
// - one on each half of the tile.) We may rotate the |iᵗʰ| domino, so that
// |tops[i]| and |bottoms[i]| swap values. Return the minimum number of
// rotations so that all the values in |tops| are the same, or all the values in
// |bottoms| are the same. If it cannot be done, return |-1|.  
//

LEETCODE_BEGIN_RESOLVING(1007, MinimumDominoRotationsForEqualRow, Solution);

class Solution {
public:
  int minDominoRotations(vector<int> &tops, vector<int> &bottoms) {
    int res = numeric_limits<int>::max(), n = tops.size();
    for (int i = 1; i <= 6; ++i) {
      int  top_cnt = 0, bottom_cnt = 0;
      auto top_it = tops.begin(), bottom_it = bottoms.begin();
      while (top_it != tops.end() && bottom_it != bottoms.end()) {
        if (*top_it != i && *bottom_it != i) {
          break;
        } else if (*top_it != i) {
          ++top_cnt;
        } else if (*bottom_it != i) {
          ++bottom_cnt;
        }
        ++top_it;
        ++bottom_it;
      }
      if (top_it != tops.end())
        continue;

      res = min({res, top_cnt, bottom_cnt});
    }
    return res == numeric_limits<int>::max() ? -1 : res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |2 <= tops.length <= 2 * 10⁴|
// * |bottoms.length == tops.length|
// * |1 <= tops[i], bottoms[i] <= 6|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: tops = [2,1,2,4,2,2], bottoms = [5,2,6,2,3,2]
// Output: 2
//
// The first figure represents the dominoes as given by tops and bottoms: before
// we do any rotations. If we rotate the second and fourth dominoes, we can make
// every value in the top row equal to 2, as indicated by the second figure.

LEETCODE_SOLUTION_UNITTEST(1007, MinimumDominoRotationsForEqualRow, example_1) {
  auto        solution = MakeSolution();
  vector<int> tops     = {2, 1, 2, 4, 2, 2};
  vector<int> bottoms  = {5, 2, 6, 2, 3, 2};
  int         expect   = 2;
  int         actual   = solution->minDominoRotations(tops, bottoms);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: tops = [3,5,1,2,3], bottoms = [3,6,3,3,4]
// Output: -1
//
// In this case, it is not possible to rotate the dominoes to make one row of
// values equal.

LEETCODE_SOLUTION_UNITTEST(1007, MinimumDominoRotationsForEqualRow, example_2) {
  auto        solution = MakeSolution();
  vector<int> tops     = {3, 5, 1, 2, 3};
  vector<int> bottoms  = {3, 6, 3, 3, 4};
  int         expect   = -1;
  int         actual   = solution->minDominoRotations(tops, bottoms);
  LCD_EXPECT_EQ(expect, actual);
}

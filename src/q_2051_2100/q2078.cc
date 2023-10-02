// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Two Furthest Houses With Different Colors
//
// https://leetcode.com/problems/two-furthest-houses-with-different-colors/
//
// Question ID: 2078
// Difficult  : Easy
// Solve Date : 2023/09/26 22:17

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2078. Two Furthest Houses With Different Colors|:
//
// There are |n| houses evenly lined up on the street, and each house is
// beautifully painted. You are given a 0-indexed integer array |colors| of
// length |n|, where |colors[i]| represents the color of the |iᵗʰ| house. Return
// the maximum distance between two houses with different colors. The distance
// between the |iᵗʰ| and |jᵗʰ| houses is |abs(i - j)|, where |abs(x)| is the
// absolute value of |x|.
//
//

LEETCODE_BEGIN_RESOLVING(2078, TwoFurthestHousesWithDifferentColors, Solution);

class Solution {
public:
  int maxDistance(vector<int> &colors) {
    int lo  = 0;
    int hi  = colors.size() - 1;
    int res = 0;
    while (lo < hi) {
      if (colors[lo] != colors[hi]) {
        res = max(res, abs(lo - hi));
      }
      --hi;
    }
    lo = 0;
    hi = colors.size() - 1;
    while (lo < hi) {
      if (colors[lo] != colors[hi]) {
        res = max(res, abs(lo - hi));
      }
      ++lo;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |n == colors.length|
// * |2 <= n <= 100|
// * |0 <= colors[i] <= 100|
// * Test data are generated such that at least two houses have different
// colors.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: colors = [1,1,1,6,1,1,1]
// Output: 3
//
// In the above image, color 1 is blue, and color 6 is red.
// The furthest two houses with different colors are house 0 and house 3.
// House 0 has color 1, and house 3 has color 6. The distance between them is
// abs(0 - 3) = 3. Note that houses 3 and 6 can also produce the optimal answer.

LEETCODE_SOLUTION_UNITTEST(2078, TwoFurthestHousesWithDifferentColors,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> colors   = {1, 1, 1, 6, 1, 1, 1};
  int         expect   = 3;
  int         actual   = solution->maxDistance(colors);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: colors = [1,8,3,8,3]
// Output: 4
//
// In the above image, color 1 is blue, color 8 is yellow, and color 3 is green.
// The furthest two houses with different colors are house 0 and house 4.
// House 0 has color 1, and house 4 has color 3. The distance between them is
// abs(0 - 4) = 4.

LEETCODE_SOLUTION_UNITTEST(2078, TwoFurthestHousesWithDifferentColors,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> colors   = {1, 8, 3, 8, 3};
  int         expect   = 4;
  int         actual   = solution->maxDistance(colors);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: colors = [0,1]
// Output: 1
//
// The furthest two houses with different colors are house 0 and house 1.
// House 0 has color 0, and house 1 has color 1. The distance between them is
// abs(0 - 1) = 1.

LEETCODE_SOLUTION_UNITTEST(2078, TwoFurthestHousesWithDifferentColors,
                           example_3) {
  auto        solution = MakeSolution();
  vector<int> colors   = {0, 1};
  int         expect   = 1;
  int         actual   = solution->maxDistance(colors);
  LCD_EXPECT_EQ(expect, actual);
}

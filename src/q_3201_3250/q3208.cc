// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Alternating Groups II
//
// https://leetcode.com/problems/alternating-groups-ii/
//
// Question ID: 3208
// Difficult  : Medium
// Solve Date : 2025/03/09 11:20

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3208. Alternating Groups II|:
//
// There is a circle of red and blue tiles. You are given an array of integers
// |colors| and an integer |k|. The color of tile |i| is represented by
// |colors[i]|:
//
//  • |colors[i] == 0| means that tile |i| is red.
//
//  • |colors[i] == 1| means that tile |i| is blue.
// An alternating group is every |k| contiguous tiles in the circle with
// alternating colors (each tile in the group except the first and last one has
// a different color from its left and right tiles). Return the number of
// alternating groups. Note that since |colors| represents a circle, the first
// and the last tiles are considered to be next to each other.
//
//

LEETCODE_BEGIN_RESOLVING(3208, AlternatingGroupsII, Solution);

class Solution {
public:
  int numberOfAlternatingGroups(vector<int> &colors, int k) {
    int n   = colors.size();
    int res = 0;
    int lo  = 0;
    for (int hi = 0; hi < n + k - 1; ++hi) {
      if (hi > 0 && colors[hi % n] == colors[(hi - 1) % n]) {
        lo = hi;
      }
      if (hi - lo + 1 >= k) {
        ++res;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |3 <= colors.length <= 10⁵|
// * |0 <= colors[i] <= 1|
// * |3 <= k <= colors.length|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: colors = [0,1,0,1,0], k = 3
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(3208, AlternatingGroupsII, example_1) {
  auto        solution = MakeSolution();
  vector<int> colors   = {0, 1, 0, 1, 0};
  int         k        = 3;
  int         expect   = 3;
  int         actual   = solution->numberOfAlternatingGroups(colors, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: colors = [0,1,0,0,1,0,1], k = 6
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(3208, AlternatingGroupsII, example_2) {
  auto        solution = MakeSolution();
  vector<int> colors   = {0, 1, 0, 0, 1, 0, 1};
  int         k        = 6;
  int         expect   = 2;
  int         actual   = solution->numberOfAlternatingGroups(colors, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: colors = [1,1,0,1], k = 4
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(3208, AlternatingGroupsII, example_3) {
  auto        solution = MakeSolution();
  vector<int> colors   = {1, 1, 0, 1};
  int         k        = 4;
  int         expect   = 0;
  int         actual   = solution->numberOfAlternatingGroups(colors, k);
  LCD_EXPECT_EQ(expect, actual);
}

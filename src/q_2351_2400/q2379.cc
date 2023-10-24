// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimum Recolors to Get K Consecutive Black Blocks
//
// https://leetcode.com/problems/minimum-recolors-to-get-k-consecutive-black-blocks/
//
// Question ID: 2379
// Difficult  : Easy
// Solve Date : 2023/10/24 20:03

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2379. Minimum Recolors to Get K Consecutive Black Blocks|:
//
// You are given a 0-indexed string |blocks| of length |n|, where |blocks[i]| is
// either |'W'| or |'B'|, representing the color of the |iᵗʰ| block. The
// characters |'W'| and |'B'| denote the colors white and black, respectively.
// You are also given an integer |k|, which is the desired number of consecutive
// black blocks. In one operation, you can recolor a white block such that it
// becomes a black block. Return the minimum number of operations needed such
// that there is at least one occurrence of |k| consecutive black blocks.
//
//

LEETCODE_BEGIN_RESOLVING(2379, MinimumRecolorsToGetKConsecutiveBlackBlocks,
                         Solution);

class Solution {
public:
  int minimumRecolors(string blocks, int k) {
    int res = blocks.size();
    int i   = 0;
    int j   = 0;
    int cur = 0;
    while (j < blocks.size()) {
      if (blocks[j] == 'W') {
        ++cur;
      }
      if ((j - i + 1) < k) {
        ++j;
      } else {
        res = min(res, cur);
        ++j;
        if (blocks[i] == 'W') {
          --cur;
        }
        ++i;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |n == blocks.length|
// * |1 <= n <= 100|
// * |blocks[i]| is either |'W'| or |'B'|.
// * |1 <= k <= n|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: blocks = "WBBWWBBWBW", k = 7
// Output: 3
//
// One way to achieve 7 consecutive black blocks is to recolor the 0th, 3rd, and
// 4th blocks so that blocks = "BBBBBBBWBW". It can be shown that there is no
// way to achieve 7 consecutive black blocks in less than 3 operations.
// Therefore, we return 3.

LEETCODE_SOLUTION_UNITTEST(2379, MinimumRecolorsToGetKConsecutiveBlackBlocks,
                           example_1) {
  auto   solution = MakeSolution();
  string blocks   = "WBBWWBBWBW";
  int    k        = 7;
  int    expect   = 3;
  int    actual   = solution->minimumRecolors(blocks, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: blocks = "WBWBBBW", k = 2
// Output: 0
//
// No changes need to be made, since 2 consecutive black blocks already exist.
// Therefore, we return 0.

LEETCODE_SOLUTION_UNITTEST(2379, MinimumRecolorsToGetKConsecutiveBlackBlocks,
                           example_2) {
  auto   solution = MakeSolution();
  string blocks   = "WBWBBBW";
  int    k        = 2;
  int    expect   = 0;
  int    actual   = solution->minimumRecolors(blocks, k);
  LCD_EXPECT_EQ(expect, actual);
}

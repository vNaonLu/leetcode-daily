// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Letter Tile Possibilities
//
// https://leetcode.com/problems/letter-tile-possibilities/
//
// Question ID: 1079
// Difficult  : Medium
// Solve Date : 2025/02/17 20:19

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1079. Letter Tile Possibilities|:
//
// You have |n|  |tiles|, where each tile has one letter |tiles[i]| printed on
// it. Return the number of possible non-empty sequences of letters you can make
// using the letters printed on those |tiles|.
//
//

LEETCODE_BEGIN_RESOLVING(1079, LetterTilePossibilities, Solution);

class Solution {
public:
  int numTilePossibilities(string tiles) {
    vector<int> cnt(26, 0);
    for (auto x : tiles) {
      ++cnt[x - 'A'];
    }
    return findSeq(&cnt);
  }

private:
  int findSeq(vector<int> *char_count) {
    int res = 0;
    for (int pos = 0; pos < 26; ++pos) {
      if ((*char_count)[pos] == 0) {
        continue;
      }

      ++res;
      --(*char_count)[pos];
      res += findSeq(char_count);
      ++(*char_count)[pos];
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= tiles.length <= 7|
// * |tiles| consists of uppercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: tiles = "AAB"
// Output: 8
//

LEETCODE_SOLUTION_UNITTEST(1079, LetterTilePossibilities, example_1) {
  auto   solution = MakeSolution();
  string tiles    = "AAB";
  int    expect   = 8;
  int    actual   = solution->numTilePossibilities(tiles);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: tiles = "AAABBC"
// Output: 188
//

LEETCODE_SOLUTION_UNITTEST(1079, LetterTilePossibilities, example_2) {
  auto   solution = MakeSolution();
  string tiles    = "AAABBC";
  int    expect   = 188;
  int    actual   = solution->numTilePossibilities(tiles);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: tiles = "V"
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(1079, LetterTilePossibilities, example_3) {
  auto   solution = MakeSolution();
  string tiles    = "V";
  int    expect   = 1;
  int    actual   = solution->numTilePossibilities(tiles);
  LCD_EXPECT_EQ(expect, actual);
}

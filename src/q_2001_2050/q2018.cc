// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Check if Word Can Be Placed In Crossword
//
// https://leetcode.com/problems/check-if-word-can-be-placed-in-crossword/
//
// Question ID: 2018
// Difficult  : Medium
// Solve Date : 2021/10/12 22:11

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2018. Check if Word Can Be Placed In Crossword|:
//
// You are given an |m x n| matrix |board|, representing the current state of a
// crossword puzzle. The crossword contains lowercase English letters (from
// solved words), |' '| to represent any empty cells, and |'#'| to represent any
// blocked cells. A word can be placed horizontally (left to right or right to
// left) or vertically (top to bottom or bottom to top) in the board if:
//
//  • It does not occupy a cell containing the character |'#'|.
//
//  • The cell each letter is placed in must either be |' '| (empty) or match
//  the letter already on the |board|.
//
//  • There must not be any empty cells |' '| or other lowercase letters
//  directly left or right of the word if the word was placed horizontally.
//
//  • There must not be any empty cells |' '| or other lowercase letters
//  directly above or below the word if the word was placed vertically.
// Given a string |word|, return |true| if |word| can be placed in |board|, or
// |false| otherwise.  
//

LEETCODE_BEGIN_RESOLVING(2018, CheckIfWordCanBePlacedInCrossword, Solution);

class Solution {
private:
  inline vector<vector<char>> transpose(const vector<vector<char>> &in) {
    vector<vector<char>> res(in[0].size(), vector<char>(in.size(), 0));
    for (int i = 0; i < in.size(); ++i)
      for (int j = 0; j < in[0].size(); ++j)
        res[j][i] = in[i][j];
    return res;
  }
  template <typename T>
  inline bool same(T beg, T end, const string &s) {
    auto c = s.begin();
    while (beg != end && c != s.end()) {
      if (*beg != ' ' && *beg != *c)
        return false;
      ++beg;
      ++c;
    }
    return beg == end;
  }
  bool match_horizontally(const vector<vector<char>> &b, string s) {
    int N = b[0].size();
    for (const auto &row : b) {
      for (int i = 0; i < N;) {
        while (i < N && row[i] == '#')
          ++i;
        int beg = i;
        while (i < N && row[i] != '#')
          ++i;
        if (i - beg == s.size()) {
          if (same(row.cbegin() + beg, row.cbegin() + i, s))
            return true;
        }
      }
    }
    return false;
  }

public:
  bool placeWordInCrossword(vector<vector<char>> &board, string word) {
    auto trans = transpose(board);
    return match_horizontally(board, word) ||
           match_horizontally(board, string(word.rbegin(), word.rend())) ||
           match_horizontally(trans, word) ||
           match_horizontally(trans, string(word.rbegin(), word.rend()));
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |m == board.length|
// * |n == board[i].length|
// * |1 <= m * n <= 2 * 10⁵|
// * |board[i][j]| will be |' '|, |'#'|, or a lowercase English letter.
// * |1 <= word.length <= max(m, n)|
// * |word| will contain only lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: board = [["#", " ", "#"], [" ", " ", "#"], ["#", "c", " "]], word =
//  "abc"
// Output: true
//
// The word "abc" can be placed as shown above (top to bottom).

LEETCODE_SOLUTION_UNITTEST(2018, CheckIfWordCanBePlacedInCrossword, example_1) {
  auto                 solution = MakeSolution();
  vector<vector<char>> board    = {
      {'#', ' ', '#'},
      {' ', ' ', '#'},
      {'#', 'c', ' '}
  };
  string word   = "abc";
  bool   expect = true;
  bool   actual = solution->placeWordInCrossword(board, word);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: board = [[" ", "#", "a"], [" ", "#", "c"], [" ", "#", "a"]], word =
//  "ac"
// Output: false
//
// It is impossible to place the word because there will always be a
// space/letter above or below it.

LEETCODE_SOLUTION_UNITTEST(2018, CheckIfWordCanBePlacedInCrossword, example_2) {
  auto                 solution = MakeSolution();
  vector<vector<char>> board    = {
      {' ', '#', 'a'},
      {' ', '#', 'c'},
      {' ', '#', 'a'}
  };
  string word   = "ac";
  bool   expect = false;
  bool   actual = solution->placeWordInCrossword(board, word);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: board = [["#", " ", "#"], [" ", " ", "#"], ["#", " ", "c"]], word =
//  "ca"
// Output: true
//
// The word "ca" can be placed as shown above (right to left).

LEETCODE_SOLUTION_UNITTEST(2018, CheckIfWordCanBePlacedInCrossword, example_3) {
  auto                 solution = MakeSolution();
  vector<vector<char>> board    = {
      {'#', ' ', '#'},
      {' ', ' ', '#'},
      {'#', ' ', 'c'}
  };
  string word   = "ca";
  bool   expect = true;
  bool   actual = solution->placeWordInCrossword(board, word);
  LCD_EXPECT_EQ(expect, actual);
}

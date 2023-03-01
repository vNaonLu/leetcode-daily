// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Word Search
//
// https://leetcode.com/problems/word-search/
//
// Question ID: 79
// Difficult  : Medium
// Solve Date : 2021/09/29 13:56

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |79. Word Search|:
//
// Given an |m x n| grid of characters |board| and a string |word|, return
// |true| if |word| exists in the grid. The word can be constructed from letters
// of sequentially adjacent cells, where adjacent cells are horizontally or
// vertically neighboring. The same letter cell may not be used more than once.
//  
//

LEETCODE_BEGIN_RESOLVING(79, WordSearch, Solution);

class Solution {
private:
  int         m      = 0;
  int         n      = 0;
  vector<int> direct = {1, 0, 0, 1, -1, 0, 0, -1};
  bool        searching(vector<vector<char>> &b, string &s, int i, int j,
                        int index = 0) {
    if (index >= s.size() || i >= m || i < 0 || j >= n || j < 0 ||
        b[i][j] == ' ')
      return false;
    if (index == s.size() - 1)
      return true;
    bool res = false;
    char ch  = b[i][j];
    b[i][j]  = ' ';
    if (i + 1 < m && b[i + 1][j] == s[index + 1])
      res |= searching(b, s, i + 1, j, index + 1);
    if (i - 1 >= 0 && b[i - 1][j] == s[index + 1])
      res |= searching(b, s, i - 1, j, index + 1);
    if (j + 1 < n && b[i][j + 1] == s[index + 1])
      res |= searching(b, s, i, j + 1, index + 1);
    if (j - 1 >= 0 && b[i][j - 1] == s[index + 1])
      res |= searching(b, s, i, j - 1, index + 1);
    b[i][j] = ch;
    return res;
  }

public:
  bool exist(vector<vector<char>> &board, string word) {
    m = board.size();
    n = board[0].size();
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (board[i][j] == word[0] && searching(board, word, i, j))
          return true;
      }
    }
    return false;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |m == board.length|
// * |n = board[i].length|
// * |1 <= m, n <= 6|
// * |1 <= word.length <= 15|
// * |board| and |word| consists of only lowercase and uppercase English
// letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word
//  = "ABCCED"
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(79, WordSearch, example_1) {
  auto                 solution = MakeSolution();
  vector<vector<char>> board    = {
      {'A', 'B', 'C', 'E'},
      {'S', 'F', 'C', 'S'},
      {'A', 'D', 'E', 'E'}
  };
  string word   = "ABCCED";
  bool   expect = true;
  bool   actual = solution->exist(board, word);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word
//  = "SEE"
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(79, WordSearch, example_2) {
  auto                 solution = MakeSolution();
  vector<vector<char>> board    = {
      {'A', 'B', 'C', 'E'},
      {'S', 'F', 'C', 'S'},
      {'A', 'D', 'E', 'E'}
  };
  string word   = "SEE";
  bool   expect = true;
  bool   actual = solution->exist(board, word);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word
//  = "ABCB"
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(79, WordSearch, example_3) {
  auto                 solution = MakeSolution();
  vector<vector<char>> board    = {
      {'A', 'B', 'C', 'E'},
      {'S', 'F', 'C', 'S'},
      {'A', 'D', 'E', 'E'}
  };
  string word   = "ABCB";
  bool   expect = false;
  bool   actual = solution->exist(board, word);
  LCD_EXPECT_EQ(expect, actual);
}

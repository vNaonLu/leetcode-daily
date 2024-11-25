// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Sliding Puzzle
//
// https://leetcode.com/problems/sliding-puzzle/
//
// Question ID: 773
// Difficult  : Hard
// Solve Date : 2024/11/25 21:22

#include <iosfwd>
#include <queue>
#include <string>
#include <unordered_set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |773. Sliding Puzzle|:
//
// On an |2 x 3| board, there are five tiles labeled from |1| to |5|, and an
// empty square represented by |0|. A move consists of choosing |0| and a
// 4-directionally adjacent number and swapping it. The state of the board is
// solved if and only if the board is |[[1,2,3],[4,5,0]]|. Given the puzzle
// board |board|, return the least number of moves required so that the state of
// the board is solved. If it is impossible for the state of the board to be
// solved, return |-1|.
//
//

LEETCODE_BEGIN_RESOLVING(773, SlidingPuzzle, Solution);

class Solution {
public:
  vector<vector<char>> const adj = {
      {1, 3},
      {0, 2, 4},
      {1, 5},
      {0, 4},
      {1, 3, 5},
      {2, 4}
  };
  using info = pair<string, char>;
  int slidingPuzzle(vector<vector<int>> &board) {
    string target = "123450";
    string start(6, '-');
    char   pos0 = -1;
    for (int i = 0; i < 2; i++)
      for (int j = 0; j < 3; j++) {
        int index    = i * 3 + j;
        start[index] = board[i][j] + '0';
        if (board[i][j] == 0)
          pos0 = index;
      }
    if (start == target)
      return 0;

    unordered_set<string> viz;
    viz.reserve(720);
    queue<info> q;
    q.emplace(start, pos0);

    for (int move = 0; !q.empty(); move++) {
      int qz = q.size();
      for (int i = 0; i < qz; i++) {
        auto [t, p0] = q.front();
        q.pop();
        if (t == target)
          return move;
        for (char p : adj[p0]) {
          string s = t;
          swap(s[p0], s[p]);

          if (viz.count(s))
            continue;
          q.emplace(s, p);
          viz.insert(s);
        }
      }
    }
    return -1;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |board.length == 2|
// * |board[i].length == 3|
// * |0 <= board[i][j] <= 5|
// * Each value |board[i][j]| is unique.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: board = [[1,2,3],[4,0,5]]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(773, SlidingPuzzle, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> board    = {
      {1, 2, 3},
      {4, 0, 5}
  };
  int expect = 1;
  int actual = solution->slidingPuzzle(board);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: board = [[1,2,3],[5,4,0]]
// Output: -1
//

LEETCODE_SOLUTION_UNITTEST(773, SlidingPuzzle, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> board    = {
      {1, 2, 3},
      {5, 4, 0}
  };
  int expect = -1;
  int actual = solution->slidingPuzzle(board);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: board = [[4,1,2],[5,0,3]]
// Output: 5
//

LEETCODE_SOLUTION_UNITTEST(773, SlidingPuzzle, example_3) {
  auto                solution = MakeSolution();
  vector<vector<int>> board    = {
      {4, 1, 2},
      {5, 0, 3}
  };
  int expect = 5;
  int actual = solution->slidingPuzzle(board);
  LCD_EXPECT_EQ(expect, actual);
}

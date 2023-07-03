// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Shortest Path to Get All Keys
//
// https://leetcode.com/problems/shortest-path-to-get-all-keys/
//
// Question ID: 864
// Difficult  : Hard
// Solve Date : 2023/06/29 19:08

#include <bitset>
#include <iosfwd>
#include <queue>
#include <set>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |864. Shortest Path to Get All Keys|:
//
// You are given an |m x n| grid |grid| where:
//
//  • |'.'| is an empty cell.
//
//  • |'#'| is a wall.
//
//  • |'@'| is the starting point.
//
//  • Lowercase letters represent keys.
//
//  • Uppercase letters represent locks.
// You start at the starting point and one move consists of walking one space in
// one of the four cardinal directions. You cannot walk outside the grid, or
// walk into a wall. If you walk over a key, you can pick it up and you cannot
// walk over a lock unless you have its corresponding key. For some |1 <= k <=
// 6|, there is exactly one lowercase and one uppercase letter of the first |k|
// letters of the English alphabet in the grid. This means that there is exactly
// one key for each lock, and one lock for each key; and also that the letters
// used to represent the keys and locks were chosen in the same order as the
// English alphabet. Return the lowest number of moves to acquire all keys. If
// it is impossible, return |-1|.
//
//

LEETCODE_BEGIN_RESOLVING(864, ShortestPathToGetAllKeys, Solution);

class Solution {
public:
  struct Block {
    int       i;
    int       j;
    bitset<7> key_mask;

    bool operator<(const Block &rhs) const {
      return key_mask.to_ulong() == rhs.key_mask.to_ulong()
                 ? (i == rhs.i ? j < rhs.j : i < rhs.i)
                 : key_mask.to_ulong() < rhs.key_mask.to_ulong();
    }
  };
  int shortestPathAllKeys(vector<string> &grid) {
    int          m = grid.size();
    int          n = grid[0].size();
    bitset<7>    key_check;
    queue<Block> path_to_go;
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (isKey(grid[i][j])) {
          key_check.set(keyHash(grid[i][j]));
        } else if (grid[i][j] == '@') {
          grid[i][j] = '.';
          path_to_go.emplace(Block{i, j, 0});
        }
      }
    }
    set<Block> memo;
    int        res = 0;
    while (!path_to_go.empty()) {
      auto tmp = std::move(path_to_go);
      while (!tmp.empty()) {
        auto curr = std::move(tmp.front());
        tmp.pop();

        if (curr.key_mask == key_check) {
          return res;
        }

        for (int i = 0; i < kDir.size(); ++i) {
          int dx = curr.i + kDir[i++];
          int dy = curr.j + kDir[i];

          if (dx < 0 || dx >= m || dy < 0 || dy >= n) {
            // outside the boundary.
            continue;
          }

          int nxt = grid[dx][dy];

          if (isWall(nxt)) {
            continue;
          }

          if (isDoor(nxt) && !curr.key_mask.test(keyHash(nxt))) {
            // without key.
            continue;
          }

          auto nxt_block = Block{dx, dy, curr.key_mask};
          if (isKey(nxt)) {
            nxt_block.key_mask.set(keyHash(nxt));
          }
          if (!memo.count(nxt_block)) {
            memo.insert(nxt_block);
            path_to_go.emplace(std::move(nxt_block));
          }
        }
      }
      ++res;
    }

    return -1;
  }

private:
  const vector<int> kDir = {1, 0, 0, 1, -1, 0, 0, -1};
  bool              isDoor(char x) { return x >= 'A' && x <= 'Z'; }
  bool              isKey(char x) { return x >= 'a' && x <= 'z'; }
  bool              isWall(char x) { return x == '#'; }
  int               keyHash(char x) { return x - (isDoor(x) ? 'A' : 'a'); }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |m == grid.length|
// * |n == grid[i].length|
// * |1 <= m, n <= 30|
// * |grid[i][j]| is either an English letter, |'.'|, |'#'|, or |'@'|.
// * The number of keys in the grid is in the range |[1, 6]|.
// * Each key in the grid is unique.
// * Each key in the grid has a matching lock.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: grid = ["@.a..","###.#","b.A.B"]
// Output: 8
//
// Note that the goal is to obtain all the keys not to open all the locks.

LEETCODE_SOLUTION_UNITTEST(864, ShortestPathToGetAllKeys, example_1) {
  auto           solution = MakeSolution();
  vector<string> grid     = {"@.a..", "###.#", "b.A.B"};
  int            expect   = 8;
  int            actual   = solution->shortestPathAllKeys(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: grid = ["@..aA","..B#.","....b"]
// Output: 6
//

LEETCODE_SOLUTION_UNITTEST(864, ShortestPathToGetAllKeys, example_2) {
  auto           solution = MakeSolution();
  vector<string> grid     = {"@..aA", "..B#.", "....b"};
  int            expect   = 6;
  int            actual   = solution->shortestPathAllKeys(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: grid = ["@Aa"]
// Output: -1
//

LEETCODE_SOLUTION_UNITTEST(864, ShortestPathToGetAllKeys, example_3) {
  auto           solution = MakeSolution();
  vector<string> grid     = {"@Aa"};
  int            expect   = -1;
  int            actual   = solution->shortestPathAllKeys(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: ["@...a",".###A","b.BCc"]
// Output: 10
//

LEETCODE_SOLUTION_UNITTEST(864, ShortestPathToGetAllKeys, extra_testcase_1) {
  auto           solution = MakeSolution();
  vector<string> grid     = {"@...a", ".###A", "b.BCc"};
  int            expect   = 10;
  int            actual   = solution->shortestPathAllKeys(grid);
  LCD_EXPECT_EQ(expect, actual);
}

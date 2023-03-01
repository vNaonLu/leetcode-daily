// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Most Stones Removed with Same Row or Column
//
// https://leetcode.com/problems/most-stones-removed-with-same-row-or-column/
//
// Question ID: 947
// Difficult  : Medium
// Solve Date : 2022/09/26 17:46

#include <iosfwd>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |947. Most Stones Removed with Same Row or Column|:
//
// On a 2D plane, we place |n| stones at some integer coordinate points. Each
// coordinate point may have at most one stone. A stone can be removed if it
// shares either the same row or the same column as another stone that has not
// been removed. Given an array |stones| of length |n| where |stones[i] = [xᵢ,
// yᵢ]| represents the location of the |iᵗʰ| stone, return the largest possible
// number of stones that can be removed.
//

LEETCODE_BEGIN_RESOLVING(947, MostStonesRemovedWithSameRowOrColumn, Solution);

class Solution {
private:
  int dfs(unordered_map<int, vector<int>> &rows,
          unordered_map<int, vector<int>> &cols, unordered_set<int> &vrows,
          int row) {
    auto res = (int)0;
    if (vrows.emplace(row).second) {
      res += rows[row].size();
      for (auto c : rows[row]) {
        for (auto r : cols[c]) {
          res += dfs(rows, cols, vrows, r);
        }
      }
    }
    return res;
  }

public:
  int removeStones(vector<vector<int>> &stones) {
    auto cols  = unordered_map<int, vector<int>>();
    auto rows  = unordered_map<int, vector<int>>();
    auto vrows = unordered_set<int>();
    auto res   = (int)0;
    for (auto &s : stones) {
      rows[s[0]].emplace_back(s[1]);
      cols[s[1]].emplace_back(s[0]);
    }
    for (auto &s : rows) {
      res += max(0, dfs(rows, cols, vrows, s.first) - 1);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= stones.length <= 1000|
// * |0 <= xᵢ, yᵢ <= 10⁴|
// * No two stones are at the same coordinate point.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: stones = [[0,0],[0,1],[1,0],[1,2],[2,1],[2,2]]
// Output: 5
//
// One way to remove 5 stones is as follows:
// 1. Remove stone [2,2] because it shares the same row as [2,1].
// 2. Remove stone [2,1] because it shares the same column as [0,1].
// 3. Remove stone [1,2] because it shares the same row as [1,0].
// 4. Remove stone [1,0] because it shares the same column as [0,0].
// 5. Remove stone [0,1] because it shares the same row as [0,0].
// Stone [0,0] cannot be removed since it does not share a row/column with
// another stone still on the plane.

LEETCODE_SOLUTION_UNITTEST(947, MostStonesRemovedWithSameRowOrColumn,
                           example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> stones   = {
      {0, 0},
      {0, 1},
      {1, 0},
      {1, 2},
      {2, 1},
      {2, 2}
  };
  int expect = 5;
  int actual = solution->removeStones(stones);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: stones = [[0,0],[0,2],[1,1],[2,0],[2,2]]
// Output: 3
//
// One way to make 3 moves is as follows:
// 1. Remove stone [2,2] because it shares the same row as [2,0].
// 2. Remove stone [2,0] because it shares the same column as [0,0].
// 3. Remove stone [0,2] because it shares the same row as [0,0].
// Stones [0,0] and [1,1] cannot be removed since they do not share a row/column
// with another stone still on the plane.

LEETCODE_SOLUTION_UNITTEST(947, MostStonesRemovedWithSameRowOrColumn,
                           example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> stones   = {
      {0, 0},
      {0, 2},
      {1, 1},
      {2, 0},
      {2, 2}
  };
  int expect = 3;
  int actual = solution->removeStones(stones);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: stones = [[0,0]]
// Output: 0
//
// [0,0] is the only stone on the plane, so you cannot remove it.

LEETCODE_SOLUTION_UNITTEST(947, MostStonesRemovedWithSameRowOrColumn,
                           example_3) {
  auto                solution = MakeSolution();
  vector<vector<int>> stones   = {
      {0, 0}
  };
  int expect = 0;
  int actual = solution->removeStones(stones);
  LCD_EXPECT_EQ(expect, actual);
}

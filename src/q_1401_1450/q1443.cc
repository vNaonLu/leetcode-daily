// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimum Time to Collect All Apples in a Tree
//
// https://leetcode.com/problems/minimum-time-to-collect-all-apples-in-a-tree/
//
// Question ID: 1443
// Difficult  : Medium
// Solve Date : 2023/01/11 18:59

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1443. Minimum Time to Collect All Apples in a Tree|:
//
// Given an undirected tree consisting of |n| vertices numbered from |0| to
// |n-1|, which has some apples in their vertices. You spend 1 second to walk
// over one edge of the tree. Return the minimum time in seconds you have to
// spend to collect all apples in the tree, starting at vertex 0 and coming back
// to this vertex. The edges of the undirected tree are given in the array
// |edges|, where |edges[i] = [aᵢ, bᵢ]| means that exists an edge connecting the
// vertices |aᵢ| and |bᵢ|. Additionally, there is a boolean array |hasApple|,
// where |hasApple[i] = true| means that vertex |i| has an apple; otherwise, it
// does not have any apple.
//

LEETCODE_BEGIN_RESOLVING(1443, MinimumTimeToCollectAllApplesInATree, Solution);

class Solution {
private:
  int dfs(int node, int parent, vector<vector<int>> &tree,
          vector<bool> &has_apple) {
    int time = 0;
    for (auto x : tree[node]) {
      if (x != parent) {
        time += dfs(x, node, tree, has_apple);
      }
    }
    return (time > 0 || has_apple[node] ? time + 2 : 0);
  }

public:
  int minTime(int n, vector<vector<int>> &edges, vector<bool> &hasApple) {
    vector<vector<int>> tree(n + 1);
    for (auto &x : edges) {
      tree[x[1]].emplace_back(x[0]);
      tree[x[0]].emplace_back(x[1]);
    }
    return max(0, dfs(0, -1, tree, hasApple) - 2);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n <= 10⁵|
// * |edges.length == n - 1|
// * |edges[i].length == 2|
// * |0 <= aᵢ < bᵢ <= n - 1|
// * |hasApple.length == n|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 7, edges = [[0,1],[0,2],[1,4],[1,5],[2,3],[2,6]], hasApple =
//  [false,false,true,false,true,true,false]
// Output: 8
//
// The figure above represents the given tree where red vertices have an apple.
// One optimal path to collect all apples is shown by the green arrows.

LEETCODE_SOLUTION_UNITTEST(1443, MinimumTimeToCollectAllApplesInATree,
                           example_1) {
  auto                solution = MakeSolution();
  int                 n        = 7;
  vector<vector<int>> edges    = {
      {0, 1},
      {0, 2},
      {1, 4},
      {1, 5},
      {2, 3},
      {2, 6}
  };
  vector<bool> hasApple = {false, false, true, false, true, true, false};
  int          expect   = 8;
  int          actual   = solution->minTime(n, edges, hasApple);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 7, edges = [[0,1],[0,2],[1,4],[1,5],[2,3],[2,6]], hasApple =
//  [false,false,true,false,false,true,false]
// Output: 6
//
// The figure above represents the given tree where red vertices have an apple.
// One optimal path to collect all apples is shown by the green arrows.

LEETCODE_SOLUTION_UNITTEST(1443, MinimumTimeToCollectAllApplesInATree,
                           example_2) {
  auto                solution = MakeSolution();
  int                 n        = 7;
  vector<vector<int>> edges    = {
      {0, 1},
      {0, 2},
      {1, 4},
      {1, 5},
      {2, 3},
      {2, 6}
  };
  vector<bool> hasApple = {false, false, true, false, false, true, false};
  int          expect   = 6;
  int          actual   = solution->minTime(n, edges, hasApple);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: n = 7, edges = [[0,1],[0,2],[1,4],[1,5],[2,3],[2,6]], hasApple =
//  [false,false,false,false,false,false,false]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(1443, MinimumTimeToCollectAllApplesInATree,
                           example_3) {
  auto                solution = MakeSolution();
  int                 n        = 7;
  vector<vector<int>> edges    = {
      {0, 1},
      {0, 2},
      {1, 4},
      {1, 5},
      {2, 3},
      {2, 6}
  };
  vector<bool> hasApple = {false, false, false, false, false, false, false};
  int          expect   = 0;
  int          actual   = solution->minTime(n, edges, hasApple);
  LCD_EXPECT_EQ(expect, actual);
}

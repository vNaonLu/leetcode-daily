// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Find Champion II
//
// https://leetcode.com/problems/find-champion-ii/
//
// Question ID: 2924
// Difficult  : Medium
// Solve Date : 2024/11/26 19:33

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2924. Find Champion II|:
//
// There are |n| teams numbered from |0| to |n - 1| in a tournament; each team
// is also a node in a DAG. You are given the integer |n| and a 0-indexed 2D
// integer array |edges| of length |m| representing the DAG, where |edges[i] =
// [uᵢ, vᵢ]| indicates that there is a directed edge from team |uᵢ| to team |vᵢ|
// in the graph. A directed edge from |a| to |b| in the graph means that team
// |a| is stronger than team |b| and team |b| is weaker than team |a|. Team |a|
// will be the champion of the tournament if there is no team |b| that is
// stronger than team |a|. Return the team that will be the champion of the
// tournament if there is a unique champion, otherwise, return |-1|. Notes
//
//  • A cycle is a series of nodes |a₁, a₂, ..., aₙ, aₙ₊₁| such that node |a₁|
//  is the same node as node |aₙ₊₁|, the nodes |a₁, a₂, ..., aₙ| are distinct,
//  and there is a directed edge from the node |aᵢ| to node |aᵢ₊₁| for every |i|
//  in the range |[1, n]|.
//
//  • A DAG is a directed graph that does not have any cycle.
//
//

LEETCODE_BEGIN_RESOLVING(2924, FindChampionII, Solution);

class Solution {
public:
  int findChampion(int n, vector<vector<int>> &edges) {
    vector<int> deg(n);
    for (auto &v : edges) {
      ++deg[v[1]];
    }
    vector<int> deg0;
    for (int i = 0; i < n; ++i) {
      if (deg[i] == 0) {
        deg0.emplace_back(i);
      }
    }

    if (deg0.size() != 1) {
      return -1;
    }

    return deg0[0];
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n <= 100|
// * |m == edges.length|
// * |0 <= m <= n * (n - 1) / 2|
// * |edges[i].length == 2|
// * |0 <= edge[i][j] <= n - 1|
// * |edges[i][0] != edges[i][1]|
// * The input is generated such that if team |a| is stronger than team |b|,
// team |b| is not stronger than team |a|.
// * The input is generated such that if team |a| is stronger than team |b| and
// team |b| is stronger than team |c|, then team |a| is stronger than team |c|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 3, edges = [[0,1],[1,2]]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(2924, FindChampionII, example_1) {
  auto                solution = MakeSolution();
  int                 n        = 3;
  vector<vector<int>> edges    = {
      {0, 1},
      {1, 2}
  };
  int expect = 0;
  int actual = solution->findChampion(n, edges);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 4, edges = [[0,2],[1,3],[1,2]]
// Output: -1
//

LEETCODE_SOLUTION_UNITTEST(2924, FindChampionII, example_2) {
  auto                solution = MakeSolution();
  int                 n        = 4;
  vector<vector<int>> edges    = {
      {0, 2},
      {1, 3},
      {1, 2}
  };
  int expect = -1;
  int actual = solution->findChampion(n, edges);
  LCD_EXPECT_EQ(expect, actual);
}

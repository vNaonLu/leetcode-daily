// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Shortest Path with Alternating Colors
//
// https://leetcode.com/problems/shortest-path-with-alternating-colors/
//
// Question ID: 1129
// Difficult  : Medium
// Solve Date : 2022/03/19 14:31

#include <iosfwd>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1129. Shortest Path with Alternating Colors|:
//
// You are given an integer |n|, the number of nodes in a directed graph where
// the nodes are labeled from |0| to |n - 1|. Each edge is red or blue in this
// graph, and there could be self-edges and parallel edges. You are given two
// arrays |redEdges| and |blueEdges| where:
//
//  • |redEdges[i] = [aᵢ, bᵢ]| indicates that there is a directed red edge from
//  node |aᵢ| to node |bᵢ| in the graph, and
//
//  • |blueEdges[j] = [uⱼ, vⱼ]| indicates that there is a directed blue edge
//  from node |uⱼ| to node |vⱼ| in the graph.
// Return an array |answer| of length |n|, where each |answer[x]| is the length
// of the shortest path from node |0| to node |x| such that the edge colors
// alternate along the path, or |-1| if such a path does not exist.  
//

LEETCODE_BEGIN_RESOLVING(1129, ShortestPathWithAlternatingColors, Solution);

class Solution {
private:
  enum path { none = 0, red = 1, blue = 2 };

public:
  vector<int> shortestAlternatingPaths(int n, vector<vector<int>> &redEdges,
                                       vector<vector<int>> &blueEdges) {
    vector<vector<int>> reds(n, vector<int>(n)), blues(n, vector<int>(n));

    for (auto &v : redEdges) {
      reds[v[0]][v[1]] = 1;
    }
    for (auto &v : blueEdges) {
      blues[v[0]][v[1]] = 1;
    }

    vector<int> res(n, -1);

    queue<pair<int, path>> q;
    q.emplace(0, path::none);
    int length = 0;

    while (!q.empty()) {
      auto temp = move(q);

      while (!temp.empty()) {
        auto [x, type] = temp.front();
        temp.pop();
        if (res[x] == -1) {
          res[x] = length;
        }

        if (type != path::blue) {
          for (int i = 0; i < blues[x].size(); ++i) {
            if (blues[x][i]) {
              blues[x][i] = 0;
              q.emplace(i, path::blue);
            }
          }
        }

        if (type != path::red) {
          for (int i = 0; i < reds[x].size(); ++i) {
            if (reds[x][i]) {
              reds[x][i] = 0;
              q.emplace(i, path::red);
            }
          }
        }
      }

      ++length;
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n <= 100|
// * |0 <= redEdges.length, blueEdges.length <= 400|
// * |redEdges[i].length == blueEdges[j].length == 2|
// * |0 <= aᵢ, bᵢ, uⱼ, vⱼ < n|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 3, redEdges = [[0,1],[1,2]], blueEdges = []
// Output: [0,1,-1]
//

LEETCODE_SOLUTION_UNITTEST(1129, ShortestPathWithAlternatingColors, example_1) {
  auto                solution = MakeSolution();
  int                 n        = 3;
  vector<vector<int>> redEdges = {
      {0, 1},
      {1, 2}
  };
  vector<vector<int>> blueEdges = {};
  vector<int>         expect    = {0, 1, -1};
  vector<int>         actual =
      solution->shortestAlternatingPaths(n, redEdges, blueEdges);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 3, redEdges = [[0,1]], blueEdges = [[2,1]]
// Output: [0,1,-1]
//

LEETCODE_SOLUTION_UNITTEST(1129, ShortestPathWithAlternatingColors, example_2) {
  auto                solution = MakeSolution();
  int                 n        = 3;
  vector<vector<int>> redEdges = {
      {0, 1}
  };
  vector<vector<int>> blueEdges = {
      {2, 1}
  };
  vector<int> expect = {0, 1, -1};
  vector<int> actual =
      solution->shortestAlternatingPaths(n, redEdges, blueEdges);
  LCD_EXPECT_EQ(expect, actual);
}

// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Largest Color Value in a Directed Graph
//
// https://leetcode.com/problems/largest-color-value-in-a-directed-graph/
//
// Question ID: 1857
// Difficult  : Hard
// Solve Date : 2023/04/09 15:18

#include <iosfwd>
#include <string>
#include <unordered_set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1857. Largest Color Value in a Directed Graph|:
//
// There is a directed graph of |n| colored nodes and |m| edges. The nodes are
// numbered from |0| to |n - 1|.
//
// You are given a string |colors| where |colors[i]| is a lowercase English
// letter representing the color of the |iᵗʰ| node in this graph (0-indexed).
// You are also given a 2D array |edges| where |edges[j] = [aⱼ, bⱼ]| indicates
// that there is a directed edge from node |aⱼ| to node |bⱼ|.
//
// A valid path in the graph is a sequence of nodes |x₁ -> x₂ -> x₃ -> ... ->
// xₖ| such that there is a directed edge from |xᵢ| to |xᵢ₊₁| for every |1 <= i
// < k|. The color value of the path is the number of nodes that are colored the
// most frequently occurring color along that path.
//
// Return the largest color value of any valid path in the given graph, or |-1|
// if the graph contains a cycle.
//
//
//

LEETCODE_BEGIN_RESOLVING(1857, LargestColorValueInADirectedGraph, Solution);

class Solution {
public:
  int largestPathValue(string colors, vector<vector<int>> &edges) {
    int                 n = colors.size();
    vector<int>         indegrees(n, 0);
    vector<vector<int>> graph(n, vector<int>());
    for (auto &v : edges) {
      int u0 = v[0];
      int u1 = v[1];
      graph[u0].emplace_back(u1);
      ++indegrees[u1];
    }
    unordered_set<int> zero_indegree;
    for (int i = 0; i < n; ++i) {
      if (indegrees[i] == 0) {
        zero_indegree.emplace(i);
      }
    }
    vector<vector<int>> counts(n, vector<int>(26, 0));
    for (int i = 0; i < n; ++i) {
      ++counts[i][colors[i] - 'a'];
    }
    int mx      = 0;
    int visited = 0;
    while (!zero_indegree.empty()) {
      int u = *zero_indegree.begin();
      zero_indegree.erase(u);
      ++visited;
      for (int v : graph[u]) {
        for (int i = 0; i < 26; ++i) {
          counts[v][i] =
              max(counts[v][i], counts[u][i] + (colors[v] - 'a' == i ? 1 : 0));
        }
        --indegrees[v];
        if (indegrees[v] == 0) {
          zero_indegree.emplace(v);
        }
      }
      mx = max(mx, *max_element(counts[u].begin(), counts[u].end()));
    }
    return visited == n ? mx : -1;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == colors.length|
// * |m == edges.length|
// * |1 <= n <= 10⁵|
// * |0 <= m <= 10⁵|
// * |colors| consists of lowercase English letters.
// * |0 <= aⱼ, bⱼ < n|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: colors = "abaca", edges = [[0,1],[0,2],[2,3],[3,4]]
// Output: 3
//
// The path 0 -> 2 -> 3 -> 4 contains 3 nodes that are colored |"a" (red in the
// above image)|.

LEETCODE_SOLUTION_UNITTEST(1857, LargestColorValueInADirectedGraph, example_1) {
  auto                solution = MakeSolution();
  string              colors   = "abaca";
  vector<vector<int>> edges    = {
      {0, 1},
      {0, 2},
      {2, 3},
      {3, 4}
  };
  int expect = 3;
  int actual = solution->largestPathValue(colors, edges);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: colors = "a", edges = [[0,0]]
// Output: -1
//
// There is a cycle from 0 to 0.

LEETCODE_SOLUTION_UNITTEST(1857, LargestColorValueInADirectedGraph, example_2) {
  auto                solution = MakeSolution();
  string              colors   = "a";
  vector<vector<int>> edges    = {
      {0, 0}
  };
  int expect = -1;
  int actual = solution->largestPathValue(colors, edges);
  LCD_EXPECT_EQ(expect, actual);
}

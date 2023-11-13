// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Design Graph With Shortest Path Calculator
//
// https://leetcode.com/problems/design-graph-with-shortest-path-calculator/
//
// Question ID: 2642
// Difficult  : Hard
// Solve Date : 2023/11/13 19:11

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2642. Design Graph With Shortest Path Calculator|:
//
// There is a directed weighted graph that consists of |n| nodes numbered from
// |0| to |n - 1|. The edges of the graph are initially represented by the given
// array |edges| where |edges[i] = [fromᵢ, toᵢ, edgeCostᵢ]| meaning that there
// is an edge from |fromᵢ| to |toᵢ| with the cost |edgeCostᵢ|. Implement the
// |Graph| class:
//
//  • |Graph(int n, int[][] edges)| initializes the object with |n| nodes and
//  the given edges.
//
//  • |addEdge(int[] edge)| adds an edge to the list of edges where |edge =
//  [from, to, edgeCost]|. It is guaranteed that there is no edge between the
//  two nodes before adding this one.
//
//  • |int shortestPath(int node1, int node2)| returns the minimum cost of a
//  path from |node1| to |node2|. If no path exists, return |-1|. The cost of a
//  path is the sum of the costs of the edges in the path.
//
//

LEETCODE_BEGIN_RESOLVING(2642, DesignGraphWithShortestPathCalculator, Graph);

class Graph {
public:
  Graph(int n, vector<vector<int>> &edges)
      : n_{n}, dist_(n, vector<int>(n, kMax)) {
    for (int i = 0; i < n; ++i) {
      dist_[i][i] = 0;
    }

    for (auto &v : edges) {
      dist_[v[0]][v[1]] = v[2];
    }

    for (int k = 0; k < n; ++k) {
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
          dist_[i][j] = min(dist_[i][j], dist_[i][k] + dist_[k][j]);
        }
      }
    }
  }

  void addEdge(vector<int> edge) {
    if (dist_[edge[0]][edge[1]] <= edge[2]) {
      return;
    }

    dist_[edge[0]][edge[1]] = edge[2];
    for (int i = 0; i < n_; ++i) {
      for (int j = 0; j < n_; ++j) {
        dist_[i][j] =
            min(dist_[i][j], dist_[i][edge[0]] + dist_[edge[1]][j] + edge[2]);
      }
    }
  }

  int shortestPath(int node1, int node2) {
    if (dist_[node1][node2] == kMax) {
      return -1;
    }

    return dist_[node1][node2];
  }

private:
  int                  n_;
  vector<vector<int>>  dist_;
  static constexpr int kMax = 5 * 1e8;
};

LEETCODE_END_RESOLVING(Graph);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n <= 100|
// * |0 <= edges.length <= n * (n - 1)|
// * |edges[i].length == edge.length == 3|
// * |0 <= fromᵢ, toᵢ, from, to, node1, node2 <= n - 1|
// * |1 <= edgeCostᵢ, edgeCost <= 10⁶|
// * There are no repeated edges and no self-loops in the graph at any point.
// * At most |100| calls will be made for |addEdge|.
// * At most |100| calls will be made for |shortestPath|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: ["Graph", "shortestPath", "shortestPath", "addEdge", "shortestPath"]
// [[4, [[0, 2, 5], [0, 1, 2], [1, 2, 1], [3, 0, 3]]], [3, 2], [0, 3], [[1, 3,
// 4]], [0, 3]] Output: [null, 6, -1, null, 6]
//
// Graph g = new Graph(4, [[0, 2, 5], [0, 1, 2], [1, 2, 1], [3, 0, 3]]);
// g.shortestPath(3, 2); // return 6. The shortest path from 3 to 2 in the first
// diagram above is 3 -> 0 -> 1 -> 2 with a total cost of 3 + 2 + 1 = 6.
// g.shortestPath(0, 3); // return -1. There is no path from 0 to 3.
// g.addEdge([1, 3, 4]); // We add an edge from node 1 to node 3, and we get the
// second diagram above. g.shortestPath(0, 3); // return 6. The shortest path
// from 0 to 3 now is 0 -> 1 -> 3 with a total cost of 2 + 4 = 6.

LEETCODE_SOLUTION_UNITTEST(2642, DesignGraphWithShortestPathCalculator,
                           example_1) {
  int                 s0_n     = 4;
  vector<vector<int>> s0_edges = {
      {0, 2, 5},
      {0, 1, 2},
      {1, 2, 1},
      {3, 0, 3}
  };
  auto graph     = MakeGraph(s0_n, s0_edges);
  int  s1_node1  = 3;
  int  s1_node2  = 2;
  int  s1_expect = 6;
  int  s1_actual = graph->shortestPath(s1_node1, s1_node2);
  LCD_EXPECT_EQ(s1_expect, s1_actual);
  int s2_node1  = 0;
  int s2_node2  = 3;
  int s2_expect = -1;
  int s2_actual = graph->shortestPath(s2_node1, s2_node2);
  LCD_EXPECT_EQ(s2_expect, s2_actual);
  vector<int> s3_edge = {1, 3, 4};
  graph->addEdge(s3_edge);
  int s4_node1  = 0;
  int s4_node2  = 3;
  int s4_expect = 6;
  int s4_actual = graph->shortestPath(s4_node1, s4_node2);
  LCD_EXPECT_EQ(s4_expect, s4_actual);
}

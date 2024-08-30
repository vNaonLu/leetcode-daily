// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Modify Graph Edge Weights
//
// https://leetcode.com/problems/modify-graph-edge-weights/
//
// Question ID: 2699
// Difficult  : Hard
// Solve Date : 2024/08/30 22:23

#include <iosfwd>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2699. Modify Graph Edge Weights|:
//
// You are given an undirected weighted connected graph containing |n| nodes
// labeled from |0| to |n - 1|, and an integer array |edges| where |edges[i] =
// [aᵢ, bᵢ, wᵢ]| indicates that there is an edge between nodes |aᵢ| and |bᵢ|
// with weight |wᵢ|. Some edges have a weight of |-1| ( |wᵢ = -1|), while others
// have a positive weight ( |wᵢ > 0|). Your task is to modify all edges with a
// weight of |-1| by assigning them positive integer values in the range |[1, 2
// * 10⁹]| so that the shortest distance between the nodes |source| and
// |destination| becomes equal to an integer |target|. If there are multiple
// modifications that make the shortest distance between |source| and
// |destination| equal to |target|, any of them will be considered correct.
// Return an array containing all edges (even unmodified ones) in any order if
// it is possible to make the shortest distance from |source| to |destination|
// equal to |target|, or an empty array if it's impossible. Note: You are not
// allowed to modify the weights of edges with initial positive weights.
//
//

LEETCODE_BEGIN_RESOLVING(2699, ModifyGraphEdgeWeights, Solution);

class Solution {
public:
  vector<vector<int>> modifiedGraphEdges(int n, vector<vector<int>> &edges,
                                         int source, int destination,
                                         int target) {
    vector<vector<pair<int, int>>> adjacency_list(n);
    for (int i = 0; i < edges.size(); i++) {
      int nodeA = edges[i][0], nodeB = edges[i][1];
      adjacency_list[nodeA].emplace_back(nodeB, i);
      adjacency_list[nodeB].emplace_back(nodeA, i);
    }

    vector<vector<int>> distances(n,
                                  vector<int>(2, numeric_limits<int>::max()));
    distances[source][0] = distances[source][1] = 0;

    runDijkstra(adjacency_list, edges, distances, source, 0, 0);
    int difference = target - distances[destination][0];
    if (difference < 0)
      return {};
    runDijkstra(adjacency_list, edges, distances, source, difference, 1);
    if (distances[destination][1] < target)
      return {};

    for (auto &edge : edges) {
      if (edge[2] == -1)
        edge[2] = 1;
    }
    return edges;
  }

private:
  void runDijkstra(const vector<vector<pair<int, int>>> &adjacency_list,
                   vector<vector<int>> &edges, vector<vector<int>> &distances,
                   int source, int difference, int run) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({0, source});
    distances[source][run] = 0;

    while (!pq.empty()) {
      auto [curr_dist, curr_node] = pq.top();
      pq.pop();

      if (curr_dist > distances[curr_node][run])
        continue;

      for (auto &neighbor : adjacency_list[curr_node]) {
        int next_node = neighbor.first, edge_idx = neighbor.second;
        int weight = edges[edge_idx][2];

        if (weight == -1)
          weight = 1;

        if (run == 1 && edges[edge_idx][2] == -1) {
          int newWeight =
              difference + distances[next_node][0] - distances[curr_node][1];
          if (newWeight > weight) {
            edges[edge_idx][2] = weight = newWeight;
          }
        }

        if (distances[next_node][run] > distances[curr_node][run] + weight) {
          distances[next_node][run] = distances[curr_node][run] + weight;
          pq.push({distances[next_node][run], next_node});
        }
      }
    }
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n <= 100|
// * |1 <= edges.length <= n * (n - 1) / 2|
// * |edges[i].length == 3|
// * |0 <= aᵢ, b_{i }< n|
// * |wᵢ = -1 |or |1 <= w_{i }<= 107|
// * |a_{i }!= bᵢ|
// * |0 <= source, destination < n|
// * |source != destination|
// * |1 <= target <= 10⁹|
// * The graph is connected, and there are no self-loops or repeated edges
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 5, edges = [[4,1,-1],[2,0,-1],[0,3,-1],[4,3,-1]], source = 0,
//  destination = 1, target = 5
// Output: [[4,1,1],[2,0,1],[0,3,3],[4,3,1]]
//

LEETCODE_SOLUTION_UNITTEST(2699, ModifyGraphEdgeWeights, example_1) {
  auto                solution = MakeSolution();
  int                 n        = 5;
  vector<vector<int>> edges    = {
      {4, 1, -1},
      {2, 0, -1},
      {0, 3, -1},
      {4, 3, -1}
  };
  int                 source      = 0;
  int                 destination = 1;
  int                 target      = 5;
  vector<vector<int>> expect      = {
      {4, 1, 1},
      {2, 0, 3},
      {0, 3, 3},
      {4, 3, 1}
  };
  vector<vector<int>> actual =
      solution->modifiedGraphEdges(n, edges, source, destination, target);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 3, edges = [[0,1,-1],[0,2,5]], source = 0, destination = 2,
//  target = 6
// Output: []
//

LEETCODE_SOLUTION_UNITTEST(2699, ModifyGraphEdgeWeights, example_2) {
  auto                solution = MakeSolution();
  int                 n        = 3;
  vector<vector<int>> edges    = {
      {0, 1, -1},
      {0, 2,  5}
  };
  int                 source      = 0;
  int                 destination = 2;
  int                 target      = 6;
  vector<vector<int>> expect      = {};
  vector<vector<int>> actual =
      solution->modifiedGraphEdges(n, edges, source, destination, target);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #3]
//  Input: n = 4, edges = [[1,0,4],[1,2,3],[2,3,5],[0,3,-1]], source = 0,
//  destination = 2, target = 6
// Output: [[1,0,4],[1,2,3],[2,3,5],[0,3,1]]
//

LEETCODE_SOLUTION_UNITTEST(2699, ModifyGraphEdgeWeights, example_3) {
  auto                solution = MakeSolution();
  int                 n        = 4;
  vector<vector<int>> edges    = {
      {1, 0,  4},
      {1, 2,  3},
      {2, 3,  5},
      {0, 3, -1}
  };
  int                 source      = 0;
  int                 destination = 2;
  int                 target      = 6;
  vector<vector<int>> expect      = {
      {1, 0, 4},
      {1, 2, 3},
      {2, 3, 5},
      {0, 3, 1}
  };
  vector<vector<int>> actual =
      solution->modifiedGraphEdges(n, edges, source, destination, target);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Find Minimum Diameter After Merging Two Trees
//
// https://leetcode.com/problems/find-minimum-diameter-after-merging-two-trees/
//
// Question ID: 3203
// Difficult  : Hard
// Solve Date : 2024/12/24 21:59

#include <cmath>
#include <iosfwd>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3203. Find Minimum Diameter After Merging Two Trees|:
//
// There exist two undirected trees with |n| and |m| nodes, numbered from |0| to
// |n - 1| and from |0| to |m - 1|, respectively. You are given two 2D integer
// arrays |edges1| and |edges2| of lengths |n - 1| and |m - 1|, respectively,
// where |edges1[i] = [aᵢ, bᵢ]| indicates that there is an edge between nodes
// |aᵢ| and |bᵢ| in the first tree and |edges2[i] = [uᵢ, vᵢ]| indicates that
// there is an edge between nodes |uᵢ| and |vᵢ| in the second tree. You must
// connect one node from the first tree with another node from the second tree
// with an edge. Return the minimum possible diameter of the resulting tree. The
// diameter of a tree is the length of the longest path between any two nodes in
// the tree.
//
//

LEETCODE_BEGIN_RESOLVING(3203, FindMinimumDiameterAfterMergingTwoTrees,
                         Solution);

class Solution {
public:
  int minimumDiameterAfterMerge(vector<vector<int>> &edges1,
                                vector<vector<int>> &edges2) {
    // Calculate the number of nodes for each tree
    int n = edges1.size() + 1;
    int m = edges2.size() + 1;

    // Build adjacency lists for both trees
    vector<vector<int>> adjList1 = buildAdjList(n, edges1);
    vector<vector<int>> adjList2 = buildAdjList(m, edges2);

    // Calculate the diameters of both trees
    int diameter1 = findDiameter(n, adjList1);
    int diameter2 = findDiameter(m, adjList2);

    // Calculate the longest path that spans across both trees
    int combinedDiameter = ceil(diameter1 / 2.0) + ceil(diameter2 / 2.0) + 1;

    // Return the maximum of the three possibilities
    return max({diameter1, diameter2, combinedDiameter});
  }

private:
  vector<vector<int>> buildAdjList(int size, vector<vector<int>> &edges) {
    vector<vector<int>> adjList(size);
    for (auto edge : edges) {
      adjList[edge[0]].push_back(edge[1]);
      adjList[edge[1]].push_back(edge[0]);
    }
    return adjList;
  }

  // Function to find the diameter of a tree using two BFS calls
  int findDiameter(int n, vector<vector<int>> &adjList) {
    // First BFS to find the farthest node from any arbitrary node (e.g., 0)
    auto [farthestNode, x] = findFarthestNode(n, adjList, 0);

    // Second BFS from the farthest node to determine the diameter
    auto [_, diameter] = findFarthestNode(n, adjList, farthestNode);
    return diameter;
  }

  // BFS helper function to find the farthest node and its distance from the
  // source
  pair<int, int> findFarthestNode(int n, vector<vector<int>> &adjList,
                                  int sourceNode) {
    queue<int>   nodesQueue;
    vector<bool> visited(n, false);
    // Push source node into the queue
    nodesQueue.push(sourceNode);
    visited[sourceNode] = true;

    int maximumDistance = 0, farthestNode = sourceNode;

    // Explore neighbors
    while (!nodesQueue.empty()) {
      int size = nodesQueue.size();
      for (int i = 0; i < size; ++i) {
        int currentNode = nodesQueue.front();
        nodesQueue.pop();
        // Update farthest node
        // The farthest node is the last one that was popped out of the
        // queue.
        farthestNode = currentNode;

        for (int neighbor : adjList[currentNode]) {
          // Explore neighbors
          if (!visited[neighbor]) {
            visited[neighbor] = true;
            nodesQueue.push(neighbor);
          }
        }
      }
      if (!nodesQueue.empty())
        maximumDistance++;
    }
    return {farthestNode, maximumDistance};
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n, m <= 10⁵|
// * |edges1.length == n - 1|
// * |edges2.length == m - 1|
// * |edges1[i].length == edges2[i].length == 2|
// * |edges1[i] = [aᵢ, bᵢ]|
// * |0 <= aᵢ, bᵢ < n|
// * |edges2[i] = [uᵢ, vᵢ]|
// * |0 <= uᵢ, vᵢ < m|
// * The input is generated such that |edges1| and |edges2| represent valid
// trees.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: edges1 = [[0,1],[0,2],[0,3]], edges2 = [[0,1]]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(3203, FindMinimumDiameterAfterMergingTwoTrees,
                           example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> edges1   = {
      {0, 1},
      {0, 2},
      {0, 3}
  };
  vector<vector<int>> edges2 = {
      {0, 1}
  };
  int expect = 3;
  int actual = solution->minimumDiameterAfterMerge(edges1, edges2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: edges1 = [[0,1],[0,2],[0,3],[2,4],[2,5],[3,6],[2,7]], edges2 =
//  [[0,1],[0,2],[0,3],[2,4],[2,5],[3,6],[2,7]]
// Output: 5
//

LEETCODE_SOLUTION_UNITTEST(3203, FindMinimumDiameterAfterMergingTwoTrees,
                           example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> edges1   = {
      {0, 1},
      {0, 2},
      {0, 3},
      {2, 4},
      {2, 5},
      {3, 6},
      {2, 7}
  };
  vector<vector<int>> edges2 = {
      {0, 1},
      {0, 2},
      {0, 3},
      {2, 4},
      {2, 5},
      {3, 6},
      {2, 7}
  };
  int expect = 5;
  int actual = solution->minimumDiameterAfterMerge(edges1, edges2);
  LCD_EXPECT_EQ(expect, actual);
}

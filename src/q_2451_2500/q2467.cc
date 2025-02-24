// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Most Profitable Path in a Tree
//
// https://leetcode.com/problems/most-profitable-path-in-a-tree/
//
// Question ID: 2467
// Difficult  : Medium
// Solve Date : 2025/02/24 20:16

#include <iosfwd>
#include <queue>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2467. Most Profitable Path in a Tree|:
//
// There is an undirected tree with |n| nodes labeled from |0| to |n - 1|,
// rooted at node |0|. You are given a 2D integer array |edges| of length |n -
// 1| where |edges[i] = [aᵢ, bᵢ]| indicates that there is an edge between nodes
// |aᵢ| and |bᵢ| in the tree. At every node |i|, there is a gate. You are also
// given an array of even integers |amount|, where |amount[i]| represents:
//
//  • the price needed to open the gate at node |i|, if |amount[i]| is negative,
//  or,
//
//  • the cash reward obtained on opening the gate at node |i|, otherwise.
// The game goes on as follows:
//
//  • Initially, Alice is at node |0| and Bob is at node |bob|.
//
//  • At every second, Alice and Bob each move to an adjacent node. Alice moves
//  towards some leaf node, while Bob moves towards node |0|.
//
//  • For every node along their path, Alice and Bob either spend money to open
//  the gate at that node, or accept the reward. Note that:
//
//
//    • If the gate is already open, no price will be required, nor will there
//    be any cash reward.
//
//    • If Alice and Bob reach the node simultaneously, they share the
//    price/reward for opening the gate there. In other words, if the price to
//    open the gate is |c|, then both Alice and Bob pay |c / 2| each. Similarly,
//    if the reward at the gate is |c|, both of them receive |c / 2| each.
//
//
//
//  • If Alice reaches a leaf node, she stops moving. Similarly, if Bob reaches
//  node |0|, he stops moving. Note that these events are independent of each
//  other.
// Return the maximum net income Alice can have if she travels towards the
// optimal leaf node.
//
//

LEETCODE_BEGIN_RESOLVING(2467, MostProfitablePathInATree, Solution);

class Solution {
public:
  int mostProfitablePath(vector<vector<int>> &edges, int bob,
                         vector<int> &amount) {
    int n = amount.size(), maxIncome = numeric_limits<int>::min();
    tree.resize(n);
    visited.assign(n, false);
    queue<vector<int>> nodeQueue;
    nodeQueue.push({0, 0, 0});

    for (vector<int> edge : edges) {
      tree[edge[0]].push_back(edge[1]);
      tree[edge[1]].push_back(edge[0]);
    }

    findBobPath(bob, 0);

    visited.assign(n, false);
    while (!nodeQueue.empty()) {
      int sourceNode = nodeQueue.front()[0], time = nodeQueue.front()[1],
          income = nodeQueue.front()[2];

      if (bobPath.find(sourceNode) == bobPath.end() ||
          time < bobPath[sourceNode]) {
        income += amount[sourceNode];
      }

      else if (time == bobPath[sourceNode]) {
        income += (amount[sourceNode] / 2);
      }

      if (tree[sourceNode].size() == 1 && sourceNode != 0) {
        maxIncome = max(maxIncome, income);
      }
      for (int adjacentNode : tree[sourceNode]) {
        if (!visited[adjacentNode]) {
          nodeQueue.push({adjacentNode, time + 1, income});
        }
      }

      visited[sourceNode] = true;
      nodeQueue.pop();
    }
    return maxIncome;
  }

private:
  unordered_map<int, int> bobPath;
  vector<bool>            visited;
  vector<vector<int>>     tree;

  bool findBobPath(int sourceNode, int time) {
    bobPath[sourceNode] = time;
    visited[sourceNode] = true;

    if (sourceNode == 0) {
      return true;
    }

    for (auto adjacentNode : tree[sourceNode]) {
      if (!visited[adjacentNode]) {
        if (findBobPath(adjacentNode, time + 1)) {
          return true;
        }
      }
    }
    bobPath.erase(sourceNode);
    return false;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= n <= 10⁵|
// * |edges.length == n - 1|
// * |edges[i].length == 2|
// * |0 <= aᵢ, bᵢ < n|
// * |aᵢ != bᵢ|
// * |edges| represents a valid tree.
// * |1 <= bob < n|
// * |amount.length == n|
// * |amount[i]| is an even integer in the range |[-10⁴, 10⁴]|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: edges = [[0,1],[1,2],[1,3],[3,4]], bob = 3, amount = [-2,4,2,-4,6]
// Output: 6
//

LEETCODE_SOLUTION_UNITTEST(2467, MostProfitablePathInATree, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> edges    = {
      {0, 1},
      {1, 2},
      {1, 3},
      {3, 4}
  };
  int         bob    = 3;
  vector<int> amount = {-2, 4, 2, -4, 6};
  int         expect = 6;
  int         actual = solution->mostProfitablePath(edges, bob, amount);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: edges = [[0,1]], bob = 1, amount = [-7280,2350]
// Output: -7280
//

LEETCODE_SOLUTION_UNITTEST(2467, MostProfitablePathInATree, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> edges    = {
      {0, 1}
  };
  int         bob    = 1;
  vector<int> amount = {-7280, 2350};
  int         expect = -7280;
  int         actual = solution->mostProfitablePath(edges, bob, amount);
  LCD_EXPECT_EQ(expect, actual);
}

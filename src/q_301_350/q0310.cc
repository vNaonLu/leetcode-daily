// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimum Height Trees
//
// https://leetcode.com/problems/minimum-height-trees/
//
// Question ID: 310
// Difficult  : Medium
// Solve Date : 2021/12/16 18:21

#include <iosfwd>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |310. Minimum Height Trees|:
//
// A tree is an undirected graph in which any two vertices are connected
// by exactly one path. In other words, any connected graph without simple
// cycles is a tree. Given a tree of |n| nodes labelled from |0| to |n - 1|, and
// an array of  |n - 1|  |edges| where |edges[i] = [aᵢ, bᵢ]| indicates that
// there is an undirected edge between the two nodes  |aᵢ| and  |bᵢ| in the
// tree, you can choose any node of the tree as the root. When you select a node
// |x| as the root, the result tree has height |h|. Among all possible rooted
// trees, those with minimum height (i.e. |min(h)|)  are called minimum height
// trees (MHTs). Return a list of all MHTs' root labels. You can return the
// answer in any order. The height of a rooted tree is the number of edges on
// the longest downward path between the root and a leaf.  
//

LEETCODE_BEGIN_RESOLVING(310, MinimumHeightTrees, Solution);

class Solution {
public:
  vector<int> findMinHeightTrees(int n, vector<vector<int>> &edges) {
    if (n == 1)
      return vector<int>{0};
    vector<vector<int>> graph(n);
    vector<int>         degree(n, 0);
    vector<int>         res;
    queue<int>          q;
    for (const auto &e : edges) {
      graph[e[0]].push_back(e[1]);
      graph[e[1]].push_back(e[0]);
      degree[e[0]]++;
      degree[e[1]]++;
    }
    for (int i = 0; i < n; i++)
      if (degree[i] == 1)
        q.push(i);
    while (!q.empty()) {
      int n = q.size();
      res.clear();
      while (n--) {
        int node = q.front();
        q.pop();
        res.push_back(node);
        for (const auto &x : graph[node])
          if (--degree[x] == 1)
            q.push(x);
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n <= 2 * 10⁴|
// * |edges.length == n - 1|
// * |0 <= aᵢ, bᵢ < n|
// * |aᵢ != bᵢ|
// * All the pairs |(aᵢ, bᵢ)| are distinct.
// * The given input is guaranteed to be a tree and there will be no repeated
// edges.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 4, edges = [[1,0],[1,2],[1,3]]
// Output: [1]
//
// As shown, the height of the tree is 1 when the root is the node with label 1
// which is the only MHT.

LEETCODE_SOLUTION_UNITTEST(310, MinimumHeightTrees, example_1) {
  auto                solution = MakeSolution();
  int                 n        = 4;
  vector<vector<int>> edges    = {
      {1, 0},
      {1, 2},
      {1, 3}
  };
  vector<int> expect = {1};
  vector<int> actual = solution->findMinHeightTrees(n, edges);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 6, edges = [[3,0],[3,1],[3,2],[3,4],[5,4]]
// Output: [3,4]
//

LEETCODE_SOLUTION_UNITTEST(310, MinimumHeightTrees, example_2) {
  auto                solution = MakeSolution();
  int                 n        = 6;
  vector<vector<int>> edges    = {
      {3, 0},
      {3, 1},
      {3, 2},
      {3, 4},
      {5, 4}
  };
  vector<int> expect = {3, 4};
  vector<int> actual = solution->findMinHeightTrees(n, edges);
  EXPECT_ANYORDER_EQ(expect, actual);
}

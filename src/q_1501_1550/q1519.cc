// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Number of Nodes in the Sub-Tree With the Same Label
//
// https://leetcode.com/problems/number-of-nodes-in-the-sub-tree-with-the-same-label/
//
// Question ID: 1519
// Difficult  : Medium
// Solve Date : 2023/01/12 16:04

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1519. Number of Nodes in the Sub-Tree With the Same Label|:
//
// You are given a tree (i.e. a connected, undirected graph that has no cycles)
// consisting of |n| nodes numbered from |0| to |n - 1| and exactly |n - 1|
// |edges|. The root of the tree is the node |0|, and each node of the tree has
// a label which is a lower-case character given in the string |labels| (i.e.
// The node with the number |i| has the label |labels[i]|). The |edges| array is
// given on the form |edges[i] = [aᵢ, bᵢ]|, which means there is an edge between
// nodes |aᵢ| and |bᵢ| in the tree. Return an array of size |n| where |ans[i]|
// is the number of nodes in the subtree of the |iᵗʰ| node which have the same
// label as node |i|. A subtree of a tree |T| is the tree consisting of a node
// in |T| and all of its descendant nodes.
//

LEETCODE_BEGIN_RESOLVING(1519, NumberOfNodesInTheSubTreeWithTheSameLabel,
                         Solution);

class Solution {
private:
  vector<int> dfs(vector<vector<int>> &path, string &s, vector<int> &vis,
                  int idx, vector<int> &res) {
    vector<int> tmp(26);
    vis[idx] = 1;
    for (auto x : path[idx]) {
      if (!vis[x]) {
        auto children = dfs(path, s, vis, x, res);
        ++tmp[s[x] - 'a'];
        for (int i = 0; i < 26; ++i) {
          tmp[i] += children[i];
        }
      }
    }
    res[idx] += tmp[s[idx] - 'a'] + 1;
    return tmp;
  }

public:
  vector<int> countSubTrees(int n, vector<vector<int>> &edges, string labels) {
    vector<int>         res(n);
    vector<int>         vis(n);
    vector<vector<int>> path(n);
    for (auto &v : edges) {
      path[v[0]].emplace_back(v[1]);
      path[v[1]].emplace_back(v[0]);
    }
    dfs(path, labels, vis, 0, res);
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n <= 10⁵|
// * |edges.length == n - 1|
// * |edges[i].length == 2|
// * |0 <= aᵢ, bᵢ < n|
// * |aᵢ != bᵢ|
// * |labels.length == n|
// * |labels| is consisting of only of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 7, edges = [[0,1],[0,2],[1,4],[1,5],[2,3],[2,6]], labels =
//  "abaedcd"
// Output: [2,1,1,1,1,1,1]
//
// Node 0 has label 'a' and its sub-tree has node 2 with label 'a' as well, thus
// the answer is 2. Notice that any node is part of its sub-tree. Node 1 has a
// label 'b'. The sub-tree of node 1 contains nodes 1,4 and 5, as nodes 4 and 5
// have different labels than node 1, the answer is just 1 (the node itself).

LEETCODE_SOLUTION_UNITTEST(1519, NumberOfNodesInTheSubTreeWithTheSameLabel,
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
  string      labels = "abaedcd";
  vector<int> expect = {2, 1, 1, 1, 1, 1, 1};
  vector<int> actual = solution->countSubTrees(n, edges, labels);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 4, edges = [[0,1],[1,2],[0,3]], labels = "bbbb"
// Output: [4,2,1,1]
//
// The sub-tree of node 2 contains only node 2, so the answer is 1.
// The sub-tree of node 3 contains only node 3, so the answer is 1.
// The sub-tree of node 1 contains nodes 1 and 2, both have label 'b', thus the
// answer is 2. The sub-tree of node 0 contains nodes 0, 1, 2 and 3, all with
// label 'b', thus the answer is 4.

LEETCODE_SOLUTION_UNITTEST(1519, NumberOfNodesInTheSubTreeWithTheSameLabel,
                           example_2) {
  auto                solution = MakeSolution();
  int                 n        = 4;
  vector<vector<int>> edges    = {
      {0, 1},
      {1, 2},
      {0, 3}
  };
  string      labels = "bbbb";
  vector<int> expect = {4, 2, 1, 1};
  vector<int> actual = solution->countSubTrees(n, edges, labels);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: n = 5, edges = [[0,1],[0,2],[1,3],[0,4]], labels = "aabab"
// Output: [3,2,1,1,1]
//

LEETCODE_SOLUTION_UNITTEST(1519, NumberOfNodesInTheSubTreeWithTheSameLabel,
                           example_3) {
  auto                solution = MakeSolution();
  int                 n        = 5;
  vector<vector<int>> edges    = {
      {0, 1},
      {0, 2},
      {1, 3},
      {0, 4}
  };
  string      labels = "aabab";
  vector<int> expect = {3, 2, 1, 1, 1};
  vector<int> actual = solution->countSubTrees(n, edges, labels);
  LCD_EXPECT_EQ(expect, actual);
}

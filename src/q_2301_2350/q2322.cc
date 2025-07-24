// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Minimum Score After Removals on a Tree
//
// https://leetcode.com/problems/minimum-score-after-removals-on-a-tree/
//
// Question ID: 2322
// Difficult  : Hard
// Solve Date : 2025/07/24 21:08

#include <algorithm>
#include <iosfwd>
#include <unordered_set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2322. Minimum Score After Removals on a Tree|:
//
// There is an undirected connected tree with |n| nodes labeled from |0| to |n -
// 1| and |n - 1| edges. You are given a 0-indexed integer array |nums| of
// length |n| where |nums[i]| represents the value of the |iᵗʰ| node. You are
// also given a 2D integer array |edges| of length |n - 1| where |edges[i] =
// [aᵢ, bᵢ]| indicates that there is an edge between nodes |aᵢ| and |bᵢ| in the
// tree. Remove two distinct edges of the tree to form three connected
// components. For a pair of removed edges, the following steps are defined:
//
//  1. Get the XOR of all the values of the nodes for each of the three
//  components respectively.
//
//  2. The difference between the largest XOR value and the smallest XOR value
//  is the score of the pair.
//
//  • For example, say the three components have the node values: |[4,5,7]|,
//  |[1,9]|, and |[3,3,3]|. The three XOR values are |4 ^ 5 ^ 7 = 6|, |1 ^ 9 =
//  8|, and |3 ^ 3 ^ 3 = 3|. The largest XOR value is |8| and the smallest XOR
//  value is |3|. The score is then |8 - 3 = 5|.
// Return the minimum score of any possible pair of edge removals on the given
// tree.
//
//

LEETCODE_BEGIN_RESOLVING(2322, MinimumScoreAfterRemovalsOnATree, Solution);

class Solution {
public:
  std::vector<int>                     subtree_xor;
  std::vector<std::unordered_set<int>> descendants;
  std::vector<std::vector<int>>        graph;

  void dfs(int node, int parent, const std::vector<int> &nums) {
    subtree_xor[node] = nums[node];
    descendants[node].insert(node);

    for (int neighbor : graph[node]) {
      if (neighbor != parent) {
        dfs(neighbor, node, nums);
        subtree_xor[node] ^= subtree_xor[neighbor];
        descendants[node].insert(descendants[neighbor].begin(),
                                 descendants[neighbor].end());
      }
    }
  }

  int minimumScore(std::vector<int>              &nums,
                   std::vector<std::vector<int>> &edges) {
    int n = nums.size();
    graph.assign(n, std::vector<int>());
    subtree_xor.assign(n, 0);
    descendants.assign(n, std::unordered_set<int>());

    for (const auto &edge : edges) {
      graph[edge[0]].push_back(edge[1]);
      graph[edge[1]].push_back(edge[0]);
    }

    dfs(0, -1, nums);

    int total_xor = subtree_xor[0];
    int min_score = numeric_limits<int>::max();

    for (int i = 1; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        int xor_i = subtree_xor[i];
        int xor_j = subtree_xor[j];
        int val1, val2, val3;

        if (descendants[i].count(j)) {
          val1 = xor_j;
          val2 = xor_i ^ xor_j;
          val3 = total_xor ^ xor_i;
        } else if (descendants[j].count(i)) {
          val1 = xor_i;
          val2 = xor_j ^ xor_i;
          val3 = total_xor ^ xor_j;
        } else {
          val1 = xor_i;
          val2 = xor_j;
          val3 = total_xor ^ xor_i ^ xor_j;
        }

        int score = std::max({val1, val2, val3}) - std::min({val1, val2, val3});
        min_score = std::min(min_score, score);
      }
    }

    return min_score;
  }
};
LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |n == nums.length|
// * |3 <= n <= 1000|
// * |1 <= nums[i] <= 10⁸|
// * |edges.length == n - 1|
// * |edges[i].length == 2|
// * |0 <= aᵢ, bᵢ < n|
// * |aᵢ != bᵢ|
// * |edges| represents a valid tree.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,5,5,4,11], edges = [[0,1],[1,2],[1,3],[3,4]]
// Output: 9
//

LEETCODE_SOLUTION_UNITTEST(2322, MinimumScoreAfterRemovalsOnATree, example_1) {
  auto                solution = MakeSolution();
  vector<int>         nums     = {1, 5, 5, 4, 11};
  vector<vector<int>> edges    = {
      {0, 1},
      {1, 2},
      {1, 3},
      {3, 4}
  };
  int expect = 9;
  int actual = solution->minimumScore(nums, edges);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [5,5,2,4,4,2], edges = [[0,1],[1,2],[5,2],[4,3],[1,3]]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(2322, MinimumScoreAfterRemovalsOnATree, example_2) {
  auto                solution = MakeSolution();
  vector<int>         nums     = {5, 5, 2, 4, 4, 2};
  vector<vector<int>> edges    = {
      {0, 1},
      {1, 2},
      {5, 2},
      {4, 3},
      {1, 3}
  };
  int expect = 0;
  int actual = solution->minimumScore(nums, edges);
  LCD_EXPECT_EQ(expect, actual);
}

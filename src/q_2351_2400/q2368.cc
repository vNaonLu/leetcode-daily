#include <gtest/gtest.h>
#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>

using namespace std;

/**
 * This file is generated by leetcode_add.py
 *
 * 2368.
 *       Reachable Nodes With Restrictions
 *
 * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
 *
 *   There is an undirected tree with ‘n’ nodes labeled from ‘0’ to ‘n - 1’
 *   and ‘n - 1’
 *   You are given a 2D integer array ‘edges’ of length ‘n - 1’ where
 *   ‘edges[i] = [aᵢ, bᵢ]’ indicates that there is an edge between nodes
 *   ‘aᵢ’ and ‘bᵢ’ in the tree. You are also given an integer array
 *   ‘restricted’ which represents “restricted”
 *   Return “the “maximum” number of nodes you can reach from node ” ‘0’ “
 *   without visiting a restricted node.”
 *   Note that node ‘0’ will “not” be a restricted node.
 *
 * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
 *
 *   • ‘2 ≤ n ≤ 10⁵’
 *   • ‘edges.length = n - 1’
 *   • ‘edges[i].length = 2’
 *   • ‘0 ≤ aᵢ, bᵢ < n’
 *   • ‘aᵢ ≠ bᵢ’
 *   • ‘edges’ represents a valid tree.
 *   • ‘1 ≤ restricted.length < n’
 *   • ‘1 ≤ restricted[i] < n’
 *   • All the values of ‘restricted’ are “unique” .
 *
 */

struct q2368 : public ::testing::Test {
  // Leetcode answer here
  class Solution {
  public:
    int reachableNodes(int n, vector<vector<int>> &edges,
                       vector<int> &restricted) {
      auto pth = vector<vector<int>>(n);
      auto vst = vector<bool>(n, false);
      auto rst = unordered_set<int>(restricted.begin(), restricted.end());
      auto cur = queue<int>();

      for (auto &e : edges) {
        pth[e[0]].emplace_back(e[1]);
        pth[e[1]].emplace_back(e[0]);
      }

      if (!rst.count(0)) {
        vst[0] = true;
        cur.emplace(0);
      }

      auto res = (int)0;

      while (!cur.empty()) {
        auto c = cur.front();
        cur.pop();

        ++res;
        for (auto x : pth[c]) {
          if (!vst[x] && !rst.count(x)) {
            vst[x] = true;
            cur.emplace(x);
          }
        }
      }

      return res;
    }
  };

  class Solution *solution;
};

TEST_F(q2368, sample_input01) {
  solution                  = new Solution();
  int                 n     = 7;
  vector<vector<int>> edges = {
      {0, 1},
      {1, 2},
      {3, 1},
      {4, 0},
      {0, 5},
      {5, 6}
  };
  vector<int> restricted = {4, 5};
  int         exp        = 4;
  int         act        = solution->reachableNodes(n, edges, restricted);
  EXPECT_EQ(act, exp);
  delete solution;
}

TEST_F(q2368, sample_input02) {
  solution                  = new Solution();
  int                 n     = 7;
  vector<vector<int>> edges = {
      {0, 1},
      {0, 2},
      {0, 5},
      {0, 4},
      {3, 2},
      {6, 5}
  };
  vector<int> restricted = {4, 2, 1};
  int         exp        = 3;
  int         act        = solution->reachableNodes(n, edges, restricted);
  EXPECT_EQ(act, exp);
  delete solution;
}
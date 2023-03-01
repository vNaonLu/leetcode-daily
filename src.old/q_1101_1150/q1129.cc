#include <gtest/gtest.h>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

/**
 * This file is generated by leetcode_add.py
 *
 * 1129.
 *       Shortest Path with Alternating Colors
 *
 * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
 *
 *   You are given an integer ‘n’ , the number of nodes in a directed graph
 *   where the nodes are labeled from ‘0’ to ‘n - 1’ . Each edge is red or
 *   blue in this graph, and there could be self-edges and parallel
 *   You are given two arrays ‘redEdges’ and ‘blueEdges’
 *       -  ‘redEdges[i] = [aᵢ, bᵢ]’ indicates that there is a directed red
 *   edge from node ‘aᵢ’ to node ‘bᵢ’ in the graph,
 *       -  ‘blueEdges[j] = [uⱼ, vⱼ]’ indicates that there is a directed
 *   blue edge from node ‘uⱼ’ to node ‘vⱼ’ in the
 *   Return an array ‘answer’ of length ‘n’ , where each ‘answer[x]’ is the
 *   length of the shortest path from node ‘0’ to node ‘x’ such that the
 *   edge colors alternate along the path, or ‘-1’ if such a path does not
 *   exist.
 *
 * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
 *
 *   • ‘1 ≤ n ≤ 100’
 *   • ‘0 ≤ redEdges.length,blueEdges.length ≤ 400’
 *   • ‘redEdges[i].length = blueEdges[j].length = 2’
 *   • ‘0 ≤ aᵢ, bᵢ, uⱼ, vⱼ < n’
 *
 */

struct q1129 : public ::testing::Test {
  // Leetcode answer here
  class Solution {
   private:
    enum path {
      none = 0,
      red = 1,
      blue = 2
    };

   public:
    vector<int> shortestAlternatingPaths(int n, vector<vector<int>> &redEdges, vector<vector<int>> &blueEdges) {
      vector<vector<int>> reds(n, vector<int>(n)),
          blues(n, vector<int>(n));

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

  class Solution *solution;
};

TEST_F(q1129, sample_input01) {
  solution = new Solution();
  int n = 3;
  vector<vector<int>> redEdges = {{0, 1}, {1, 2}};
  vector<vector<int>> blueEdges = {};
  vector<int> exp = {0, 1, -1};
  vector<int> act = solution->shortestAlternatingPaths(n, redEdges, blueEdges);
  EXPECT_EQ(act, exp);
  delete solution;
}

TEST_F(q1129, sample_input02) {
  solution = new Solution();
  int n = 3;
  vector<vector<int>> redEdges = {{0, 1}};
  vector<vector<int>> blueEdges = {{2, 1}};
  vector<int> exp = {0, 1, -1};
  vector<int> act = solution->shortestAlternatingPaths(n, redEdges, blueEdges);
  EXPECT_EQ(act, exp);
  delete solution;
}
#include <gtest/gtest.h>
#include <iostream>
#include <leetcode/anyorder.hpp>
#include <unordered_set>
#include <vector>

using namespace std;

/**
 * This file is generated by leetcode_add.py v1.0
 *
 * 1557.
 *       Minimum Number of Vertices to Reach All Nodes
 *
 * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
 *
 *   Given a “directed acyclic graph” ,with ‘n’ vertices numbered from ‘0’
 *   to ‘n-1’ ,and an array ‘edges’ where ‘edges[i] = [fromᵢ, toᵢ]’
 *   represents a directed edge from node ‘fromᵢ’ to node ‘toᵢ’
 *   Find “the smallest set of vertices from which all nodes in the graph
 *   are reachable” . It's guaranteed that a unique solution
 *   Notice that you can return the vertices in any
 *   
 *
 * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
 *
 *   • ‘2 ≤ n ≤ 10^5’
 *   • ‘1 ≤ edges.length ≤ min(10^5, n × (n - 1) / 2)’
 *   • ‘edges[i].length = 2’
 *   • ‘0 ≤ from⎽(i,)toᵢ < n’
 *   • All pairs ‘(fromᵢ, toᵢ)’ are distinct.
 *
 */

struct q1557 : public ::testing::Test {
  // Leetcode answer here
  class Solution {
   public:
    vector<int> findSmallestSetOfVertices(int n, vector<vector<int>>& edges) {
      unordered_set<int> reachable;
      for (const auto& e : edges)
        reachable.insert(e[1]);
      vector<int> res;
      for (int i = 0; i < n; ++i)
        if (!reachable.count(i))
          res.push_back(i);
      return res;
    }
  };

  class Solution *solution;
};

TEST_F(q1557, sample_input01) {
  solution = new Solution();
  int n = 6;
  vector<vector<int>> edges = {{0, 1}, {0, 2}, {2, 5}, {3, 4}, {4, 2}};
  vector<int> exp = {0, 3};
  // Try EXPECT_EQ_ANY_ORDER_RECURSIVE
  // if the element is also matched in any order.
  EXPECT_EQ_ANY_ORDER(solution->findSmallestSetOfVertices(n, edges), exp);
  delete solution;
}

TEST_F(q1557, sample_input02) {
  solution = new Solution();
  int n = 5;
  vector<vector<int>> edges = {{0, 1}, {2, 1}, {3, 1}, {1, 4}, {2, 4}};
  vector<int> exp = {0, 2, 3};
  // Try EXPECT_EQ_ANY_ORDER_RECURSIVE
  // if the element is also matched in any order.
  EXPECT_EQ_ANY_ORDER(solution->findSmallestSetOfVertices(n, edges), exp);
  delete solution;
}
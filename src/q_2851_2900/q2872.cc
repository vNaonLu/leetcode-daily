// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Maximum Number of K-Divisible Components
//
// https://leetcode.com/problems/maximum-number-of-k-divisible-components/
//
// Question ID: 2872
// Difficult  : Hard
// Solve Date : 2024/12/21 16:09

#include <iosfwd>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2872. Maximum Number of K-Divisible Components|:
//
// There is an undirected tree with |n| nodes labeled from |0| to |n - 1|. You
// are given the integer |n| and a 2D integer array |edges| of length |n - 1|,
// where |edges[i] = [aᵢ, bᵢ]| indicates that there is an edge between nodes
// |aᵢ| and |bᵢ| in the tree. You are also given a 0-indexed integer array
// |values| of length |n|, where |values[i]| is the value associated with the
// |iᵗʰ| node, and an integer |k|. A valid split of the tree is obtained by
// removing any set of edges, possibly empty, from the tree such that the
// resulting components all have values that are divisible by |k|, where the
// value of a connected component is the sum of the values of its nodes. Return
// the maximum number of components in any valid split.
//
//

LEETCODE_BEGIN_RESOLVING(2872, MaximumNumberOfKDivisibleComponents, Solution);

class Solution {
public:
  int maxKDivisibleComponents(int n, vector<vector<int>> &edges,
                              vector<int> &values, int k) {
    unordered_map<int, vector<int>> adj;
    int                             res = 0;
    for (auto &v : edges) {
      adj[v[1]].emplace_back(v[0]);
      adj[v[0]].emplace_back(v[1]);
    }
    dfs(0, -1, k, values, &adj, &res);
    return res;
  }

private:
  int64_t dfs(int node, int parent, int k, vector<int> const &val,
              unordered_map<int, vector<int>> *adj, int *res) {
    int64_t s = val[node];
    for (auto &child : (*adj)[node]) {
      if (child != parent) {
        s += dfs(child, node, k, val, adj, res);
      }
    }

    if (s % k == 0) {
      ++(*res);
      s = 0;
    }
    return s;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n <= 3 * 10⁴|
// * |edges.length == n - 1|
// * |edges[i].length == 2|
// * |0 <= aᵢ, bᵢ < n|
// * |values.length == n|
// * |0 <= values[i] <= 10⁹|
// * |1 <= k <= 10⁹|
// * Sum of |values| is divisible by |k|.
// * The input is generated such that |edges| represents a valid tree.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 5, edges = [[0,2],[1,2],[1,3],[2,4]], values = [1,8,1,4,4], k = 6
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(2872, MaximumNumberOfKDivisibleComponents,
                           example_1) {
  auto                solution = MakeSolution();
  int                 n        = 5;
  vector<vector<int>> edges    = {
      {0, 2},
      {1, 2},
      {1, 3},
      {2, 4}
  };
  vector<int> values = {1, 8, 1, 4, 4};
  int         k      = 6;
  int         expect = 2;
  int         actual = solution->maxKDivisibleComponents(n, edges, values, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 7, edges = [[0,1],[0,2],[1,3],[1,4],[2,5],[2,6]], values =
//  [3,0,6,1,5,2,1], k = 3
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(2872, MaximumNumberOfKDivisibleComponents,
                           example_2) {
  auto                solution = MakeSolution();
  int                 n        = 7;
  vector<vector<int>> edges    = {
      {0, 1},
      {0, 2},
      {1, 3},
      {1, 4},
      {2, 5},
      {2, 6}
  };
  vector<int> values = {3, 0, 6, 1, 5, 2, 1};
  int         k      = 3;
  int         expect = 3;
  int         actual = solution->maxKDivisibleComponents(n, edges, values, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: 7
// [[0,1],[0,2],[1,3],[1,4],[2,5],[2,6]]
// [1000000000,1000000000,1000000000,1000000000,1000000000,1000000000,1000000000]
// 7
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(2872, MaximumNumberOfKDivisibleComponents,
                           extra_testcase_1) {
  auto                solution = MakeSolution();
  int                 n        = 7;
  vector<vector<int>> edges    = {
      {0, 1},
      {0, 2},
      {1, 3},
      {1, 4},
      {2, 5},
      {2, 6}
  };
  vector<int> values = {1000000000, 1000000000, 1000000000, 1000000000,
                        1000000000, 1000000000, 1000000000};
  int         k      = 7;
  int         expect = 1;
  int         actual = solution->maxKDivisibleComponents(n, edges, values, k);
  LCD_EXPECT_EQ(expect, actual);
}

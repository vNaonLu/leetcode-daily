// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Redundant Connection
//
// https://leetcode.com/problems/redundant-connection/
//
// Question ID: 684
// Difficult  : Medium
// Solve Date : 2022/02/17 23:02

#include <iosfwd>
#include <map>
#include <queue>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |684. Redundant Connection|:
//
// In this problem, a tree is an undirected graph that is connected and has no
// cycles. You are given a graph that started as a tree with |n| nodes labeled
// from |1| to |n|, with one additional edge added. The added edge has two
// different vertices chosen from |1| to |n|, and was not an edge that already
// existed. The graph is represented as an array |edges| of length |n| where
// |edges[i] = [aᵢ, bᵢ]| indicates that there is an edge between nodes |aᵢ| and
// |bᵢ| in the graph. Return an edge that can be removed so that the resulting
// graph is a tree of |n| nodes. If there are multiple answers, return the
// answer that occurs last in the input.  
//

LEETCODE_BEGIN_RESOLVING(684, RedundantConnection, Solution);

class Solution {
private:
  unordered_map<int, vector<int>> graph;
  inline bool                     is_connected(int x, int y) noexcept {
    int          n = graph.size();
    vector<bool> visit(n + 1, false);
    queue<int>   q;
    q.push(x);
    visit[0] = true;
    visit[x] = true;

    while (q.empty() == false) {
      int curr = q.front();
      q.pop();
      for (const auto &to : graph[curr]) {
        if ((curr == x && to == y) || (curr == y && to == x))
          continue;
        if (visit[to] == false) {
          visit[to] = true;
          q.push(to);
        }
      }
    }

    for (const auto b : visit) {
      if (b == false) {
        return false;
      }
    }
    return true;
  }

public:
  vector<int> findRedundantConnection(vector<vector<int>> &edges) {
    int n = 0;
    for (const auto &e : edges) {
      n = max({e[0], e[1], n});
      graph[e[0]].emplace_back(e[1]);
      graph[e[1]].emplace_back(e[0]);
    }
    for (auto it = edges.rbegin(); it != edges.rend(); ++it) {
      if (is_connected((*it)[0], (*it)[1])) {
        return *it;
      }
    }
    return {-1, -1};
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == edges.length|
// * |3 <= n <= 1000|
// * |edges[i].length == 2|
// * |1 <= aᵢ < bᵢ <= edges.length|
// * |aᵢ != bᵢ|
// * There are no repeated edges.
// * The given graph is connected.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: edges = [[1,2],[1,3],[2,3]]
// Output: [2,3]
//

LEETCODE_SOLUTION_UNITTEST(684, RedundantConnection, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> edges    = {
      {1, 2},
      {1, 3},
      {2, 3}
  };
  vector<int> expect = {2, 3};
  vector<int> actual = solution->findRedundantConnection(edges);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: edges = [[1,2],[2,3],[3,4],[1,4],[1,5]]
// Output: [1,4]
//

LEETCODE_SOLUTION_UNITTEST(684, RedundantConnection, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> edges    = {
      {1, 2},
      {2, 3},
      {3, 4},
      {1, 4},
      {1, 5}
  };
  vector<int> expect = {1, 4};
  vector<int> actual = solution->findRedundantConnection(edges);
  LCD_EXPECT_EQ(expect, actual);
}

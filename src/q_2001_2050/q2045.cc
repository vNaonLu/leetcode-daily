// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Second Minimum Time to Reach Destination
//
// https://leetcode.com/problems/second-minimum-time-to-reach-destination/
//
// Question ID: 2045
// Difficult  : Hard
// Solve Date : 2024/07/28 14:33

#include <iosfwd>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2045. Second Minimum Time to Reach Destination|:
//
// A city is represented as a bi-directional connected graph with |n| vertices
// where each vertex is labeled from |1| to |n| (inclusive). The edges in the
// graph are represented as a 2D integer array |edges|, where each |edges[i] =
// [uᵢ, vᵢ]| denotes a bi-directional edge between vertex |uᵢ| and vertex |vᵢ|.
// Every vertex pair is connected by at most one edge, and no vertex has an edge
// to itself. The time taken to traverse any edge is |time| minutes. Each vertex
// has a traffic signal which changes its color from green to red and vice versa
// every |change| minutes. All signals change at the same time. You can enter a
// vertex at any time, but can leave a vertex only when the signal is green. You
// cannot wait at a vertex if the signal is green. The second minimum value is
// defined as the smallest value strictly larger than the minimum value.
//
//  • For example the second minimum value of |[2, 3, 4]| is |3|, and the second
//  minimum value of |[2, 2, 4]| is |4|.
// Given |n|, |edges|, |time|, and |change|, return the second minimum time it
// will take to go from vertex |1| to vertex |n|. Notes:
//
//  • You can go through any vertex any number of times, including |1| and |n|.
//
//  • You can assume that when the journey starts, all signals have just turned
//  green.
//
//

LEETCODE_BEGIN_RESOLVING(2045, SecondMinimumTimeToReachDestination, Solution);

class Solution {
public:
  int secondMinimum(int n, vector<vector<int>> &edges, int time, int change) {
    vector<vector<int>> adj(n + 1);
    for (auto &e : edges) {
      int v = e[0];
      int w = e[1];
      adj[v].push_back(w);
      adj[w].push_back(v);
    }

    vector<int>           dist(n + 1, numeric_limits<int>::max());
    vector<int>           dist2(n + 1, numeric_limits<int>::max());
    queue<pair<int, int>> q;
    q.emplace(1, 0);
    dist[1] = 0;
    while (!q.empty()) {
      auto [x, d] = q.front();
      q.pop();
      for (int y : adj[x]) {
        int n = d + 1;
        if (n < dist[y]) {
          dist2[y] = dist[y];
          dist[y]  = n;
          q.emplace(y, n);
        } else if (n > dist[y] && n < dist2[y]) {
          dist2[y] = n;
          q.emplace(y, n);
        }
      }
    }
    int steps = dist2[n];
    if (steps == numeric_limits<int>::max()) {
      return -1;
    }
    return wtime(steps, time, change);
  }

private:
  int wtime(int step, int time, int change) {
    int res = 0;
    for (int i = 0; i < step; ++i) {
      int gr = res / change;
      if (gr & 1) {
        res = (gr + 1) * change;
      }
      res += time;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= n <= 10⁴|
// * |n - 1 <= edges.length <= min(2 * 10⁴, n * (n - 1) / 2)|
// * |edges[i].length == 2|
// * |1 <= uᵢ, vᵢ <= n|
// * |uᵢ != vᵢ|
// * There are no duplicate edges.
// * Each vertex can be reached directly or indirectly from every other vertex.
// * |1 <= time, change <= 10³|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 5, edges = [[1,2],[1,3],[1,4],[3,4],[4,5]], time = 3, change = 5
// Output: 13
//

LEETCODE_SOLUTION_UNITTEST(2045, SecondMinimumTimeToReachDestination,
                           example_1) {
  auto                solution = MakeSolution();
  int                 n        = 5;
  vector<vector<int>> edges    = {
      {1, 2},
      {1, 3},
      {1, 4},
      {3, 4},
      {4, 5}
  };
  int time   = 3;
  int change = 5;
  int expect = 13;
  int actual = solution->secondMinimum(n, edges, time, change);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 2, edges = [[1,2]], time = 3, change = 2
// Output: 11
//

LEETCODE_SOLUTION_UNITTEST(2045, SecondMinimumTimeToReachDestination,
                           example_2) {
  auto                solution = MakeSolution();
  int                 n        = 2;
  vector<vector<int>> edges    = {
      {1, 2}
  };
  int time   = 3;
  int change = 2;
  int expect = 11;
  int actual = solution->secondMinimum(n, edges, time, change);
  LCD_EXPECT_EQ(expect, actual);
}

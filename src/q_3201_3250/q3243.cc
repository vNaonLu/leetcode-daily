// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Shortest Distance After Road Addition Queries I
//
// https://leetcode.com/problems/shortest-distance-after-road-addition-queries-i/
//
// Question ID: 3243
// Difficult  : Medium
// Solve Date : 2024/11/28 22:19

#include <iosfwd>
#include <numeric>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3243. Shortest Distance After Road Addition Queries I|:
//
// You are given an integer |n| and a 2D integer array |queries|.
// There are |n| cities numbered from |0| to |n - 1|. Initially, there is a
// unidirectional road from city |i| to city |i + 1| for all |0 <= i < n - 1|.
// |queries[i] = [uᵢ, vᵢ]| represents the addition of a new unidirectional road
// from city |uᵢ| to city |vᵢ|. After each query, you need to find the length of
// the shortest path from city |0| to city |n - 1|. Return an array |answer|
// where for each |i| in the range |[0, queries.length - 1]|, |answer[i]| is the
// length of the shortest path from city |0| to city |n - 1| after processing
// the first |i + 1| queries.
//
//

LEETCODE_BEGIN_RESOLVING(3243, ShortestDistanceAfterRoadAdditionQueriesI,
                         Solution);

class Solution {
public:
  vector<int> shortestDistanceAfterQueries(int                  n,
                                           vector<vector<int>> &queries) {
    vector<int>         res;
    vector<vector<int>> adj(n);
    vector<int>         dist(n);

    iota(dist.begin(), dist.end(), 0);
    for (int i = 0; i < n - 1; ++i) {
      adj[i].emplace_back(i + 1);
    }

    for (auto &it : queries) {
      int src = it[0];
      int des = it[1];
      adj[src].emplace_back(des);

      if (dist[src] + 1 < dist[des]) {
        queue<int> q;
        q.emplace(des);
        dist[des] = dist[src] + 1;

        while (!q.empty()) {
          int idx = q.front();
          q.pop();

          for (auto e : adj[idx]) {
            if (dist[idx] + 1 < dist[e]) {
              dist[e] = dist[idx] + 1;
              q.emplace(e);
            }
          }
        }
      }

      res.emplace_back(dist.back());
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |3 <= n <= 500|
// * |1 <= queries.length <= 500|
// * |queries[i].length == 2|
// * |0 <= queries[i][0] < queries[i][1] < n|
// * |1 < queries[i][1] - queries[i][0]|
// * There are no repeated roads among the queries.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 5, queries = [[2,4],[0,2],[0,4]]
// Output: [3,2,1]
//

LEETCODE_SOLUTION_UNITTEST(3243, ShortestDistanceAfterRoadAdditionQueriesI,
                           example_1) {
  auto                solution = MakeSolution();
  int                 n        = 5;
  vector<vector<int>> queries  = {
      {2, 4},
      {0, 2},
      {0, 4}
  };
  vector<int> expect = {3, 2, 1};
  vector<int> actual = solution->shortestDistanceAfterQueries(n, queries);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 4, queries = [[0,3],[0,2]]
// Output: [1,1]
//

LEETCODE_SOLUTION_UNITTEST(3243, ShortestDistanceAfterRoadAdditionQueriesI,
                           example_2) {
  auto                solution = MakeSolution();
  int                 n        = 4;
  vector<vector<int>> queries  = {
      {0, 3},
      {0, 2}
  };
  vector<int> expect = {1, 1};
  vector<int> actual = solution->shortestDistanceAfterQueries(n, queries);
  LCD_EXPECT_EQ(expect, actual);
}

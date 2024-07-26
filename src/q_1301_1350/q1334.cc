// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Find the City With the Smallest Number of Neighbors at a Threshold Distance
//
// https://leetcode.com/problems/find-the-city-with-the-smallest-number-of-neighbors-at-a-threshold-distance/
//
// Question ID: 1334
// Difficult  : Medium
// Solve Date : 2024/07/26 21:42

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1334. Find the City With the Smallest Number of Neighbors at
// a Threshold Distance|:
//
// There are |n| cities numbered from |0| to |n-1|. Given the array |edges|
// where |edges[i] = [fromᵢ, toᵢ, weightᵢ]| represents a bidirectional and
// weighted edge between cities |fromᵢ| and |toᵢ|, and given the integer
// |distanceThreshold|. Return the city with the smallest number of cities that
// are reachable through some path and whose distance is at most
// |distanceThreshold|, If there are multiple such cities, return the city with
// the greatest number. Notice that the distance of a path connecting cities i
// and j is equal to the sum of the edges' weights along that path.
//
//

LEETCODE_BEGIN_RESOLVING(
    1334, FindTheCityWithTheSmallestNumberOfNeighborsAtAThresholdDistance,
    Solution);

class Solution {
public:
  int findTheCity(int n, vector<vector<int>> &edges, int distanceThreshold) {
    vector<vector<int>> dist(n, vector<int>(n, numeric_limits<int>::max()));
    for (int i = 0; i < n; ++i) {
      dist[i][i] = 0;
    }

    for (auto &e : edges) {
      int u      = e[0];
      int v      = e[1];
      int w      = e[2];
      dist[u][v] = w;
      dist[v][u] = w;
    }

    for (int k = 0; k < n; ++k) {
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
          if (dist[i][k] != numeric_limits<int>::max() &&
              dist[k][j] != numeric_limits<int>::max()) {
            dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
          }
        }
      }
    }
    int res = -1;
    int mn  = numeric_limits<int>::max();
    for (int i = 0; i < n; ++i) {
      int r = 0;
      for (int j = 0; j < n; ++j) {
        if (dist[i][j] <= distanceThreshold) {
          ++r;
        }
      }

      if (r <= mn) {
        mn  = r;
        res = i;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= n <= 100|
// * |1 <= edges.length <= n * (n - 1) / 2|
// * |edges[i].length == 3|
// * |0 <= fromᵢ < toᵢ < n|
// * |1 <= weightᵢ, distanceThreshold <= 10^4|
// * All pairs |(fromᵢ, toᵢ)| are distinct.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 4, edges = [[0,1,3],[1,2,1],[1,3,4],[2,3,1]], distanceThreshold =
//  4
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(
    1334, FindTheCityWithTheSmallestNumberOfNeighborsAtAThresholdDistance,
    example_1) {
  auto                solution = MakeSolution();
  int                 n        = 4;
  vector<vector<int>> edges    = {
      {0, 1, 3},
      {1, 2, 1},
      {1, 3, 4},
      {2, 3, 1}
  };
  int distanceThreshold = 4;
  int expect            = 3;
  int actual            = solution->findTheCity(n, edges, distanceThreshold);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 5, edges = [[0,1,2],[0,4,8],[1,2,3],[1,4,2],[2,3,1],[3,4,1]],
//  distanceThreshold = 2
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(
    1334, FindTheCityWithTheSmallestNumberOfNeighborsAtAThresholdDistance,
    example_2) {
  auto                solution = MakeSolution();
  int                 n        = 5;
  vector<vector<int>> edges    = {
      {0, 1, 2},
      {0, 4, 8},
      {1, 2, 3},
      {1, 4, 2},
      {2, 3, 1},
      {3, 4, 1}
  };
  int distanceThreshold = 2;
  int expect            = 0;
  int actual            = solution->findTheCity(n, edges, distanceThreshold);
  LCD_EXPECT_EQ(expect, actual);
}

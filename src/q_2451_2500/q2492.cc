// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimum Score of a Path Between Two Cities
//
// https://leetcode.com/problems/minimum-score-of-a-path-between-two-cities/
//
// Question ID: 2492
// Difficult  : Medium
// Solve Date : 2023/03/22 19:46

#include <iosfwd>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2492. Minimum Score of a Path Between Two Cities|:
//
// You are given a positive integer |n| representing |n| cities numbered from
// |1| to |n|. You are also given a 2D array |roads| where |roads[i] = [aᵢ, bᵢ,
// distanceᵢ]| indicates that there is a bidirectional road between cities |aᵢ|
// and |bᵢ| with a distance equal to |distanceᵢ|. The cities graph is not
// necessarily connected. The score of a path between two cities is defined as
// the minimum distance of a road in this path. Return the minimum possible
// score of a path between cities |1| and |n|. Note:
//
//  • A path is a sequence of roads between two cities.
//
//  • It is allowed for a path to contain the same road multiple times, and you
//  can visit cities |1| and |n| multiple times along the path.
//
//  • The test cases are generated such that there is at least one path between
//  |1| and |n|.
//
//

LEETCODE_BEGIN_RESOLVING(2492, MinimumScoreOfAPathBetweenTwoCities, Solution);

class Solution {
public:
  int minScore(int n, vector<vector<int>> &roads) {
    vector<bool>                   visit(n + 1, false);
    priority_queue<pair<int, int>> pq;
    vector<vector<pair<int, int>>> graph(n + 1);
    for (auto &v : roads) {
      graph[v[0]].emplace_back(v[1], v[2]);
      graph[v[1]].emplace_back(v[0], v[2]);
    }
    int res  = numeric_limits<int>::max();
    visit[1] = true;
    pq.emplace(1, res);
    while (!pq.empty()) {
      auto [city, len] = pq.top();
      pq.pop();
      for (auto c : graph[city]) {
        res = min(res, c.second);
        if (!visit[c.first]) {
          visit[c.first] = true;
          pq.emplace(c);
        }
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |2 <= n <= 10⁵|
// * |1 <= roads.length <= 10⁵|
// * |roads[i].length == 3|
// * |1 <= aᵢ, bᵢ <= n|
// * |aᵢ != bᵢ|
// * |1 <= distanceᵢ <= 10⁴|
// * There are no repeated edges.
// * There is at least one path between |1| and |n|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 4, roads = [[1,2,9],[2,3,6],[2,4,5],[1,4,7]]
// Output: 5
//
// The path from city 1 to 4 with the minimum score is: 1 -> 2 -> 4. The score
// of this path is min(9,5) = 5. It can be shown that no other path has less
// score.

LEETCODE_SOLUTION_UNITTEST(2492, MinimumScoreOfAPathBetweenTwoCities,
                           example_1) {
  auto                solution = MakeSolution();
  int                 n        = 4;
  vector<vector<int>> roads    = {
      {1, 2, 9},
      {2, 3, 6},
      {2, 4, 5},
      {1, 4, 7}
  };
  int expect = 5;
  int actual = solution->minScore(n, roads);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 4, roads = [[1,2,2],[1,3,4],[3,4,7]]
// Output: 2
//
// The path from city 1 to 4 with the minimum score is: 1 -> 2 -> 1 -> 3 -> 4.
// The score of this path is min(2,2,4,7) = 2.

LEETCODE_SOLUTION_UNITTEST(2492, MinimumScoreOfAPathBetweenTwoCities,
                           example_2) {
  auto                solution = MakeSolution();
  int                 n        = 4;
  vector<vector<int>> roads    = {
      {1, 2, 2},
      {1, 3, 4},
      {3, 4, 7}
  };
  int expect = 2;
  int actual = solution->minScore(n, roads);
  LCD_EXPECT_EQ(expect, actual);
}

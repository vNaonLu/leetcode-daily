// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Maximum Total Importance of Roads
//
// https://leetcode.com/problems/maximum-total-importance-of-roads/
//
// Question ID: 2285
// Difficult  : Medium
// Solve Date : 2024/06/28 21:08

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2285. Maximum Total Importance of Roads|:
//
// You are given an integer |n| denoting the number of cities in a country. The
// cities are numbered from |0| to |n - 1|. You are also given a 2D integer
// array |roads| where |roads[i] = [aᵢ, bᵢ]| denotes that there exists a
// bidirectional road connecting cities |aᵢ| and |bᵢ|. You need to assign each
// city with an integer value from |1| to |n|, where each value can only be used
// once. The importance of a road is then defined as the sum of the values of
// the two cities it connects. Return the maximum total importance of all roads
// possible after assigning the values optimally.
//
//

LEETCODE_BEGIN_RESOLVING(2285, MaximumTotalImportanceOfRoads, Solution);

class Solution {
public:
  long long maximumImportance(int n, vector<vector<int>> &roads) {
    vector<int> deg(n, 0);
    for (auto &e : roads) {
      ++deg[e[0]];
      ++deg[e[1]];
    }

    vector<int> freq(n, 0);
    int         mx  = -1;
    int64_t     res = 0;
    int64_t     x   = 1;
    for (int i = 0; i < n; ++i) {
      ++freq[deg[i]];
      mx = max(mx, deg[i]);
    }
    for (int d = 0; d <= mx; ++d) {
      if (freq[d] == 0) {
        continue;
      }
      res += (2ll * x + freq[d] - 1) * freq[d] / 2 * d;
      x += freq[d];
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= n <= 5 * 10⁴|
// * |1 <= roads.length <= 5 * 10⁴|
// * |roads[i].length == 2|
// * |0 <= aᵢ, bᵢ <= n - 1|
// * |aᵢ != bᵢ|
// * There are no duplicate roads.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 5, roads = [[0,1],[1,2],[2,3],[0,2],[1,3],[2,4]]
// Output: 43
//

LEETCODE_SOLUTION_UNITTEST(2285, MaximumTotalImportanceOfRoads, example_1) {
  auto                solution = MakeSolution();
  int                 n        = 5;
  vector<vector<int>> roads    = {
      {0, 1},
      {1, 2},
      {2, 3},
      {0, 2},
      {1, 3},
      {2, 4}
  };
  long long expect = 43;
  long long actual = solution->maximumImportance(n, roads);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 5, roads = [[0,3],[2,4],[1,3]]
// Output: 20
//

LEETCODE_SOLUTION_UNITTEST(2285, MaximumTotalImportanceOfRoads, example_2) {
  auto                solution = MakeSolution();
  int                 n        = 5;
  vector<vector<int>> roads    = {
      {0, 3},
      {2, 4},
      {1, 3}
  };
  long long expect = 20;
  long long actual = solution->maximumImportance(n, roads);
  LCD_EXPECT_EQ(expect, actual);
}

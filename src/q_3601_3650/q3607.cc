// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Power Grid Maintenance
//
// https://leetcode.com/problems/power-grid-maintenance/
//
// Question ID: 3607
// Difficult  : Medium
// Solve Date : 2025/11/06 19:54

#include <iosfwd>
#include <numeric>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3607. Power Grid Maintenance|:
//
// You are given an integer |c| representing |c| power stations, each with a
// unique identifier |id| from 1 to |c| (1‑based indexing). These stations are
// interconnected via |n| bidirectional cables, represented by a 2D array
// |connections|, where each element |connections[i] = [uᵢ, vᵢ]| indicates a
// connection between station |uᵢ| and station |vᵢ|. Stations that are directly
// or indirectly connected form a power grid. Initially, all stations are online
// (operational). You are also given a 2D array |queries|, where each query is
// one of the following two types:
//
//  •
// 	|[1, x]|: A maintenance check is requested for station |x|. If station
// |x| is online, it resolves the check by itself. If station |x| is offline,
// the check is resolved by the operational station with the smallest |id| in
// the same power grid as |x|. If no operational station exists in that grid,
// return -1.
//
//
//  •
// 	|[2, x]|: Station |x| goes offline (i.e., it becomes non-operational).
//
// Return an array of integers representing the results of each query of type
// |[1, x]| in the order they appear. Note: The power grid preserves its
// structure; an offline (non‑operational) node remains part of its grid and
// taking it offline does not alter connectivity.
//
//

LEETCODE_BEGIN_RESOLVING(3607, PowerGridMaintenance, Solution);

class Solution {
public:
  vector<int> processQueries(int c, vector<vector<int>> &connections,
                             vector<vector<int>> &queries) {
    vector<int> parent(c + 1);
    iota(parent.begin(), parent.end(), 0);

    function<int(int)> find = [&](int x) {
      while (parent[x] != x) {
        parent[x] = parent[parent[x]];
        x         = parent[x];
      }
      return x;
    };

    for (auto &conn : connections) {
      int a = conn[0], b = conn[1];
      int ra = find(a), rb = find(b);
      if (ra != rb)
        parent[rb] = ra;
    }

    vector<int> next_node(c + 1, 0), comp_min(c + 1, 0), last(c + 1, 0);
    for (int i = 1; i <= c; ++i) {
      int r = find(i);
      if (comp_min[r] == 0) {
        comp_min[r] = i;
      } else {
        next_node[last[r]] = i;
      }
      last[r] = i;
    }

    vector<bool> offline(c + 1, false);
    vector<int>  res;

    for (auto &q : queries) {
      int t = q[0], x = q[1];

      if (t == 1) {
        if (!offline[x]) {
          res.push_back(x);
        } else {
          int r = find(x);
          res.push_back(comp_min[r] ? comp_min[r] : -1);
        }
      } else {
        if (!offline[x]) {
          offline[x] = true;
          int r      = find(x);
          if (comp_min[r] == x) {
            int y = next_node[x];
            while (y && offline[y])
              y = next_node[y];
            comp_min[r] = y ? y : 0;
          }
        }
      }
    }

    return res;
  }
};
LEETCODE_END_RESOLVING(Solution);

// [Example #1]
//  Input: c = 5, connections = [[1,2],[2,3],[3,4],[4,5]], queries =
//  [[1,3],[2,1],[1,1],[2,2],[1,2]]
// Output: [3,2,3]
//

LEETCODE_SOLUTION_UNITTEST(3607, PowerGridMaintenance, example_1) {
  auto                solution    = MakeSolution();
  int                 c           = 5;
  vector<vector<int>> connections = {
      {1, 2},
      {2, 3},
      {3, 4},
      {4, 5}
  };
  vector<vector<int>> queries = {
      {1, 3},
      {2, 1},
      {1, 1},
      {2, 2},
      {1, 2}
  };
  vector<int> expect = {3, 2, 3};
  vector<int> actual = solution->processQueries(c, connections, queries);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: c = 3, connections = [], queries = [[1,1],[2,1],[1,1]]
// Output: [1,-1]
//

LEETCODE_SOLUTION_UNITTEST(3607, PowerGridMaintenance, example_2) {
  auto                solution    = MakeSolution();
  int                 c           = 3;
  vector<vector<int>> connections = {};
  vector<vector<int>> queries     = {
      {1, 1},
      {2, 1},
      {1, 1}
  };
  vector<int> expect = {1, -1};
  vector<int> actual = solution->processQueries(c, connections, queries);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: 4
// [[2,3],[1,3],[4,1],[3,4]]
// [[1,2],[2,4],[2,1],[1,4],[2,1],[1,1],[2,2],[1,4],[2,1],[2,2],[2,3],[2,4],[2,1],[1,1],[2,3],[2,2],[2,3],[1,4],[2,4]]
// Output: [2,2,2,3,-1,-1]
//

LEETCODE_SOLUTION_UNITTEST(3607, PowerGridMaintenance, extra_testcase_1) {
  auto                solution    = MakeSolution();
  int                 c           = 4;
  vector<vector<int>> connections = {
      {2, 3},
      {1, 3},
      {4, 1},
      {3, 4}
  };
  vector<vector<int>> queries = {
      {1, 2},
      {2, 4},
      {2, 1},
      {1, 4},
      {2, 1},
      {1, 1},
      {2, 2},
      {1, 4},
      {2, 1},
      {2, 2},
      {2, 3},
      {2, 4},
      {2, 1},
      {1, 1},
      {2, 3},
      {2, 2},
      {2, 3},
      {1, 4},
      {2, 4}
  };
  vector<int> expect = {2, 2, 2, 3, -1, -1};
  vector<int> actual = solution->processQueries(c, connections, queries);
  LCD_EXPECT_EQ(expect, actual);
}

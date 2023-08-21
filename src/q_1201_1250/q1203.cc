// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Sort Items by Groups Respecting Dependencies
//
// https://leetcode.com/problems/sort-items-by-groups-respecting-dependencies/
//
// Question ID: 1203
// Difficult  : Hard
// Solve Date : 2023/08/20 18:22

#include <iosfwd>
#include <queue>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1203. Sort Items by Groups Respecting Dependencies|:
//
// There are |n| items each belonging to zero or one of |m| groups where
// |group[i]| is the group that the |i|-th item belongs to and it's equal to
// |-1| if the |i|-th item belongs to no group. The items and the groups are
// zero indexed. A group can have no item belonging to it. Return a sorted list
// of the items such that:
//
//  • The items that belong to the same group are next to each other in the
//  sorted list.
//
//  • There are some relations between these items where |beforeItems[i]| is a
//  list containing all the items that should come before the |i|-th item in the
//  sorted array (to the left of the |i|-th item).
// Return any solution if there is more than one solution and return an empty
// list if there is no solution.
//
//

LEETCODE_BEGIN_RESOLVING(1203, SortItemsByGroupsRespectingDependencies,
                         Solution);

class Solution {
public:
  vector<int> topo_sort(vector<vector<int>> &adj, vector<int> &deg, int sz) {
    queue<int> q;
    for (int i = 0; i < sz; i++) {
      if (deg[i] == 0) {
        q.push(i);
      }
    }
    vector<int> res;
    while (!q.empty()) {
      int x = q.front();
      q.pop();
      res.push_back(x);
      for (int y : adj[x]) {
        deg[y]--;
        if (deg[y] == 0) {
          q.push(y);
        }
      }
    }
    for (int i = 0; i < sz; i++)
      if (deg[i] > 0) {
        return {};
      }
    return res;
  }

  vector<int> sortItems(int n, int m, vector<int> &group,
                        vector<vector<int>> &beforeItems) {
    for (int i = 0; i < n; i++) {
      if (group[i] == -1) {
        group[i] = m++;
      }
    }
    vector<vector<int>> adj_group(m), adj_item(n);
    vector<int>         deg_group(m, 0), deg_item(n, 0);
    for (int i = 0; i < n; i++) {
      int to_i = group[i];
      for (int from : beforeItems[i]) {
        int from_j = group[from];
        if (to_i != from_j) {
          adj_group[from_j].push_back(to_i);
          deg_group[to_i]++;
        }
        adj_item[from].push_back(i);
        deg_item[i]++;
      }
    }
    vector<int> sort_group = topo_sort(adj_group, deg_group, m);
    vector<int> sort_item  = topo_sort(adj_item, deg_item, n);
    if (sort_group.empty() || sort_item.empty()) {
      return {};
    }

    vector<vector<int>> item_gp(m);
    for (int i : sort_item) {
      item_gp[group[i]].push_back(i);
    }

    vector<int> ans;
    for (int i : sort_group) {
      for (int item : item_gp[i]) {
        ans.push_back(item);
      }
    }

    return ans;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= m <= n <= 3 * 10⁴|
// * |group.length == beforeItems.length == n|
// * |-1 <= group[i] <= m - 1|
// * |0 <= beforeItems[i].length <= n - 1|
// * |0 <= beforeItems[i][j] <= n - 1|
// * |i != beforeItems[i][j]|
// * |beforeItems[i] |does not contain duplicates elements.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 8, m = 2, group = [-1,-1,1,0,0,1,0,-1], beforeItems =
//  [[],[6],[5],[6],[3,6],[],[],[]]
// Output: [6,3,4,1,5,2,0,7]
//

LEETCODE_SOLUTION_UNITTEST(1203, SortItemsByGroupsRespectingDependencies,
                           example_1) {
  auto                solution    = MakeSolution();
  int                 n           = 8;
  int                 m           = 2;
  vector<int>         group       = {-1, -1, 1, 0, 0, 1, 0, -1};
  vector<vector<int>> beforeItems = {
      {},
      {6},
      {5},
      {6},
      {3, 6},
      {},
      {},
      {}
  };
  vector<int> expect = {6, 3, 4, 1, 5, 2, 0, 7};
  vector<int> actual = solution->sortItems(n, m, group, beforeItems);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 8, m = 2, group = [-1,-1,1,0,0,1,0,-1], beforeItems =
//  [[],[6],[5],[6],[3],[],[4],[]]
// Output: []
//
//  This is the same as example 1 except that 4 needs to be before 6 in the
//  sorted list.

LEETCODE_SOLUTION_UNITTEST(1203, SortItemsByGroupsRespectingDependencies,
                           example_2) {
  auto                solution    = MakeSolution();
  int                 n           = 8;
  int                 m           = 2;
  vector<int>         group       = {-1, -1, 1, 0, 0, 1, 0, -1};
  vector<vector<int>> beforeItems = {{}, {6}, {5}, {6}, {3}, {}, {4}, {}};
  vector<int>         expect      = {};
  vector<int>         actual = solution->sortItems(n, m, group, beforeItems);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Checking Existence of Edge Length Limited Paths
//
// https://leetcode.com/problems/checking-existence-of-edge-length-limited-paths/
//
// Question ID: 1697
// Difficult  : Hard
// Solve Date : 2023/04/29 13:49

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1697. Checking Existence of Edge Length Limited Paths|:
//
// An undirected graph of |n| nodes is defined by |edgeList|, where |edgeList[i]
// = [uᵢ, vᵢ, disᵢ]| denotes an edge between nodes |uᵢ| and |vᵢ| with distance
// |disᵢ|. Note that there may be multiple edges between two nodes. Given an
// array |queries|, where |queries[j] = [pⱼ, qⱼ, limitⱼ]|, your task is to
// determine for each |queries[j]| whether there is a path between |pⱼ| and
// |qⱼ|_{ }such that each edge on the path has a distance strictly less than
// |limitⱼ| . Return a boolean array |answer|, where |answer.length ==
// queries.length| and the |jᵗʰ| value of |answer| is |true| if there is a path
// for |queries[j]| is |true|, and |false| otherwise.
//
//

LEETCODE_BEGIN_RESOLVING(1697, CheckingExistenceOfEdgeLengthLimitedPaths,
                         Solution);

class Solution {

public:
  vector<bool> distanceLimitedPathsExist(int n, vector<vector<int>> &edgeList,
                                         vector<vector<int>> &queries) {
    DisjointSet ds(n);

    for (int i = 0; i < queries.size(); ++i) {
      queries[i].emplace_back(i);
    }
    vector<bool> res(queries.size(), false);

    sort(queries.begin(), queries.end(), cmp);
    sort(edgeList.begin(), edgeList.end(), cmp);

    int j = 0;
    for (int i = 0; i < queries.size(); ++i) {
      while (j < edgeList.size() && edgeList[j][2] < queries[i][2]) {
        ds.UnionBySize(edgeList[j][0], edgeList[j][1]);
        ++j;
      }
      if (ds.findUpar(queries[i][0]) == ds.findUpar(queries[i][1])) {
        res[queries[i][3]] = true;
      }
    }

    return res;
  }

private:
  static bool cmp(vector<int> &a, vector<int> &b) { return a[2] < b[2]; }

  class DisjointSet {
  public:
    vector<int> size;
    vector<int> parent;

    DisjointSet(int n) : size(n, 1), parent(n) {
      for (int i = 0; i < n; ++i) {
        parent[i] = i;
      }
    }
    int findUpar(int node) {
      if (node == parent[node]) {
        return node;
      }
      return parent[node] = findUpar(parent[node]);
    }
    void UnionBySize(int u, int v) {
      int ulp_u = findUpar(u);
      int ulp_v = findUpar(v);
      if (ulp_u == ulp_v) {
        return;
      }
      if (size[ulp_u] < size[ulp_v]) {
        parent[ulp_u] = ulp_v;
        size[ulp_v] += size[ulp_u];
      } else {
        parent[ulp_v] = ulp_u;
        size[ulp_u] += size[ulp_v];
      }
    }
  };
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |2 <= n <= 10⁵|
// * |1 <= edgeList.length, queries.length <= 10⁵|
// * |edgeList[i].length == 3|
// * |queries[j].length == 3|
// * |0 <= uᵢ, vᵢ, pⱼ, qⱼ <= n - 1|
// * |uᵢ != vᵢ|
// * |pⱼ != qⱼ|
// * |1 <= disᵢ, limitⱼ <= 10⁹|
// * There may be multiple edges between two nodes.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 3, edgeList = [[0,1,2],[1,2,4],[2,0,8],[1,0,16]], queries =
//  [[0,1,2],[0,2,5]]
// Output: [false,true]
//
// The above figure shows the given graph. Note that there are two overlapping
// edges between 0 and 1 with distances 2 and 16. For the first query, between 0
// and 1 there is no path where each distance is less than 2, thus we return
// false for this query. For the second query, there is a path (0 -> 1 -> 2) of
// two edges with distances less than 5, thus we return true for this query.

LEETCODE_SOLUTION_UNITTEST(1697, CheckingExistenceOfEdgeLengthLimitedPaths,
                           example_1) {
  auto                solution = MakeSolution();
  int                 n        = 3;
  vector<vector<int>> edgeList = {
      {0, 1,  2},
      {1, 2,  4},
      {2, 0,  8},
      {1, 0, 16}
  };
  vector<vector<int>> queries = {
      {0, 1, 2},
      {0, 2, 5}
  };
  vector<bool> expect = {false, true};
  vector<bool> actual =
      solution->distanceLimitedPathsExist(n, edgeList, queries);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 5, edgeList = [[0,1,10],[1,2,5],[2,3,9],[3,4,13]], queries =
//  [[0,4,14],[1,4,13]]
// Output: [true,false]
// Exaplanation: The above figure shows the given graph.
//

LEETCODE_SOLUTION_UNITTEST(1697, CheckingExistenceOfEdgeLengthLimitedPaths,
                           example_2) {
  auto                solution = MakeSolution();
  int                 n        = 5;
  vector<vector<int>> edgeList = {
      {0, 1, 10},
      {1, 2,  5},
      {2, 3,  9},
      {3, 4, 13}
  };
  vector<vector<int>> queries = {
      {0, 4, 14},
      {1, 4, 13}
  };
  vector<bool> expect = {true, false};
  vector<bool> actual =
      solution->distanceLimitedPathsExist(n, edgeList, queries);
  LCD_EXPECT_EQ(expect, actual);
}

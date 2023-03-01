// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Number of Good Paths
//
// https://leetcode.com/problems/number-of-good-paths/
//
// Question ID: 2421
// Difficult  : Hard
// Solve Date : 2023/01/15 17:33

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2421. Number of Good Paths|:
//
// There is a tree (i.e. a connected, undirected graph with no cycles)
// consisting of |n| nodes numbered from |0| to |n - 1| and exactly |n - 1|
// edges. You are given a 0-indexed integer array |vals| of length |n| where
// |vals[i]| denotes the value of the |iᵗʰ| node. You are also given a 2D
// integer array |edges| where |edges[i] = [aᵢ, bᵢ]| denotes that there exists
// an undirected edge connecting nodes |aᵢ| and |bᵢ|. A good path is a simple
// path that satisfies the following conditions:
//
//  1. The starting node and the ending node have the same value.
//
//  2. All nodes between the starting node and the ending node have values less
//  than or equal to the starting node (i.e. the starting node's value should be
//  the maximum value along the path).
// Return the number of distinct good paths.
// Note that a path and its reverse are counted as the same path. For example,
// |0 -> 1| is considered to be the same as |1 -> 0|. A single node is also
// considered as a valid path.
//

LEETCODE_BEGIN_RESOLVING(2421, NumberOfGoodPaths, Solution);

class Solution {
private:
  int find(vector<int> &v, int i) {
    if (i == v[i]) {
      return i;
    }
    v[i] = find(v, v[i]);
    return v[i];
  }

public:
  int numberOfGoodPaths(vector<int> &vals, vector<vector<int>> &edges) {
    int                 n   = vals.size();
    int                 m   = edges.size();
    int                 res = 0;
    vector<vector<int>> x(n);
    vector<int>         v(n);
    for (int i = 0; i < n; ++i) {
      v[i] = i;
      x[i] = {vals[i], 1};
    }
    sort(edges.begin(), edges.end(), [&](auto &a, auto &b) {
      return max(vals[a[0]], vals[a[1]]) < max(vals[b[0]], vals[b[1]]);
    });
    for (int i = 0; i < m; ++i) {
      auto a = find(v, edges[i][0]);
      auto b = find(v, edges[i][1]);
      if (x[a][0] != x[b][0]) {
        if (x[a][0] > x[b][0]) {
          v[b] = a;
        } else {
          v[a] = b;
        }
      } else {
        v[a] = b;
        res += x[a][1] * x[b][1];
        x[b][1] += x[a][1];
      }
    }

    return res + n;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == vals.length|
// * |1 <= n <= 3 * 10⁴|
// * |0 <= vals[i] <= 10⁵|
// * |edges.length == n - 1|
// * |edges[i].length == 2|
// * |0 <= aᵢ, bᵢ < n|
// * |aᵢ != bᵢ|
// * |edges| represents a valid tree.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: vals = [1,3,2,1,3], edges = [[0,1],[0,2],[2,3],[2,4]]
// Output: 6
//
// There are 5 good paths consisting of a single node.
// There is 1 additional good path: 1 -> 0 -> 2 -> 4.
// (The reverse path 4 -> 2 -> 0 -> 1 is treated as the same as 1 -> 0 -> 2
// -> 4.) Note that 0 -> 2 -> 3 is not a good path because vals[2] > vals[0].

LEETCODE_SOLUTION_UNITTEST(2421, NumberOfGoodPaths, example_1) {
  auto                solution = MakeSolution();
  vector<int>         vals     = {1, 3, 2, 1, 3};
  vector<vector<int>> edges    = {
      {0, 1},
      {0, 2},
      {2, 3},
      {2, 4}
  };
  int expect = 6;
  int actual = solution->numberOfGoodPaths(vals, edges);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: vals = [1,1,2,2,3], edges = [[0,1],[1,2],[2,3],[2,4]]
// Output: 7
//
// There are 5 good paths consisting of a single node.
// There are 2 additional good paths: 0 -> 1 and 2 -> 3.

LEETCODE_SOLUTION_UNITTEST(2421, NumberOfGoodPaths, example_2) {
  auto                solution = MakeSolution();
  vector<int>         vals     = {1, 1, 2, 2, 3};
  vector<vector<int>> edges    = {
      {0, 1},
      {1, 2},
      {2, 3},
      {2, 4}
  };
  int expect = 7;
  int actual = solution->numberOfGoodPaths(vals, edges);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: vals = [1], edges = []
// Output: 1
//
// The tree consists of only one node, so there is one good path.

LEETCODE_SOLUTION_UNITTEST(2421, NumberOfGoodPaths, example_3) {
  auto                solution = MakeSolution();
  vector<int>         vals     = {1};
  vector<vector<int>> edges    = {};
  int                 expect   = 1;
  int                 actual   = solution->numberOfGoodPaths(vals, edges);
  LCD_EXPECT_EQ(expect, actual);
}

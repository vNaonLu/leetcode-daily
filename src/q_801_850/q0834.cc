// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Sum of Distances in Tree
//
// https://leetcode.com/problems/sum-of-distances-in-tree/
//
// Question ID: 834
// Difficult  : Hard
// Solve Date : 2024/04/28 14:41

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |834. Sum of Distances in Tree|:
//
// There is an undirected connected tree with |n| nodes labeled from |0| to |n -
// 1| and |n - 1| edges. You are given the integer |n| and the array |edges|
// where |edges[i] = [aᵢ, bᵢ]| indicates that there is an edge between nodes
// |aᵢ| and |bᵢ| in the tree. Return an array |answer| of length |n| where
// |answer[i]| is the sum of the distances between the |iᵗʰ| node in the tree
// and all other nodes.
//
//

LEETCODE_BEGIN_RESOLVING(834, SumOfDistancesInTree, Solution);

class Solution {
public:
  vector<int> sumOfDistancesInTree(int n, vector<vector<int>> &edges) {
    vector<int> res(n);

    mp.resize(n, vector<int>());
    cnt.resize(n, 1);

    for (auto &a : edges) {
      mp[a[0]].push_back(a[1]);
      mp[a[1]].push_back(a[0]);
    }

    dfs(res, 0, -1);
    dfs2(res, 0, -1);

    return res;
  }

private:
  vector<vector<int>> mp;
  vector<int>         cnt;

  void dfs(vector<int> &r, int node, int pre) {
    for (auto &child : mp[node]) {
      if (child != pre) {
        dfs(r, child, node);
        cnt[node] += cnt[child];
        r[node] += r[child] + cnt[child];
      }
    }
  }

  void dfs2(vector<int> &r, int node, int pre) {
    for (auto &child : mp[node]) {
      if (child != pre) {
        r[child] = r[node] + mp.size() - cnt[child] * 2;
        dfs2(r, child, node);
      }
    }
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n <= 3 * 10⁴|
// * |edges.length == n - 1|
// * |edges[i].length == 2|
// * |0 <= aᵢ, bᵢ < n|
// * |aᵢ != bᵢ|
// * The given input represents a valid tree.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 6, edges = [[0,1],[0,2],[2,3],[2,4],[2,5]]
// Output: [8,12,6,10,10,10]
//

LEETCODE_SOLUTION_UNITTEST(834, SumOfDistancesInTree, example_1) {
  auto                solution = MakeSolution();
  int                 n        = 6;
  vector<vector<int>> edges    = {
      {0, 1},
      {0, 2},
      {2, 3},
      {2, 4},
      {2, 5}
  };
  vector<int> expect = {8, 12, 6, 10, 10, 10};
  vector<int> actual = solution->sumOfDistancesInTree(n, edges);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 1, edges = []
// Output: [0]
//

LEETCODE_SOLUTION_UNITTEST(834, SumOfDistancesInTree, example_2) {
  auto                solution = MakeSolution();
  int                 n        = 1;
  vector<vector<int>> edges    = {};
  vector<int>         expect   = {0};
  vector<int>         actual   = solution->sumOfDistancesInTree(n, edges);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: n = 2, edges = [[1,0]]
// Output: [1,1]
//

LEETCODE_SOLUTION_UNITTEST(834, SumOfDistancesInTree, example_3) {
  auto                solution = MakeSolution();
  int                 n        = 2;
  vector<vector<int>> edges    = {
      {1, 0}
  };
  vector<int> expect = {1, 1};
  vector<int> actual = solution->sumOfDistancesInTree(n, edges);
  LCD_EXPECT_EQ(expect, actual);
}

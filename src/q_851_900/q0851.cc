// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Loud and Rich
//
// https://leetcode.com/problems/loud-and-rich/
//
// Question ID: 851
// Difficult  : Medium
// Solve Date : 2024/09/19 23:59

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |851. Loud and Rich|:
//
// There is a group of |n| people labeled from |0| to |n - 1| where each person
// has a different amount of money and a different level of quietness. You are
// given an array |richer| where |richer[i] = [aᵢ, bᵢ]| indicates that |aᵢ| has
// more money than |bᵢ| and an integer array |quiet| where |quiet[i]| is the
// quietness of the |iᵗʰ| person. All the given data in richer are logically
// correct (i.e., the data will not lead you to a situation where |x| is richer
// than |y| and |y| is richer than |x| at the same time). Return an integer
// array |answer| where |answer[x] = y| if |y| is the least quiet person (that
// is, the person |y| with the smallest value of |quiet[y]|) among all people
// who definitely have equal to or more money than the person |x|.
//
//

LEETCODE_BEGIN_RESOLVING(851, LoudAndRich, Solution);

class Solution {
public:
  vector<int> loudAndRich(vector<vector<int>> &richer, vector<int> &quiet) {
    int                 n = quiet.size();
    vector<vector<int>> g(n);
    vector<int>         res(n, -1);
    for (auto &v : richer) {
      g[v[1]].emplace_back(v[0]);
    }
    for (int i = 0; i < n; ++i) {
      dfs(i, g, quiet, &res);
    }
    return res;
  }

private:
  int dfs(int node, vector<vector<int>> const &g, vector<int> const &quiet,
          vector<int> *res) {
    if ((*res)[node] != -1) {
      return (*res)[node];
    }
    (*res)[node] = node;
    for (auto &v : g[node]) {
      int cand = dfs(v, g, quiet, res);
      if (quiet[cand] < quiet[(*res)[node]]) {
        (*res)[node] = cand;
      }
    }
    return (*res)[node];
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |n == quiet.length|
// * |1 <= n <= 500|
// * |0 <= quiet[i] < n|
// * All the values of |quiet| are unique.
// * |0 <= richer.length <= n * (n - 1) / 2|
// * |0 <= aᵢ, bᵢ < n|
// * |a_{i }!= bᵢ|
// * All the pairs of |richer| are unique.
// * The observations in |richer| are all logically consistent.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: richer = [[1,0],[2,1],[3,1],[3,7],[4,3],[5,3],[6,3]], quiet =
//  [3,2,5,4,6,1,7,0]
// Output: [5,5,2,5,4,5,6,7]
//

LEETCODE_SOLUTION_UNITTEST(851, LoudAndRich, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> richer   = {
      {1, 0},
      {2, 1},
      {3, 1},
      {3, 7},
      {4, 3},
      {5, 3},
      {6, 3}
  };
  vector<int> quiet  = {3, 2, 5, 4, 6, 1, 7, 0};
  vector<int> expect = {5, 5, 2, 5, 4, 5, 6, 7};
  vector<int> actual = solution->loudAndRich(richer, quiet);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: richer = [], quiet = [0]
// Output: [0]
//

LEETCODE_SOLUTION_UNITTEST(851, LoudAndRich, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> richer   = {};
  vector<int>         quiet    = {0};
  vector<int>         expect   = {0};
  vector<int>         actual   = solution->loudAndRich(richer, quiet);
  LCD_EXPECT_EQ(expect, actual);
}

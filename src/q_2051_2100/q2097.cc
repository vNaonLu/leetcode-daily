// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Valid Arrangement of Pairs
//
// https://leetcode.com/problems/valid-arrangement-of-pairs/
//
// Question ID: 2097
// Difficult  : Hard
// Solve Date : 2024/11/30 15:19

#include <iosfwd>
#include <list>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2097. Valid Arrangement of Pairs|:
//
// You are given a 0-indexed 2D integer array |pairs| where |pairs[i] = [startᵢ,
// endᵢ]|. An arrangement of |pairs| is valid if for every index |i| where |1 <=
// i < pairs.length|, we have |endᵢ₋₁ == startᵢ|. Return any valid arrangement
// of |pairs|. Note: The inputs will be generated such that there exists a valid
// arrangement of |pairs|.
//
//

LEETCODE_BEGIN_RESOLVING(2097, ValidArrangementOfPairs, Solution);

class Solution {
public:
  vector<vector<int>> validArrangement(vector<vector<int>> &pairs) {
    unordered_map<int, list<int>> g;
    unordered_map<int, int>       in_out_deg;

    for (auto &v : pairs) {
      int start = v[0];
      int end   = v[1];
      g[start].emplace_back(end);
      ++in_out_deg[start];
      --in_out_deg[end];
    }

    int start_node = pairs[0][0];
    for (auto &[node, deg] : in_out_deg) {
      if (deg == 1) {
        start_node = node;
        break;
      }
    }

    vector<vector<int>> res;
    dfs(&g, start_node, &res);
    reverse(res.begin(), res.end());
    return res;
  }

private:
  void dfs(auto *g, int curr, vector<vector<int>> *res) {
    auto &neighbors = (*g)[curr];
    while (!neighbors.empty()) {
      int next = neighbors.front();
      neighbors.pop_front();
      dfs(g, next, res);
      res->push_back({curr, next});
    }
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= pairs.length <= 10⁵|
// * |pairs[i].length == 2|
// * |0 <= startᵢ, endᵢ <= 10⁹|
// * |startᵢ != endᵢ|
// * No two pairs are exactly the same.
// * There exists a valid arrangement of |pairs|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: pairs = [[5,1],[4,5],[11,9],[9,4]]
// Output: [[11,9],[9,4],[4,5],[5,1]]
// Explanation:
// This is a valid arrangement since endᵢ₋₁ always equals startᵢ.
// end₀ = 9 == 9 = start₁
// end₁ = 4 == 4 = start₂
// end₂ = 5 == 5 = start₃
//

LEETCODE_SOLUTION_UNITTEST(2097, ValidArrangementOfPairs, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> pairs    = {
      { 5, 1},
      { 4, 5},
      {11, 9},
      { 9, 4}
  };
  vector<vector<int>> expect = {
      {11, 9},
      { 9, 4},
      { 4, 5},
      { 5, 1}
  };
  vector<vector<int>> actual = solution->validArrangement(pairs);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: pairs = [[1,3],[3,2],[2,1]]
// Output: [[1,3],[3,2],[2,1]]
//

LEETCODE_SOLUTION_UNITTEST(2097, ValidArrangementOfPairs, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> pairs    = {
      {1, 3},
      {3, 2},
      {2, 1}
  };
  vector<vector<int>> expect = {
      {1, 3},
      {3, 2},
      {2, 1}
  };
  vector<vector<int>> actual = solution->validArrangement(pairs);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: pairs = [[1,2],[1,3],[2,1]]
// Output: [[1,2],[2,1],[1,3]]
//

LEETCODE_SOLUTION_UNITTEST(2097, ValidArrangementOfPairs, example_3) {
  auto                solution = MakeSolution();
  vector<vector<int>> pairs    = {
      {1, 2},
      {1, 3},
      {2, 1}
  };
  vector<vector<int>> expect = {
      {1, 2},
      {2, 1},
      {1, 3}
  };
  vector<vector<int>> actual = solution->validArrangement(pairs);
  LCD_EXPECT_EQ(expect, actual);
}

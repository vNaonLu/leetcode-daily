// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Number of Ways of Cutting a Pizza
//
// https://leetcode.com/problems/number-of-ways-of-cutting-a-pizza/
//
// Question ID: 1444
// Difficult  : Hard
// Solve Date : 2023/03/31 15:02

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1444. Number of Ways of Cutting a Pizza|:
//
// Given a rectangular pizza represented as a |rows x cols| matrix containing
// the following characters: |'A'| (an apple) and |'.'| (empty cell) and given
// the integer |k|. You have to cut the pizza into |k| pieces using |k-1| cuts.
//
// For each cut you choose the direction: vertical or horizontal, then you
// choose a cut position at the cell boundary and cut the pizza into two pieces.
// If you cut the pizza vertically, give the left part of the pizza to a person.
// If you cut the pizza horizontally, give the upper part of the pizza to a
// person. Give the last piece of pizza to the last person.
//
// Return the number of ways of cutting the pizza such that each piece contains
// at least one apple. Since the answer can be a huge number, return this modulo
// 10^9 + 7.
//
//
//

LEETCODE_BEGIN_RESOLVING(1444, NumberOfWaysOfCuttingAPizza, Solution);

class Solution {
private:
  inline static constexpr int kMod = 1e9 + 7;
  int solve(vector<vector<int>> &v, int ci, int cj, int cuts,
            vector<vector<vector<int>>> &dp) {
    if (cuts == 0) {
      return v[ci][cj] > 0 ? 1 : 0;
    }
    if (dp[ci][cj][cuts] == -1) {
      int64_t rows = 0;
      int64_t cols = 0;
      for (int i = ci + 1; i < v.size() - 1; ++i) {
        if (v[i][cj] >= cuts && v[ci][cj] - v[i][cj] > 0) {
          rows = (rows + solve(v, i, cj, cuts - 1, dp)) % kMod;
        }
      }
      for (int j = cj + 1; j < v[0].size() - 1; ++j) {
        if (v[ci][j] >= cuts && v[ci][cj] - v[ci][j] > 0) {
          cols = (cols + solve(v, ci, j, cuts - 1, dp)) % kMod;
        }
      }
      dp[ci][cj][cuts] = (rows + cols) % kMod;
    }
    return dp[ci][cj][cuts];
  }

public:
  int ways(vector<string> &pizza, int k) {
    int                         m = pizza.size();
    int                         n = pizza[0].size();
    vector<vector<vector<int>>> dp(
        m + 1, vector<vector<int>>(n + 1, vector<int>(k + 1, -1)));
    vector<vector<int>> cnt(m + 1, vector<int>(n + 1, 0));
    for (int i = m - 1; i >= 0; --i) {
      for (int j = n - 1; j >= 0; --j) {
        cnt[i][j] = cnt[i + 1][j] + cnt[i][j + 1] - cnt[i + 1][j + 1] +
                    (pizza[i][j] == 'A' ? 1 : 0);
      }
    }
    return solve(cnt, 0, 0, k - 1, dp);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= rows, cols <= 50|
// * |rows == pizza.length|
// * |cols == pizza[i].length|
// * |1 <= k <= 10|
// * |pizza| consists of characters |'A'| and |'.'| only.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: pizza = ["A..","AAA","..."], k = 3
// Output: 3
//
// The figure above shows the three ways to cut the pizza. Note that pieces must
// contain at least one apple.

LEETCODE_SOLUTION_UNITTEST(1444, NumberOfWaysOfCuttingAPizza, example_1) {
  auto           solution = MakeSolution();
  vector<string> pizza    = {"A..", "AAA", "..."};
  int            k        = 3;
  int            expect   = 3;
  int            actual   = solution->ways(pizza, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: pizza = ["A..","AA.","..."], k = 3
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(1444, NumberOfWaysOfCuttingAPizza, example_2) {
  auto           solution = MakeSolution();
  vector<string> pizza    = {"A..", "AA.", "..."};
  int            k        = 3;
  int            expect   = 1;
  int            actual   = solution->ways(pizza, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: pizza = ["A..","A..","..."], k = 1
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(1444, NumberOfWaysOfCuttingAPizza, example_3) {
  auto           solution = MakeSolution();
  vector<string> pizza    = {"A..", "A..", "..."};
  int            k        = 1;
  int            expect   = 1;
  int            actual   = solution->ways(pizza, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: [".A","AA","A."]
// 3
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(1444, NumberOfWaysOfCuttingAPizza,
                           extra_testcase_1) {
  auto           solution = MakeSolution();
  vector<string> pizza    = {".A", "AA", "A."};
  int            k        = 3;
  int            expect   = 3;
  int            actual   = solution->ways(pizza, k);
  LCD_EXPECT_EQ(expect, actual);
}

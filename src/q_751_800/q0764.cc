// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Largest Plus Sign
//
// https://leetcode.com/problems/largest-plus-sign/
//
// Question ID: 764
// Difficult  : Medium
// Solve Date : 2021/09/09 08:00

#include <iosfwd>
#include <map>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |764. Largest Plus Sign|:
//
// You are given an integer |n|. You have an |n x n| binary grid |grid| with all
// values initially |1|'s except for some indices given in the array |mines|.
// The |iᵗʰ| element of the array |mines| is defined as |mines[i] = [xᵢ, yᵢ]|
// where |grid[xᵢ][yᵢ] == 0|. Return the order of the largest axis-aligned plus
// sign of 1's contained in |grid|. If there is none, return |0|. An
// axis-aligned plus sign of |1|'s of order |k| has some center |grid[r][c] ==
// 1| along with four arms of length |k - 1| going up, down, left, and right,
// and made of |1|'s. Note that there could be |0|'s or |1|'s beyond the arms of
// the plus sign, only the relevant area of the plus sign is checked for |1|'s.
//  
//

LEETCODE_BEGIN_RESOLVING(764, LargestPlusSign, Solution);

class Solution {
public:
  int orderOfLargestPlusSign(int n, vector<vector<int>> &mines) {
    unordered_map<int, bool> banned;
    vector<vector<int>>      dp(n, vector<int>(n));
    for (vector<int> mine : mines) {
      banned.insert({mine[0] * n + mine[1], true});
    }
    int res = 0, count;
    for (int i = 0; i < n; ++i) {
      count = 0;
      for (int j = 0; j < n; ++j) {
        count    = banned.count(i * n + j) ? 0 : count + 1;
        dp[i][j] = count;
      }
      count = 0;
      for (int j = n - 1; j > -1; --j) {
        count    = banned.count(i * n + j) ? 0 : count + 1;
        dp[i][j] = min(dp[i][j], count);
      }
    }
    for (int i = 0; i < n; ++i) {
      count = 0;
      for (int j = 0; j < n; ++j) {
        count    = banned.count(j * n + i) ? 0 : count + 1;
        dp[j][i] = min(dp[j][i], count);
      }
      count = 0;
      for (int j = n - 1; j > -1; --j) {
        count    = banned.count(j * n + i) ? 0 : count + 1;
        dp[j][i] = min(dp[j][i], count);
        res      = max(res, dp[j][i]);
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n <= 500|
// * |1 <= mines.length <= 5000|
// * |0 <= xᵢ, yᵢ < n|
// * All the pairs |(xᵢ, yᵢ)| are unique.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 5, mines = [[4,2]]
// Output: 2
//
// In the above grid, the largest plus sign can only be of order 2. One of them
// is shown.

LEETCODE_SOLUTION_UNITTEST(764, LargestPlusSign, example_1) {
  auto                solution = MakeSolution();
  int                 n        = 5;
  vector<vector<int>> mines    = {
      {4, 2}
  };
  int expect = 2;
  int actual = solution->orderOfLargestPlusSign(n, mines);
  EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 1, mines = [[0,0]]
// Output: 0
//
// There is no plus sign, so return 0.

LEETCODE_SOLUTION_UNITTEST(764, LargestPlusSign, example_2) {
  auto                solution = MakeSolution();
  int                 n        = 1;
  vector<vector<int>> mines    = {
      {0, 0}
  };
  int expect = 0;
  int actual = solution->orderOfLargestPlusSign(n, mines);
  EXPECT_EQ(expect, actual);
}

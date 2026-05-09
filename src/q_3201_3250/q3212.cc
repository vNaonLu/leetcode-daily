// Copyright 2026 Naon Lu
//
// This file describes the solution of
// Count Submatrices With Equal Frequency of X and Y
//
// https://leetcode.com/problems/count-submatrices-with-equal-frequency-of-x-and-y/
//
// Question ID: 3212
// Difficult  : Medium
// Solve Date : 2026/03/19 19:21

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3212. Count Submatrices With Equal Frequency of X and Y|:
//
// Given a 2D character matrix |grid|, where |grid[i][j]| is either |'X'|,
// |'Y'|, or |'.'|, return the number of submatrices that contain:
//
//  • |grid[0][0]|
//
//  • an equal frequency of |'X'| and |'Y'|.
//
//  • at least one |'X'|.
//
//

LEETCODE_BEGIN_RESOLVING(3212, CountSubmatricesWithEqualFrequencyOfXAndY,
                         Solution);

class Solution {
public:
  int numberOfSubmatrices(vector<vector<char>> &grid) {
    vector<vector<pair<int, int>>> cnt(grid.size());
    for (int i = 0; i < grid.size(); ++i) {
      cnt[i].resize(grid[i].size());
      for (int j = 0; j < grid[i].size(); ++j) {
        cnt[i][j].first  = grid[i][j] == 'X';
        cnt[i][j].second = grid[i][j] == 'Y';

        if (i > 0) {
          cnt[i][j].first += cnt[i - 1][j].first;
          cnt[i][j].second += cnt[i - 1][j].second;
        }
        if (j > 0) {
          cnt[i][j].first += cnt[i][j - 1].first;
          cnt[i][j].second += cnt[i][j - 1].second;
        }
        if (i > 0 && j > 0) {
          cnt[i][j].first -= cnt[i - 1][j - 1].first;
          cnt[i][j].second -= cnt[i - 1][j - 1].second;
        }
      }
    }

    int res = 0;
    for (int i = 0; i < cnt.size(); ++i) {
      for (int j = 0; j < cnt[i].size(); ++j) {
        if (cnt[i][j].first > 0 && cnt[i][j].first == cnt[i][j].second) {
          ++res;
        }
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= grid.length, grid[i].length <= 1000|
// * |grid[i][j]| is either |'X'|, |'Y'|, or |'.'|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: grid = [["X","Y","."],["Y",".","."]]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(3212, CountSubmatricesWithEqualFrequencyOfXAndY,
                           example_1) {
  auto                 solution = MakeSolution();
  vector<vector<char>> grid     = {
      {'X', 'Y', '.'},
      {'Y', '.', '.'}
  };
  int expect = 3;
  int actual = solution->numberOfSubmatrices(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: grid = [["X","X"],["X","Y"]]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(3212, CountSubmatricesWithEqualFrequencyOfXAndY,
                           example_2) {
  auto                 solution = MakeSolution();
  vector<vector<char>> grid     = {
      {'X', 'X'},
      {'X', 'Y'}
  };
  int expect = 0;
  int actual = solution->numberOfSubmatrices(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: grid = [[".","."],[".","."]]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(3212, CountSubmatricesWithEqualFrequencyOfXAndY,
                           example_3) {
  auto                 solution = MakeSolution();
  vector<vector<char>> grid     = {
      {'.', '.'},
      {'.', '.'}
  };
  int expect = 0;
  int actual = solution->numberOfSubmatrices(grid);
  LCD_EXPECT_EQ(expect, actual);
}

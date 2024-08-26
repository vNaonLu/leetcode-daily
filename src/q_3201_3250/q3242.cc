// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Design Neighbor Sum Service
//
// https://leetcode.com/problems/design-neighbor-sum-service/
//
// Question ID: 3242
// Difficult  : Easy
// Solve Date : 2024/08/26 21:23

#include <iosfwd>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3242. Design Neighbor Sum Service|:
//
//

LEETCODE_BEGIN_RESOLVING(3242, DesignNeighborSumService, NeighborSum);

class NeighborSum {
public:
  NeighborSum(vector<vector<int>> &grid) : g_{std::move(grid)} {
    for (int i = 0; i < g_.size(); ++i) {
      for (int j = 0; j < g_[i].size(); ++j) {
        pos_.try_emplace(g_[i][j], i, j);
      }
    }
  }

  int adjacentSum(int value) {
    auto it  = pos_.find(value);
    int  res = 0;
    if (it == pos_.end()) {
      return res;
    }

    auto [i, j] = it->second;
    res += i > 0 ? g_[i - 1][j] : 0;
    res += i < g_.size() - 1 ? g_[i + 1][j] : 0;
    res += j > 0 ? g_[i][j - 1] : 0;
    res += j < g_[0].size() - 1 ? g_[i][j + 1] : 0;
    return res;
  }

  int diagonalSum(int value) {
    auto it  = pos_.find(value);
    int  res = 0;
    if (it == pos_.end()) {
      return res;
    }

    auto [i, j] = it->second;
    res += i > 0 && j > 0 ? g_[i - 1][j - 1] : 0;
    res += i < g_.size() - 1 && j > 0 ? g_[i + 1][j - 1] : 0;
    res += i > 0 && j < g_[0].size() - 1 ? g_[i - 1][j + 1] : 0;
    res += i < g_.size() - 1 && j < g_[0].size() - 1 ? g_[i + 1][j + 1] : 0;
    return res;
  }

private:
  unordered_map<int, pair<int, int>> pos_;
  vector<vector<int>>                g_;
};

LEETCODE_END_RESOLVING(NeighborSum);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |3 <= n == grid.length == grid[0].length <= 10|
// * |0 <= grid[i][j] <= n² - 1|
// * All |grid[i][j]| are distinct.
// * |value| in |adjacentSum| and |diagonalSum| will be in the range |[0, n² -
// 1]|.
// * At most |2 * n²| calls will be made to |adjacentSum| and |diagonalSum|.
///////////////////////////////////////////////////////////////////////////////

LEETCODE_SOLUTION_UNITTEST(3242, DesignNeighborSumService, example_1) {
  vector<vector<int>> s0_grid = {
      {0, 1, 2},
      {3, 4, 5},
      {6, 7, 8}
  };
  auto lru_cache = MakeNeighborSum(s0_grid);
  int  s1_value  = 1;
  int  s1_expect = 6;
  int  s1_actual = lru_cache->adjacentSum(s1_value);
  LCD_EXPECT_EQ(s1_expect, s1_actual);
  int s2_value  = 4;
  int s2_expect = 16;
  int s2_actual = lru_cache->adjacentSum(s2_value);
  LCD_EXPECT_EQ(s2_expect, s2_actual);
  int s3_value  = 4;
  int s3_expect = 16;
  int s3_actual = lru_cache->diagonalSum(s3_value);
  LCD_EXPECT_EQ(s3_expect, s3_actual);
  int s4_value  = 8;
  int s4_expect = 4;
  int s4_actual = lru_cache->diagonalSum(s4_value);
  LCD_EXPECT_EQ(s4_expect, s4_actual);
}

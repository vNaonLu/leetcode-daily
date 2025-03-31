// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Maximum Number of Points From Grid Queries
//
// https://leetcode.com/problems/maximum-number-of-points-from-grid-queries/
//
// Question ID: 2503
// Difficult  : Hard
// Solve Date : 2025/03/29 00:36

#include <iosfwd>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2503. Maximum Number of Points From Grid Queries|:
//
// You are given an |m x n| integer matrix |grid| and an array |queries| of size
// |k|. Find an array |answer| of size |k| such that for each integer
// |queries[i]| you start in the top left cell of the matrix and repeat the
// following process:
//
//  • If |queries[i]| is strictly greater than the value of the current cell
//  that you are in, then you get one point if it is your first time visiting
//  this cell, and you can move to any adjacent cell in all |4| directions: up,
//  down, left, and right.
//
//  • Otherwise, you do not get any points, and you end this process.
// After the process, |answer[i]| is the maximum number of points you can get.
// Note that for each query you are allowed to visit the same cell multiple
// times. Return the resulting array |answer|.
//
//

LEETCODE_BEGIN_RESOLVING(2503, MaximumNumberOfPointsFromGridQueries, Solution);

class Solution {
public:
  vector<int> maxPoints(vector<vector<int>> &grid, vector<int> &queries) {
    int                    rows = grid.size(), cols = grid[0].size();
    vector<pair<int, int>> sortedQueries;
    for (int i = 0; i < queries.size(); i++) {
      sortedQueries.emplace_back(queries[i], i);
    }
    sort(sortedQueries.begin(), sortedQueries.end());

    vector<int> result(queries.size(), 0);
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>,
                   greater<>>
                         minHeap;
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));

    minHeap.emplace(grid[0][0], make_pair(0, 0));
    visited[0][0]                     = true;
    int                    points     = 0;
    vector<pair<int, int>> directions = {
        { 0,  1},
        { 1,  0},
        { 0, -1},
        {-1,  0}
    };

    for (auto &[queryVal, queryIdx] : sortedQueries) {
      while (!minHeap.empty() && minHeap.top().first < queryVal) {
        auto [val, pos] = minHeap.top();
        minHeap.pop();
        int row = pos.first, col = pos.second;
        points++;

        for (auto &[dr, dc] : directions) {
          int nr = row + dr, nc = col + dc;
          if (nr >= 0 && nr < rows && nc >= 0 && nc < cols &&
              !visited[nr][nc]) {
            minHeap.emplace(grid[nr][nc], make_pair(nr, nc));
            visited[nr][nc] = true;
          }
        }
      }
      result[queryIdx] = points;
    }

    return result;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |m == grid.length|
// * |n == grid[i].length|
// * |2 <= m, n <= 1000|
// * |4 <= m * n <= 10⁵|
// * |k == queries.length|
// * |1 <= k <= 10⁴|
// * |1 <= grid[i][j], queries[i] <= 10⁶|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: grid = [[1,2,3],[2,5,7],[3,5,1]], queries = [5,6,2]
// Output: [5,8,1]
//

LEETCODE_SOLUTION_UNITTEST(2503, MaximumNumberOfPointsFromGridQueries,
                           example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {1, 2, 3},
      {2, 5, 7},
      {3, 5, 1}
  };
  vector<int> queries = {5, 6, 2};
  vector<int> expect  = {5, 8, 1};
  vector<int> actual  = solution->maxPoints(grid, queries);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: grid = [[5,2,1],[1,1,2]], queries = [3]
// Output: [0]
//

LEETCODE_SOLUTION_UNITTEST(2503, MaximumNumberOfPointsFromGridQueries,
                           example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {5, 2, 1},
      {1, 1, 2}
  };
  vector<int> queries = {3};
  vector<int> expect  = {0};
  vector<int> actual  = solution->maxPoints(grid, queries);
  LCD_EXPECT_EQ(expect, actual);
}

// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Pacific Atlantic Water Flow
//
// https://leetcode.com/problems/pacific-atlantic-water-flow/
//
// Question ID: 417
// Difficult  : Medium
// Solve Date : 2022/03/13 14:08

#include <iosfwd>
#include <limits>
#include <set>
#include <unordered_set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |417. Pacific Atlantic Water Flow|:
//
// There is an |m x n| rectangular island that borders both the Pacific Ocean
// and Atlantic Ocean. The Pacific Ocean touches the island's left and top
// edges, and the Atlantic Ocean touches the island's right and bottom edges.
// The island is partitioned into a grid of square cells. You are given an |m x
// n| integer matrix |heights| where |heights[r][c]| represents the height above
// sea level of the cell at coordinate |(r, c)|. The island receives a lot of
// rain, and the rain water can flow to neighboring cells directly north, south,
// east, and west if the neighboring cell's height is less than or equal to the
// current cell's height. Water can flow from any cell adjacent to an ocean into
// the ocean. Return a 2D list of grid coordinates |result| where |result[i] =
// [rᵢ, cᵢ]| denotes that rain water can flow from cell |(rᵢ, cᵢ)| to both the
// Pacific and Atlantic oceans.  
//

LEETCODE_BEGIN_RESOLVING(417, PacificAtlanticWaterFlow, Solution);

class Solution {
private:
  int                 m, n;
  vector<vector<int>> terrain;

  inline void helper(int i, int j, unordered_set<int> &ocean,
                     int prev_alt = numeric_limits<int>::min()) {
    int  pos = i * n + j;
    auto it  = ocean.find(pos);
    if (i < 0 || i >= m || j < 0 || j >= n)
      return;

    int curr = terrain[i][j];
    if (curr < prev_alt || it != ocean.end())
      return;

    ocean.insert(pos);
    helper(i + 1, j, ocean, curr);
    helper(i - 1, j, ocean, curr);
    helper(i, j + 1, ocean, curr);
    helper(i, j - 1, ocean, curr);
  }

public:
  vector<vector<int>> pacificAtlantic(vector<vector<int>> &heights) {
    m       = heights.size();
    n       = heights[0].size();
    terrain = move(heights);
    unordered_set<int> pacific, atlantic;
    for (int i = 0; i < max(m, n); ++i) {
      helper(i, 0, pacific);
      helper(0, i, pacific);
    }
    for (int i = 0; i < max(m, n); ++i) {
      helper(i, n - 1, atlantic);
      helper(m - 1, i, atlantic);
    }

    vector<vector<int>> res;
    heights = move(terrain);
    for (auto it = pacific.begin(); it != pacific.end(); ++it) {
      if (atlantic.count(*it)) {
        res.emplace_back(vector<int>{*it / n, *it % n});
      }
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |m == heights.length|
// * |n == heights[r].length|
// * |1 <= m, n <= 200|
// * |0 <= heights[r][c] <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: heights =
//  [[1,2,2,3,5],[3,2,3,4,4],[2,4,5,3,1],[6,7,1,4,5],[5,1,1,2,4]]
// Output: [[0,4],[1,3],[1,4],[2,2],[3,0],[3,1],[4,0]]
//
// The following cells can flow to the Pacific and Atlantic oceans, as shown
// below: [0,4]: [0,4] -> Pacific Ocean   [0,4] -> Atlantic Ocean [1,3]: [1,3]
// -> [0,3] -> Pacific Ocean   [1,3] -> [1,4] -> Atlantic Ocean [1,4]: [1,4] ->
// [1,3] -> [0,3] -> Pacific Ocean   [1,4] -> Atlantic Ocean [2,2]: [2,2] ->
// [1,2] -> [0,2] -> Pacific Ocean   [2,2] -> [2,3] -> [2,4] -> Atlantic Ocean
// [3,0]: [3,0] -> Pacific Ocean
//   [3,0] -> [4,0] -> Atlantic Ocean
// [3,1]: [3,1] -> [3,0] -> Pacific Ocean
//   [3,1] -> [4,1] -> Atlantic Ocean
// [4,0]: [4,0] -> Pacific Ocean
//  [4,0] -> Atlantic Ocean
// Note that there are other possible paths for these cells to flow to the
// Pacific and Atlantic oceans.

LEETCODE_SOLUTION_UNITTEST(417, PacificAtlanticWaterFlow, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> heights  = {
      {1, 2, 2, 3, 5},
      {3, 2, 3, 4, 4},
      {2, 4, 5, 3, 1},
      {6, 7, 1, 4, 5},
      {5, 1, 1, 2, 4}
  };
  vector<vector<int>> expect = {
      {0, 4},
      {1, 3},
      {1, 4},
      {2, 2},
      {3, 0},
      {3, 1},
      {4, 0}
  };
  vector<vector<int>> actual = solution->pacificAtlantic(heights);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #2]
//  Input: heights = [[1]]
// Output: [[0,0]]
//
// The water can flow from the only cell to the Pacific and Atlantic oceans.

LEETCODE_SOLUTION_UNITTEST(417, PacificAtlanticWaterFlow, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> heights  = {{1}};
  vector<vector<int>> expect   = {
      {0, 0}
  };
  vector<vector<int>> actual = solution->pacificAtlantic(heights);
  EXPECT_ANYORDER_EQ(expect, actual);
}

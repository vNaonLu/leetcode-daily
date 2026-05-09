// Copyright 2026 Naon Lu
//
// This file describes the solution of
// Get Biggest Three Rhombus Sums in a Grid
//
// https://leetcode.com/problems/get-biggest-three-rhombus-sums-in-a-grid/
//
// Question ID: 1878
// Difficult  : Medium
// Solve Date : 2026/03/16 13:18

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1878. Get Biggest Three Rhombus Sums in a Grid|:
//
// You are given an |m x n| integer matrix |grid|​​​.
// A rhombus sum is the sum of the elements that form the border of a regular
// rhombus shape in |grid|​​​. The rhombus must have the shape of a square
// rotated 45 degrees with each of the corners centered in a grid cell. Below is
// an image of four valid rhombus shapes with the corresponding colored cells
// that should be included in each rhombus sum:
// ![img](https://assets.leetcode.com/uploads/2021/04/23/pc73-q4-desc-2.png)
// Note that the rhombus can have an area of 0, which is depicted by the purple
// rhombus in the bottom right corner. Return the biggest three distinct rhombus
// sums in the |grid| in descending order. If there are less than three distinct
// values, return all of them.
//
//

LEETCODE_BEGIN_RESOLVING(1878, GetBiggestThreeRhombusSumsInAGrid, Solution);

class Solution {
public:
  vector<int> getBiggestThree(vector<vector<int>> &grid) {
    int m = grid.size();
    int n = grid[0].size();

    set<int> st;

    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {

        st.insert(grid[i][j]);
        for (int k = 1;; k++) {

          int r     = i + 2 * k;
          int left  = j - k;
          int right = j + k;

          if (r >= m || left < 0 || right >= n)
            break;

          int sum = 0;

          int x = i, y = j;

          for (int t = 0; t < k; t++) {
            sum += grid[x + t][y + t];
          }

          for (int t = 0; t < k; t++) {
            sum += grid[x + k + t][y + k - t];
          }

          for (int t = 0; t < k; t++) {
            sum += grid[x + 2 * k - t][y - t];
          }

          for (int t = 0; t < k; t++) {
            sum += grid[x + k - t][y - k + t];
          }

          st.insert(sum);
        }
      }
    }

    vector<int> ans;
    for (auto it = st.rbegin(); it != st.rend() && ans.size() < 3; ++it) {
      ans.push_back(*it);
    }

    return ans;
  }
};
LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |m == grid.length|
// * |n == grid[i].length|
// * |1 <= m, n <= 50|
// * |1 <= grid[i][j] <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: grid =
//  [[3,4,5,1,3],[3,3,4,2,3],[20,30,200,40,10],[1,5,5,4,1],[4,3,2,2,5]]
// Output: [228,216,211]
//

LEETCODE_SOLUTION_UNITTEST(1878, GetBiggestThreeRhombusSumsInAGrid, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      { 3,  4,   5,  1,  3},
      { 3,  3,   4,  2,  3},
      {20, 30, 200, 40, 10},
      { 1,  5,   5,  4,  1},
      { 4,  3,   2,  2,  5}
  };
  vector<int> expect = {228, 216, 211};
  vector<int> actual = solution->getBiggestThree(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: grid = [[1,2,3],[4,5,6],[7,8,9]]
// Output: [20,9,8]
//

LEETCODE_SOLUTION_UNITTEST(1878, GetBiggestThreeRhombusSumsInAGrid, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {1, 2, 3},
      {4, 5, 6},
      {7, 8, 9}
  };
  vector<int> expect = {20, 9, 8};
  vector<int> actual = solution->getBiggestThree(grid);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: grid = [[7,7,7]]
// Output: [7]
//

LEETCODE_SOLUTION_UNITTEST(1878, GetBiggestThreeRhombusSumsInAGrid, example_3) {
  auto                solution = MakeSolution();
  vector<vector<int>> grid     = {
      {7, 7, 7}
  };
  vector<int> expect = {7};
  vector<int> actual = solution->getBiggestThree(grid);
  LCD_EXPECT_EQ(expect, actual);
}

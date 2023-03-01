// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Find a Peak Element II
//
// https://leetcode.com/problems/find-a-peak-element-ii/
//
// Question ID: 1901
// Difficult  : Medium
// Solve Date : 2022/07/30 17:22

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1901. Find a Peak Element II|:
//
// A peak element in a 2D grid is an element that is strictly greater than all
// of its adjacent neighbors to the left, right, top, and bottom. Given a
// 0-indexed |m x n| matrix |mat| where no two adjacent cells are equal, find
// any peak element |mat[i][j]| and return the length 2 array |[i,j]|. You may
// assume that the entire matrix is surrounded by an outer perimeter with the
// value |-1| in each cell. You must write an algorithm that runs in |O(m
// log(n))| or |O(n log(m))| time.
//

LEETCODE_BEGIN_RESOLVING(1901, FindAPeakElementII, Solution);

class Solution {
public:
  vector<int> findPeakGrid(vector<vector<int>> &mat) {
    auto m  = mat.size();
    auto n  = mat.front().size();
    int  lo = 0, hi = m - 1;

    while (lo <= hi) {
      int mid = lo + (hi - lo) / 2;
      int idx =
          max_element(mat[mid].begin(), mat[mid].end()) - mat[mid].begin();
      if (mid < m - 1 && mat[mid][idx] < mat[mid + 1][idx]) {
        lo = mid + 1;
      } else if (mid > 0 && mat[mid][idx] < mat[mid - 1][idx]) {
        hi = mid - 1;
      } else {
        return {mid, idx};
      }
    }

    return {-1, -1};
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |m == mat.length|
// * |n == mat[i].length|
// * |1 <= m, n <= 500|
// * |1 <= mat[i][j] <= 10⁵|
// * No two adjacent cells are equal.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: mat = [[1,4],[3,2]]
// Output: [0,1]
//
// Both 3 and 4 are peak elements so [1,0] and [0,1] are both acceptable
// answers.

LEETCODE_SOLUTION_UNITTEST(1901, FindAPeakElementII, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> mat      = {
      {1, 4},
      {3, 2}
  };
  vector<int> expect = {0, 1};
  vector<int> actual = solution->findPeakGrid(mat);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: mat = [[10,20,15],[21,30,14],[7,16,32]]
// Output: [1,1]
//
// Both 30 and 32 are peak elements so [1,1] and [2,2] are both acceptable
// answers.

LEETCODE_SOLUTION_UNITTEST(1901, FindAPeakElementII, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> mat      = {
      {10, 20, 15},
      {21, 30, 14},
      { 7, 16, 32}
  };
  vector<int> expect = {1, 1};
  vector<int> actual = solution->findPeakGrid(mat);
  LCD_EXPECT_EQ(expect, actual);
}

// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Search a 2D Matrix
//
// https://leetcode.com/problems/search-a-2d-matrix/
//
// Question ID: 74
// Difficult  : Medium
// Solve Date : 2021/09/09 08:00

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |74. Search a 2D Matrix|:
//
// You are given an |m x n| integer matrix |matrix| with the following two
// properties:
//
//  • Each row is sorted in non-decreasing order.
//
//  • The first integer of each row is greater than the last integer of the
//  previous row.
// Given an integer |target|, return |true| if |target| is in |matrix| or
// |false| otherwise. You must write a solution in |O(log(m * n))| time
// complexity.  
//

LEETCODE_BEGIN_RESOLVING(74, Searcha2DMatrix, Solution);

class Solution {
private:
  vector<int>  nil;
  vector<int> &find_row(vector<vector<int>> &m, int target) {
    int l = 0, r = m.size();
    while (l < r) {
      int mid = l + (r - l) / 2;
      if (m[mid].front() <= target && m[mid].back() >= target) {
        return m[mid];
      } else if (m[mid].front() > target) {
        r = mid;
      } else {
        l = mid + 1;
      }
    }
    return nil;
  }

  bool find(vector<int> &v, int target) {
    int l = 0, r = v.size();
    while (l < r) {
      int m = l + (r - l) / 2;
      if (v[m] == target) {
        return true;
      } else if (v[m] > target) {
        r = m;
      } else {
        l = m + 1;
      }
    }

    return false;
  }

public:
  bool searchMatrix(vector<vector<int>> &matrix, int target) {
    auto row = find_row(matrix, target);
    return find(row, target);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |m == matrix.length|
// * |n == matrix[i].length|
// * |1 <= m, n <= 100|
// * |-10⁴ <= matrix[i][j], target <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 3
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(74, Searcha2DMatrix, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> matrix   = {
      { 1,  3,  5,  7},
      {10, 11, 16, 20},
      {23, 30, 34, 60}
  };
  int  target = 3;
  bool expect = true;
  bool actual = solution->searchMatrix(matrix, target);
  EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 13
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(74, Searcha2DMatrix, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> matrix   = {
      { 1,  3,  5,  7},
      {10, 11, 16, 20},
      {23, 30, 34, 60}
  };
  int  target = 13;
  bool expect = false;
  bool actual = solution->searchMatrix(matrix, target);
  EXPECT_EQ(expect, actual);
}

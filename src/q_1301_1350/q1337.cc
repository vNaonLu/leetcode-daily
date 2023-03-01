// Copyright 2023 Naon Lu
//
// This file describes the solution of
// The K Weakest Rows in a Matrix
//
// https://leetcode.com/problems/the-k-weakest-rows-in-a-matrix/
//
// Question ID: 1337
// Difficult  : Easy
// Solve Date : 2022/03/27 23:33

#include <iosfwd>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1337. The K Weakest Rows in a Matrix|:
//
// You are given an |m x n| binary matrix |mat| of |1|'s (representing soldiers)
// and |0|'s (representing civilians). The soldiers are positioned in front of
// the civilians. That is, all the |1|'s will appear to the left of all the
// |0|'s in each row. A row |i| is weaker than a row |j| if one of the following
// is true:
//
//  • The number of soldiers in row |i| is less than the number of soldiers in
//  row |j|.
//
//  • Both rows have the same number of soldiers and |i < j|.
// Return the indices of the |k| weakest rows in the matrix ordered from weakest
// to strongest.  
//

LEETCODE_BEGIN_RESOLVING(1337, TheKWeakestRowsInAMatrix, Solution);

class Solution {
public:
  vector<int> kWeakestRows(vector<vector<int>> &mat, int k) {
    priority_queue<pair<int, int>, vector<pair<int, int>>,
                   greater<pair<int, int>>>
        pq;

    int row = 0;
    for (const auto &v : mat) {
      int l = 0, r = v.size() - 1;
      while (l <= r) {
        int mid = l + (r - l) / 2;
        if (v[mid] == 1) {
          l = mid + 1;
        } else {
          r = mid - 1;
        }
      }
      pq.emplace(l, row++);
    }
    vector<int> res;
    while (k-- && !pq.empty()) {
      res.emplace_back(pq.top().second);
      pq.pop();
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |m == mat.length|
// * |n == mat[i].length|
// * |2 <= n, m <= 100|
// * |1 <= k <= m|
// * |matrix[i][j]| is either 0 or 1.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: mat =
// [[1,1,0,0,0],
//  [1,1,1,1,0],
//  [1,0,0,0,0],
//  [1,1,0,0,0],
//  [1,1,1,1,1]],
// k = 3
// Output: [2,0,3]
//
// The number of soldiers in each row is:
// - Row 0: 2
// - Row 1: 4
// - Row 2: 1
// - Row 3: 2
// - Row 4: 5
// The rows ordered from weakest to strongest are [2,0,3,1,4].

LEETCODE_SOLUTION_UNITTEST(1337, TheKWeakestRowsInAMatrix, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> mat      = {
      {1, 1, 0, 0, 0},
      {1, 1, 1, 1, 0},
      {1, 0, 0, 0, 0},
      {1, 1, 0, 0, 0},
      {1, 1, 1, 1, 1}
  };
  int         k      = 3;
  vector<int> expect = {2, 0, 3};
  vector<int> actual = solution->kWeakestRows(mat, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: mat =
// [[1,0,0,0],
//  [1,1,1,1],
//  [1,0,0,0],
//  [1,0,0,0]],
// k = 2
// Output: [0,2]
//
// The number of soldiers in each row is:
// - Row 0: 1
// - Row 1: 4
// - Row 2: 1
// - Row 3: 1
// The rows ordered from weakest to strongest are [0,2,3,1].

LEETCODE_SOLUTION_UNITTEST(1337, TheKWeakestRowsInAMatrix, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> mat      = {
      {1, 0, 0, 0},
      {1, 1, 1, 1},
      {1, 0, 0, 0},
      {1, 0, 0, 0}
  };
  int         k      = 2;
  vector<int> expect = {0, 2};
  vector<int> actual = solution->kWeakestRows(mat, k);
  LCD_EXPECT_EQ(expect, actual);
}

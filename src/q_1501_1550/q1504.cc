// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Count Submatrices With All Ones
//
// https://leetcode.com/problems/count-submatrices-with-all-ones/
//
// Question ID: 1504
// Difficult  : Medium
// Solve Date : 2025/08/21 21:19

#include <iosfwd>
#include <stack>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1504. Count Submatrices With All Ones|:
//
// Given an |m x n| binary matrix |mat|, return the number of submatrices that
// have all ones.
//
//

LEETCODE_BEGIN_RESOLVING(1504, CountSubmatricesWithAllOnes, Solution);

class Solution {
public:
  int numSubmat(vector<vector<int>> &mat) {
    int         m   = mat.size();
    int         n   = mat[0].size();
    int         res = 0;
    vector<int> h(n);
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        h[j] = mat[i][j] ? h[j] + 1 : 0;
      }
      vector<int> sum(n);
      stack<int>  st;
      for (int j = 0; j < n; ++j) {
        while (!st.empty() && h[st.top()] >= h[j]) {
          st.pop();
        }
        if (!st.empty()) {
          int p  = st.top();
          sum[j] = sum[p] + h[j] * (j - p);
        } else {
          sum[j] = h[j] * (j + 1);
        }
        st.push(j);
        res += sum[j];
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= m, n <= 150|
// * |mat[i][j]| is either |0| or |1|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: mat = [[1,0,1],[1,1,0],[1,1,0]]
// Output: 13
//

LEETCODE_SOLUTION_UNITTEST(1504, CountSubmatricesWithAllOnes, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> mat      = {
      {1, 0, 1},
      {1, 1, 0},
      {1, 1, 0}
  };
  int expect = 13;
  int actual = solution->numSubmat(mat);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: mat = [[0,1,1,0],[0,1,1,1],[1,1,1,0]]
// Output: 24
//

LEETCODE_SOLUTION_UNITTEST(1504, CountSubmatricesWithAllOnes, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> mat      = {
      {0, 1, 1, 0},
      {0, 1, 1, 1},
      {1, 1, 1, 0}
  };
  int expect = 24;
  int actual = solution->numSubmat(mat);
  LCD_EXPECT_EQ(expect, actual);
}

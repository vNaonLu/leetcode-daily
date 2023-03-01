// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Combinations
//
// https://leetcode.com/problems/combinations/
//
// Question ID: 77
// Difficult  : Medium
// Solve Date : 2021/09/15 08:00

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |77. Combinations|:
//
// Given two integers |n| and |k|, return all possible combinations of |k|
// numbers chosen from the range |[1, n]|. You may return the answer in any
// order.  
//

LEETCODE_BEGIN_RESOLVING(77, Combinations, Solution);

class Solution {
private:
  void helper(const int &n, const int &k, vector<vector<int>> &r,
              vector<int> &cur, int c = 1) {
    if (cur.size() == k) {
      r.push_back(cur);
      return;
    }
    if (c > n)
      return;
    cur.reserve(k);
    for (int i = c; i <= n; ++i) {
      cur.push_back(i);
      helper(n, k, r, cur, i + 1);
      cur.pop_back();
    }
  }

public:
  vector<vector<int>> combine(int n, int k) {
    vector<vector<int>> res;
    vector<int>         tmp;
    helper(n, k, res, tmp);
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n <= 20|
// * |1 <= k <= n|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 4, k = 2
// Output: [[1,2],[1,3],[1,4],[2,3],[2,4],[3,4]]
//
// There are 4 choose 2 = 6 total combinations.
// Note that combinations are unordered, i.e., [1,2] and [2,1] are considered to
// be the same combination.

LEETCODE_SOLUTION_UNITTEST(77, Combinations, example_1) {
  auto                solution = MakeSolution();
  int                 n        = 4;
  int                 k        = 2;
  vector<vector<int>> expect   = {
      {1, 2},
      {1, 3},
      {1, 4},
      {2, 3},
      {2, 4},
      {3, 4}
  };
  vector<vector<int>> actual = solution->combine(n, k);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 1, k = 1
// Output: [[1]]
//
// There is 1 choose 1 = 1 total combination.

LEETCODE_SOLUTION_UNITTEST(77, Combinations, example_2) {
  auto                solution = MakeSolution();
  int                 n        = 1;
  int                 k        = 1;
  vector<vector<int>> expect   = {{1}};
  vector<vector<int>> actual   = solution->combine(n, k);
  EXPECT_ANYORDER_EQ(expect, actual);
}

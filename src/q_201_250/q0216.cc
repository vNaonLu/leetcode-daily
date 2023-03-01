// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Combination Sum III
//
// https://leetcode.com/problems/combination-sum-iii/
//
// Question ID: 216
// Difficult  : Medium
// Solve Date : 2022/05/10 19:01

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |216. Combination Sum III|:
//
// Find all valid combinations of |k| numbers that sum up to |n| such that the
// following conditions are true:
//
//  • Only numbers |1| through |9| are used.
//
//  • Each number is used at most once.
// Return a list of all possible valid combinations. The list must not contain
// the same combination twice, and the combinations may be returned in any
// order.  
//

LEETCODE_BEGIN_RESOLVING(216, CombinationSumIII, Solution);

class Solution {
private:
  bool helper(int k, int n, vector<vector<int>> &res, vector<int> &curr,
              int sum, int from) {
    if (curr.size() >= k) {
      if (sum == n) {
        res.emplace_back(curr);
      } else if (sum > n) {
        return false;
      }
    } else {
      for (int i = from; i <= 9; ++i) {
        curr.emplace_back(i);
        if (!helper(k, n, res, curr, sum + i, i + 1)) {
          curr.pop_back();
          break;
        }
        curr.pop_back();
      }
    }

    return true;
  }

public:
  vector<vector<int>> combinationSum3(int k, int n) {
    vector<vector<int>> res;
    vector<int>         tmp;
    res.reserve(k);
    helper(k, n, res, tmp, 0, 1);

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |2 <= k <= 9|
// * |1 <= n <= 60|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: k = 3, n = 7
// Output: [[1,2,4]]
//
// 1 + 2 + 4 = 7
// There are no other valid combinations.

LEETCODE_SOLUTION_UNITTEST(216, CombinationSumIII, example_1) {
  auto                solution = MakeSolution();
  int                 k        = 3;
  int                 n        = 7;
  vector<vector<int>> expect   = {
      {1, 2, 4}
  };
  vector<vector<int>> actual = solution->combinationSum3(k, n);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #2]
//  Input: k = 3, n = 9
// Output: [[1,2,6],[1,3,5],[2,3,4]]
//
// 1 + 2 + 6 = 9
// 1 + 3 + 5 = 9
// 2 + 3 + 4 = 9
// There are no other valid combinations.

LEETCODE_SOLUTION_UNITTEST(216, CombinationSumIII, example_2) {
  auto                solution = MakeSolution();
  int                 k        = 3;
  int                 n        = 9;
  vector<vector<int>> expect   = {
      {1, 2, 6},
      {1, 3, 5},
      {2, 3, 4}
  };
  vector<vector<int>> actual = solution->combinationSum3(k, n);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #3]
//  Input: k = 4, n = 1
// Output: []
//
// There are no valid combinations.
// Using 4 different numbers in the range [1,9], the smallest sum we can get is
// 1+2+3+4 = 10 and since 10 > 1, there are no valid combination.

LEETCODE_SOLUTION_UNITTEST(216, CombinationSumIII, example_3) {
  auto                solution = MakeSolution();
  int                 k        = 4;
  int                 n        = 1;
  vector<vector<int>> expect   = {};
  vector<vector<int>> actual   = solution->combinationSum3(k, n);
  EXPECT_ANYORDER_EQ(expect, actual);
}

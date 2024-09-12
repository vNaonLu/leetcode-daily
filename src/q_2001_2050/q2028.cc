// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Find Missing Observations
//
// https://leetcode.com/problems/find-missing-observations/
//
// Question ID: 2028
// Difficult  : Medium
// Solve Date : 2024/09/07 15:41

#include <iosfwd>
#include <numeric>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2028. Find Missing Observations|:
//
// You have observations of |n + m| 6-sided dice rolls with each face numbered
// from |1| to |6|. |n| of the observations went missing, and you only have the
// observations of |m| rolls. Fortunately, you have also calculated the average
// value of the |n + m| rolls. You are given an integer array |rolls| of length
// |m| where |rolls[i]| is the value of the |iᵗʰ| observation. You are also
// given the two integers |mean| and |n|. Return an array of length |n|
// containing the missing observations such that the average value of the |n +
// m| rolls is exactly |mean|. If there are multiple valid answers, return any
// of them. If no such array exists, return an empty array. The average value of
// a set of |k| numbers is the sum of the numbers divided by |k|. Note that
// |mean| is an integer, so the sum of the |n + m| rolls should be divisible by
// |n + m|.
//
//

LEETCODE_BEGIN_RESOLVING(2028, FindMissingObservations, Solution);

class Solution {
public:
  vector<int> missingRolls(vector<int> &rolls, int mean, int n) {
    int m            = rolls.size();
    int required_sum = (n + m) * mean;
    int sum          = accumulate(begin(rolls), end(rolls), 0);
    int missing_sum  = required_sum - sum;

    if (missing_sum < n || missing_sum > n * 6) {
      return {};
    }

    vector<int> res(n, 1);
    missing_sum -= n;
    for (int i = 0; i < n; i++) {
      res[i] += min(5, missing_sum);

      missing_sum -= min(5, missing_sum);

      if (missing_sum <= 0) {
        break;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |m == rolls.length|
// * |1 <= n, m <= 10⁵|
// * |1 <= rolls[i], mean <= 6|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: rolls = [3,2,4,3], mean = 4, n = 2
// Output: [6,6]
//

LEETCODE_SOLUTION_UNITTEST(2028, FindMissingObservations, example_1) {
  auto        solution = MakeSolution();
  vector<int> rolls    = {3, 2, 4, 3};
  int         mean     = 4;
  int         n        = 2;
  vector<int> expect   = {6, 6};
  vector<int> actual   = solution->missingRolls(rolls, mean, n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: rolls = [1,5,6], mean = 3, n = 4
// Output: [2,3,2,2]
//

LEETCODE_SOLUTION_UNITTEST(2028, FindMissingObservations, example_2) {
  auto        solution = MakeSolution();
  vector<int> rolls    = {1, 5, 6};
  int         mean     = 3;
  int         n        = 4;
  vector<int> expect   = {6, 1, 1, 1};
  vector<int> actual   = solution->missingRolls(rolls, mean, n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: rolls = [1,2,3,4], mean = 6, n = 4
// Output: []
//

LEETCODE_SOLUTION_UNITTEST(2028, FindMissingObservations, example_3) {
  auto        solution = MakeSolution();
  vector<int> rolls    = {1, 2, 3, 4};
  int         mean     = 6;
  int         n        = 4;
  vector<int> expect   = {};
  vector<int> actual   = solution->missingRolls(rolls, mean, n);
  LCD_EXPECT_EQ(expect, actual);
}

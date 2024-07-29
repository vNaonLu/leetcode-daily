// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Count Number of Teams
//
// https://leetcode.com/problems/count-number-of-teams/
//
// Question ID: 1395
// Difficult  : Medium
// Solve Date : 2024/07/29 18:02

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1395. Count Number of Teams|:
//
// There are |n| soldiers standing in a line. Each soldier is assigned a unique
// |rating| value. You have to form a team of 3 soldiers amongst them under the
// following rules:
//
//  • Choose 3 soldiers with index ( |i|, |j|, |k|) with rating ( |rating[i]|,
//  |rating[j]|, |rating[k]|).
//
//  • A team is valid if: ( |rating[i] < rating[j] < rating[k]|) or ( |rating[i]
//  > rating[j] > rating[k]|) where ( |0 <= i < j < k < n|).
// Return the number of teams you can form given the conditions. (soldiers can
// be part of multiple teams).
//
//

LEETCODE_BEGIN_RESOLVING(1395, CountNumberOfTeams, Solution);

class Solution {
public:
  int numTeams(vector<int> &rating) {
    int n   = rating.size();
    int res = 0;
    for (int i = 0; i < n - 1; ++i) {
      int l[2] = {0};
      int r[2] = {0};
      for (int j = 0; j < i; ++j) {
        l[rating[j] < rating[i]]++;
      }
      for (int k = i + 1; k < n; ++k) {
        r[rating[k] < rating[i]]++;
      }
      res += l[0] * r[1] + l[1] * r[0];
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |n == rating.length|
// * |3 <= n <= 1000|
// * |1 <= rating[i] <= 10⁵|
// * All the integers in |rating| are unique.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: rating = [2,5,3,4,1]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(1395, CountNumberOfTeams, example_1) {
  auto        solution = MakeSolution();
  vector<int> rating   = {2, 5, 3, 4, 1};
  int         expect   = 3;
  int         actual   = solution->numTeams(rating);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: rating = [2,1,3]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(1395, CountNumberOfTeams, example_2) {
  auto        solution = MakeSolution();
  vector<int> rating   = {2, 1, 3};
  int         expect   = 0;
  int         actual   = solution->numTeams(rating);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: rating = [1,2,3,4]
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(1395, CountNumberOfTeams, example_3) {
  auto        solution = MakeSolution();
  vector<int> rating   = {1, 2, 3, 4};
  int         expect   = 4;
  int         actual   = solution->numTeams(rating);
  LCD_EXPECT_EQ(expect, actual);
}

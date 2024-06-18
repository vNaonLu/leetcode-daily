// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Beautiful Arrangement II
//
// https://leetcode.com/problems/beautiful-arrangement-ii/
//
// Question ID: 667
// Difficult  : Medium
// Solve Date : 2024/06/15 13:04

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |667. Beautiful Arrangement II|:
//
// Given two integers |n| and |k|, construct a list |answer| that contains |n|
// different positive integers ranging from |1| to |n| and obeys the following
// requirement:
//
//  • Suppose this list is |answer = [a₁, a₂, a₃, ... , aₙ]|, then the list
//  |[|a₁ - a₂|, |a₂ - a₃|, |a₃ - a₄|, ... , |aₙ₋₁ - aₙ|]| has exactly |k|
//  distinct integers.
// Return the list |answer|. If there multiple valid answers, return any of
// them.
//
//

LEETCODE_BEGIN_RESOLVING(667, BeautifulArrangementII, Solution);

class Solution {
public:
  vector<int> constructArray(int n, int k) {
    vector<int> res(n);
    for (int i = 0, a = 1, z = k + 1; i <= k; ++i) {
      res[i] = i % 2 ? z-- : a++;
    }

    for (int i = k + 1; i < n; ++i) {
      res[i] = i + 1;
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= k < n <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 3, k = 1
// Output: [1,2,3]
// Explanation: The [1,2,3] has three different positive integers ranging from 1
// to 3, and the [1,1] has exactly 1 distinct integer: 1
//

LEETCODE_SOLUTION_UNITTEST(667, BeautifulArrangementII, example_1) {
  auto        solution = MakeSolution();
  int         n        = 3;
  int         k        = 1;
  vector<int> expect   = {1, 2, 3};
  vector<int> actual   = solution->constructArray(n, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 3, k = 2
// Output: [1,3,2]
// Explanation: The [1,3,2] has three different positive integers ranging from 1
// to 3, and the [2,1] has exactly 2 distinct integers: 1 and 2.
//

LEETCODE_SOLUTION_UNITTEST(667, BeautifulArrangementII, example_2) {
  auto        solution = MakeSolution();
  int         n        = 3;
  int         k        = 2;
  vector<int> expect   = {1, 3, 2};
  vector<int> actual   = solution->constructArray(n, k);
  LCD_EXPECT_EQ(expect, actual);
}

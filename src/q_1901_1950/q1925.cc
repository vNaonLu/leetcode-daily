// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Count Square Sum Triples
//
// https://leetcode.com/problems/count-square-sum-triples/
//
// Question ID: 1925
// Difficult  : Easy
// Solve Date : 2022/12/13 19:38

#include <iosfwd>
#include <set>
#include <unordered_set>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1925. Count Square Sum Triples|:
//
// A square triple |(a,b,c)| is a triple where |a|, |b|, and |c| are integers
// and |a² + b² = c²|. Given an integer |n|, return the number of square triples
// such that |1 <= a, b, c <= n|.
//

LEETCODE_BEGIN_RESOLVING(1925, CountSquareSumTriples, Solution);

class Solution {
public:
  int countTriples(int n) {
    auto memo = unordered_set<int>();
    auto res  = (int)0;
    for (int i = 1; i <= n; ++i) {
      memo.emplace(i * i);
    }
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= n; ++j) {
        if (i == j) {
          continue;
        }
        if (memo.count(i * i + j * j)) {
          ++res;
        }
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n <= 250|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 5
// Output: 2
//
// : The square triples are (3,4,5) and (4,3,5).

LEETCODE_SOLUTION_UNITTEST(1925, CountSquareSumTriples, example_1) {
  auto solution = MakeSolution();
  int  n        = 5;
  int  expect   = 2;
  int  actual   = solution->countTriples(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 10
// Output: 4
//
// : The square triples are (3,4,5), (4,3,5), (6,8,10), and (8,6,10).

LEETCODE_SOLUTION_UNITTEST(1925, CountSquareSumTriples, example_2) {
  auto solution = MakeSolution();
  int  n        = 10;
  int  expect   = 4;
  int  actual   = solution->countTriples(n);
  LCD_EXPECT_EQ(expect, actual);
}

// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Happy Number
//
// https://leetcode.com/problems/happy-number/
//
// Question ID: 202
// Difficult  : Easy
// Solve Date : 2021/10/09 14:21

#include <iosfwd>
#include <set>
#include <unordered_set>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |202. Happy Number|:
//
// Write an algorithm to determine if a number |n| is happy.
// A happy number is a number defined by the following process:
//
//  • Starting with any positive integer, replace the number by the sum of the
//  squares of its digits.
//
//  • Repeat the process until the number equals 1 (where it will stay), or it
//  loops endlessly in a cycle which does not include 1.
//
//  • Those numbers for which this process ends in 1 are happy.
// Return |true| if |n| is a happy number, and |false| if not.
//  
//

LEETCODE_BEGIN_RESOLVING(202, HappyNumber, Solution);

class Solution {
public:
  bool isHappy(int n) {
    auto memo = unordered_set<int>{n};
    while (n != 1) {
      auto x = n;
      n      = 0;
      while (x != 0) {
        n += (x % 10) * (x % 10);
        x /= 10;
      }
      if (!memo.emplace(n).second) {
        return false;
      }
    }
    return true;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n <= 2³¹ - 1|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 19
// Output: true
//
// 1² + 9² = 82
// 8² + 2² = 68
// 6² + 8² = 100
// 1² + 0² + 0² = 1

LEETCODE_SOLUTION_UNITTEST(202, HappyNumber, example_1) {
  auto solution = MakeSolution();
  int  n        = 19;
  bool expect   = true;
  bool actual   = solution->isHappy(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 2
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(202, HappyNumber, example_2) {
  auto solution = MakeSolution();
  int  n        = 2;
  bool expect   = false;
  bool actual   = solution->isHappy(n);
  LCD_EXPECT_EQ(expect, actual);
}

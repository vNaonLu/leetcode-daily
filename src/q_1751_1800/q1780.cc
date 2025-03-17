// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Check if Number is a Sum of Powers of Three
//
// https://leetcode.com/problems/check-if-number-is-a-sum-of-powers-of-three/
//
// Question ID: 1780
// Difficult  : Medium
// Solve Date : 2025/03/04 18:38

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1780. Check if Number is a Sum of Powers of Three|:
//
// Given an integer |n|, return |true| if it is possible to represent |n| as the
// sum of distinct powers of three. Otherwise, return |false|. An integer |y| is
// a power of three if there exists an integer |x| such that |y == 3ˣ|.
//
//

LEETCODE_BEGIN_RESOLVING(1780, CheckIfNumberIsASumOfPowersOfThree, Solution);

class Solution {
public:
  bool checkPowersOfThree(int n) {
    while (n > 0) {
      if (n % 3 == 2) {
        return false;
      }
      n /= 3;
    }
    return true;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n <= 10⁷|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 12
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(1780, CheckIfNumberIsASumOfPowersOfThree,
                           example_1) {
  auto solution = MakeSolution();
  int  n        = 12;
  bool expect   = true;
  bool actual   = solution->checkPowersOfThree(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 91
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(1780, CheckIfNumberIsASumOfPowersOfThree,
                           example_2) {
  auto solution = MakeSolution();
  int  n        = 91;
  bool expect   = true;
  bool actual   = solution->checkPowersOfThree(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: n = 21
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(1780, CheckIfNumberIsASumOfPowersOfThree,
                           example_3) {
  auto solution = MakeSolution();
  int  n        = 21;
  bool expect   = false;
  bool actual   = solution->checkPowersOfThree(n);
  LCD_EXPECT_EQ(expect, actual);
}

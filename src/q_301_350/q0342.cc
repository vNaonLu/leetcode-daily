// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Power of Four
//
// https://leetcode.com/problems/power-of-four/
//
// Question ID: 342
// Difficult  : Easy
// Solve Date : 2022/06/10 11:29

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |342. Power of Four|:
//
// Given an integer |n|, return |true| if it is a power of four. Otherwise,
// return |false|. An integer |n| is a power of four, if there exists an integer
// |x| such that |n == 4ˣ|.
//

LEETCODE_BEGIN_RESOLVING(342, PowerOfFour, Solution);

class Solution {
public:
  bool isPowerOfFour(int n) {
    while (n != 1) {
      if (n == 0 || n & 0b11) {
        return false;
      }

      n >>= 2;
    }

    return true;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |-2³¹ <= n <= 2³¹ - 1|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 16
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(342, PowerOfFour, example_1) {
  auto solution = MakeSolution();
  int  n        = 16;
  bool expect   = true;
  bool actual   = solution->isPowerOfFour(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 5
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(342, PowerOfFour, example_2) {
  auto solution = MakeSolution();
  int  n        = 5;
  bool expect   = false;
  bool actual   = solution->isPowerOfFour(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: n = 1
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(342, PowerOfFour, example_3) {
  auto solution = MakeSolution();
  int  n        = 1;
  bool expect   = true;
  bool actual   = solution->isPowerOfFour(n);
  LCD_EXPECT_EQ(expect, actual);
}

// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Power of Two
//
// https://leetcode.com/problems/power-of-two/
//
// Question ID: 231
// Difficult  : Easy
// Solve Date : 2021/09/17 08:00

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |231. Power of Two|:
//
// Given an integer |n|, return |true| if it is a power of two. Otherwise,
// return |false|. An integer |n| is a power of two, if there exists an integer
// |x| such that |n == 2ˣ|.  
//

LEETCODE_BEGIN_RESOLVING(231, PowerOfTwo, Solution);

class Solution {
public:
  bool isPowerOfTwo(int n) { return n > 0 && (n & (n - 1)) == 0; }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |-2³¹ <= n <= 2³¹ - 1|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 1
// Output: true
//
// 2⁰ = 1

LEETCODE_SOLUTION_UNITTEST(231, PowerOfTwo, example_1) {
  auto solution = MakeSolution();
  int  n        = 1;
  bool expect   = true;
  bool actual   = solution->isPowerOfTwo(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 16
// Output: true
//
// 2⁴ = 16

LEETCODE_SOLUTION_UNITTEST(231, PowerOfTwo, example_2) {
  auto solution = MakeSolution();
  int  n        = 16;
  bool expect   = true;
  bool actual   = solution->isPowerOfTwo(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: n = 3
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(231, PowerOfTwo, example_3) {
  auto solution = MakeSolution();
  int  n        = 3;
  bool expect   = false;
  bool actual   = solution->isPowerOfTwo(n);
  LCD_EXPECT_EQ(expect, actual);
}

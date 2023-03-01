// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Power of Three
//
// https://leetcode.com/problems/power-of-three/
//
// Question ID: 326
// Difficult  : Easy
// Solve Date : 2022/08/17 18:25

#include <cmath>
#include <iosfwd>
#include <limits>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |326. Power of Three|:
//
// Given an integer |n|, return |true| if it is a power of three. Otherwise,
// return |false|. An integer |n| is a power of three, if there exists an
// integer |x| such that |n == 3ˣ|.
//

LEETCODE_BEGIN_RESOLVING(326, PowerOfThree, Solution);

class Solution {
public:
  bool isPowerOfThree(int n) {
    auto max_log =
        decltype(n)(log10(numeric_limits<decltype(n)>::max()) / log10(3));
    auto maximum = (decltype(n))pow(3, max_log);

    return n > 0 && maximum % n == 0;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |-2³¹ <= n <= 2³¹ - 1|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 27
// Output: true
//
// 27 = 3³

LEETCODE_SOLUTION_UNITTEST(326, PowerOfThree, example_1) {
  auto solution = MakeSolution();
  int  n        = 27;
  bool expect   = true;
  bool actual   = solution->isPowerOfThree(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 0
// Output: false
//
// There is no x where 3ˣ = 0.

LEETCODE_SOLUTION_UNITTEST(326, PowerOfThree, example_2) {
  auto solution = MakeSolution();
  int  n        = 0;
  bool expect   = false;
  bool actual   = solution->isPowerOfThree(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: n = -1
// Output: false
//
// There is no x where 3ˣ = (-1).

LEETCODE_SOLUTION_UNITTEST(326, PowerOfThree, example_3) {
  auto solution = MakeSolution();
  int  n        = -1;
  bool expect   = false;
  bool actual   = solution->isPowerOfThree(n);
  LCD_EXPECT_EQ(expect, actual);
}

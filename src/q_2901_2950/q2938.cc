// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Separate Black and White Balls
//
// https://leetcode.com/problems/separate-black-and-white-balls/
//
// Question ID: 2938
// Difficult  : Medium
// Solve Date : 2024/10/15 21:22

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2938. Separate Black and White Balls|:
//
// There are |n| balls on a table, each ball has a color black or white.
// You are given a 0-indexed binary string |s| of length |n|, where |1| and |0|
// represent black and white balls, respectively. In each step, you can choose
// two adjacent balls and swap them. Return the minimum number of steps to group
// all the black balls to the right and all the white balls to the left.
//
//

LEETCODE_BEGIN_RESOLVING(2938, SeparateBlackAndWhiteBalls, Solution);

class Solution {
public:
  long long minimumSteps(string s) {
    int64_t res = 0;
    int     b   = 0;
    for (auto c : s) {
      if (c == '0') {
        res += 1ul * b;
      } else {
        ++b;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n == s.length <= 10⁵|
// * |s[i]| is either |'0'| or |'1'|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "101"
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(2938, SeparateBlackAndWhiteBalls, example_1) {
  auto      solution = MakeSolution();
  string    s        = "101";
  long long expect   = 1;
  long long actual   = solution->minimumSteps(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "100"
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(2938, SeparateBlackAndWhiteBalls, example_2) {
  auto      solution = MakeSolution();
  string    s        = "100";
  long long expect   = 2;
  long long actual   = solution->minimumSteps(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "0111"
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(2938, SeparateBlackAndWhiteBalls, example_3) {
  auto      solution = MakeSolution();
  string    s        = "0111";
  long long expect   = 0;
  long long actual   = solution->minimumSteps(s);
  LCD_EXPECT_EQ(expect, actual);
}

// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Magical String
//
// https://leetcode.com/problems/magical-string/
//
// Question ID: 481
// Difficult  : Medium
// Solve Date : 2024/04/18 21:07

#include <iosfwd>
#include <queue>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |481. Magical String|:
//
// A magical string |s| consists of only |'1'| and |'2'| and obeys the following
// rules:
//
//  • The string s is magical because concatenating the number of contiguous
//  occurrences of characters |'1'| and |'2'| generates the string |s| itself.
// The first few elements of |s| is |s = "1221121221221121122……"|. If we group
// the consecutive |1|'s and |2|'s in |s|, it will be |"1 22 11 2 1 22 1 22 11 2
// 11 22 ......"| and the occurrences of |1|'s or |2|'s in each group are |"1 2
// 2 1 1 2 1 2 2 1 2 2 ......"|. You can see that the occurrence sequence is |s|
// itself. Given an integer |n|, return the number of |1|'s in the first |n|
// number in the magical string |s|.
//
//

LEETCODE_BEGIN_RESOLVING(481, MagicalString, Solution);

class Solution {
public:
  int magicalString(int n) {
    queue<int> q;
    q.emplace(2);
    int res  = 1;
    int prev = 2;
    for (int i = 2; i < n; ++i) {
      int x = q.front();
      q.pop();
      if (x == 1) {
        ++res;
      }
      if (!q.empty()) {
        prev = q.back();
      }
      auto bk = prev == 2 ? 1 : 2;
      for (int j = 0; j < x; ++j) {
        q.emplace(bk);
      }
    }
    if (n == 0) {
      return 0;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 6
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(481, MagicalString, example_1) {
  auto solution = MakeSolution();
  int  n        = 6;
  int  expect   = 3;
  int  actual   = solution->magicalString(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 1
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(481, MagicalString, example_2) {
  auto solution = MakeSolution();
  int  n        = 1;
  int  expect   = 1;
  int  actual   = solution->magicalString(n);
  LCD_EXPECT_EQ(expect, actual);
}

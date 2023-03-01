// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Count and Say
//
// https://leetcode.com/problems/count-and-say/
//
// Question ID: 38
// Difficult  : Medium
// Solve Date : 2022/01/03 18:16

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |38. Count and Say|:
//
// The count-and-say sequence is a sequence of digit strings defined by the
// recursive formula:
//
//  • |countAndSay(1) = "1"|
//
//  • |countAndSay(n)| is the way you would "say" the digit string from
//  |countAndSay(n-1)|, which is then converted into a different digit string.
// To determine how you "say" a digit string, split it into the minimal number
// of substrings such that each substring contains exactly one unique digit.
// Then for each substring, say the number of digits, then say the digit.
// Finally, concatenate every said digit. For example, the saying and conversion
// for digit string |"3322251"|:
// ![img](https://assets.leetcode.com/uploads/2020/10/23/countandsay.jpg)
// Given a positive integer |n|, return the |nᵗʰ| term of the count-and-say
// sequence.  
//

LEETCODE_BEGIN_RESOLVING(38, CountAndSay, Solution);

class Solution {
public:
  string countAndSay(int n) {
    string res = "1";

    for (int i = 2; i <= n; ++i) {
      string next;
      char   cur   = res.front();
      size_t count = 1;
      for (int j = 1; j < res.size(); ++j) {
        if (cur == res[j]) {
          ++count;
        } else {
          next += to_string(count);
          next += cur;
          cur   = res[j];
          count = 1;
        }
      }
      next += to_string(count);
      next += cur;
      res = move(next);
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n <= 30|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 1
// Output: "1"
//
// This is the base case.

LEETCODE_SOLUTION_UNITTEST(38, CountAndSay, example_1) {
  auto   solution = MakeSolution();
  int    n        = 1;
  string expect   = "1";
  string actual   = solution->countAndSay(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 4
// Output: "1211"
//
// countAndSay(1) = "1"
// countAndSay(2) = say "1" = one 1 = "11"
// countAndSay(3) = say "11" = two 1's = "21"
// countAndSay(4) = say "21" = one 2 + one 1 = "12" + "11" = "1211"

LEETCODE_SOLUTION_UNITTEST(38, CountAndSay, example_2) {
  auto   solution = MakeSolution();
  int    n        = 4;
  string expect   = "1211";
  string actual   = solution->countAndSay(n);
  LCD_EXPECT_EQ(expect, actual);
}

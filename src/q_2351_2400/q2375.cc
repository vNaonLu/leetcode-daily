// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Construct Smallest Number From DI String
//
// https://leetcode.com/problems/construct-smallest-number-from-di-string/
//
// Question ID: 2375
// Difficult  : Medium
// Solve Date : 2025/02/18 19:27

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2375. Construct Smallest Number From DI String|:
//
// You are given a 0-indexed string |pattern| of length |n| consisting of the
// characters |'I'| meaning increasing and |'D'| meaning decreasing. A 0-indexed
// string |num| of length |n + 1| is created using the following conditions:
//
//  • |num| consists of the digits |'1'| to |'9'|, where each digit is used at
//  most once.
//
//  • If |pattern[i] == 'I'|, then |num[i] < num[i + 1]|.
//
//  • If |pattern[i] == 'D'|, then |num[i] > num[i + 1]|.
// Return the lexicographically smallest possible string |num| that meets the
// conditions.
//
//

LEETCODE_BEGIN_RESOLVING(2375, ConstructSmallestNumberFromDIString, Solution);

class Solution {
public:
  string smallestNumber(string pattern) {
    string res = "1";
    string tmp;
    for (int i = 0; i < pattern.size(); ++i) {
      if (pattern[i] == 'I') {
        res += tmp + char(i + '2');
        tmp = "";
      } else {
        tmp = char(res.back()) + tmp;
        res.pop_back();
        res += char(i + '2');
      }
    }
    return res + tmp;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= pattern.length <= 8|
// * |pattern| consists of only the letters |'I'| and |'D'|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: pattern = "IIIDIDDD"
// Output: "123549876"
// Explanation:
// At indices 0, 1, 2, and 4 we must have that num[i] < num[i+1].
// At indices 3, 5, 6, and 7 we must have that num[i] > num[i+1].
// Some possible values of num are "245639871", "135749862", and "123849765".
// It can be proven that "123549876" is the smallest possible num that meets the
// conditions. Note that "123414321" is not possible because the digit '1' is
// used more than once.
//

LEETCODE_SOLUTION_UNITTEST(2375, ConstructSmallestNumberFromDIString,
                           example_1) {
  auto   solution = MakeSolution();
  string pattern  = "IIIDIDDD";
  string expect   = "123549876";
  string actual   = solution->smallestNumber(pattern);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: pattern = "DDD"
// Output: "4321"
//

LEETCODE_SOLUTION_UNITTEST(2375, ConstructSmallestNumberFromDIString,
                           example_2) {
  auto   solution = MakeSolution();
  string pattern  = "DDD";
  string expect   = "4321";
  string actual   = solution->smallestNumber(pattern);
  LCD_EXPECT_EQ(expect, actual);
}

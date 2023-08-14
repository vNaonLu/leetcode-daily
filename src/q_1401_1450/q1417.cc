// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Reformat The String
//
// https://leetcode.com/problems/reformat-the-string/
//
// Question ID: 1417
// Difficult  : Easy
// Solve Date : 2023/08/12 14:06

#include <cctype>
#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1417. Reformat The String|:
//
// You are given an alphanumeric string |s|. (Alphanumeric string is a string
// consisting of lowercase English letters and digits). You have to find a
// permutation of the string where no letter is followed by another letter and
// no digit is followed by another digit. That is, no two adjacent characters
// have the same type. Return the reformatted string or return an empty string
// if it is impossible to reformat the string.
//
//

LEETCODE_BEGIN_RESOLVING(1417, ReformatTheString, Solution);

class Solution {
public:
  string reformat(string s) {
    vector<char> v1;
    vector<char> v2;
    string       res;
    for (auto c : s) {
      if (isdigit(c)) {
        v1.emplace_back(c);
      } else {
        v2.emplace_back(c);
      }
    }
    if (abs(int(v1.size() - v2.size())) > 1) {
      return "";
    }

    if (v1.size() < v2.size()) {
      v1.swap(v2);
    }

    while (!v1.empty() || !v2.empty()) {
      if (!v1.empty()) {
        res.push_back(v1.back());
        v1.pop_back();
      }
      if (!v2.empty()) {
        res.push_back(v2.back());
        v2.pop_back();
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 500|
// * |s| consists of only lowercase English letters and/or digits.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "a0b1c2"
// Output: "0a1b2c"
//
// No two adjacent characters have the same type in "0a1b2c". "a0b1c2",
// "0a1b2c", "0c2a1b" are also valid permutations.

LEETCODE_SOLUTION_UNITTEST(1417, ReformatTheString, example_1) {
  auto   solution = MakeSolution();
  string s        = "a0b1c2";
  string expect   = "2c1b0a";
  string actual   = solution->reformat(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "leetcode"
// Output: ""
//
// "leetcode" has only characters so we cannot separate them by digits.

LEETCODE_SOLUTION_UNITTEST(1417, ReformatTheString, example_2) {
  auto   solution = MakeSolution();
  string s        = "leetcode";
  string expect   = "";
  string actual   = solution->reformat(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "1229857369"
// Output: ""
//
// "1229857369" has only digits so we cannot separate them by characters.

LEETCODE_SOLUTION_UNITTEST(1417, ReformatTheString, example_3) {
  auto   solution = MakeSolution();
  string s        = "1229857369";
  string expect   = "";
  string actual   = solution->reformat(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: "covid2019"
// Output: "c2o0v1i9d"
//

LEETCODE_SOLUTION_UNITTEST(1417, ReformatTheString, extra_testcase_1) {
  auto   solution = MakeSolution();
  string s        = "covid2019";
  string expect   = "d9i1v0o2c";
  string actual   = solution->reformat(s);
  LCD_EXPECT_EQ(expect, actual);
}

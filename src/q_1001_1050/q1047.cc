// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Remove All Adjacent Duplicates In String
//
// https://leetcode.com/problems/remove-all-adjacent-duplicates-in-string/
//
// Question ID: 1047
// Difficult  : Easy
// Solve Date : 2022/11/10 18:12

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1047. Remove All Adjacent Duplicates In String|:
//
// You are given a string |s| consisting of lowercase English letters. A
// duplicate removal consists of choosing two adjacent and equal letters and
// removing them. We repeatedly make duplicate removals on |s| until we no
// longer can. Return the final string after all such duplicate removals have
// been made. It can be proven that the answer is unique.
//

LEETCODE_BEGIN_RESOLVING(1047, RemoveAllAdjacentDuplicatesInString, Solution);

class Solution {
public:
  string removeDuplicates(string s) {
    auto res = string("");
    res.reserve(s.size());
    for (auto c : s) {
      if (res.empty() || res.back() != c) {
        res.push_back(c);
      } else {
        res.pop_back();
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 10⁵|
// * |s| consists of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "abbaca"
// Output: "ca"
//
// For example, in "abbaca" we could remove "bb" since the letters are adjacent
// and equal, and this is the only possible move. The result of this move is
// that the string is "aaca", of which only "aa" is possible, so the final
// string is "ca".

LEETCODE_SOLUTION_UNITTEST(1047, RemoveAllAdjacentDuplicatesInString,
                           example_1) {
  auto   solution = MakeSolution();
  string s        = "abbaca";
  string expect   = "ca";
  string actual   = solution->removeDuplicates(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "azxxzy"
// Output: "ay"
//

LEETCODE_SOLUTION_UNITTEST(1047, RemoveAllAdjacentDuplicatesInString,
                           example_2) {
  auto   solution = MakeSolution();
  string s        = "azxxzy";
  string expect   = "ay";
  string actual   = solution->removeDuplicates(s);
  LCD_EXPECT_EQ(expect, actual);
}

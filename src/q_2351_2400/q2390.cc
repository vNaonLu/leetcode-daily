// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Removing Stars From a String
//
// https://leetcode.com/problems/removing-stars-from-a-string/
//
// Question ID: 2390
// Difficult  : Medium
// Solve Date : 2023/04/11 10:18

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2390. Removing Stars From a String|:
//
// You are given a string |s|, which contains stars |*|.
// In one operation, you can:
//
//  • Choose a star in |s|.
//
//  • Remove the closest non-star character to its left, as well as remove the
//  star itself.
// Return the string after all stars have been removed.
// Note:
//
//  • The input will be generated such that the operation is always possible.
//
//  • It can be shown that the resulting string will always be unique.
//
//

LEETCODE_BEGIN_RESOLVING(2390, RemovingStarsFromAString, Solution);

class Solution {
public:
  string removeStars(string s) {
    string res = "";
    for (auto c : s) {
      if (c == '*') {
        res.pop_back();
      } else {
        res.push_back(c);
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
// * |s| consists of lowercase English letters and stars |*|.
// * The operation above can be performed on |s|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "leet**cod*e"
// Output: "lecoe"
//
// Performing the removals from left to right:
// - The closest character to the 1ˢᵗ star is 't' in "leet**cod*e". s becomes
// "lee*cod*e".
// - The closest character to the 2ⁿᵈ star is 'e' in "lee*cod*e". s becomes
// "lecod*e".
// - The closest character to the 3ʳᵈ star is 'd' in "lecod*e". s becomes
// "lecoe". There are no more stars, so we return "lecoe".

LEETCODE_SOLUTION_UNITTEST(2390, RemovingStarsFromAString, example_1) {
  auto   solution = MakeSolution();
  string s        = "leet**cod*e";
  string expect   = "lecoe";
  string actual   = solution->removeStars(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "erase*****"
// Output: ""
//
// The entire string is removed, so we return an empty string.

LEETCODE_SOLUTION_UNITTEST(2390, RemovingStarsFromAString, example_2) {
  auto   solution = MakeSolution();
  string s        = "erase*****";
  string expect   = "";
  string actual   = solution->removeStars(s);
  LCD_EXPECT_EQ(expect, actual);
}

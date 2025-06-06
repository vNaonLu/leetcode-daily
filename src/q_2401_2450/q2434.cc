// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Using a Robot to Print the Lexicographically Smallest String
//
// https://leetcode.com/problems/using-a-robot-to-print-the-lexicographically-smallest-string/
//
// Question ID: 2434
// Difficult  : Medium
// Solve Date : 2025/06/06 12:24

#include <iosfwd>
#include <string>
#include <unordered_map>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2434. Using a Robot to Print the Lexicographically Smallest
// String|:
//
// You are given a string |s| and a robot that currently holds an empty string
// |t|. Apply one of the following operations until |s| and |t| are both empty:
//
//  • Remove the first character of a string |s| and give it to the robot. The
//  robot will append this character to the string |t|.
//
//  • Remove the last character of a string |t| and give it to the robot. The
//  robot will write this character on paper.
// Return the lexicographically smallest string that can be written on the
// paper.
//
//

LEETCODE_BEGIN_RESOLVING(2434,
                         UsingARobotToPrintTheLexicographicallySmallestString,
                         Solution);

class Solution {
public:
  string robotWithString(string s) {
    string                   res;
    string                   t;
    unordered_map<char, int> freq;
    for (auto c : s) {
      ++freq[c];
    }
    char sml = 'a';
    for (char c : s) {
      if (c == sml) {
        res += c;
      } else {
        t.push_back(c);
      }
      if (--freq[c] == 0) {
        freq.erase(c);
      }

      while (sml <= 'z' && freq.count(sml) == 0) {
        sml++;
      }

      while (!t.empty() && t.back() <= sml) {
        res += t.back();
        t.pop_back();
      }
    }

    while (!t.empty()) {
      res += t.back();
      t.pop_back();
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 10⁵|
// * |s| consists of only English lowercase letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "zza"
// Output: "azz"
//

LEETCODE_SOLUTION_UNITTEST(2434,
                           UsingARobotToPrintTheLexicographicallySmallestString,
                           example_1) {
  auto   solution = MakeSolution();
  string s        = "zza";
  string expect   = "azz";
  string actual   = solution->robotWithString(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "bac"
// Output: "abc"
//

LEETCODE_SOLUTION_UNITTEST(2434,
                           UsingARobotToPrintTheLexicographicallySmallestString,
                           example_2) {
  auto   solution = MakeSolution();
  string s        = "bac";
  string expect   = "abc";
  string actual   = solution->robotWithString(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "bdda"
// Output: "addb"
//

LEETCODE_SOLUTION_UNITTEST(2434,
                           UsingARobotToPrintTheLexicographicallySmallestString,
                           example_3) {
  auto   solution = MakeSolution();
  string s        = "bdda";
  string expect   = "addb";
  string actual   = solution->robotWithString(s);
  LCD_EXPECT_EQ(expect, actual);
}

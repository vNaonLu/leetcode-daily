// Copyright 2026 Naon Lu
//
// This file describes the solution of
// Check if Strings Can be Made Equal With Operations II
//
// https://leetcode.com/problems/check-if-strings-can-be-made-equal-with-operations-ii/
//
// Question ID: 2840
// Difficult  : Medium
// Solve Date : 2026/03/30 19:06

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2840. Check if Strings Can be Made Equal With Operations II|:
//
// You are given two strings |s1| and |s2|, both of length |n|, consisting of
// lowercase English letters. You can apply the following operation on any of
// the two strings any number of times:
//
//  • Choose any two indices |i| and |j| such that |i < j| and the difference |j
//  - i| is even, then swap the two characters at those indices in the string.
// Return |true| if you can make the strings |s1| and |s2| equal, and |false|
// otherwise.
//
//

LEETCODE_BEGIN_RESOLVING(2840, CheckIfStringsCanBeMadeEqualWithOperationsII,
                         Solution);

class Solution {
public:
  bool checkStrings(string s1, string s2) {
    int freq[52] = {};

    for (int i = 0; i < s1.length(); i++) {
      int off = (i & 1) * 26;
      freq[s1[i] - 'a' + off]++;
      freq[s2[i] - 'a' + off]--;
    }

    for (int i = 0; i < 52; i++)
      if (freq[i] != 0)
        return false;

    return true;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |n == s1.length == s2.length|
// * |1 <= n <= 10⁵|
// * |s1| and |s2| consist only of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s1 = "abcdba", s2 = "cabdab"
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(2840, CheckIfStringsCanBeMadeEqualWithOperationsII,
                           example_1) {
  auto   solution = MakeSolution();
  string s1       = "abcdba";
  string s2       = "cabdab";
  bool   expect   = true;
  bool   actual   = solution->checkStrings(s1, s2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s1 = "abe", s2 = "bea"
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(2840, CheckIfStringsCanBeMadeEqualWithOperationsII,
                           example_2) {
  auto   solution = MakeSolution();
  string s1       = "abe";
  string s2       = "bea";
  bool   expect   = false;
  bool   actual   = solution->checkStrings(s1, s2);
  LCD_EXPECT_EQ(expect, actual);
}

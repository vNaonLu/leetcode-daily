// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Find the Encrypted String
//
// https://leetcode.com/problems/find-the-encrypted-string/
//
// Question ID: 3210
// Difficult  : Easy
// Solve Date : 2024/07/19 22:17

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3210. Find the Encrypted String|:
//
// You are given a string |s| and an integer |k|. Encrypt the string using the
// following algorithm:
//
//  • For each character |c| in |s|, replace |c| with the |kᵗʰ| character after
//  |c| in the string (in a cyclic manner).
// Return the encrypted string.
//
//

LEETCODE_BEGIN_RESOLVING(3210, FindTheEncryptedString, Solution);

class Solution {
public:
  string getEncryptedString(string s, int k) {
    return s.substr(k % s.size()) + s.substr(0, k % s.size());
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 100|
// * |1 <= k <= 10⁴|
// * |s| consists only of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "dart", k = 3
// Output: "tdar"
//

LEETCODE_SOLUTION_UNITTEST(3210, FindTheEncryptedString, example_1) {
  auto   solution = MakeSolution();
  string s        = "dart";
  int    k        = 3;
  string expect   = "tdar";
  string actual   = solution->getEncryptedString(s, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "aaa", k = 1
// Output: "aaa"
//

LEETCODE_SOLUTION_UNITTEST(3210, FindTheEncryptedString, example_2) {
  auto   solution = MakeSolution();
  string s        = "aaa";
  int    k        = 1;
  string expect   = "aaa";
  string actual   = solution->getEncryptedString(s, k);
  LCD_EXPECT_EQ(expect, actual);
}

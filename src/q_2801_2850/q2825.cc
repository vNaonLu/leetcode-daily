// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Make String a Subsequence Using Cyclic Increments
//
// https://leetcode.com/problems/make-string-a-subsequence-using-cyclic-increments/
//
// Question ID: 2825
// Difficult  : Medium
// Solve Date : 2024/12/04 19:55

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2825. Make String a Subsequence Using Cyclic Increments|:
//
// You are given two 0-indexed strings |str1| and |str2|.
// In an operation, you select a set of indices in |str1|, and for each index
// |i| in the set, increment |str1[i]| to the next character cyclically. That is
// |'a'| becomes |'b'|, |'b'| becomes |'c'|, and so on, and |'z'| becomes |'a'|.
// Return |true| if it is possible to make |str2| a subsequence of |str1| by
// performing the operation at most once, and |false| otherwise. Note: A
// subsequence of a string is a new string that is formed from the original
// string by deleting some (possibly none) of the characters without disturbing
// the relative positions of the remaining characters.
//
//

LEETCODE_BEGIN_RESOLVING(2825, MakeStringASubsequenceUsingCyclicIncrements,
                         Solution);

class Solution {
public:
  bool canMakeSubsequence(string str1, string str2) {
    int target_idx = 0;
    int target_len = str2.size();
    for (auto c : str1) {
      if (target_idx < target_len && (str2[target_idx] - c + 26) % 26 <= 1) {
        ++target_idx;
      }
    }
    return target_idx == target_len;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= str1.length <= 10⁵|
// * |1 <= str2.length <= 10⁵|
// * |str1| and |str2| consist of only lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: str1 = "abc", str2 = "ad"
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(2825, MakeStringASubsequenceUsingCyclicIncrements,
                           example_1) {
  auto   solution = MakeSolution();
  string str1     = "abc";
  string str2     = "ad";
  bool   expect   = true;
  bool   actual   = solution->canMakeSubsequence(str1, str2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: str1 = "zc", str2 = "ad"
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(2825, MakeStringASubsequenceUsingCyclicIncrements,
                           example_2) {
  auto   solution = MakeSolution();
  string str1     = "zc";
  string str2     = "ad";
  bool   expect   = true;
  bool   actual   = solution->canMakeSubsequence(str1, str2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: str1 = "ab", str2 = "d"
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(2825, MakeStringASubsequenceUsingCyclicIncrements,
                           example_3) {
  auto   solution = MakeSolution();
  string str1     = "ab";
  string str2     = "d";
  bool   expect   = false;
  bool   actual   = solution->canMakeSubsequence(str1, str2);
  LCD_EXPECT_EQ(expect, actual);
}

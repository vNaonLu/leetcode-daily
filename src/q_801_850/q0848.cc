// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Shifting Letters
//
// https://leetcode.com/problems/shifting-letters/
//
// Question ID: 848
// Difficult  : Medium
// Solve Date : 2021/09/08 08:00

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |848. Shifting Letters|:
//
// You are given a string |s| of lowercase English letters and an integer array
// |shifts| of the same length. Call the |shift()| of a letter, the next letter
// in the alphabet, (wrapping around so that |'z'| becomes |'a'|).
//
//  • For example, |shift('a') = 'b'|, |shift('t') = 'u'|, and |shift('z') =
//  'a'|.
// Now for each |shifts[i] = x|, we want to shift the first |i + 1| letters of
// |s|, |x| times. Return the final string after all such shifts to s are
// applied.  
//

LEETCODE_BEGIN_RESOLVING(848, ShiftingLetters, Solution);

class Solution {
public:
  string shiftingLetters(string s, vector<int> &shifts) {
    for (auto it = shifts.rbegin(); it != shifts.rend(); ++it) {
      if (it == shifts.rbegin())
        *it %= 26;
      else
        *it = (*it + *(it - 1)) % 26;
    }
    for (int i = 0; i < shifts.size(); ++i) {
      s[i] = (s[i] - 'a' + shifts[i]) % 26 + 'a';
    }
    return s;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 10⁵|
// * |s| consists of lowercase English letters.
// * |shifts.length == s.length|
// * |0 <= shifts[i] <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "abc", shifts = [3,5,9]
// Output: "rpl"
//
// We start with "abc".
// After shifting the first 1 letters of s by 3, we have "dbc".
// After shifting the first 2 letters of s by 5, we have "igc".
// After shifting the first 3 letters of s by 9, we have "rpl", the answer.

LEETCODE_SOLUTION_UNITTEST(848, ShiftingLetters, example_1) {
  auto        solution = MakeSolution();
  string      s        = "abc";
  vector<int> shifts   = {3, 5, 9};
  string      expect   = "rpl";
  string      actual   = solution->shiftingLetters(s, shifts);
  EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "aaa", shifts = [1,2,3]
// Output: "gfd"
//

LEETCODE_SOLUTION_UNITTEST(848, ShiftingLetters, example_2) {
  auto        solution = MakeSolution();
  string      s        = "aaa";
  vector<int> shifts   = {1, 2, 3};
  string      expect   = "gfd";
  string      actual   = solution->shiftingLetters(s, shifts);
  EXPECT_EQ(expect, actual);
}

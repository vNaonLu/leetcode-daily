// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Decoded String at Index
//
// https://leetcode.com/problems/decoded-string-at-index/
//
// Question ID: 880
// Difficult  : Medium
// Solve Date : 2023/09/27 20:30

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |880. Decoded String at Index|:
//
// You are given an encoded string |s|. To decode the string to a tape, the
// encoded string is read one character at a time and the following steps are
// taken:
//
//  • If the character read is a letter, that letter is written onto the tape.
//
//  • If the character read is a digit |d|, the entire current tape is
//  repeatedly written |d - 1| more times in total.
// Given an integer |k|, return the |kᵗʰ| letter (1-indexed) in the decoded
// string.
//
//

LEETCODE_BEGIN_RESOLVING(880, DecodedStringAtIndex, Solution);

class Solution {
public:
  string decodeAtIndex(string s, int k) {
    int64_t decoded = 0;
    for (auto c : s) {
      if (isdigit(c)) {
        decoded *= c - '0';
      } else {
        ++decoded;
      }
    }

    for (int i = s.size() - 1; i >= 0; --i) {
      if (isdigit(s[i])) {
        decoded /= (s[i] - '0');
        k = k % decoded;
      } else {
        if (k == 0 || decoded == k) {
          return string("") + s[i];
        }
        --decoded;
      }
    }
    return "";
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= s.length <= 100|
// * |s| consists of lowercase English letters and digits |2| through |9|.
// * |s| starts with a letter.
// * |1 <= k <= 10⁹|
// * It is guaranteed that |k| is less than or equal to the length of the
// decoded string.
// * The decoded string is guaranteed to have less than |2⁶³| letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "leet2code3", k = 10
// Output: "o"
//
// The decoded string is "leetleetcodeleetleetcodeleetleetcode".
// The 10ᵗʰ letter in the string is "o".

LEETCODE_SOLUTION_UNITTEST(880, DecodedStringAtIndex, example_1) {
  auto   solution = MakeSolution();
  string s        = "leet2code3";
  int    k        = 10;
  string expect   = "o";
  string actual   = solution->decodeAtIndex(s, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "ha22", k = 5
// Output: "h"
//
// The decoded string is "hahahaha".
// The 5ᵗʰ letter is "h".

LEETCODE_SOLUTION_UNITTEST(880, DecodedStringAtIndex, example_2) {
  auto   solution = MakeSolution();
  string s        = "ha22";
  int    k        = 5;
  string expect   = "h";
  string actual   = solution->decodeAtIndex(s, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "a2345678999999999999999", k = 1
// Output: "a"
//
// The decoded string is "a" repeated 8301530446056247680 times.
// The 1ˢᵗ letter is "a".

LEETCODE_SOLUTION_UNITTEST(880, DecodedStringAtIndex, example_3) {
  auto   solution = MakeSolution();
  string s        = "a2345678999999999999999";
  int    k        = 1;
  string expect   = "a";
  string actual   = solution->decodeAtIndex(s, k);
  LCD_EXPECT_EQ(expect, actual);
}

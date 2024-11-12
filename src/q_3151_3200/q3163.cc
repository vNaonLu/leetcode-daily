// Copyright 2024 Naon Lu
//
// This file describes the solution of
// String Compression III
//
// https://leetcode.com/problems/string-compression-iii/
//
// Question ID: 3163
// Difficult  : Medium
// Solve Date : 2024/11/04 23:07

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3163. String Compression III|:
//
// Given a string |word|, compress it using the following algorithm:
//
//  • Begin with an empty string |comp|. While |word| is not empty, use the
//  following operation:
//
//
//    • Remove a maximum length prefix of |word| made of a single character |c|
//    repeating at most 9 times.
//
//    • Append the length of the prefix followed by |c| to |comp|.
//
//
// Return the string |comp|.
//
//

LEETCODE_BEGIN_RESOLVING(3163, StringCompressionIII, Solution);

class Solution {
public:
  string compressedString(string word) {
    string res;
    int    cnt = 1;
    int    n   = word.size();
    char   ch  = word[0];
    for (int i = 1; i < n; ++i) {
      if (word[i] == ch && cnt < 9) {
        ++cnt;
      } else {
        res += cnt + '0';
        res += ch;
        ch  = word[i];
        cnt = 1;
      }
    }
    res += cnt + '0';
    res += ch;
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= word.length <= 2 * 10⁵|
// * |word| consists only of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: word = "abcde"
// Output: "1a1b1c1d1e"
//

LEETCODE_SOLUTION_UNITTEST(3163, StringCompressionIII, example_1) {
  auto   solution = MakeSolution();
  string word     = "abcde";
  string expect   = "1a1b1c1d1e";
  string actual   = solution->compressedString(word);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: word = "aaaaaaaaaaaaaabb"
// Output: "9a5a2b"
//

LEETCODE_SOLUTION_UNITTEST(3163, StringCompressionIII, example_2) {
  auto   solution = MakeSolution();
  string word     = "aaaaaaaaaaaaaabb";
  string expect   = "9a5a2b";
  string actual   = solution->compressedString(word);
  LCD_EXPECT_EQ(expect, actual);
}

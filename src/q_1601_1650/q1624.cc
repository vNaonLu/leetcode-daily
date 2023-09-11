// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Largest Substring Between Two Equal Characters
//
// https://leetcode.com/problems/largest-substring-between-two-equal-characters/
//
// Question ID: 1624
// Difficult  : Easy
// Solve Date : 2023/09/03 09:08

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1624. Largest Substring Between Two Equal Characters|:
//
// Given a string |s|, return the length of the longest substring between two
// equal characters, excluding the two characters. If there is no such substring
// return |-1|. A substring is a contiguous sequence of characters within a
// string.
//
//

LEETCODE_BEGIN_RESOLVING(1624, LargestSubstringBetweenTwoEqualCharacters,
                         Solution);

class Solution {
public:
  int maxLengthBetweenEqualCharacters(string s) {
    vector<int> last(26, -1);
    int         res = -1;
    for (int i = 0; i < s.size(); ++i) {
      if (last[s[i] - 'a'] != -1) {
        res = max(res, i - last[s[i] - 'a'] - 1);
      } else {
        last[s[i] - 'a'] = i;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 300|
// * |s| contains only lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "aa"
// Output: 0
//
// The optimal substring here is an empty substring between the two |'a's|.

LEETCODE_SOLUTION_UNITTEST(1624, LargestSubstringBetweenTwoEqualCharacters,
                           example_1) {
  auto   solution = MakeSolution();
  string s        = "aa";
  int    expect   = 0;
  int    actual   = solution->maxLengthBetweenEqualCharacters(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "abca"
// Output: 2
//
// The optimal substring here is "bc".

LEETCODE_SOLUTION_UNITTEST(1624, LargestSubstringBetweenTwoEqualCharacters,
                           example_2) {
  auto   solution = MakeSolution();
  string s        = "abca";
  int    expect   = 2;
  int    actual   = solution->maxLengthBetweenEqualCharacters(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "cbzxy"
// Output: -1
//
// There are no characters that appear twice in s.

LEETCODE_SOLUTION_UNITTEST(1624, LargestSubstringBetweenTwoEqualCharacters,
                           example_3) {
  auto   solution = MakeSolution();
  string s        = "cbzxy";
  int    expect   = -1;
  int    actual   = solution->maxLengthBetweenEqualCharacters(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: "mgntdygtxrvxjnwksqhxuxtrv"
// Output: 18
//

LEETCODE_SOLUTION_UNITTEST(1624, LargestSubstringBetweenTwoEqualCharacters,
                           extra_testcase_1) {
  auto   solution = MakeSolution();
  string s        = "mgntdygtxrvxjnwksqhxuxtrv";
  int    expect   = 18;
  int    actual   = solution->maxLengthBetweenEqualCharacters(s);
  LCD_EXPECT_EQ(expect, actual);
}

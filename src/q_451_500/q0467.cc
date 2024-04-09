// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Unique Substrings in Wraparound String
//
// https://leetcode.com/problems/unique-substrings-in-wraparound-string/
//
// Question ID: 467
// Difficult  : Medium
// Solve Date : 2024/04/09 22:07

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |467. Unique Substrings in Wraparound String|:
//
// We define the string |base| to be the infinite wraparound string of
// |"abcdefghijklmnopqrstuvwxyz"|, so |base| will look like this:
//
//  • |"...zabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcd...."|.
// Given a string |s|, return the number of unique non-empty substrings of |s|
// are present in |base|.
//
//

LEETCODE_BEGIN_RESOLVING(467, UniqueSubstringsInWraparoundString, Solution);

class Solution {
public:
  int findSubstringInWraproundString(string s) {
    int         res  = 1;
    int         prev = 1;
    vector<int> arr(26, 0);
    arr[s[0] - 'a'] = 1;
    for (int i = 1; i < s.size(); ++i) {
      if ((s[i - 1] - 'a' + 1) % 26 == s[i] - 'a') {
        ++prev;
      } else {
        prev = 1;
      }

      if (arr[s[i] - 'a'] < prev) {
        res += prev - arr[s[i] - 'a'];
        arr[s[i] - 'a'] = prev;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 10⁵|
// * |s| consists of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "a"
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(467, UniqueSubstringsInWraparoundString, example_1) {
  auto   solution = MakeSolution();
  string s        = "a";
  int    expect   = 1;
  int    actual   = solution->findSubstringInWraproundString(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "cac"
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(467, UniqueSubstringsInWraparoundString, example_2) {
  auto   solution = MakeSolution();
  string s        = "cac";
  int    expect   = 2;
  int    actual   = solution->findSubstringInWraproundString(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "zab"
// Output: 6
//

LEETCODE_SOLUTION_UNITTEST(467, UniqueSubstringsInWraparoundString, example_3) {
  auto   solution = MakeSolution();
  string s        = "zab";
  int    expect   = 6;
  int    actual   = solution->findSubstringInWraproundString(s);
  LCD_EXPECT_EQ(expect, actual);
}

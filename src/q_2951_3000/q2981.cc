// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Find Longest Special Substring That Occurs Thrice I
//
// https://leetcode.com/problems/find-longest-special-substring-that-occurs-thrice-i/
//
// Question ID: 2981
// Difficult  : Medium
// Solve Date : 2024/12/10 20:31

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2981. Find Longest Special Substring That Occurs Thrice I|:
//
// You are given a string |s| that consists of lowercase English letters.
// A string is called special if it is made up of only a single character. For
// example, the string |"abc"| is not special, whereas the strings |"ddd"|,
// |"zz"|, and |"f"| are special. Return the length of the longest special
// substring of |s| which occurs at least thrice, or |-1| if no special
// substring occurs at least thrice. A substring is a contiguous non-empty
// sequence of characters within a string.
//
//

LEETCODE_BEGIN_RESOLVING(2981, FindLongestSpecialSubstringThatOccursThriceI,
                         Solution);

class Solution {
public:
  int maximumLength(string s) {
    int n = s.size();
    int l = 1;
    int r = n;
    if (!helper(s, n, 1)) {
      return -1;
    }

    while (l + 1 < r) {
      int m = l + (r - l) / 2;
      if (helper(s, n, m)) {
        l = m;
      } else {
        r = m;
      }
    }

    return l;
  }

private:
  bool helper(string const &s, int n, int x) {
    vector<int> cnt(26);
    int         p = 0;
    for (int i = 0; i < n; ++i) {
      while (s[p] != s[i]) {
        ++p;
      }

      if (i - p + 1 >= x) {
        ++cnt[s[i] - 'a'];
      }

      if (cnt[s[i] - 'a'] > 2) {
        return true;
      }
    }
    return false;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |3 <= s.length <= 50|
// * |s| consists of only lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "aaaa"
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(2981, FindLongestSpecialSubstringThatOccursThriceI,
                           example_1) {
  auto   solution = MakeSolution();
  string s        = "aaaa";
  int    expect   = 2;
  int    actual   = solution->maximumLength(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "abcdef"
// Output: -1
//

LEETCODE_SOLUTION_UNITTEST(2981, FindLongestSpecialSubstringThatOccursThriceI,
                           example_2) {
  auto   solution = MakeSolution();
  string s        = "abcdef";
  int    expect   = -1;
  int    actual   = solution->maximumLength(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "abcaba"
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(2981, FindLongestSpecialSubstringThatOccursThriceI,
                           example_3) {
  auto   solution = MakeSolution();
  string s        = "abcaba";
  int    expect   = 1;
  int    actual   = solution->maximumLength(s);
  LCD_EXPECT_EQ(expect, actual);
}

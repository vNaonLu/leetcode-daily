// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Substring With Largest Variance
//
// https://leetcode.com/problems/substring-with-largest-variance/
//
// Question ID: 2272
// Difficult  : Hard
// Solve Date : 2023/07/09 12:43

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2272. Substring With Largest Variance|:
//
// The variance of a string is defined as the largest difference between the
// number of occurrences of any |2| characters present in the string. Note the
// two characters may or may not be the same. Given a string |s| consisting of
// lowercase English letters only, return the largest variance possible among
// all substrings of |s|. A substring is a contiguous sequence of characters
// within a string.
//
//

LEETCODE_BEGIN_RESOLVING(2272, SubstringWithLargestVariance, Solution);

class Solution {
public:
  int largestVariance(string s) {
    int         res = 0;
    vector<int> freq(26);
    for (auto c : s) {
      ++freq[c - 'a'];
    }

    for (auto i = 'a'; i <= 'z'; ++i) {
      for (auto j = 'a'; j <= 'z'; ++j) {
        if (i == j || freq[i - 'a'] == 0 || freq[j - 'a'] == 0) {
          continue;
        }

        helper(s.begin(), s.end(), i, j, &res);
        helper(s.rbegin(), s.rend(), i, j, &res);
      }
    }

    return res;
  }

private:
  template <typename It>
  void helper(It beg, It end, char x, char y, int *res) {
    int a1 = 0;
    int a2 = 0;
    while (beg != end) {
      if (*beg == x) {
        ++a1;
      }
      if (*beg == y) {
        ++a2;
      }
      if (a2 > a1) {
        a1 = 0;
        a2 = 0;
      }
      if (a1 > 0 && a2 > 0) {
        *res = max(*res, a1 - a2);
      }
      ++beg;
    }
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 10⁴|
// * |s| consists of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "aababbb"
// Output: 3
//
// All possible variances along with their respective substrings are listed
// below:
// - Variance 0 for substrings "a", "aa", "ab", "abab", "aababb", "ba", "b",
// "bb", and "bbb".
// - Variance 1 for substrings "aab", "aba", "abb", "aabab", "ababb", "aababbb",
// and "bab".
// - Variance 2 for substrings "aaba", "ababbb", "abbb", and "babb".
// - Variance 3 for substring "babbb".
// Since the largest possible variance is 3, we return it.

LEETCODE_SOLUTION_UNITTEST(2272, SubstringWithLargestVariance, example_1) {
  auto   solution = MakeSolution();
  string s        = "aababbb";
  int    expect   = 3;
  int    actual   = solution->largestVariance(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "abcde"
// Output: 0
//
// No letter occurs more than once in s, so the variance of every substring is
// 0.

LEETCODE_SOLUTION_UNITTEST(2272, SubstringWithLargestVariance, example_2) {
  auto   solution = MakeSolution();
  string s        = "abcde";
  int    expect   = 0;
  int    actual   = solution->largestVariance(s);
  LCD_EXPECT_EQ(expect, actual);
}

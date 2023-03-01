// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Shortest Palindrome
//
// https://leetcode.com/problems/shortest-palindrome/
//
// Question ID: 214
// Difficult  : Hard
// Solve Date : 2022/09/29 17:28

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |214. Shortest Palindrome|:
//
// You are given a string |s|. You can convert |s| to a palindrome by adding
// characters in front of it. Return the shortest palindrome you can find by
// performing this transformation.
//

LEETCODE_BEGIN_RESOLVING(214, ShortestPalindrome, Solution);

class Solution {
public:
  string shortestPalindrome(string s) {
    auto n   = s.size();
    auto rev = string(s);
    reverse(rev.begin(), rev.end());
    auto str = s + "#" + rev;
    auto ns  = str.size();
    auto nxt = vector<int>(ns, 0);
    for (auto i = 1; i < ns; ++i) {
      auto t = nxt[i - 1];
      while (t > 0 && str[i] != s[t]) {
        t = nxt[t - 1];
      }
      if (str[i] == str[t]) {
        ++t;
      }
      nxt[i] = t;
    }
    return rev.substr(0, n - nxt.back()) + s;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |0 <= s.length <= 5 * 10⁴|
// * |s| consists of lowercase English letters only.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "aacecaaa"
// Output: "aaacecaaa"
//

LEETCODE_SOLUTION_UNITTEST(214, ShortestPalindrome, example_1) {
  auto   solution = MakeSolution();
  string s        = "aacecaaa";
  string expect   = "aaacecaaa";
  string actual   = solution->shortestPalindrome(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "abcd"
// Output: "dcbabcd"
//

LEETCODE_SOLUTION_UNITTEST(214, ShortestPalindrome, example_2) {
  auto   solution = MakeSolution();
  string s        = "abcd";
  string expect   = "dcbabcd";
  string actual   = solution->shortestPalindrome(s);
  LCD_EXPECT_EQ(expect, actual);
}

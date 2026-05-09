// Copyright 2026 Naon Lu
//
// This file describes the solution of
// Longest Balanced Substring II
//
// https://leetcode.com/problems/longest-balanced-substring-ii/
//
// Question ID: 3714
// Difficult  : Medium
// Solve Date : 2026/02/13 12:41

#include <iosfwd>
#include <string>
#include <unordered_map>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3714. Longest Balanced Substring II|:
//
// You are given a string |s| consisting only of the characters |'a'|, |'b'|,
// and |'c'|. A substring of |s| is called balanced if all distinct characters
// in the substring appear the same number of times. Return the length of the
// longest balanced substring of |s|.
//
//

LEETCODE_BEGIN_RESOLVING(3714, LongestBalancedSubstringII, Solution);

class Solution {
public:
  int longestBalanced(string s) {
    int x = calc1(s);
    int y = max({calc2(s, 'a', 'b'), calc2(s, 'b', 'c'), calc2(s, 'a', 'c')});
    int z = calc3(s);
    return max({x, y, z});
  }

private:
  int calc1(const string &s) {
    int res = 0;
    for (int i = 0; i < s.size();) {
      int j = i;
      while (j < s.size() && s[j] == s[i])
        j++;
      res = max(res, j - i);
      i   = j;
    }
    return res;
  }

  int calc2(const string &s, char a, char b) {
    int res = 0, n = s.size(), i = 0;
    while (i < n) {
      while (i < n && s[i] != a && s[i] != b)
        i++;
      unordered_map<int, int> mp;
      mp[0]    = i - 1;
      int diff = 0;
      while (i < n && (s[i] == a || s[i] == b)) {
        diff += (s[i] == a ? 1 : -1);
        if (mp.count(diff))
          res = max(res, i - mp[diff]);
        else
          mp[diff] = i;
        i++;
      }
    }
    return res;
  }

  long long key(int x, int y) {
    return ((long long)(x + 100000) << 20) | (y + 100000);
  }

  int calc3(const string &s) {
    unordered_map<long long, int> mp;
    mp[key(0, 0)] = -1;
    int cnt[3]    = {0};
    int res       = 0;
    for (int i = 0; i < s.size(); i++) {
      cnt[s[i] - 'a']++;
      int       x = cnt[0] - cnt[1];
      int       y = cnt[1] - cnt[2];
      long long k = key(x, y);
      if (mp.count(k))
        res = max(res, i - mp[k]);
      else
        mp[k] = i;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 10⁵|
// * |s| contains only the characters |'a'|, |'b'|, and |'c'|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "abbac"
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(3714, LongestBalancedSubstringII, example_1) {
  auto   solution = MakeSolution();
  string s        = "abbac";
  int    expect   = 4;
  int    actual   = solution->longestBalanced(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "aabcc"
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(3714, LongestBalancedSubstringII, example_2) {
  auto   solution = MakeSolution();
  string s        = "aabcc";
  int    expect   = 3;
  int    actual   = solution->longestBalanced(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "aba"
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(3714, LongestBalancedSubstringII, example_3) {
  auto   solution = MakeSolution();
  string s        = "aba";
  int    expect   = 2;
  int    actual   = solution->longestBalanced(s);
  LCD_EXPECT_EQ(expect, actual);
}

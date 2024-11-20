// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Take K of Each Character From Left and Right
//
// https://leetcode.com/problems/take-k-of-each-character-from-left-and-right/
//
// Question ID: 2516
// Difficult  : Medium
// Solve Date : 2024/11/20 18:56

#include <algorithm>
#include <iosfwd>
#include <string>
#include <unordered_set>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2516. Take K of Each Character From Left and Right|:
//
// You are given a string |s| consisting of the characters |'a'|, |'b'|, and
// |'c'| and a non-negative integer |k|. Each minute, you may take either the
// leftmost character of |s|, or the rightmost character of |s|. Return the
// minimum number of minutes needed for you to take at least |k| of each
// character, or return |-1| if it is not possible to take |k| of each
// character.
//
//

LEETCODE_BEGIN_RESOLVING(2516, TakeKOfEachCharacterFromLeftAndRight, Solution);

class Solution {
public:
  int takeCharacters(string s, int k) {
    int         n = s.size();
    vector<int> freq(3, 0);
    for (auto c : s) {
      ++freq[c - 'a'];
    }

    if (any_of(freq.begin(), freq.end(), [k](int f) { return f < k; })) {
      return -1;
    }

    int res = n;
    for (int l = 0, r = 0; r < n; ++r) {
      int x = s[r] - 'a';
      --freq[x];
      while (l <= r &&
             any_of(freq.begin(), freq.end(), [k](int f) { return f < k; })) {
        ++freq[s[l++] - 'a'];
      }

      res = min(res, n - (r - l + 1));
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 10⁵|
// * |s| consists of only the letters |'a'|, |'b'|, and |'c'|.
// * |0 <= k <= s.length|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "aabaaaacaabc", k = 2
// Output: 8
//

LEETCODE_SOLUTION_UNITTEST(2516, TakeKOfEachCharacterFromLeftAndRight,
                           example_1) {
  auto   solution = MakeSolution();
  string s        = "aabaaaacaabc";
  int    k        = 2;
  int    expect   = 8;
  int    actual   = solution->takeCharacters(s, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "a", k = 1
// Output: -1
//

LEETCODE_SOLUTION_UNITTEST(2516, TakeKOfEachCharacterFromLeftAndRight,
                           example_2) {
  auto   solution = MakeSolution();
  string s        = "a";
  int    k        = 1;
  int    expect   = -1;
  int    actual   = solution->takeCharacters(s, k);
  LCD_EXPECT_EQ(expect, actual);
}

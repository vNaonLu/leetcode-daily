// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Maximum Difference Between Even and Odd Frequency I
//
// https://leetcode.com/problems/maximum-difference-between-even-and-odd-frequency-i/
//
// Question ID: 3442
// Difficult  : Easy
// Solve Date : 2025/06/10 19:17

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3442. Maximum Difference Between Even and Odd Frequency I|:
//
//

LEETCODE_BEGIN_RESOLVING(3442, MaximumDifferenceBetweenEvenAndOddFrequencyI,
                         Solution);

class Solution {
public:
  int maxDifference(string s) {
    vector<int> freq(26, 0);
    for (auto c : s) {
      ++freq[c - 'a'];
    }
    int odd = 0;
    int eve = 100;
    for (auto x : freq) {
      if (x == 0) {
        continue;
      }
      if (x & 1) {
        odd = max(odd, x);
      } else {
        eve = min(eve, x);
      }
    }
    return odd - eve;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |3 <= s.length <= 100|
// * |s| consists only of lowercase English letters.
// * |s| contains at least one character with an odd frequency and one with an
// even frequency.
///////////////////////////////////////////////////////////////////////////////

LEETCODE_SOLUTION_UNITTEST(3442, MaximumDifferenceBetweenEvenAndOddFrequencyI,
                           example_1) {
  auto   solution = MakeSolution();
  string s        = "aaaaabbc";
  int    expect   = 3;
  int    actual   = solution->maxDifference(s);
  LCD_EXPECT_EQ(expect, actual);
}

LEETCODE_SOLUTION_UNITTEST(3442, MaximumDifferenceBetweenEvenAndOddFrequencyI,
                           example_2) {
  auto   solution = MakeSolution();
  string s        = "abcabcab";
  int    expect   = 1;
  int    actual   = solution->maxDifference(s);
  LCD_EXPECT_EQ(expect, actual);
}

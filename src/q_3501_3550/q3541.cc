// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Find Most Frequent Vowel and Consonant
//
// https://leetcode.com/problems/find-most-frequent-vowel-and-consonant/
//
// Question ID: 3541
// Difficult  : Easy
// Solve Date : 2025/09/21 19:38

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3541. Find Most Frequent Vowel and Consonant|:
//
// You are given a string |s| consisting of lowercase English letters ( |'a'| to
// |'z'|). Your task is to:
//
//  • Find the vowel (one of |'a'|, |'e'|, |'i'|, |'o'|, or |'u'|) with the
//  maximum frequency.
//
//  • Find the consonant (all other letters excluding vowels) with the maximum
//  frequency.
// Return the sum of the two frequencies.
// Note: If multiple vowels or consonants have the same maximum frequency, you
// may choose any one of them. If there are no vowels or no consonants in the
// string, consider their frequency as 0. The frequency of a letter |x| is the
// number of times it occurs in the string.
//
//

LEETCODE_BEGIN_RESOLVING(3541, FindMostFrequentVowelAndConsonant, Solution);

class Solution {
public:
  int maxFreqSum(string s) {
    vector<int> freq(26, 0);
    for (auto c : s) {
      ++freq[c - 'a'];
    }

    int v  = 0;
    int nv = 0;
    for (int i = 0; i < freq.size(); ++i) {
      if (i == 0 || i == 'e' - 'a' || i == 'i' - 'a' || i == 'o' - 'a' ||
          i == 'u' - 'a') {
        v = max(v, freq[i]);
      } else {
        nv = max(nv, freq[i]);
      }
    }
    return v + nv;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 100|
// * |s| consists of lowercase English letters only.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "successes"
// Output: 6
//

LEETCODE_SOLUTION_UNITTEST(3541, FindMostFrequentVowelAndConsonant, example_1) {
  auto   solution = MakeSolution();
  string s        = "successes";
  int    expect   = 6;
  int    actual   = solution->maxFreqSum(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "aeiaeia"
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(3541, FindMostFrequentVowelAndConsonant, example_2) {
  auto   solution = MakeSolution();
  string s        = "aeiaeia";
  int    expect   = 3;
  int    actual   = solution->maxFreqSum(s);
  LCD_EXPECT_EQ(expect, actual);
}

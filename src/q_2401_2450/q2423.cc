// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Remove Letter To Equalize Frequency
//
// https://leetcode.com/problems/remove-letter-to-equalize-frequency/
//
// Question ID: 2423
// Difficult  : Easy
// Solve Date : 2023/01/21 09:29

#include <algorithm>
#include <iosfwd>
#include <map>
#include <string>
#include <unordered_map>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2423. Remove Letter To Equalize Frequency|:
//
// You are given a 0-indexed string |word|, consisting of lowercase English
// letters. You need to select one index and remove the letter at that index
// from |word| so that the frequency of every letter present in |word| is equal.
// Return |true| if it is possible to remove one letter so that the frequency of
// all letters in |word| are equal, and |false| otherwise. Note:
//
//  • The frequency of a letter |x| is the number of times it occurs in the
//  string.
//
//  • You must remove exactly one letter and cannot chose to do nothing.
//

LEETCODE_BEGIN_RESOLVING(2423, RemoveLetterToEqualizeFrequency, Solution);

class Solution {
public:
  bool equalFrequency(string word) {
    unordered_map<char, int> freq;
    vector<int>              cnt;
    for (auto c : word) {
      ++freq[c];
    }

    for (auto &x : freq) {
      cnt.emplace_back(x.second);
    }
    sort(cnt.begin(), cnt.end());

    return cnt.size() == 1 ||
           (cnt.back() - cnt.front() == 1 && cnt.front() == *(cnt.end() - 2)) ||
           (cnt.front() == 1 && cnt.front() == cnt.back()) ||
           (cnt.front() == 1 && *(cnt.begin() + 1) == cnt.back());
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |2 <= word.length <= 100|
// * |word| consists of lowercase English letters only.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: word = "abcc"
// Output: true
//
// Select index 3 and delete it: word becomes "abc" and each character has a
// frequency of 1.

LEETCODE_SOLUTION_UNITTEST(2423, RemoveLetterToEqualizeFrequency, example_1) {
  auto   solution = MakeSolution();
  string word     = "abcc";
  bool   expect   = true;
  bool   actual   = solution->equalFrequency(word);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: word = "aazz"
// Output: false
//
// We must delete a character, so either the frequency of "a" is 1 and the
// frequency of "z" is 2, or vice versa. It is impossible to make all present
// letters have equal frequency.

LEETCODE_SOLUTION_UNITTEST(2423, RemoveLetterToEqualizeFrequency, example_2) {
  auto   solution = MakeSolution();
  string word     = "aazz";
  bool   expect   = false;
  bool   actual   = solution->equalFrequency(word);
  LCD_EXPECT_EQ(expect, actual);
}

// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Sort Characters By Frequency
//
// https://leetcode.com/problems/sort-characters-by-frequency/
//
// Question ID: 451
// Difficult  : Medium
// Solve Date : 2021/10/09 15:05

#include <iosfwd>
#include <map>
#include <queue>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |451. Sort Characters By Frequency|:
//
// Given a string |s|, sort it in decreasing order based on the frequency of the
// characters. The frequency of a character is the number of times it appears in
// the string. Return the sorted string. If there are multiple answers, return
// any of them.  
//

LEETCODE_BEGIN_RESOLVING(451, SortCharactersByFrequency, Solution);

class Solution {
public:
  string frequencySort(string s) {
    string         res;
    map<char, int> cnt;
    for (const auto &c : s)
      ++cnt[c];
    priority_queue<int> pq;
    for (const auto &it : cnt)
      pq.push(it.second);
    while (!pq.empty()) {
      int count = pq.top();
      pq.pop();
      for (const auto &it : cnt) {
        if (it.second == count) {
          while (count--)
            res.push_back(it.first);
          cnt.erase(it.first);
          break;
        }
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 5 * 10⁵|
// * |s| consists of uppercase and lowercase English letters and digits.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "tree"
// Output: "eert"
//
// 'e' appears twice while 'r' and 't' both appear once.
// So 'e' must appear before both 'r' and 't'. Therefore "eetr" is also a valid
// answer.

LEETCODE_SOLUTION_UNITTEST(451, SortCharactersByFrequency, example_1) {
  auto   solution = MakeSolution();
  string s        = "tree";
  string expect   = "eert";
  string actual   = solution->frequencySort(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "cccaaa"
// Output: "aaaccc"
//
// Both 'c' and 'a' appear three times, so both "cccaaa" and "aaaccc" are valid
// answers. Note that "cacaca" is incorrect, as the same characters must be
// together.

LEETCODE_SOLUTION_UNITTEST(451, SortCharactersByFrequency, example_2) {
  auto   solution = MakeSolution();
  string s        = "cccaaa";
  string expect   = "aaaccc";
  string actual   = solution->frequencySort(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "Aabb"
// Output: "bbAa"
//
// "bbaA" is also a valid answer, but "Aabb" is incorrect.
// Note that 'A' and 'a' are treated as two different characters.

LEETCODE_SOLUTION_UNITTEST(451, SortCharactersByFrequency, example_3) {
  auto   solution = MakeSolution();
  string s        = "Aabb";
  string expect   = "bbAa";
  string actual   = solution->frequencySort(s);
  LCD_EXPECT_EQ(expect, actual);
}

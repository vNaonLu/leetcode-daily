// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Increasing Decreasing String
//
// https://leetcode.com/problems/increasing-decreasing-string/
//
// Question ID: 1370
// Difficult  : Easy
// Solve Date : 2023/08/07 19:46

#include <iosfwd>
#include <map>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1370. Increasing Decreasing String|:
//
// You are given a string |s|. Reorder the string using the following algorithm:
//
//  1. Pick the smallest character from |s| and append it to the result.
//
//  2. Pick the smallest character from |s| which is greater than the last
//  appended character to the result and append it.
//
//  3. Repeat step 2 until you cannot pick more characters.
//
//  4. Pick the largest character from |s| and append it to the result.
//
//  5. Pick the largest character from |s| which is smaller than the last
//  appended character to the result and append it.
//
//  6. Repeat step 5 until you cannot pick more characters.
//
//  7. Repeat the steps from 1 to 6 until you pick all characters from |s|.
// In each step, If the smallest or the largest character appears more than once
// you can choose any occurrence and append it to the result. Return the result
// string after sorting |s| with this algorithm.
//
//

LEETCODE_BEGIN_RESOLVING(1370, IncreasingDecreasingString, Solution);

class Solution {
public:
  string sortString(string s) {
    map<char, int> freq;
    string         res;
    for (auto c : s) {
      ++freq[c];
    }
    while (!freq.empty()) {
      {
        auto iter = freq.begin();
        while (iter != freq.end()) {
          if (--iter->second >= 0) {
            res.push_back(iter->first);
          }
          ++iter;
        }
      }

      {
        auto iter = freq.rbegin();
        while (iter != freq.rend()) {
          if (--iter->second >= 0) {
            res.push_back(iter->first);
          }
          ++iter;
        }
      }

      auto iter = freq.begin();
      while (iter != freq.end()) {
        auto prev = iter++;
        if (prev->second <= 0) {
          freq.erase(prev);
        }
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 500|
// * |s| consists of only lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "aaaabbbbcccc"
// Output: "abccbaabccba"
//
// After steps 1, 2 and 3 of the first iteration, result = "abc"
// After steps 4, 5 and 6 of the first iteration, result = "abccba"
// First iteration is done. Now s = "aabbcc" and we go back to step 1
// After steps 1, 2 and 3 of the second iteration, result = "abccbaabc"
// After steps 4, 5 and 6 of the second iteration, result = "abccbaabccba"

LEETCODE_SOLUTION_UNITTEST(1370, IncreasingDecreasingString, example_1) {
  auto   solution = MakeSolution();
  string s        = "aaaabbbbcccc";
  string expect   = "abccbaabccba";
  string actual   = solution->sortString(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "rat"
// Output: "art"
//
// The word "rat" becomes "art" after re-ordering it with the mentioned
// algorithm.

LEETCODE_SOLUTION_UNITTEST(1370, IncreasingDecreasingString, example_2) {
  auto   solution = MakeSolution();
  string s        = "rat";
  string expect   = "art";
  string actual   = solution->sortString(s);
  LCD_EXPECT_EQ(expect, actual);
}

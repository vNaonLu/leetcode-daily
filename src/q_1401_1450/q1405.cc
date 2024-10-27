// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Longest Happy String
//
// https://leetcode.com/problems/longest-happy-string/
//
// Question ID: 1405
// Difficult  : Medium
// Solve Date : 2024/10/16 21:14

#include <iosfwd>
#include <queue>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1405. Longest Happy String|:
//
// A string |s| is called happy if it satisfies the following conditions:
//
//  • |s| only contains the letters |'a'|, |'b'|, and |'c'|.
//
//  • |s| does not contain any of |"aaa"|, |"bbb"|, or |"ccc"| as a substring.
//
//  • |s| contains at most |a| occurrences of the letter |'a'|.
//
//  • |s| contains at most |b| occurrences of the letter |'b'|.
//
//  • |s| contains at most |c| occurrences of the letter |'c'|.
// Given three integers |a|, |b|, and |c|, return the longest possible happy
// string. If there are multiple longest happy strings, return any of them. If
// there is no such string, return the empty string |""|. A substring is a
// contiguous sequence of characters within a string.
//
//

LEETCODE_BEGIN_RESOLVING(1405, LongestHappyString, Solution);

class Solution {
public:
  string longestDiverseString(int a, int b, int c) {
    string                          res;
    priority_queue<pair<int, char>> pq;
    if (a > 0) {
      pq.emplace(a, 'a');
    }
    if (b > 0) {
      pq.emplace(b, 'b');
    }
    if (c > 0) {
      pq.emplace(c, 'c');
    }
    while (!pq.empty()) {
      auto [freq, ch] = pq.top();
      pq.pop();

      if (res.size() >= 2 && res.back() == ch && (*(res.rbegin() + 1) == ch)) {
        if (pq.empty()) {
          break;
        }

        auto [next_freq, next_ch] = pq.top();
        pq.pop();
        res.push_back(next_ch);
        if (--next_freq > 0) {
          pq.emplace(next_freq, next_ch);
        }
      } else {
        res.push_back(ch);
        --freq;
      }

      if (freq > 0) {
        pq.emplace(freq, ch);
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |0 <= a, b, c <= 100|
// * |a + b + c > 0|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: a = 1, b = 1, c = 7
// Output: "ccaccbcc"
//

LEETCODE_SOLUTION_UNITTEST(1405, LongestHappyString, example_1) {
  auto   solution = MakeSolution();
  int    a        = 1;
  int    b        = 1;
  int    c        = 7;
  string expect   = "ccbccacc";
  string actual   = solution->longestDiverseString(a, b, c);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: a = 7, b = 1, c = 0
// Output: "aabaa"
//

LEETCODE_SOLUTION_UNITTEST(1405, LongestHappyString, example_2) {
  auto   solution = MakeSolution();
  int    a        = 7;
  int    b        = 1;
  int    c        = 0;
  string expect   = "aabaa";
  string actual   = solution->longestDiverseString(a, b, c);
  LCD_EXPECT_EQ(expect, actual);
}

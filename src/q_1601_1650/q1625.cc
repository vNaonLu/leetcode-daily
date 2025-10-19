// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Lexicographically Smallest String After Applying Operations
//
// https://leetcode.com/problems/lexicographically-smallest-string-after-applying-operations/
//
// Question ID: 1625
// Difficult  : Medium
// Solve Date : 2025/10/19 17:52

#include <iosfwd>
#include <queue>
#include <string>
#include <unordered_set>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1625. Lexicographically Smallest String After Applying
// Operations|:
//
// You are given a string |s| of even length consisting of digits from |0| to
// |9|, and two integers |a| and |b|. You can apply either of the following two
// operations any number of times and in any order on |s|:
//
//  • Add |a| to all odd indices of |s| (0-indexed). Digits post |9| are cycled
//  back to |0|. For example, if |s = "3456"| and |a = 5|, |s| becomes |"3951"|.
//
//  • Rotate |s| to the right by |b| positions. For example, if |s = "3456"| and
//  |b = 1|, |s| becomes |"6345"|.
// Return the lexicographically smallest string you can obtain by applying the
// above operations any number of times on |s|. A string |a| is
// lexicographically smaller than a string |b| (of the same length) if in the
// first position where |a| and |b| differ, string |a| has a letter that appears
// earlier in the alphabet than the corresponding letter in |b|. For example,
// |"0158"| is lexicographically smaller than |"0190"| because the first
// position they differ is at the third letter, and |'5'| comes before |'9'|.
//
//

LEETCODE_BEGIN_RESOLVING(1625,
                         LexicographicallySmallestStringAfterApplyingOperations,
                         Solution);

class Solution {
public:
  string findLexSmallestString(string s, int a, int b) {
    unordered_set<string> vis;
    string                res = s;
    queue<string>         q;
    q.push(s);
    vis.insert(s);
    while (!q.empty()) {
      auto cur = std::move(q.front());
      q.pop();
      if (cur < res) {
        res = cur;
      }

      string tmp = cur;
      for (int i = 1; i < tmp.size(); i += 2) {
        tmp[i] = ((tmp[i] - '0' + a) % 10) + '0';
      }
      if (auto [_, ok] = vis.insert(tmp); ok) {
        q.push(tmp);
      }

      tmp = cur.substr(cur.size() - b) + cur.substr(0, cur.size() - b);
      if (auto [_, ok] = vis.insert(tmp); ok) {
        q.push(tmp);
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= s.length <= 100|
// * |s.length| is even.
// * |s| consists of digits from |0| to |9| only.
// * |1 <= a <= 9|
// * |1 <= b <= s.length - 1|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "5525", a = 9, b = 2
// Output: "2050"
//

LEETCODE_SOLUTION_UNITTEST(
    1625, LexicographicallySmallestStringAfterApplyingOperations, example_1) {
  auto   solution = MakeSolution();
  string s        = "5525";
  int    a        = 9;
  int    b        = 2;
  string expect   = "2050";
  string actual   = solution->findLexSmallestString(s, a, b);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "74", a = 5, b = 1
// Output: "24"
//

LEETCODE_SOLUTION_UNITTEST(
    1625, LexicographicallySmallestStringAfterApplyingOperations, example_2) {
  auto   solution = MakeSolution();
  string s        = "74";
  int    a        = 5;
  int    b        = 1;
  string expect   = "24";
  string actual   = solution->findLexSmallestString(s, a, b);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "0011", a = 4, b = 2
// Output: "0011"
//

LEETCODE_SOLUTION_UNITTEST(
    1625, LexicographicallySmallestStringAfterApplyingOperations, example_3) {
  auto   solution = MakeSolution();
  string s        = "0011";
  int    a        = 4;
  int    b        = 2;
  string expect   = "0011";
  string actual   = solution->findLexSmallestString(s, a, b);
  LCD_EXPECT_EQ(expect, actual);
}

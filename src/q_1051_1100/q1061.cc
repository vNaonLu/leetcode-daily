// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Lexicographically Smallest Equivalent String
//
// https://leetcode.com/problems/lexicographically-smallest-equivalent-string/
//
// Question ID: 1061
// Difficult  : Medium
// Solve Date : 2023/01/14 13:54

#include <iosfwd>
#include <list>
#include <map>
#include <set>
#include <string>
#include <unordered_map>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1061. Lexicographically Smallest Equivalent String|:
//
// You are given two strings of the same length |s1| and |s2| and a string
// |baseStr|. We say |s1[i]| and |s2[i]| are equivalent characters.
//
//  • For example, if |s1 = "abc"| and |s2 = "cde"|, then we have |'a' == 'c'|,
//  |'b' == 'd'|, and |'c' == 'e'|.
// Equivalent characters follow the usual rules of any equivalence relation:
//
//  • Reflexivity: |'a' == 'a'|.
//
//  • Symmetry: |'a' == 'b'| implies |'b' == 'a'|.
//
//  • Transitivity: |'a' == 'b'| and |'b' == 'c'| implies |'a' == 'c'|.
// For example, given the equivalency information from |s1 = "abc"| and |s2 =
// "cde"|, |"acd"| and |"aab"| are equivalent strings of |baseStr = "eed"|, and
// |"aab"| is the lexicographically smallest equivalent string of |baseStr|.
// Return the lexicographically smallest equivalent string of |baseStr| by using
// the equivalency information from |s1| and |s2|.
//

LEETCODE_BEGIN_RESOLVING(1061, LexicographicallySmallestEquivalentString,
                         Solution);

class Solution {
public:
  string smallestEquivalentString(string s1, string s2, string baseStr) {
    list<set<char>>                                group;
    unordered_map<char, list<set<char>>::iterator> memo;
    for (int i = 0; i < s1.size(); ++i) {
      auto g1 = memo.find(s1[i]);
      auto g2 = memo.find(s2[i]);

      if (g1 == memo.end() && g2 == memo.end()) {
        auto iter   = group.insert(group.end(), set<char>{s1[i], s2[i]});
        memo[s1[i]] = iter;
        memo[s2[i]] = iter;
      } else if (g1 != memo.end() && g2 == memo.end()) {
        (*g1->second).emplace(s2[i]);
        memo[s2[i]] = g1->second;
      } else if (g1 == memo.end() && g2 != memo.end()) {
        (*g2->second).emplace(s1[i]);
        memo[s1[i]] = g2->second;
      } else {
        if (g1->second != g2->second) {
          auto s = std::move(*g2->second);
          group.erase(g2->second);
          (*g1->second).insert(s.begin(), s.end());
          for (auto x : s) {
            memo[x] = g1->second;
          }
        }
      }
    }
    for (auto &c : baseStr) {
      auto gp = memo.find(c);
      if (gp != memo.end()) {
        c = *(*gp->second).begin();
      }
    }
    return baseStr;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s1.length, s2.length, baseStr <= 1000|
// * |s1.length == s2.length|
// * |s1|, |s2|, and |baseStr| consist of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s1 = "parker", s2 = "morris", baseStr = "parser"
// Output: "makkek"
//
// Based on the equivalency information in s1 and s2, we can group their
// characters as [m,p], [a,o], [k,r,s], [e,i]. The characters in each group are
// equivalent and sorted in lexicographical order. So the answer is "makkek".

LEETCODE_SOLUTION_UNITTEST(1061, LexicographicallySmallestEquivalentString,
                           example_1) {
  auto   solution = MakeSolution();
  string s1       = "parker";
  string s2       = "morris";
  string baseStr  = "parser";
  string expect   = "makkek";
  string actual   = solution->smallestEquivalentString(s1, s2, baseStr);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s1 = "hello", s2 = "world", baseStr = "hold"
// Output: "hdld"
//
// Based on the equivalency information in s1 and s2, we can group their
// characters as [h,w], [d,e,o], [l,r]. So only the second letter 'o' in baseStr
// is changed to 'd', the answer is "hdld".

LEETCODE_SOLUTION_UNITTEST(1061, LexicographicallySmallestEquivalentString,
                           example_2) {
  auto   solution = MakeSolution();
  string s1       = "hello";
  string s2       = "world";
  string baseStr  = "hold";
  string expect   = "hdld";
  string actual   = solution->smallestEquivalentString(s1, s2, baseStr);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s1 = "leetcode", s2 = "programs", baseStr = "sourcecode"
// Output: "aauaaaaada"
//
// We group the equivalent characters in s1 and s2 as [a,o,e,r,s,c], [l,p],
// [g,t] and [d,m], thus all letters in baseStr except 'u' and 'd' are
// transformed to 'a', the answer is "aauaaaaada".

LEETCODE_SOLUTION_UNITTEST(1061, LexicographicallySmallestEquivalentString,
                           example_3) {
  auto   solution = MakeSolution();
  string s1       = "leetcode";
  string s2       = "programs";
  string baseStr  = "sourcecode";
  string expect   = "aauaaaaada";
  string actual   = solution->smallestEquivalentString(s1, s2, baseStr);
  LCD_EXPECT_EQ(expect, actual);
}

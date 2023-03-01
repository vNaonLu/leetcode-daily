// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Permutation in String
//
// https://leetcode.com/problems/permutation-in-string/
//
// Question ID: 567
// Difficult  : Medium
// Solve Date : 2021/09/10 08:00

#include <iosfwd>
#include <map>
#include <string>
#include <unordered_map>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |567. Permutation in String|:
//
// Given two strings |s1| and |s2|, return |true| if |s2| contains a permutation
// of |s1|, or |false| otherwise. In other words, return |true| if one of |s1|'s
// permutations is the substring of |s2|.  
//

LEETCODE_BEGIN_RESOLVING(567, PermutationinString, Solution);

class Solution {
public:
  bool checkInclusion(string s1, string s2) {
    unordered_map<int, int> key;
    vector<int>             count(26, 0);
    int                     length = 0, left = 0;
    size_t                  key_size = s1.size();
    for (const auto &c : s1)
      ++key[c - 'a'];
    for (int i = 0; i < s2.size(); ++i) {
      ++length;
      ++count[s2[i] - 'a'];
      if (length > key_size) {
        --length;
        --count[s2[left++] - 'a'];
      }

      bool match = true;
      for (auto &[c, v] : key) {
        match &= count[c] == v;
      }
      if (match)
        return true;
    }
    return false;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s1.length, s2.length <= 10⁴|
// * |s1| and |s2| consist of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s1 = "ab", s2 = "eidbaooo"
// Output: true
//
// s2 contains one permutation of s1 ("ba").

LEETCODE_SOLUTION_UNITTEST(567, PermutationinString, example_1) {
  auto   solution = MakeSolution();
  string s1       = "ab";
  string s2       = "eidbaooo";
  bool   expect   = true;
  bool   actual   = solution->checkInclusion(s1, s2);
  EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s1 = "ab", s2 = "eidboaoo"
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(567, PermutationinString, example_2) {
  auto   solution = MakeSolution();
  string s1       = "ab";
  string s2       = "eidboaoo";
  bool   expect   = false;
  bool   actual   = solution->checkInclusion(s1, s2);
  EXPECT_EQ(expect, actual);
}

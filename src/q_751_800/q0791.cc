// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Custom Sort String
//
// https://leetcode.com/problems/custom-sort-string/
//
// Question ID: 791
// Difficult  : Medium
// Solve Date : 2024/03/11 22:39

#include <iosfwd>
#include <string>
#include <unordered_map>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |791. Custom Sort String|:
//
// You are given two strings |order| and |s|. All the characters of |order| are
// unique and were sorted in some custom order previously. Permute the
// characters of |s| so that they match the order that |order| was sorted. More
// specifically, if a character |x| occurs before a character |y| in |order|,
// then |x| should occur before |y| in the permuted string. Return any
// permutation of |s| that satisfies this property.
//
//

LEETCODE_BEGIN_RESOLVING(791, CustomSortString, Solution);

class Solution {
public:
  string customSortString(string order, string s) {
    unordered_map<char, int> cnt;
    for (auto c : order) {
      cnt[c] = 0;
    }
    for (auto c : s) {
      if (cnt.count(c)) {
        ++cnt[c];
      }
    }

    string res;
    for (auto c : order) {
      res.append(cnt[c], c);
    }

    for (auto c : s) {
      if (!cnt.count(c)) {
        res.push_back(c);
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= order.length <= 26|
// * |1 <= s.length <= 200|
// * |order| and |s| consist of lowercase English letters.
// * All the characters of |order| are unique.
///////////////////////////////////////////////////////////////////////////////

LEETCODE_SOLUTION_UNITTEST(791, CustomSortString, example_1) {
  auto   solution = MakeSolution();
  string order    = "cba";
  string s        = "abcd";
  string expect   = "cbad";
  string actual   = solution->customSortString(order, s);
  EXPECT_EQ(expect, actual);
}

LEETCODE_SOLUTION_UNITTEST(791, CustomSortString, example_2) {
  auto   solution = MakeSolution();
  string order    = "bcafg";
  string s        = "abcd";
  string expect   = "bcad";
  string actual   = solution->customSortString(order, s);
  EXPECT_EQ(expect, actual);
}

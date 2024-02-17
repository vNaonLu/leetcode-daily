// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Longest Unequal Adjacent Groups Subsequence I
//
// https://leetcode.com/problems/longest-unequal-adjacent-groups-subsequence-i/
//
// Question ID: 2900
// Difficult  : Easy
// Solve Date : 2024/02/17 14:29

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2900. Longest Unequal Adjacent Groups Subsequence I|:
//
// You are given a binary array |groups| and a string array |words| both of
// length |n|, where |words[i]| is associated with |groups[i]|. Your task is to
// select the longest alternating subsequence from |words|. A subsequence of
// |words| is alternating if for any two consecutive strings in the sequence,
// their corresponding elements in the binary array |groups| differ.
// Essentially, you are to choose strings such that adjacent elements have
// non-matching corresponding bits in the |groups| array. Formally, you need to
// find the longest subsequence of an array of indices |[0, 1, ..., n - 1]|
// denoted as |[i₀, i₁, ..., iₖ₋₁]|, such that |groups[iⱼ] != groups[iⱼ₊₁]| for
// each |0 <= j < k - 1| and then find the words corresponding to these indices.
// Return the selected subsequence. If there are multiple answers, return any of
// them. Note: The elements in |words| are distinct.
//
//

LEETCODE_BEGIN_RESOLVING(2900, LongestUnequalAdjacentGroupsSubsequenceI,
                         Solution);

class Solution {
public:
  vector<string> getLongestSubsequence(vector<string> &words,
                                       vector<int>    &groups) {
    vector<string> res;
    int            prev = groups[0];
    res.emplace_back(words[0]);
    for (int i = 1; i < words.size(); ++i) {
      if (groups[i] != prev) {
        res.emplace_back(words[i]);
        prev = groups[i];
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n == words.length == groups.length <= 100|
// * |1 <= words[i].length <= 10|
// * |groups[i]| is either |0| or |1.|
// * |words| consists of distinct strings.
// * |words[i]| consists of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

LEETCODE_SOLUTION_UNITTEST(2900, LongestUnequalAdjacentGroupsSubsequenceI,
                           example_1) {
  auto           solution = MakeSolution();
  vector<string> words    = {"e", "a", "b"};
  vector<int>    groups   = {0, 0, 1};
  vector<string> expect   = {"e", "b"};
  vector<string> actual   = solution->getLongestSubsequence(words, groups);
  LCD_EXPECT_EQ(expect, actual);
}

LEETCODE_SOLUTION_UNITTEST(2900, LongestUnequalAdjacentGroupsSubsequenceI,
                           example_2) {
  auto           solution = MakeSolution();
  vector<string> words    = {"a", "b", "c", "d"};
  vector<int>    groups   = {1, 0, 1, 1};
  vector<string> expect   = {"a", "b", "c"};
  vector<string> actual   = solution->getLongestSubsequence(words, groups);
  LCD_EXPECT_EQ(expect, actual);
}

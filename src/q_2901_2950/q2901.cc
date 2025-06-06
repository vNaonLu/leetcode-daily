// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Longest Unequal Adjacent Groups Subsequence II
//
// https://leetcode.com/problems/longest-unequal-adjacent-groups-subsequence-ii/
//
// Question ID: 2901
// Difficult  : Medium
// Solve Date : 2025/05/16 19:11

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2901. Longest Unequal Adjacent Groups Subsequence II|:
//
// You are given a string array |words|, and an array |groups|, both arrays
// having length |n|. The hamming distance between two strings of equal length
// is the number of positions at which the corresponding characters are
// different. You need to select the longest subsequence from an array of
// indices |[0, 1, ..., n - 1]|, such that for the subsequence denoted as |[i₀,
// i₁, ..., iₖ₋₁]| having length |k|, the following holds:
//
//  • For adjacent indices in the subsequence, their corresponding groups are
//  unequal, i.e., |groups[iⱼ] != groups[iⱼ₊₁]|, for each |j| where |0 < j + 1 <
//  k|.
//
//  • |words[iⱼ]| and |words[iⱼ₊₁]| are equal in length, and the hamming
//  distance between them is |1|, where |0 < j + 1 < k|, for all indices in the
//  subsequence.
// Return a string array containing the words corresponding to the indices (in
// order) in the selected subsequence. If there are multiple answers, return any
// of them. Note: strings in |words| may be unequal in length.
//
//

LEETCODE_BEGIN_RESOLVING(2901, LongestUnequalAdjacentGroupsSubsequenceII,
                         Solution);

class Solution {
public:
  vector<string> getWordsInLongestSubsequence(vector<string> &words,
                                              vector<int>    &groups) {
    int         n = groups.size();
    vector<int> dp(n, 1);
    vector<int> parent(n, -1);
    int         mxi = 0;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < i; ++j) {
        if (groups[i] != groups[j] && differ(words[i], words[j]) &&
            dp[i] < dp[j] + 1) {
          parent[i] = j;
          dp[i]     = dp[j] + 1;
        }
      }
      mxi = max(mxi, dp[i]);
    }

    vector<string> res;
    for (int i = 0; i < n; ++i) {
      if (mxi == dp[i]) {
        while (i != -1) {
          res.emplace_back(words[i]);
          i = parent[i];
        }
        break;
      }
    }
    reverse(res.begin(), res.end());
    return res;
  }

private:
  bool differ(string const &s1, string const &s2) {
    if (s1.size() != s2.size()) {
      return false;
    }
    int diff = 0;
    for (int i = 0; i < s1.size(); ++i) {
      diff += s1[i] != s2[i];
    }
    return diff == 1;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n == words.length == groups.length <= 1000|
// * |1 <= words[i].length <= 10|
// * |1 <= groups[i] <= n|
// * |words| consists of distinct strings.
// * |words[i]| consists of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: words = ["bab","dab","cab"], groups = [1,2,2]
// Output: ["bab","cab"]
//

LEETCODE_SOLUTION_UNITTEST(2901, LongestUnequalAdjacentGroupsSubsequenceII,
                           example_1) {
  auto           solution = MakeSolution();
  vector<string> words    = {"bab", "dab", "cab"};
  vector<int>    groups   = {1, 2, 2};
  vector<string> expect   = {"bab", "dab"};
  vector<string> actual = solution->getWordsInLongestSubsequence(words, groups);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: words = ["a","b","c","d"], groups = [1,2,3,4]
// Output: ["a","b","c","d"]
//

LEETCODE_SOLUTION_UNITTEST(2901, LongestUnequalAdjacentGroupsSubsequenceII,
                           example_2) {
  auto           solution = MakeSolution();
  vector<string> words    = {"a", "b", "c", "d"};
  vector<int>    groups   = {1, 2, 3, 4};
  vector<string> expect   = {"a", "b", "c", "d"};
  vector<string> actual = solution->getWordsInLongestSubsequence(words, groups);
  LCD_EXPECT_EQ(expect, actual);
}

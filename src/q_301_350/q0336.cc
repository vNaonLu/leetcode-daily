// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Palindrome Pairs
//
// https://leetcode.com/problems/palindrome-pairs/
//
// Question ID: 336
// Difficult  : Hard
// Solve Date : 2022/09/17 13:41

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |336. Palindrome Pairs|:
//
// You are given a 0-indexed array of unique strings |words|.
// A palindrome pair is a pair of integers |(i, j)| such that:
//
//  • |0 <= i, j < words.length|,
//
//  • |i != j|, and
//
//  • |words[i] + words[j]| (the concatenation of the two strings) is a
//  palindrome.
// Return an array of all the palindrome pairs of |words|.
//

LEETCODE_BEGIN_RESOLVING(336, PalindromePairs, Solution);

struct TrieNode {
  TrieNode   *next[26] = {};
  int         index    = -1;
  vector<int> palindromeIndexes;
};

class Solution {
  TrieNode root;
  void     add(string &s, int i) {
    auto node = &root;
    for (int j = s.size() - 1; j >= 0; --j) {
      if (isPalindrome(s, 0, j))
        node->palindromeIndexes.push_back(i);
      int c = s[j] - 'a';
      if (!node->next[c])
        node->next[c] = new TrieNode();
      node = node->next[c];
    }
    node->index = i;
    node->palindromeIndexes.push_back(i);
  }

  bool isPalindrome(string &s, int i, int j) {
    while (i < j && s[i] == s[j])
      ++i, --j;
    return i >= j;
  }

public:
  vector<vector<int>> palindromePairs(vector<string> &A) {
    int N = A.size();
    for (int i = 0; i < N; ++i)
      add(A[i], i);
    vector<vector<int>> ans;
    for (int i = 0; i < N; ++i) {
      auto s    = A[i];
      auto node = &root;
      for (int j = 0; j < s.size() && node; ++j) {
        if (node->index != -1 && node->index != i &&
            isPalindrome(s, j, s.size() - 1))
          ans.push_back({i, node->index});
        node = node->next[s[j] - 'a'];
      }
      if (!node)
        continue;
      for (int j : node->palindromeIndexes) {
        if (i != j)
          ans.push_back({i, j});
      }
    }
    return ans;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= words.length <= 5000|
// * |0 <= words[i].length <= 300|
// * |words[i]| consists of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: words = ["abcd","dcba","lls","s","sssll"]
// Output: [[0,1],[1,0],[3,2],[2,4]]
//
// The palindromes are ["abcddcba","dcbaabcd","slls","llssssll"]

LEETCODE_SOLUTION_UNITTEST(336, PalindromePairs, example_1) {
  auto                solution = MakeSolution();
  vector<string>      words    = {"abcd", "dcba", "lls", "s", "sssll"};
  vector<vector<int>> expect   = {
      {0, 1},
      {1, 0},
      {3, 2},
      {2, 4}
  };
  vector<vector<int>> actual = solution->palindromePairs(words);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #2]
//  Input: words = ["bat","tab","cat"]
// Output: [[0,1],[1,0]]
//
// The palindromes are ["battab","tabbat"]

LEETCODE_SOLUTION_UNITTEST(336, PalindromePairs, example_2) {
  auto                solution = MakeSolution();
  vector<string>      words    = {"bat", "tab", "cat"};
  vector<vector<int>> expect   = {
      {0, 1},
      {1, 0}
  };
  vector<vector<int>> actual = solution->palindromePairs(words);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #3]
//  Input: words = ["a",""]
// Output: [[0,1],[1,0]]
//
// The palindromes are ["a","a"]

LEETCODE_SOLUTION_UNITTEST(336, PalindromePairs, example_3) {
  auto                solution = MakeSolution();
  vector<string>      words    = {"a", ""};
  vector<vector<int>> expect   = {
      {0, 1},
      {1, 0}
  };
  vector<vector<int>> actual = solution->palindromePairs(words);
  EXPECT_ANYORDER_EQ(expect, actual);
}

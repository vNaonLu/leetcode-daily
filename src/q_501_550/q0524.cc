// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Longest Word in Dictionary through Deleting
//
// https://leetcode.com/problems/longest-word-in-dictionary-through-deleting/
//
// Question ID: 524
// Difficult  : Medium
// Solve Date : 2024/05/02 22:33

#include <algorithm>
#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |524. Longest Word in Dictionary through Deleting|:
//
// Given a string |s| and a string array |dictionary|, return the longest string
// in the dictionary that can be formed by deleting some of the given string
// characters. If there is more than one possible result, return the longest
// word with the smallest lexicographical order. If there is no possible result,
// return the empty string.
//
//

LEETCODE_BEGIN_RESOLVING(524, LongestWordInDictionaryThroughDeleting, Solution);

class Solution {
public:
  string findLongestWord(string s, vector<string> &dictionary) {
    sort(dictionary.begin(), dictionary.end(), [](auto &a, auto &b) {
      return a.size() == b.size() ? (a < b) : (a.size() > b.size());
    });
    for (auto &w : dictionary) {
      if (find(s, w)) {
        return w;
      }
    }
    return "";
  }

private:
  bool find(string const &targ, string const &patt) {
    auto it = targ.begin();
    auto pi = patt.begin();
    while (it != targ.end() && pi != patt.end()) {
      if (*it == *pi) {
        ++pi;
      }
      ++it;
    }
    return pi == patt.end();
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 1000|
// * |1 <= dictionary.length <= 1000|
// * |1 <= dictionary[i].length <= 1000|
// * |s| and |dictionary[i]| consist of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "abpcplea", dictionary = ["ale","apple","monkey","plea"]
// Output: "apple"
//

LEETCODE_SOLUTION_UNITTEST(524, LongestWordInDictionaryThroughDeleting,
                           example_1) {
  auto           solution   = MakeSolution();
  string         s          = "abpcplea";
  vector<string> dictionary = {"ale", "apple", "monkey", "plea"};
  string         expect     = "apple";
  string         actual     = solution->findLongestWord(s, dictionary);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "abpcplea", dictionary = ["a","b","c"]
// Output: "a"
//

LEETCODE_SOLUTION_UNITTEST(524, LongestWordInDictionaryThroughDeleting,
                           example_2) {
  auto           solution   = MakeSolution();
  string         s          = "abpcplea";
  vector<string> dictionary = {"a", "b", "c"};
  string         expect     = "a";
  string         actual     = solution->findLongestWord(s, dictionary);
  LCD_EXPECT_EQ(expect, actual);
}

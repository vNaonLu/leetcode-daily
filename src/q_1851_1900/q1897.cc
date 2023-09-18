// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Redistribute Characters to Make All Strings Equal
//
// https://leetcode.com/problems/redistribute-characters-to-make-all-strings-equal/
//
// Question ID: 1897
// Difficult  : Easy
// Solve Date : 2023/09/16 11:35

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1897. Redistribute Characters to Make All Strings Equal|:
//
// You are given an array of strings |words| (0-indexed).
// In one operation, pick two distinct indices |i| and |j|, where |words[i]| is
// a non-empty string, and move any character from |words[i]| to any position in
// |words[j]|. Return |true| if you can make every string in |words| equal using
// any number of operations, and |false| otherwise.
//
//

LEETCODE_BEGIN_RESOLVING(1897, RedistributeCharactersToMakeAllStringsEqual,
                         Solution);

class Solution {
public:
  bool makeEqual(vector<string> &words) {
    vector<int> freq(26, 0);
    for (auto &s : words) {
      for (auto c : s) {
        ++freq[c - 'a'];
      }
    }

    for (auto c : freq) {
      if (c != 0 && (c % words.size()) != 0) {
        return false;
      }
    }

    return true;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= words.length <= 100|
// * |1 <= words[i].length <= 100|
// * |words[i]| consists of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: words = ["abc","aabc","bc"]
// Output: true
//
// Move the first 'a' in |words[1] to the front of words[2],
// to make | |words[1]| = "abc" and words[2] = "abc".
// All the strings are now equal to "abc", so return |true|.

LEETCODE_SOLUTION_UNITTEST(1897, RedistributeCharactersToMakeAllStringsEqual,
                           example_1) {
  auto           solution = MakeSolution();
  vector<string> words    = {"abc", "aabc", "bc"};
  bool           expect   = true;
  bool           actual   = solution->makeEqual(words);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: words = ["ab","a"]
// Output: false
//
// It is impossible to make all the strings equal using the operation.

LEETCODE_SOLUTION_UNITTEST(1897, RedistributeCharactersToMakeAllStringsEqual,
                           example_2) {
  auto           solution = MakeSolution();
  vector<string> words    = {"ab", "a"};
  bool           expect   = false;
  bool           actual   = solution->makeEqual(words);
  LCD_EXPECT_EQ(expect, actual);
}

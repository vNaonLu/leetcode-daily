// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Find Words Containing Character
//
// https://leetcode.com/problems/find-words-containing-character/
//
// Question ID: 2942
// Difficult  : Easy
// Solve Date : 2024/02/06 22:49

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2942. Find Words Containing Character|:
//
// You are given a 0-indexed array of strings |words| and a character |x|.
// Return an array of indices representing the words that contain the character
// |x|. Note that the returned array may be in any order.
//
//

LEETCODE_BEGIN_RESOLVING(2942, FindWordsContainingCharacter, Solution);

class Solution {
public:
  vector<int> findWordsContaining(vector<string> &words, char x) {
    vector<int> res;
    int         idx = 0;
    for (auto &s : words) {
      if (s.find(x) != s.npos) {
        res.emplace_back(idx);
      }
      ++idx;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= words.length <= 50|
// * |1 <= words[i].length <= 50|
// * |x| is a lowercase English letter.
// * |words[i]| consists only of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: words = ["leet","code"], x = "e"
// Output: [0,1]
//
// "e" occurs in both words: "leet", and "code". Hence, we return indices 0
// and 1.

LEETCODE_SOLUTION_UNITTEST(2942, FindWordsContainingCharacter, example_1) {
  auto           solution = MakeSolution();
  vector<string> words    = {"leet", "code"};
  char           x        = 'e';
  vector<int>    expect   = {0, 1};
  vector<int>    actual   = solution->findWordsContaining(words, x);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: words = ["abc","bcd","aaaa","cbc"], x = "a"
// Output: [0,2]
//
// "a" occurs in "abc", and "aaaa". Hence, we return indices 0 and 2.

LEETCODE_SOLUTION_UNITTEST(2942, FindWordsContainingCharacter, example_2) {
  auto           solution = MakeSolution();
  vector<string> words    = {"abc", "bcd", "aaaa", "cbc"};
  char           x        = 'a';
  vector<int>    expect   = {0, 2};
  vector<int>    actual   = solution->findWordsContaining(words, x);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: words = ["abc","bcd","aaaa","cbc"], x = "z"
// Output: []
//
// "z" does not occur in any of the words. Hence, we return an empty array.

LEETCODE_SOLUTION_UNITTEST(2942, FindWordsContainingCharacter, example_3) {
  auto           solution = MakeSolution();
  vector<string> words    = {"abc", "bcd", "aaaa", "cbc"};
  char           x        = 'z';
  vector<int>    expect   = {};
  vector<int>    actual   = solution->findWordsContaining(words, x);
  LCD_EXPECT_EQ(expect, actual);
}

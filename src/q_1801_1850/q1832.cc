// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Check if the Sentence Is Pangram
//
// https://leetcode.com/problems/check-if-the-sentence-is-pangram/
//
// Question ID: 1832
// Difficult  : Easy
// Solve Date : 2022/10/17 15:18

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1832. Check if the Sentence Is Pangram|:
//
// A pangram is a sentence where every letter of the English alphabet appears at
// least once. Given a string |sentence| containing only lowercase English
// letters, return |true| if |sentence| is a pangram, or |false| otherwise.
//

LEETCODE_BEGIN_RESOLVING(1832, CheckIfTheSentenceIsPangram, Solution);

class Solution {
public:
  bool checkIfPangram(string sentence) {
    auto freq = vector<int>(26, 0);
    for (auto c : sentence) {
      ++freq[c - 'a'];
    }
    for (auto f : freq) {
      if (f == 0) {
        return false;
      }
    }
    return true;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= sentence.length <= 1000|
// * |sentence| consists of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: sentence = "thequickbrownfoxjumpsoverthelazydog"
// Output: true
//
// sentence contains at least one of every letter of the English alphabet.

LEETCODE_SOLUTION_UNITTEST(1832, CheckIfTheSentenceIsPangram, example_1) {
  auto   solution = MakeSolution();
  string sentence = "thequickbrownfoxjumpsoverthelazydog";
  bool   expect   = true;
  bool   actual   = solution->checkIfPangram(sentence);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: sentence = "leetcode"
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(1832, CheckIfTheSentenceIsPangram, example_2) {
  auto   solution = MakeSolution();
  string sentence = "leetcode";
  bool   expect   = false;
  bool   actual   = solution->checkIfPangram(sentence);
  LCD_EXPECT_EQ(expect, actual);
}

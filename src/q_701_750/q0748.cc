// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Shortest Completing Word
//
// https://leetcode.com/problems/shortest-completing-word/
//
// Question ID: 748
// Difficult  : Easy
// Solve Date : 2022/10/22 19:02

#include <iosfwd>
#include <limits>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |748. Shortest Completing Word|:
//
// Given a string |licensePlate| and an array of strings |words|, find the
// shortest completing word in |words|. A completing word is a word that
// contains all the letters in |licensePlate|. Ignore numbers and spaces in
// |licensePlate|, and treat letters as case insensitive. If a letter appears
// more than once in |licensePlate|, then it must appear in the word the same
// number of times or more. For example, if |licensePlate| | = "aBc 12c"|, then
// it contains letters |'a'|, |'b'| (ignoring case), and |'c'| twice. Possible
// completing words are |"abccdef"|, |"caaacab"|, and |"cbca"|. Return the
// shortest completing word in |words|. It is guaranteed an answer exists. If
// there are multiple shortest completing words, return the first one that
// occurs in |words|.
//

LEETCODE_BEGIN_RESOLVING(748, ShortestCompletingWord, Solution);

class Solution {
public:
  string shortestCompletingWord(string licensePlate, vector<string> &words) {
    vector<int> cntlic(26, 0);
    for (auto ch : licensePlate) {
      if (isalpha(ch)) {
        ++cntlic[tolower(ch) - 'a'];
      }
    }

    int    minL = numeric_limits<int>::max();
    string res;
    for (auto &str : words) {
      vector<int> cnt(26, 0);
      for (auto ch : str) {
        ++cnt[ch - 'a'];
      }

      bool complete = true;
      for (int i = 0; i < 26; ++i) {
        if (cnt[i] < cntlic[i]) {
          complete = false;
          break;
        }
      }

      if (complete && str.length() < (size_t)minL) {
        res  = str;
        minL = str.length();
      }
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= licensePlate.length <= 7|
// * |licensePlate| contains digits, letters (uppercase or lowercase), or space
// |' '|.
// * |1 <= words.length <= 1000|
// * |1 <= words[i].length <= 15|
// * |words[i]| consists of lower case English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: licensePlate = "1s3 PSt", words = ["step","steps","stripe","stepple"]
// Output: "steps"
//
// licensePlate contains letters 's', 'p', 's' (ignoring case), and 't'.
// "step" contains 't' and 'p', but only contains 1 's'.
// "steps" contains 't', 'p', and both 's' characters.
// "stripe" is missing an 's'.
// "stepple" is missing an 's'.
// Since "steps" is the only word containing all the letters, that is the
// answer.

LEETCODE_SOLUTION_UNITTEST(748, ShortestCompletingWord, example_1) {
  auto           solution     = MakeSolution();
  string         licensePlate = "1s3 PSt";
  vector<string> words        = {"step", "steps", "stripe", "stepple"};
  string         expect       = "steps";
  string         actual = solution->shortestCompletingWord(licensePlate, words);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: licensePlate = "1s3 456", words = ["looks","pest","stew","show"]
// Output: "pest"
//
// licensePlate only contains the letter 's'. All the words contain 's', but
// among these "pest", "stew", and "show" are shortest. The answer is "pest"
// because it is the word that appears earliest of the 3.

LEETCODE_SOLUTION_UNITTEST(748, ShortestCompletingWord, example_2) {
  auto           solution     = MakeSolution();
  string         licensePlate = "1s3 456";
  vector<string> words        = {"looks", "pest", "stew", "show"};
  string         expect       = "pest";
  string         actual = solution->shortestCompletingWord(licensePlate, words);
  LCD_EXPECT_EQ(expect, actual);
}

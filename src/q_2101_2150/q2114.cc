// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Maximum Number of Words Found in Sentences
//
// https://leetcode.com/problems/maximum-number-of-words-found-in-sentences/
//
// Question ID: 2114
// Difficult  : Easy
// Solve Date : 2023/04/24 08:40

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2114. Maximum Number of Words Found in Sentences|:
//
// A sentence is a list of words that are separated by a single space with no
// leading or trailing spaces. You are given an array of strings |sentences|,
// where each |sentences[i]| represents a single sentence. Return the maximum
// number of words that appear in a single sentence.
//
//

LEETCODE_BEGIN_RESOLVING(2114, MaximumNumberOfWordsFoundInSentences, Solution);

class Solution {
public:
  int mostWordsFound(vector<string> &sentences) {
    int res = 0;
    for (auto &s : sentences) {
      res = max(res, countWord(s.begin(), s.end()));
    }
    return res;
  }

private:
  template <typename It>
  int countWord(It beg, It end) {
    auto iter = beg;
    int  res  = 0;
    while (beg != end) {
      while (iter != end && *iter != ' ') {
        ++iter;
      }
      while (iter != end && *iter == ' ') {
        ++iter;
      }
      ++res;
      beg = iter;
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= sentences.length <= 100|
// * |1 <= sentences[i].length <= 100|
// * |sentences[i]| consists only of lowercase English letters and |' '| only.
// * |sentences[i]| does not have leading or trailing spaces.
// * All the words in |sentences[i]| are separated by a single space.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: sentences = ["alice and bob love leetcode", "i think so too", "this
//  is great thanks very much"]
// Output: 6
//
// - The first sentence, "alice and bob love leetcode", has 5 words in total.
// - The second sentence, "i think so too", has 4 words in total.
// - The third sentence, "this is great thanks very much", has 6 words in total.
// Thus, the maximum number of words in a single sentence comes from the third
// sentence, which has 6 words.

LEETCODE_SOLUTION_UNITTEST(2114, MaximumNumberOfWordsFoundInSentences,
                           example_1) {
  auto           solution  = MakeSolution();
  vector<string> sentences = {"alice and bob love leetcode", "i think so too",
                              "this is great thanks very much"};
  int            expect    = 6;
  int            actual    = solution->mostWordsFound(sentences);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: sentences = ["please wait", "continue to fight", "continue to win"]
// Output: 3
//
// It is possible that multiple sentences contain the same number of words.
// In this example, the second and third sentences (underlined) have the same
// number of words.

LEETCODE_SOLUTION_UNITTEST(2114, MaximumNumberOfWordsFoundInSentences,
                           example_2) {
  auto           solution  = MakeSolution();
  vector<string> sentences = {"please wait", "continue to fight",
                              "continue to win"};
  int            expect    = 3;
  int            actual    = solution->mostWordsFound(sentences);
  LCD_EXPECT_EQ(expect, actual);
}

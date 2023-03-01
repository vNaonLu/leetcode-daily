// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Sorting the Sentence
//
// https://leetcode.com/problems/sorting-the-sentence/
//
// Question ID: 1859
// Difficult  : Easy
// Solve Date : 2022/12/22 19:32

#include <algorithm>
#include <iosfwd>
#include <map>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1859. Sorting the Sentence|:
//
// A sentence is a list of words that are separated by a single space with no
// leading or trailing spaces. Each word consists of lowercase and uppercase
// English letters.
//
// A sentence can be shuffled by appending the 1-indexed word position to each
// word then rearranging the words in the sentence.
//
//
//
//  • For example, the sentence |"This is a sentence"| can be shuffled as
//  |"sentence4 a3 is2 This1"| or |"is2 sentence4 This1 a3"|.
//
//
// Given a shuffled sentence |s| containing no more than |9| words, reconstruct
// and return the original sentence.
//
//
//

LEETCODE_BEGIN_RESOLVING(1859, SortingTheSentence, Solution);

class Solution {
private:
  template <typename It>
  It toNotSpace(It beg, It end) {
    while (beg != end && *beg == ' ') {
      ++beg;
    }
    return beg;
  }

  template <typename It>
  It getSpace(It beg, It end) {
    while (beg != end && *beg != ' ') {
      ++beg;
    }
    return beg;
  }

  map<int, string> toDict(string const &s) {
    auto beg = toNotSpace(s.begin(), s.end());
    auto res = map<int, string>();
    while (beg != s.end()) {
      auto space = getSpace(beg, s.end());
      auto word  = string(beg, space);
      auto num   = word.back() - '0';
      word.pop_back();
      res.emplace(num, std::move(word));
      beg = toNotSpace(space, s.end());
    }
    return res;
  }

public:
  string sortSentence(string s) {
    auto dict = toDict(s);
    auto res  = string("");
    for (auto &x : dict) {
      if (!res.empty()) {
        res += " ";
      }
      res += std::move(x.second);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |2 <= s.length <= 200|
// * |s| consists of lowercase and uppercase English letters, spaces, and digits
// from |1| to |9|.
// * The number of words in |s| is between |1| and |9|.
// * The words in |s| are separated by a single space.
// * |s| contains no leading or trailing spaces.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "is2 sentence4 This1 a3"
// Output: "This is a sentence"
//
// Sort the words in s to their original positions "This1 is2 a3 sentence4",
// then remove the numbers.

LEETCODE_SOLUTION_UNITTEST(1859, SortingTheSentence, example_1) {
  auto   solution = MakeSolution();
  string s        = "is2 sentence4 This1 a3";
  string expect   = "This is a sentence";
  string actual   = solution->sortSentence(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "Myself2 Me1 I4 and3"
// Output: "Me Myself and I"
//
// Sort the words in s to their original positions "Me1 Myself2 and3 I4", then
// remove the numbers.

LEETCODE_SOLUTION_UNITTEST(1859, SortingTheSentence, example_2) {
  auto   solution = MakeSolution();
  string s        = "Myself2 Me1 I4 and3";
  string expect   = "Me Myself and I";
  string actual   = solution->sortSentence(s);
  LCD_EXPECT_EQ(expect, actual);
}

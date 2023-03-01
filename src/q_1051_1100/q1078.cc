// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Occurrences After Bigram
//
// https://leetcode.com/problems/occurrences-after-bigram/
//
// Question ID: 1078
// Difficult  : Easy
// Solve Date : 2022/11/11 19:44

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1078. Occurrences After Bigram|:
//
// Given two strings |first| and |second|, consider occurrences in some text of
// the form |"first second third"|, where |second| comes immediately after
// |first|, and |third| comes immediately after |second|. Return an array of all
// the words |third| for each occurrence of |"first second third"|.
//

LEETCODE_BEGIN_RESOLVING(1078, OccurrencesAfterBigram, Solution);

class Solution {
private:
  template <typename It>
  It trim(It beg, It end) {
    while (beg != end) {
      if (*beg != ' ') {
        break;
      }
      ++beg;
    }
    return beg;
  }

  template <typename It>
  vector<string> split(It beg, It end) {
    auto res = vector<string>();
    auto it  = trim(beg, end);
    beg      = it;
    while (it != end) {
      if (*it == ' ') {
        if (beg != it) {
          res.emplace_back(beg, it);
        }
        beg = it = trim(it, end);
      }
      ++it;
    }
    if (beg != it) {
      res.emplace_back(beg, it);
    }
    return res;
  }

public:
  vector<string> findOcurrences(string text, string first, string second) {
    auto strs = split(text.begin(), text.end());
    auto beg  = strs.begin();
    auto res  = vector<string>();
    while (beg != strs.end()) {
      if (*(beg++) == first) {
        if (*beg == second) {
          if (beg + 1 != strs.end()) {
            res.emplace_back(*(beg + 1));
          }
        }
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= text.length <= 1000|
// * |text| consists of lowercase English letters and spaces.
// * All the words in |text| a separated by a single space.
// * |1 <= first.length, second.length <= 10|
// * |first| and |second| consist of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: text = "alice is a good girl she is a good student", first = "a",
//  second = "good"
// Output: ["girl","student"]
//

LEETCODE_SOLUTION_UNITTEST(1078, OccurrencesAfterBigram, example_1) {
  auto           solution = MakeSolution();
  string         text     = "alice is a good girl she is a good student";
  string         first    = "a";
  string         second   = "good";
  vector<string> expect   = {"girl", "student"};
  vector<string> actual   = solution->findOcurrences(text, first, second);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: text = "we will we will rock you", first = "we", second = "will"
// Output: ["we","rock"]
//

LEETCODE_SOLUTION_UNITTEST(1078, OccurrencesAfterBigram, example_2) {
  auto           solution = MakeSolution();
  string         text     = "we will we will rock you";
  string         first    = "we";
  string         second   = "will";
  vector<string> expect   = {"we", "rock"};
  vector<string> actual   = solution->findOcurrences(text, first, second);
  LCD_EXPECT_EQ(expect, actual);
}

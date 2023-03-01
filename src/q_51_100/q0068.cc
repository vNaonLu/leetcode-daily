// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Text Justification
//
// https://leetcode.com/problems/text-justification/
//
// Question ID: 68
// Difficult  : Hard
// Solve Date : 2022/03/01 21:04

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |68. Text Justification|:
//
// Given an array of strings |words| and a width |maxWidth|, format the text
// such that each line has exactly |maxWidth| characters and is fully (left and
// right) justified. You should pack your words in a greedy approach; that is,
// pack as many words as you can in each line. Pad extra spaces |' '| when
// necessary so that each line has exactly |maxWidth| characters. Extra spaces
// between words should be distributed as evenly as possible. If the number of
// spaces on a line does not divide evenly between words, the empty slots on the
// left will be assigned more spaces than the slots on the right. For the last
// line of text, it should be left-justified, and no extra space is inserted
// between words. Note:
//
//  • A word is defined as a character sequence consisting of non-space
//  characters only.
//
//  • Each word's length is guaranteed to be greater than |0| and not exceed
//  |maxWidth|.
//
//  • The input array |words| contains at least one word.
//  
//

LEETCODE_BEGIN_RESOLVING(68, TextJustification, Solution);

class Solution {
private:
  int max_width;

  template <typename Iterator>
  inline pair<int, int> getWordCountLength(Iterator beg, Iterator end) {
    int count = 0, length = 0;
    while (beg != end) {
      length += (*beg++).size();
      ++count;
    }
    return make_pair(count, length);
  }

  template <typename Iterator>
  string centerJustified(Iterator &p, Iterator end) {
    auto [cnt, len] = getWordCountLength(p, end);
    if (cnt == 1)
      return leftJustified(p, end);
    string res;
    res.resize(max_width, ' ');
    int remain_space = max_width - len, gap = cnt - 1,
        each_space = remain_space / gap, mod = remain_space % gap;
    int idx = 0;
    while (p != end) {
      for (const auto &c : *p) {
        res[idx++] = c;
      }
      idx += each_space + (--mod >= 0 ? 1 : 0);
      ++p;
    }
    return res;
  }

  template <typename Iterator>
  string leftJustified(Iterator &p, Iterator end) {
    int    idx = 0;
    string res;
    res.resize(max_width, ' ');
    while (p != end) {
      for (const auto &c : *p) {
        res[idx++] = c;
      }
      ++idx; /// space
      ++p;
    }
    return res;
  }

public:
  vector<string> fullJustify(vector<string> &words, int maxWidth) {
    vector<string>::iterator left = words.begin();
    vector<string>           res;
    int                      curr_length = 0;
    this->max_width                      = maxWidth;
    for (auto it = words.begin(); it != words.end(); ++it) {
      if (curr_length > max_width - (int)(*it).size()) {
        res.push_back(centerJustified(left, it));
        curr_length = 0;
      }
      curr_length += (*it).size();
      ++curr_length; /// at least one space
    }
    if (left != words.end()) {
      res.push_back(leftJustified(left, words.end()));
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= words.length <= 300|
// * |1 <= words[i].length <= 20|
// * |words[i]| consists of only English letters and symbols.
// * |1 <= maxWidth <= 100|
// * |words[i].length <= maxWidth|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: words = ["This", "is", "an", "example", "of", "text",
//  "justification."], maxWidth = 16
// Output: [
//    "This    is    an",
//    "example  of text",
//    "justification.  "
// ]
//

LEETCODE_SOLUTION_UNITTEST(68, TextJustification, example_1) {
  auto           solution = MakeSolution();
  vector<string> words = {"This",          "is", "an", "example", "of", "text",
                          "justification."};
  int            maxWidth = 16;
  vector<string> expect   = {"This    is    an", "example  of text",
                             "justification.  "};
  vector<string> actual   = solution->fullJustify(words, maxWidth);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: words = ["What","must","be","acknowledgment","shall","be"], maxWidth
//  = 16
// Output: [
//   "What   must   be",
//   "acknowledgment  ",
//   "shall be        "
// ]
//
// Note that the last line is "shall be " instead of "shall be", because the
// last line must be left-justified instead of fully-justified. Note that the
// second line is also left-justified because it contains only one word.

LEETCODE_SOLUTION_UNITTEST(68, TextJustification, example_2) {
  auto           solution = MakeSolution();
  vector<string> words    = {"What",           "must",  "be",
                             "acknowledgment", "shall", "be"};
  int            maxWidth = 16;
  vector<string> expect   = {"What   must   be", "acknowledgment  ",
                             "shall be        "};
  vector<string> actual   = solution->fullJustify(words, maxWidth);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: words =
//  ["Science","is","what","we","understand","well","enough","to","explain","to","a","computer.","Art","is","everything","else","we","do"],
//  maxWidth = 20
// Output: [
//   "Science  is  what we",
//  "understand      well",
//   "enough to explain to",
//   "a  computer.  Art is",
//   "everything  else  we",
//   "do                  "
// ]
//

LEETCODE_SOLUTION_UNITTEST(68, TextJustification, example_3) {
  auto           solution = MakeSolution();
  vector<string> words    = {
      "Science", "is", "what",       "we",   "understand", "well",
      "enough",  "to", "explain",    "to",   "a",          "computer.",
      "Art",     "is", "everything", "else", "we",         "do"};
  int            maxWidth = 20;
  vector<string> expect   = {"Science  is  what we", "understand      well",
                             "enough to explain to", "a  computer.  Art is",
                             "everything  else  we", "do                  "};
  vector<string> actual   = solution->fullJustify(words, maxWidth);
  LCD_EXPECT_EQ(expect, actual);
}

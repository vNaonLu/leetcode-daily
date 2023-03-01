// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Most Common Word
//
// https://leetcode.com/problems/most-common-word/
//
// Question ID: 819
// Difficult  : Easy
// Solve Date : 2022/10/04 12:48

#include <iosfwd>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |819. Most Common Word|:
//
// Given a string |paragraph| and a string array of the banned words |banned|,
// return the most frequent word that is not banned. It is guaranteed there is
// at least one word that is not banned, and that the answer is unique. The
// words in |paragraph| are case-insensitive and the answer should be returned
// in lowercase.
//

LEETCODE_BEGIN_RESOLVING(819, MostCommonWord, Solution);

class Solution {
private:
  template <typename It>
  string extractWord(It *beg, It end) {
    while (*beg != end && (**beg < 'a' || **beg > 'z')) {
      ++*beg;
    }
    auto it = *beg;
    while (it != end && (*it >= 'a' && *it <= 'z')) {
      ++it;
    }
    auto res = string(*beg, it);
    *beg     = it;
    return res;
  }

public:
  string mostCommonWord(string paragraph, vector<string> &banned) {
    auto ban  = unordered_set<string>(banned.begin(), banned.end());
    auto freq = unordered_map<string, int>();
    auto beg  = paragraph.begin();
    transform(paragraph.begin(), paragraph.end(), paragraph.begin(),
              [](auto &c) { return tolower(c); });
    while (beg != paragraph.end()) {
      auto word = extractWord(&beg, paragraph.end());
      if (!word.empty() && !ban.count(word)) {
        ++freq[move(word)];
      }
    }
    auto res = max_element(freq.begin(), freq.end(), [](auto &x, auto &y) {
      return x.second < y.second;
    });
    return res->first;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= paragraph.length <= 1000|
// * paragraph consists of English letters, space |' '|, or one of the symbols:
// |"!?',;."|.
// * |0 <= banned.length <= 100|
// * |1 <= banned[i].length <= 10|
// * |banned[i]| consists of only lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: paragraph = "Bob hit a ball, the hit BALL flew far after it was
//  hit.", banned = ["hit"]
// Output: "ball"
//
// "hit" occurs 3 times, but it is a banned word.
// "ball" occurs twice (and no other word does), so it is the most frequent
// non-banned word in the paragraph. Note that words in the paragraph are not
// case sensitive, that punctuation is ignored (even if adjacent to words, such
// as "ball,"), and that "hit" isn't the answer even though it occurs more
// because it is banned.

LEETCODE_SOLUTION_UNITTEST(819, MostCommonWord, example_1) {
  auto   solution  = MakeSolution();
  string paragraph = "Bob hit a ball, the hit BALL flew far after it was hit.";
  vector<string> banned = {"hit"};
  string         expect = "ball";
  string         actual = solution->mostCommonWord(paragraph, banned);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: paragraph = "a.", banned = []
// Output: "a"
//

LEETCODE_SOLUTION_UNITTEST(819, MostCommonWord, example_2) {
  auto           solution  = MakeSolution();
  string         paragraph = "a.";
  vector<string> banned    = {};
  string         expect    = "a";
  string         actual    = solution->mostCommonWord(paragraph, banned);
  LCD_EXPECT_EQ(expect, actual);
}

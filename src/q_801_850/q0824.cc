// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Goat Latin
//
// https://leetcode.com/problems/goat-latin/
//
// Question ID: 824
// Difficult  : Easy
// Solve Date : 2022/10/23 20:54

#include <iosfwd>
#include <set>
#include <string>
#include <unordered_set>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |824. Goat Latin|:
//
// You are given a string |sentence| that consist of words separated by spaces.
// Each word consists of lowercase and uppercase letters only. We would like to
// convert the sentence to "Goat Latin" (a made-up language similar to Pig
// Latin.) The rules of Goat Latin are as follows:
//
//  • If a word begins with a vowel ( |'a'|, |'e'|, |'i'|, |'o'|, or |'u'|),
//  append |"ma"| to the end of the word.
//
//
//    • For example, the word |"apple"| becomes |"applema"|.
//
//
//
//  • If a word begins with a consonant (i.e., not a vowel), remove the first
//  letter and append it to the end, then add |"ma"|.
//
//
//    • For example, the word |"goat"| becomes |"oatgma"|.
//
//
//
//  • Add one letter |'a'| to the end of each word per its word index in the
//  sentence, starting with |1|.
//
//
//    • For example, the first word gets |"a"| added to the end, the second word
//    gets |"aa"| added to the end, and so on.
//
//
// Return the final sentence representing the conversion from sentence to Goat
// Latin.
//

LEETCODE_BEGIN_RESOLVING(824, GoatLatin, Solution);

class Solution {
private:
  template <typename It>
  string getWord(It *beg, It end) {
    auto init = *beg;
    while (*beg != end) {
      if (**beg == ' ') {
        auto res = string(init, *beg);
        ++(*beg);
        return res;
      }
      ++(*beg);
    }
    return string(init, *beg);
  }

public:
  string toGoatLatin(string sentence) {
    static auto const mp =
        unordered_set<char>({'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'});
    auto beg = sentence.begin();
    auto res = string("");
    auto idx = (int)1;
    while (beg != sentence.end()) {
      string s = getWord(&beg, sentence.end());
      if (!s.empty()) {
        if (!mp.count(s[0])) {
          rotate(s.begin(), s.begin() + 1, s.end());
        }
        res += s + "ma";
        for (int i = 0; i < idx; ++i) {
          res += 'a';
        }
        res += ' ';
        ++idx;
      }
    }
    res.pop_back();
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= sentence.length <= 150|
// * |sentence| consists of English letters and spaces.
// * |sentence| has no leading or trailing spaces.
// * All the words in |sentence| are separated by a single space.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: sentence = "I speak Goat Latin"
// Output: "Imaa peaksmaaa oatGmaaaa atinLmaaaaa"
//

LEETCODE_SOLUTION_UNITTEST(824, GoatLatin, example_1) {
  auto   solution = MakeSolution();
  string sentence = "I speak Goat Latin";
  string expect   = "Imaa peaksmaaa oatGmaaaa atinLmaaaaa";
  string actual   = solution->toGoatLatin(sentence);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: sentence = "The quick brown fox jumped over the lazy dog"
// Output: "heTmaa uickqmaaa rownbmaaaa oxfmaaaaa umpedjmaaaaaa overmaaaaaaa
// hetmaaaaaaaa azylmaaaaaaaaa ogdmaaaaaaaaaa"
//

LEETCODE_SOLUTION_UNITTEST(824, GoatLatin, example_2) {
  auto   solution = MakeSolution();
  string sentence = "The quick brown fox jumped over the lazy dog";
  string expect   = "heTmaa uickqmaaa rownbmaaaa oxfmaaaaa umpedjmaaaaaa "
                    "overmaaaaaaa hetmaaaaaaaa azylmaaaaaaaaa ogdmaaaaaaaaaa";
  string actual   = solution->toGoatLatin(sentence);
  LCD_EXPECT_EQ(expect, actual);
}

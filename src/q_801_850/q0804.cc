// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Unique Morse Code Words
//
// https://leetcode.com/problems/unique-morse-code-words/
//
// Question ID: 804
// Difficult  : Easy
// Solve Date : 2022/08/16 18:33

#include <array>
#include <iosfwd>
#include <set>
#include <string>
#include <unordered_set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |804. Unique Morse Code Words|:
//
// International Morse Code defines a standard encoding where each letter is
// mapped to a series of dots and dashes, as follows:
//
//  • |'a'| maps to |".-"|,
//
//  • |'b'| maps to |"-..."|,
//
//  • |'c'| maps to |"-.-."|, and so on.
// For convenience, the full table for the |26| letters of the English alphabet
// is given below:
// [".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.."]
// Given an array of strings |words| where each word can be written as a
// concatenation of the Morse code of each letter.
//
//  • For example, |"cab"| can be written as |"-.-..--..."|, which is the
//  concatenation of |"-.-."|, |".-"|, and |"-..."|. We will call such a
//  concatenation the transformation of a word.
// Return the number of different transformations among all words we have.
//

LEETCODE_BEGIN_RESOLVING(804, UniqueMorseCodeWords, Solution);

class Solution {
private:
  constexpr static auto dict = array<string_view, 26>{
      ".-",   "-...", "-.-.", "-..",  ".",   "..-.", "--.",  "....", "..",
      ".---", "-.-",  ".-..", "--",   "-.",  "---",  ".--.", "--.-", ".-.",
      "...",  "-",    "..-",  "...-", ".--", "-..-", "-.--", "--.."};

  template <typename Iterator>
  string decode(Iterator beg, Iterator end) {
    auto res = string();

    while (beg != end) {
      res += dict[*beg++ - 'a'];
    }

    return res;
  }

public:
  int uniqueMorseRepresentations(vector<string> &words) {
    auto res = unordered_set<string>();
    for (auto &s : words) {
      res.emplace(decode(s.begin(), s.end()));
    }

    return res.size();
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= words.length <= 100|
// * |1 <= words[i].length <= 12|
// * |words[i]| consists of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: words = ["gin","zen","gig","msg"]
// Output: 2
//
// The transformation of each word is:
// "gin" -> "--...-."
// "zen" -> "--...-."
// "gig" -> "--...--."
// "msg" -> "--...--."
// There are 2 different transformations: "--...-." and "--...--.".

LEETCODE_SOLUTION_UNITTEST(804, UniqueMorseCodeWords, example_1) {
  auto           solution = MakeSolution();
  vector<string> words    = {"gin", "zen", "gig", "msg"};
  int            expect   = 2;
  int            actual   = solution->uniqueMorseRepresentations(words);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: words = ["a"]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(804, UniqueMorseCodeWords, example_2) {
  auto           solution = MakeSolution();
  vector<string> words    = {"a"};
  int            expect   = 1;
  int            actual   = solution->uniqueMorseRepresentations(words);
  LCD_EXPECT_EQ(expect, actual);
}

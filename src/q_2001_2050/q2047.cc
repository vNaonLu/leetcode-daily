// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Number of Valid Words in a Sentence
//
// https://leetcode.com/problems/number-of-valid-words-in-a-sentence/
//
// Question ID: 2047
// Difficult  : Easy
// Solve Date : 2023/09/24 12:18

#include <iosfwd>
#include <istream>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2047. Number of Valid Words in a Sentence|:
//
// A sentence consists of lowercase letters ( |'a'| to |'z'|), digits ( |'0'| to
// |'9'|), hyphens ( |'-'|), punctuation marks ( |'!'|, |'.'|, and |','|), and
// spaces ( |' '|) only. Each sentence can be broken down into one or more
// tokens separated by one or more spaces |' '|. A token is a valid word if all
// three of the following are true:
//
//  • It only contains lowercase letters, hyphens, and/or punctuation (no
//  digits).
//
//  • There is at most one hyphen |'-'|. If present, it must be surrounded by
//  lowercase characters ( |"a-b"| is valid, but |"-ab"| and |"ab-"| are not
//  valid).
//
//  • There is at most one punctuation mark. If present, it must be at the end
//  of the token ( |"ab,"|, |"cd!"|, and |"."| are valid, but |"a!b"| and
//  |"c.,"| are not valid).
// Examples of valid words include |"a-b."|, |"afad"|, |"ba-c"|, |"a!"|, and
// |"!"|. Given a string |sentence|, return the number of valid words in
// |sentence|.
//
//

LEETCODE_BEGIN_RESOLVING(2047, NumberOfValidWordsInASentence, Solution);

class Solution {
public:
  int countValidWords(string sentence) {
    istringstream ss(sentence);
    string        w;
    int           res = 0;
    while (ss >> w) {
      res += isValid(w.begin(), w.end());
    }
    return res;
  }

private:
  template <typename It>
  bool isValid(It beg, It end) {
    int  dash = 0;
    auto it   = beg;
    while (it != end) {
      if (isalpha(*it)) {
        ++it;
        continue;
      }

      if (*it == '-') {
        if (++dash > 1) {
          return false;
        }
        if (it == beg || it + 1 == end || !isalpha(*(it + 1)) ||
            !isalpha(*(it - 1))) {
          return false;
        }
      } else if (it + 1 != end) {
        return false;
      }

      if (isdigit(*it)) {
        return false;
      }

      ++it;
    }
    return it == end;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= sentence.length <= 1000|
// * |sentence| only contains lowercase English letters, digits, |' '|, |'-'|,
// |'!'|, |'.'|, and |','|.
// * There will be at least |1| token.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: sentence = "cat and dog"
// Output: 3
//
// The valid words in the sentence are "cat", "and", and "dog".

LEETCODE_SOLUTION_UNITTEST(2047, NumberOfValidWordsInASentence, example_1) {
  auto   solution = MakeSolution();
  string sentence = "cat and dog";
  int    expect   = 3;
  int    actual   = solution->countValidWords(sentence);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: sentence = "!this 1-s b8d!"
// Output: 0
//
// There are no valid words in the sentence.
// "!this" is invalid because it starts with a punctuation mark.
// "1-s" and "b8d" are invalid because they contain digits.

LEETCODE_SOLUTION_UNITTEST(2047, NumberOfValidWordsInASentence, example_2) {
  auto   solution = MakeSolution();
  string sentence = "!this 1-s b8d!";
  int    expect   = 0;
  int    actual   = solution->countValidWords(sentence);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: sentence = "alice and bob are playing stone-game10"
// Output: 5
//
// The valid words in the sentence are "alice", "and", "bob", "are", and
// "playing". "stone-game10" is invalid because it contains digits.

LEETCODE_SOLUTION_UNITTEST(2047, NumberOfValidWordsInASentence, example_3) {
  auto   solution = MakeSolution();
  string sentence = "alice and bob are playing stone-game10";
  int    expect   = 5;
  int    actual   = solution->countValidWords(sentence);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: " 62   nvtk0wr4f  8 qt3r! w1ph 1l ,e0d 0n 2v 7c.  n06huu2n9 s9   ui4
//  nsr!d7olr  q-, vqdo!btpmtmui.bb83lf g .!v9-lg 2fyoykex uy5a 8v whvu8 .y sc5
//  -0n4 zo pfgju 5u 4 3x,3!wl  fv4   s  aig cf j1 a i  8m5o1  !u n!.1tz87d3 .9
//  n a3  .xb1p9f  b1i a j8s2 cugf l494cx1! hisceovf3 8d93 sg 4r.f1z9w   4- cb
//  r97jo hln3s h2 o .  8dx08as7l!mcmc isa49afk i1 fk,s e !1 ln rt2vhu 4ks4zq c
//  w  o- 6  5!.n8ten0 6mk 2k2y3e335,yj  h p3 5 -0  5g1c  tr49, ,qp9 -v p
//  7p4v110926wwr h x wklq u zo 16. !8  u63n0c l3 yckifu 1cgz t.i   lh w xa l,jt
//  hpi ng-gvtk8 9 j u9qfcd!2  kyu42v dmv.cst6i5fo rxhw4wvp2 1 okc8!  z aribcam0
//  cp-zp,!e x  agj-gb3 !om3934 k vnuo056h g7 t-6j! 8w8fncebuj-lq    inzqhw v39,
//  f e 9. 50 , ru3r  mbuab  6  wz dw79.av2xp . gbmy gc s6pi pra4fo9fwq k j-ppy
//  -3vpf   o k4hy3 -!..5s ,2 k5 j p38dtd   !i   b!fgj,nx qgif "
// Output: 49
//

LEETCODE_SOLUTION_UNITTEST(2047, NumberOfValidWordsInASentence,
                           extra_testcase_1) {
  auto   solution = MakeSolution();
  string sentence =
      " 62   nvtk0wr4f  8 qt3r! w1ph 1l ,e0d 0n 2v 7c.  n06huu2n9 s9   ui4 "
      "nsr!d7olr  q-, vqdo!btpmtmui.bb83lf g .!v9-lg 2fyoykex uy5a 8v whvu8 .y "
      "sc5 -0n4 zo pfgju 5u 4 3x,3!wl  fv4   s  aig cf j1 a i  8m5o1  !u "
      "n!.1tz87d3 .9    n a3  .xb1p9f  b1i a j8s2 cugf l494cx1! hisceovf3 8d93 "
      "sg 4r.f1z9w   4- cb r97jo hln3s h2 o .  8dx08as7l!mcmc isa49afk i1 fk,s "
      "e !1 ln rt2vhu 4ks4zq c w  o- 6  5!.n8ten0 6mk 2k2y3e335,yj  h p3 5 -0  "
      "5g1c  tr49, ,qp9 -v p  7p4v110926wwr h x wklq u zo 16. !8  u63n0c l3 "
      "yckifu 1cgz t.i   lh w xa l,jt   hpi ng-gvtk8 9 j u9qfcd!2  kyu42v "
      "dmv.cst6i5fo rxhw4wvp2 1 okc8!  z aribcam0  cp-zp,!e x  agj-gb3 !om3934 "
      "k vnuo056h g7 t-6j! 8w8fncebuj-lq    inzqhw v39,  f e 9. 50 , ru3r  "
      "mbuab  6  wz dw79.av2xp . gbmy gc s6pi pra4fo9fwq k   j-ppy -3vpf   o "
      "k4hy3 -!..5s ,2 k5 j p38dtd   !i   b!fgj,nx qgif ";
  int expect = 49;
  int actual = solution->countValidWords(sentence);
  LCD_EXPECT_EQ(expect, actual);
}

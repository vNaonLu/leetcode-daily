// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Verifying an Alien Dictionary
//
// https://leetcode.com/problems/verifying-an-alien-dictionary/
//
// Question ID: 953
// Difficult  : Easy
// Solve Date : 2022/04/22 09:06

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |953. Verifying an Alien Dictionary|:
//
// In an alien language, surprisingly, they also use English lowercase letters,
// but possibly in a different |order|. The |order| of the alphabet is some
// permutation of lowercase letters. Given a sequence of |words| written in the
// alien language, and the |order| of the alphabet, return |true| if and only if
// the given |words| are sorted lexicographically in this alien language.  
//

LEETCODE_BEGIN_RESOLVING(953, VerifyingAnAlienDictionary, Solution);

class Solution {
public:
  bool isAlienSorted(vector<string> &words, string order) {
    vector<int> dict(26, -1);
    for (int i = 0; i < order.size(); ++i) {
      dict[order[i] - 'a'] = i;
    }

    for (int i = 0; i < words.size() - 1; ++i) {
      for (int j = 0; j < words[i].size(); ++j) {
        if (j >= words[i + 1].size())
          return false;

        if (words[i][j] != words[i + 1][j]) {
          char curr = words[i][j], next = words[i + 1][j];

          if (dict[curr - 'a'] > dict[next - 'a']) {
            return false;
          }

          break;
        }
      }
    }

    return true;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= words.length <= 100|
// * |1 <= words[i].length <= 20|
// * |order.length == 26|
// * All characters in |words[i]| and |order| are English lowercase letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: words = ["hello","leetcode"], order = "hlabcdefgijkmnopqrstuvwxyz"
// Output: true
//
// As 'h' comes before 'l' in this language, then the sequence is sorted.

LEETCODE_SOLUTION_UNITTEST(953, VerifyingAnAlienDictionary, example_1) {
  auto           solution = MakeSolution();
  vector<string> words    = {"hello", "leetcode"};
  string         order    = "hlabcdefgijkmnopqrstuvwxyz";
  bool           expect   = true;
  bool           actual   = solution->isAlienSorted(words, order);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: words = ["word","world","row"], order = "worldabcefghijkmnpqstuvxyz"
// Output: false
//
// As 'd' comes after 'l' in this language, then words[0] > words[1], hence the
// sequence is unsorted.

LEETCODE_SOLUTION_UNITTEST(953, VerifyingAnAlienDictionary, example_2) {
  auto           solution = MakeSolution();
  vector<string> words    = {"word", "world", "row"};
  string         order    = "worldabcefghijkmnpqstuvxyz";
  bool           expect   = false;
  bool           actual   = solution->isAlienSorted(words, order);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: words = ["apple","app"], order = "abcdefghijklmnopqrstuvwxyz"
// Output: false
//
// The first three characters "app" match, and the second string is shorter (in
// size.) According to lexicographical rules "apple" > "app", because 'l' > '∅',
// where '∅' is defined as the blank character which is less than any other
// character ([More info]).

LEETCODE_SOLUTION_UNITTEST(953, VerifyingAnAlienDictionary, example_3) {
  auto           solution = MakeSolution();
  vector<string> words    = {"apple", "app"};
  string         order    = "abcdefghijklmnopqrstuvwxyz";
  bool           expect   = false;
  bool           actual   = solution->isAlienSorted(words, order);
  LCD_EXPECT_EQ(expect, actual);
}

// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Keyboard Row
//
// https://leetcode.com/problems/keyboard-row/
//
// Question ID: 500
// Difficult  : Easy
// Solve Date : 2022/09/08 01:06

#include <iosfwd>
#include <set>
#include <string>
#include <unordered_set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |500. Keyboard Row|:
//
// Given an array of strings |words|, return the words that can be typed using
// letters of the alphabet on only one row of American keyboard like the image
// below. In the American keyboard:
//
//  • the first row consists of the characters |"qwertyuiop"|,
//
//  • the second row consists of the characters |"asdfghjkl"|, and
//
//  • the third row consists of the characters |"zxcvbnm"|.
// ![img](https://assets.leetcode.com/uploads/2018/10/12/keyboard.png)
//

LEETCODE_BEGIN_RESOLVING(500, KeyboardRow, Solution);

class Solution {
private:
  inline const static unordered_set<char> row1{'q', 'w', 'e', 'r', 't',
                                               'y', 'u', 'i', 'o', 'p'};
  inline const static unordered_set<char> row2{'a', 's', 'd', 'f', 'g',
                                               'h', 'j', 'k', 'l'};
  inline const static unordered_set<char> row3{'z', 'x', 'c', 'v',
                                               'b', 'n', 'm'};

public:
  vector<string> findWords(vector<string> &words) {
    auto res = vector<string>();
    for (auto &s : words) {
      unordered_set<char> const *target = nullptr;
      auto                       beg    = s.begin();
      if (row1.count(tolower(*beg))) {
        target = &row1;
      } else if (row2.count(tolower(*beg))) {
        target = &row2;
      } else if (row3.count(tolower(*beg))) {
        target = &row3;
      }

      while (target != nullptr && ++beg != s.end()) {
        if (!target->count(tolower(*beg))) {
          break;
        }
      }

      if (beg == s.end()) {
        res.emplace_back(move(s));
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= words.length <= 20|
// * |1 <= words[i].length <= 100|
// * |words[i]| consists of English letters (both lowercase and uppercase).
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: words = ["Hello","Alaska","Dad","Peace"]
// Output: ["Alaska","Dad"]
//

LEETCODE_SOLUTION_UNITTEST(500, KeyboardRow, example_1) {
  auto           solution = MakeSolution();
  vector<string> words    = {"Hello", "Alaska", "Dad", "Peace"};
  vector<string> expect   = {"Alaska", "Dad"};
  vector<string> actual   = solution->findWords(words);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: words = ["omk"]
// Output: []
//

LEETCODE_SOLUTION_UNITTEST(500, KeyboardRow, example_2) {
  auto           solution = MakeSolution();
  vector<string> words    = {"omk"};
  vector<string> expect   = {};
  vector<string> actual   = solution->findWords(words);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: words = ["adsdf","sfd"]
// Output: ["adsdf","sfd"]
//

LEETCODE_SOLUTION_UNITTEST(500, KeyboardRow, example_3) {
  auto           solution = MakeSolution();
  vector<string> words    = {"adsdf", "sfd"};
  vector<string> expect   = {"adsdf", "sfd"};
  vector<string> actual   = solution->findWords(words);
  LCD_EXPECT_EQ(expect, actual);
}

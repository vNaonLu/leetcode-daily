// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Find Words That Can Be Formed by Characters
//
// https://leetcode.com/problems/find-words-that-can-be-formed-by-characters/
//
// Question ID: 1160
// Difficult  : Easy
// Solve Date : 2022/12/03 17:23

#include <iosfwd>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1160. Find Words That Can Be Formed by Characters|:
//
// You are given an array of strings |words| and a string |chars|.
// A string is good if it can be formed by characters from chars (each character
// can only be used once). Return the sum of lengths of all good strings in
// words.
//

LEETCODE_BEGIN_RESOLVING(1160, FindWordsThatCanBeFormedByCharacters, Solution);

class Solution {
public:
  int countCharacters(vector<string> &words, string chars) {
    auto freq = vector<int>(26, 0);
    auto res  = (int)0;
    for (auto c : chars) {
      ++freq[c - 'a'];
    }
    for (auto &w : words) {
      auto can_form = true;
      auto cnt      = unordered_map<char, int>();
      for (auto c : w) {
        if (freq[c - 'a'] < ++cnt[c]) {
          can_form = false;
          break;
        }
      }
      if (can_form) {
        res += w.size();
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= words.length <= 1000|
// * |1 <= words[i].length, chars.length <= 100|
// * |words[i]| and |chars| consist of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: words = ["cat","bt","hat","tree"], chars = "atach"
// Output: 6
//
// The strings that can be formed are "cat" and "hat" so the answer is 3 + 3
// = 6.

LEETCODE_SOLUTION_UNITTEST(1160, FindWordsThatCanBeFormedByCharacters,
                           example_1) {
  auto           solution = MakeSolution();
  vector<string> words    = {"cat", "bt", "hat", "tree"};
  string         chars    = "atach";
  int            expect   = 6;
  int            actual   = solution->countCharacters(words, chars);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: words = ["hello","world","leetcode"], chars = "welldonehoneyr"
// Output: 10
//
// The strings that can be formed are "hello" and "world" so the answer is 5 + 5
// = 10.

LEETCODE_SOLUTION_UNITTEST(1160, FindWordsThatCanBeFormedByCharacters,
                           example_2) {
  auto           solution = MakeSolution();
  vector<string> words    = {"hello", "world", "leetcode"};
  string         chars    = "welldonehoneyr";
  int            expect   = 10;
  int            actual   = solution->countCharacters(words, chars);
  LCD_EXPECT_EQ(expect, actual);
}

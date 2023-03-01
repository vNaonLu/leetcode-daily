// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Longest Palindrome by Concatenating Two Letter Words
//
// https://leetcode.com/problems/longest-palindrome-by-concatenating-two-letter-words/
//
// Question ID: 2131
// Difficult  : Medium
// Solve Date : 2022/09/12 18:25

#include <iosfwd>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2131. Longest Palindrome by Concatenating Two Letter Words|:
//
// You are given an array of strings |words|. Each element of |words| consists
// of two lowercase English letters. Create the longest possible palindrome by
// selecting some elements from |words| and concatenating them in any order.
// Each element can be selected at most once. Return the length of the longest
// palindrome that you can create. If it is impossible to create any palindrome,
// return |0|. A palindrome is a string that reads the same forward and
// backward.
//

LEETCODE_BEGIN_RESOLVING(2131, LongestPalindromeByConcatenatingTwoLetterWords,
                         Solution);

class Solution {
private:
  int hash(char x, char y) { return (x - 'a') * 100 + (y - 'a'); }

public:
  int longestPalindrome(vector<string> &words) {
    auto dict = unordered_map<int, int>();
    auto dupl = (int)0;
    auto rept = (int)0;
    for (auto &s : words) {
      auto find = dict.find(hash(s[1], s[0]));
      if (find != dict.end() && find->second > 0) {
        --find->second;
        dupl += 2;
      } else {
        ++dict[hash(s[0], s[1])];
      }
    }
    for (auto &v : dict) {
      auto sh = v.first;
      if (v.second > 0 && sh / 100 == sh % 100) {
        rept = 1;
        break;
      }
    }
    return 2 * rept + 2 * dupl;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= words.length <= 10⁵|
// * |words[i].length == 2|
// * |words[i]| consists of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: words = ["lc","cl","gg"]
// Output: 6
//
// One longest palindrome is "lc" + "gg" + "cl" = "lcggcl", of length 6.
// Note that "clgglc" is another longest palindrome that can be created.

LEETCODE_SOLUTION_UNITTEST(2131, LongestPalindromeByConcatenatingTwoLetterWords,
                           example_1) {
  auto           solution = MakeSolution();
  vector<string> words    = {"lc", "cl", "gg"};
  int            expect   = 6;
  int            actual   = solution->longestPalindrome(words);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: words = ["ab","ty","yt","lc","cl","ab"]
// Output: 8
//
// One longest palindrome is "ty" + "lc" + "cl" + "yt" = "tylcclyt", of
// length 8. Note that "lcyttycl" is another longest palindrome that can be
// created.

LEETCODE_SOLUTION_UNITTEST(2131, LongestPalindromeByConcatenatingTwoLetterWords,
                           example_2) {
  auto           solution = MakeSolution();
  vector<string> words    = {"ab", "ty", "yt", "lc", "cl", "ab"};
  int            expect   = 8;
  int            actual   = solution->longestPalindrome(words);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: words = ["cc","ll","xx"]
// Output: 2
//
// One longest palindrome is "cc", of length 2.
// Note that "ll" is another longest palindrome that can be created, and so is
// "xx".

LEETCODE_SOLUTION_UNITTEST(2131, LongestPalindromeByConcatenatingTwoLetterWords,
                           example_3) {
  auto           solution = MakeSolution();
  vector<string> words    = {"cc", "ll", "xx"};
  int            expect   = 2;
  int            actual   = solution->longestPalindrome(words);
  LCD_EXPECT_EQ(expect, actual);
}

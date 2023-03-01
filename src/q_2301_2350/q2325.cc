// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Decode the Message
//
// https://leetcode.com/problems/decode-the-message/
//
// Question ID: 2325
// Difficult  : Easy
// Solve Date : 2023/02/11 14:52

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2325. Decode the Message|:
//
// You are given the strings |key| and |message|, which represent a cipher key
// and a secret message, respectively. The steps to decode |message| are as
// follows:
//
//  1. Use the first appearance of all 26 lowercase English letters in |key| as
//  the order of the substitution table.
//
//  2. Align the substitution table with the regular English alphabet.
//
//  3. Each letter in |message| is then substituted using the table.
//
//  4. Spaces |' '| are transformed to themselves.
//
//  • For example, given |key = "happy boy"| (actual key would have at least one
//  instance of each letter in the alphabet), we have the partial substitution
//  table of ( |'h' -> 'a'|, |'a' -> 'b'|, |'p' -> 'c'|, |'y' -> 'd'|, |'b' ->
//  'e'|, |'o' -> 'f'|).
// Return the decoded message.
//

LEETCODE_BEGIN_RESOLVING(2325, DecodeTheMessage, Solution);

class Solution {
public:
  string decodeMessage(string key, string message) {
    char         curr_char = 'a';
    vector<char> mp(26, 0);
    for (auto c : key) {
      if (c == ' ') {
        continue;
      }
      if (mp[c - 'a'] == 0) {
        mp[c - 'a'] = curr_char++;
      }
    }
    for (auto &c : message) {
      if (c == ' ') {
        continue;
      }
      c = mp[c - 'a'];
    }
    return message;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |26 <= key.length <= 2000|
// * |key| consists of lowercase English letters and |' '|.
// * |key| contains every letter in the English alphabet ( |'a'| to |'z'|) at
// least once.
// * |1 <= message.length <= 2000|
// * |message| consists of lowercase English letters and |' '|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: key = "the quick brown fox jumps over the lazy dog", message = "vkbs
//  bs t suepuv"
// Output: "this is a secret"
//
// The diagram above shows the substitution table.
// It is obtained by taking the first appearance of each letter in "the quick
// brown fox jumps over the lazy dog".

LEETCODE_SOLUTION_UNITTEST(2325, DecodeTheMessage, example_1) {
  auto   solution = MakeSolution();
  string key      = "the quick brown fox jumps over the lazy dog";
  string message  = "vkbs bs t suepuv";
  string expect   = "this is a secret";
  string actual   = solution->decodeMessage(key, message);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: key = "eljuxhpwnyrdgtqkviszcfmabo", message = "zwx hnfx lqantp
//  mnoeius ycgk vcnjrdb"
// Output: "the five boxing wizards jump quickly"
//
// The diagram above shows the substitution table.
// It is obtained by taking the first appearance of each letter in
// "eljuxhpwnyrdgtqkviszcfmabo".

LEETCODE_SOLUTION_UNITTEST(2325, DecodeTheMessage, example_2) {
  auto   solution = MakeSolution();
  string key      = "eljuxhpwnyrdgtqkviszcfmabo";
  string message  = "zwx hnfx lqantp mnoeius ycgk vcnjrdb";
  string expect   = "the five boxing wizards jump quickly";
  string actual   = solution->decodeMessage(key, message);
  LCD_EXPECT_EQ(expect, actual);
}

// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Find the Lexicographically Largest String From the Box I
//
// https://leetcode.com/problems/find-the-lexicographically-largest-string-from-the-box-i/
//
// Question ID: 3403
// Difficult  : Medium
// Solve Date : 2025/06/04 18:46

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3403. Find the Lexicographically Largest String From the Box
// I|:
//
// You are given a string |word|, and an integer |numFriends|.
// Alice is organizing a game for her |numFriends| friends. There are multiple
// rounds in the game, where in each round:
//
//  • |word| is split into |numFriends| non-empty strings, such that no previous
//  round has had the exact same split.
//
//  • All the split words are put into a box.
// Find the lexicographically largest string from the box after all the rounds
// are finished.
//
//

LEETCODE_BEGIN_RESOLVING(3403, FindTheLexicographicallyLargestStringFromTheBoxI,
                         Solution);

class Solution {
public:
  string answerString(string word, int numFriends) {
    if (numFriends == 1) {
      return word;
    }
    string res = "";
    for (int i = 0; i < word.size(); ++i) {
      res = max(res, word.substr(i, word.size() - numFriends + 1));
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= word.length <= 5 * 10³|
// * |word| consists only of lowercase English letters.
// * |1 <= numFriends <= word.length|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: word = "dbca", numFriends = 2
// Output: "dbc"
//

LEETCODE_SOLUTION_UNITTEST(3403,
                           FindTheLexicographicallyLargestStringFromTheBoxI,
                           example_1) {
  auto   solution   = MakeSolution();
  string word       = "dbca";
  int    numFriends = 2;
  string expect     = "dbc";
  string actual     = solution->answerString(word, numFriends);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: word = "gggg", numFriends = 4
// Output: "g"
//

LEETCODE_SOLUTION_UNITTEST(3403,
                           FindTheLexicographicallyLargestStringFromTheBoxI,
                           example_2) {
  auto   solution   = MakeSolution();
  string word       = "gggg";
  int    numFriends = 4;
  string expect     = "g";
  string actual     = solution->answerString(word, numFriends);
  LCD_EXPECT_EQ(expect, actual);
}

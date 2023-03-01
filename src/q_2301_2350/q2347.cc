// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Best Poker Hand
//
// https://leetcode.com/problems/best-poker-hand/
//
// Question ID: 2347
// Difficult  : Easy
// Solve Date : 2023/01/30 15:42

#include <iosfwd>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2347. Best Poker Hand|:
//
// You are given an integer array |ranks| and a character array |suits|. You
// have |5| cards where the |iᵗʰ| card has a rank of |ranks[i]| and a suit of
// |suits[i]|. The following are the types of poker hands you can make from best
// to worst:
//
//  1. |"Flush"|: Five cards of the same suit.
//
//  2. |"Three of a Kind"|: Three cards of the same rank.
//
//  3. |"Pair"|: Two cards of the same rank.
//
//  4. |"High Card"|: Any single card.
// Return a string representing the best type of poker hand you can make with
// the given cards. Note that the return values are case-sensitive.
//

LEETCODE_BEGIN_RESOLVING(2347, BestPokerHand, Solution);

class Solution {
public:
  string bestHand(vector<int> &ranks, vector<char> &suits) {
    // Check flush
    auto suit_beg = suits.begin();
    while (suit_beg != suits.end()) {
      if (suit_beg + 1 == suits.end()) {
        return "Flush";
      }
      if (*(suit_beg + 1) != *suit_beg) {
        break;
      }
      ++suit_beg;
    }
    // Check Three of a Kind and Pair
    string                  res = "High Card";
    unordered_map<int, int> freq;
    for (auto x : ranks) {
      ++freq[x];
      if (freq[x] >= 3) {
        return "Three of a Kind";
      } else if (freq[x] == 2) {
        res = "Pair";
      }
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |ranks.length == suits.length == 5|
// * |1 <= ranks[i] <= 13|
// * |'a' <= suits[i] <= 'd'|
// * No two cards have the same rank and suit.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: ranks = [13,2,3,1,9], suits = ["a","a","a","a","a"]
// Output: "Flush"
//
// The hand with all the cards consists of 5 cards with the same suit, so we
// have a "Flush".

LEETCODE_SOLUTION_UNITTEST(2347, BestPokerHand, example_1) {
  auto         solution = MakeSolution();
  vector<int>  ranks    = {13, 2, 3, 1, 9};
  vector<char> suits    = {'a', 'a', 'a', 'a', 'a'};
  string       expect   = "Flush";
  string       actual   = solution->bestHand(ranks, suits);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: ranks = [4,4,2,4,4], suits = ["d","a","a","b","c"]
// Output: "Three of a Kind"
//
// The hand with the first, second, and fourth card consists of 3 cards with the
// same rank, so we have a "Three of a Kind". Note that we could also make a
// "Pair" hand but "Three of a Kind" is a better hand. Also note that other
// cards could be used to make the "Three of a Kind" hand.

LEETCODE_SOLUTION_UNITTEST(2347, BestPokerHand, example_2) {
  auto         solution = MakeSolution();
  vector<int>  ranks    = {4, 4, 2, 4, 4};
  vector<char> suits    = {'d', 'a', 'a', 'b', 'c'};
  string       expect   = "Three of a Kind";
  string       actual   = solution->bestHand(ranks, suits);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: ranks = [10,10,2,12,9], suits = ["a","b","c","a","d"]
// Output: "Pair"
//
// The hand with the first and second card consists of 2 cards with the same
// rank, so we have a "Pair". Note that we cannot make a "Flush" or a "Three of
// a Kind".

LEETCODE_SOLUTION_UNITTEST(2347, BestPokerHand, example_3) {
  auto         solution = MakeSolution();
  vector<int>  ranks    = {10, 10, 2, 12, 9};
  vector<char> suits    = {'a', 'b', 'c', 'a', 'd'};
  string       expect   = "Pair";
  string       actual   = solution->bestHand(ranks, suits);
  LCD_EXPECT_EQ(expect, actual);
}

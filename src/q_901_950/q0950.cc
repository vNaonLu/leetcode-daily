// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Reveal Cards In Increasing Order
//
// https://leetcode.com/problems/reveal-cards-in-increasing-order/
//
// Question ID: 950
// Difficult  : Medium
// Solve Date : 2024/04/10 21:46

#include <algorithm>
#include <deque>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |950. Reveal Cards In Increasing Order|:
//
// You are given an integer array |deck|. There is a deck of cards where every
// card has a unique integer. The integer on the |iᵗʰ| card is |deck[i]|. You
// can order the deck in any order you want. Initially, all the cards start face
// down (unrevealed) in one deck. You will do the following steps repeatedly
// until all cards are revealed:
//
//  1. Take the top card of the deck, reveal it, and take it out of the deck.
//
//  2. If there are still cards in the deck then put the next top card of the
//  deck at the bottom of the deck.
//
//  3. If there are still unrevealed cards, go back to step 1. Otherwise, stop.
// Return an ordering of the deck that would reveal the cards in increasing
// order. Note that the first entry in the answer is considered to be the top of
// the deck.
//
//

LEETCODE_BEGIN_RESOLVING(950, RevealCardsInIncreasingOrder, Solution);

class Solution {
public:
  vector<int> deckRevealedIncreasing(vector<int> &deck) {
    sort(deck.rbegin(), deck.rend());
    int        n = deck.size();
    deque<int> r;
    r.emplace_back(deck.front());
    for (int i = 1; i < n; ++i) {
      int b = r.back();
      r.pop_back();
      r.push_front(b);
      r.push_front(deck[i]);
    }
    return vector<int>(r.begin(), r.end());
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= deck.length <= 1000|
// * |1 <= deck[i] <= 10⁶|
// * All the values of |deck| are unique.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: deck = [17,13,11,2,3,5,7]
// Output: [2,13,3,11,5,17,7]
//

LEETCODE_SOLUTION_UNITTEST(950, RevealCardsInIncreasingOrder, example_1) {
  auto        solution = MakeSolution();
  vector<int> deck     = {17, 13, 11, 2, 3, 5, 7};
  vector<int> expect   = {2, 13, 3, 11, 5, 17, 7};
  vector<int> actual   = solution->deckRevealedIncreasing(deck);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #2]
//  Input: deck = [1,1000]
// Output: [1,1000]
//

LEETCODE_SOLUTION_UNITTEST(950, RevealCardsInIncreasingOrder, example_2) {
  auto        solution = MakeSolution();
  vector<int> deck     = {1, 1000};
  vector<int> expect   = {1, 1000};
  vector<int> actual   = solution->deckRevealedIncreasing(deck);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: [17,13,11,2,3,5,7]
// Output: [2,13,3,11,5,17,7]
//

LEETCODE_SOLUTION_UNITTEST(950, RevealCardsInIncreasingOrder,
                           extra_testcase_1) {
  auto        solution = MakeSolution();
  vector<int> deck     = {17, 13, 11, 2, 3, 5, 7};
  vector<int> expect   = {2, 13, 3, 11, 5, 17, 7};
  vector<int> actual   = solution->deckRevealedIncreasing(deck);
  EXPECT_ANYORDER_EQ(expect, actual);
}

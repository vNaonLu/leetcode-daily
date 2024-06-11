// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Hand of Straights
//
// https://leetcode.com/problems/hand-of-straights/
//
// Question ID: 846
// Difficult  : Medium
// Solve Date : 2024/06/06 11:00

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |846. Hand of Straights|:
//
// Alice has some number of cards and she wants to rearrange the cards into
// groups so that each group is of size |groupSize|, and consists of |groupSize|
// consecutive cards. Given an integer array |hand| where |hand[i]| is the value
// written on the |iᵗʰ| card and an integer |groupSize|, return |true| if she
// can rearrange the cards, or |false| otherwise.
//
//

LEETCODE_BEGIN_RESOLVING(846, HandOfStraights, Solution);

class Solution {
public:
  bool isNStraightHand(vector<int> &hand, int groupSize) {
    int n = hand.size();
    if (n % groupSize != 0) {
      return false;
    }

    sort(hand.begin(), hand.end());
    for (int i = 0; i < n; ++i) {
      if (hand[i] >= 0 && !helper(hand, groupSize, i, n)) {
        return false;
      }
    }
    return true;
  }

private:
  bool helper(vector<int> &hand, int size, int i, int n) {
    int next  = hand[i] + 1;
    hand[i++] = -1;
    int count = 1;
    while (i < n && count < size) {
      if (hand[i] == next) {
        next    = hand[i] + 1;
        hand[i] = -1;
        ++count;
      }
      ++i;
    }
    return count == size;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= hand.length <= 10⁴|
// * |0 <= hand[i] <= 10⁹|
// * |1 <= groupSize <= hand.length|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: hand = [1,2,3,6,2,3,4,7,8], groupSize = 3
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(846, HandOfStraights, example_1) {
  auto        solution  = MakeSolution();
  vector<int> hand      = {1, 2, 3, 6, 2, 3, 4, 7, 8};
  int         groupSize = 3;
  bool        expect    = true;
  bool        actual    = solution->isNStraightHand(hand, groupSize);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: hand = [1,2,3,4,5], groupSize = 4
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(846, HandOfStraights, example_2) {
  auto        solution  = MakeSolution();
  vector<int> hand      = {1, 2, 3, 4, 5};
  int         groupSize = 4;
  bool        expect    = false;
  bool        actual    = solution->isNStraightHand(hand, groupSize);
  LCD_EXPECT_EQ(expect, actual);
}

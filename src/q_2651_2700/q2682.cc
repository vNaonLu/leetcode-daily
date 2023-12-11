// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Find the Losers of the Circular Game
//
// https://leetcode.com/problems/find-the-losers-of-the-circular-game/
//
// Question ID: 2682
// Difficult  : Easy
// Solve Date : 2023/12/11 18:56

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2682. Find the Losers of the Circular Game|:
//
// There are |n| friends that are playing a game. The friends are sitting in a
// circle and are numbered from |1| to |n| in clockwise order. More formally,
// moving clockwise from the |iᵗʰ| friend brings you to the |(i+1)ᵗʰ| friend for
// |1 <= i < n|, and moving clockwise from the |nᵗʰ| friend brings you to the
// |1ˢᵗ| friend. The rules of the game are as follows: |1ˢᵗ| friend receives the
// ball.
//
//  • After that, |1ˢᵗ| friend passes it to the friend who is |k| steps away
//  from them in the clockwise direction.
//
//  • After that, the friend who receives the ball should pass it to the friend
//  who is |2 * k| steps away from them in the clockwise direction.
//
//  • After that, the friend who receives the ball should pass it to the friend
//  who is |3 * k| steps away from them in the clockwise direction, and so on
//  and so forth.
// In other words, on the |iᵗʰ| turn, the friend holding the ball should pass it
// to the friend who is |i * k| steps away from them in the clockwise direction.
// The game is finished when some friend receives the ball for the second time.
// The losers of the game are friends who did not receive the ball in the entire
// game. Given the number of friends, |n|, and an integer |k|, return the array
// answer, which contains the losers of the game in the ascending order.
//
//

LEETCODE_BEGIN_RESOLVING(2682, FindTheLosersOfTheCircularGame, Solution);

class Solution {
public:
  vector<int> circularGameLosers(int n, int k) {
    vector<int> cnt(n, 0);
    vector<int> res;
    int         beg = 0;
    int         i   = 1;
    cnt[beg]        = 1;
    while (cnt[beg] != 2) {
      beg = (beg + (i * k)) % n;
      ++cnt[beg];
      ++i;
    }
    for (int i = 0; i < n; ++i) {
      if (cnt[i] == 0) {
        res.emplace_back(i + 1);
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= k <= n <= 50|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 5, k = 2
// Output: [4,5]
//
// The game goes as follows:
// 1) Start at 1ˢᵗ friend and pass the ball to the friend who is 2 steps away
// from them - 3ʳᵈ friend. 2) 3ʳᵈ friend passes the ball to the friend who is
// 4 steps away from them - 2ⁿᵈ friend. 3) 2ⁿᵈ friend passes the ball to the
// friend who is 6 steps away from them - 3ʳᵈ friend. 4) The game ends as 3ʳᵈ
// friend receives the ball for the second time.

LEETCODE_SOLUTION_UNITTEST(2682, FindTheLosersOfTheCircularGame, example_1) {
  auto        solution = MakeSolution();
  int         n        = 5;
  int         k        = 2;
  vector<int> expect   = {4, 5};
  vector<int> actual   = solution->circularGameLosers(n, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 4, k = 4
// Output: [2,3,4]
//
// The game goes as follows:
// 1) Start at the 1ˢᵗ friend and pass the ball to the friend who is 4 steps
// away from them - 1ˢᵗ friend. 2) The game ends as 1ˢᵗ friend receives the
// ball for the second time.

LEETCODE_SOLUTION_UNITTEST(2682, FindTheLosersOfTheCircularGame, example_2) {
  auto        solution = MakeSolution();
  int         n        = 4;
  int         k        = 4;
  vector<int> expect   = {2, 3, 4};
  vector<int> actual   = solution->circularGameLosers(n, k);
  LCD_EXPECT_EQ(expect, actual);
}

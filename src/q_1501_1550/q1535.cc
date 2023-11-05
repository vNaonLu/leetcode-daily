// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Find the Winner of an Array Game
//
// https://leetcode.com/problems/find-the-winner-of-an-array-game/
//
// Question ID: 1535
// Difficult  : Medium
// Solve Date : 2023/11/05 12:13

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1535. Find the Winner of an Array Game|:
//
// Given an integer array |arr| of distinct integers and an integer |k|.
// A game will be played between the first two elements of the array (i.e.
// |arr[0]| and |arr[1]|). In each round of the game, we compare |arr[0]| with
// |arr[1]|, the larger integer wins and remains at position |0|, and the
// smaller integer moves to the end of the array. The game ends when an integer
// wins |k| consecutive rounds. Return the integer which will win the game. It
// is guaranteed that there will be a winner of the game.
//
//

LEETCODE_BEGIN_RESOLVING(1535, FindTheWinnerOfAnArrayGame, Solution);

class Solution {
public:
  int getWinner(vector<int> &arr, int k) {
    if (k == 1) {
      return max(arr[0], arr[1]);
    }

    if (k >= arr.size()) {
      return *max_element(arr.begin(), arr.end());
    }

    int res         = arr[0];
    int consecutive = 0;

    for (int i = 1; i < arr.size(); ++i) {
      if (res > arr[i]) {
        consecutive++;
      } else {
        res         = arr[i];
        consecutive = 1;
      }

      if (consecutive == k) {
        return res;
      }
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= arr.length <= 10⁵|
// * |1 <= arr[i] <= 10⁶|
// * |arr| contains distinct integers.
// * |1 <= k <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: arr = [2,1,3,5,4,6,7], k = 2
// Output: 5
//
// Let's see the rounds of the game:
// Round | arr | winner | win_count
//  1 | [2,1,3,5,4,6,7] | 2 | 1
//  2 | [2,3,5,4,6,7,1] | 3 | 1
//  3 | [3,5,4,6,7,1,2] | 5 | 1
//  4 | [5,4,6,7,1,2,3] | 5 | 2
// So we can see that 4 rounds will be played and 5 is the winner because it
// wins 2 consecutive games.

LEETCODE_SOLUTION_UNITTEST(1535, FindTheWinnerOfAnArrayGame, example_1) {
  auto        solution = MakeSolution();
  vector<int> arr      = {2, 1, 3, 5, 4, 6, 7};
  int         k        = 2;
  int         expect   = 5;
  int         actual   = solution->getWinner(arr, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: arr = [3,2,1], k = 10
// Output: 3
//
// 3 will win the first 10 rounds consecutively.

LEETCODE_SOLUTION_UNITTEST(1535, FindTheWinnerOfAnArrayGame, example_2) {
  auto        solution = MakeSolution();
  vector<int> arr      = {3, 2, 1};
  int         k        = 10;
  int         expect   = 3;
  int         actual   = solution->getWinner(arr, k);
  LCD_EXPECT_EQ(expect, actual);
}

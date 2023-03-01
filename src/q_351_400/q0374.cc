// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Guess Number Higher or Lower
//
// https://leetcode.com/problems/guess-number-higher-or-lower/
//
// Question ID: 374
// Difficult  : Easy
// Solve Date : 2021/10/12 11:20

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |374. Guess Number Higher or Lower|:
//
// We are playing the Guess Game. The game is as follows:
// I pick a number from |1| to |n|. You have to guess which number I picked.
// Every time you guess wrong, I will tell you whether the number I picked is
// higher or lower than your guess. You call a pre-defined API |int guess(int
// num)|, which returns three possible results:
//
//  • |-1|: Your guess is higher than the number I picked (i.e. |num > pick|).
//
//  • |1|: Your guess is lower than the number I picked (i.e. |num < pick|).
//
//  • |0|: your guess is equal to the number I picked (i.e. |num == pick|).
// Return the number that I picked.
//  
//

int pick = 0;

int guess(const int &guess) noexcept {
  if (guess == pick)
    return 0;
  else if (guess > pick)
    return -1;
  else
    return 1;
}

LEETCODE_BEGIN_RESOLVING(374, GuessNumberHigherOrLower, Solution);

class Solution {
public:
  int guessNumber(int n) {
    int l = 1, r = n;
    int mid = 0;
    while (l <= r) {
      mid   = l + (r - l) / 2;
      int g = guess(mid);
      if (g < 0) {
        r = mid - 1;
      } else if (g > 0) {
        l = mid + 1;
      } else
        break;
    }
    return mid;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n <= 2³¹ - 1|
// * |1 <= pick <= n|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 10, pick = 6
// Output: 6
//

LEETCODE_SOLUTION_UNITTEST(374, GuessNumberHigherOrLower, example_1) {
  auto solution = MakeSolution();
  pick          = 6;
  int n         = 10;
  int expect    = 6;
  int actual    = solution->guessNumber(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 1, pick = 1
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(374, GuessNumberHigherOrLower, example_2) {
  auto solution = MakeSolution();
  pick          = 1;
  int n         = 1;
  int expect    = 1;
  int actual    = solution->guessNumber(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: n = 2, pick = 1
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(374, GuessNumberHigherOrLower, example_3) {
  auto solution = MakeSolution();
  pick          = 1;
  int n         = 2;
  int expect    = 1;
  int actual    = solution->guessNumber(n);
  LCD_EXPECT_EQ(expect, actual);
}

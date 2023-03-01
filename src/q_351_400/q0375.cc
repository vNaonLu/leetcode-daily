// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Guess Number Higher or Lower II
//
// https://leetcode.com/problems/guess-number-higher-or-lower-ii/
//
// Question ID: 375
// Difficult  : Medium
// Solve Date : 2022/02/17 22:24

#include <iosfwd>
#include <limits>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |375. Guess Number Higher or Lower II|:
//
// We are playing the Guessing Game. The game will work as follows:
//
//  1. I pick a number between  |1| and  |n|.
//
//  2. You guess a number.
//
//  3. If you guess the right number, you win the game.
//
//  4. If you guess the wrong number, then I will tell you whether the number I
//  picked is higher or lower, and you will continue guessing.
//
//  5. Every time you guess a wrong number  |x|, you will pay  |x| dollars. If
//  you run out of money, you lose the game.
// Given a particular  |n|, return the minimum amount of money you need
// to guarantee a win regardless of what number I pick.  
//

LEETCODE_BEGIN_RESOLVING(375, GuessNumberHigherOrLowerII, Solution);

class Solution {
private:
  vector<vector<int>> memos;
  int                 helper(int beg, int end) {
    if (beg >= end)
      return 0;
    if (memos[beg][end] == -1) {
      int res = numeric_limits<int>::max();
      for (int i = beg; i <= end; ++i) {
        int temp = i;
        temp += max(helper(beg, i - 1), helper(i + 1, end));
        res = min(res, temp);
      }
      memos[beg][end] = res;
    }
    return memos[beg][end];
  }

public:
  int getMoneyAmount(int n) {
    memos.resize(n + 1, vector<int>(n + 1, -1));
    return helper(1, n);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n <= 200|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 10
// Output: 16
//
// The winning strategy is as follows:
// - The range is [1,10]. Guess 7.
//   - If this is my number, your total is $0. Otherwise, you pay $7.
//   - If my number is higher, the range is [8,10]. Guess 9.
//   - If this is my number, your total is $7. Otherwise, you pay $9.
//   - If my number is higher, it must be 10. Guess 10. Your total is $7 + $9 =
// $16.   - If my number is lower, it must be 8. Guess 8. Your total is $7 + $9
// = $16.   - If my number is lower, the range is [1,6]. Guess 3.   - If this is
// my number, your total is $7. Otherwise, you pay $3.   - If my number is
// higher, the range is [4,6]. Guess 5.   - If this is my number, your total is
// $7 + $3 = $10. Otherwise, you pay $5.   - If my number is higher, it must
// be 6. Guess 6. Your total is $7 + $3 + $5 = $15.   - If my number is lower,
// it must be 4. Guess 4. Your total is $7 + $3 + $5 = $15.   - If my number is
// lower, the range is [1,2]. Guess 1.   - If this is my number, your total is
// $7 + $3 = $10. Otherwise, you pay $1.   - If my number is higher, it must
// be 2. Guess 2. Your total is $7 + $3 + $1 = $11. The worst case in all these
// scenarios is that you pay $16. Hence, you only need $16 to guarantee a win.

LEETCODE_SOLUTION_UNITTEST(375, GuessNumberHigherOrLowerII, example_1) {
  auto solution = MakeSolution();
  int  n        = 10;
  int  expect   = 16;
  int  actual   = solution->getMoneyAmount(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 1
// Output: 0
//
//  There is only one possible number, so you can guess 1 and not have to pay
// anything.

LEETCODE_SOLUTION_UNITTEST(375, GuessNumberHigherOrLowerII, example_2) {
  auto solution = MakeSolution();
  int  n        = 1;
  int  expect   = 0;
  int  actual   = solution->getMoneyAmount(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: n = 2
// Output: 1
//
//  There are two possible numbers, 1 and 2.
// - Guess 1.
//   - If this is my number, your total is $0. Otherwise, you pay $1.
//   - If my number is higher, it must be 2. Guess 2. Your total is $1.
// The worst case is that you pay $1.

LEETCODE_SOLUTION_UNITTEST(375, GuessNumberHigherOrLowerII, example_3) {
  auto solution = MakeSolution();
  int  n        = 2;
  int  expect   = 1;
  int  actual   = solution->getMoneyAmount(n);
  LCD_EXPECT_EQ(expect, actual);
}

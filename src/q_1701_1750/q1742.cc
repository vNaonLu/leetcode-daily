// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Maximum Number of Balls in a Box
//
// https://leetcode.com/problems/maximum-number-of-balls-in-a-box/
//
// Question ID: 1742
// Difficult  : Easy
// Solve Date : 2023/09/07 16:12

#include <iosfwd>
#include <unordered_map>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1742. Maximum Number of Balls in a Box|:
//
// You are working in a ball factory where you have |n| balls numbered from
// |lowLimit| up to |highLimit| inclusive (i.e., |n == highLimit - lowLimit +
// 1|), and an infinite number of boxes numbered from |1| to |infinity|. Your
// job at this factory is to put each ball in the box with a number equal to the
// sum of digits of the ball's number. For example, the ball number |321| will
// be put in the box number |3 + 2 + 1 = 6| and the ball number |10| will be put
// in the box number |1 + 0 = 1|. Given two integers |lowLimit| and |highLimit|,
// return the number of balls in the box with the most balls.
//
//

LEETCODE_BEGIN_RESOLVING(1742, MaximumNumberOfBallsInABox, Solution);

class Solution {
public:
  int countBalls(int lowLimit, int highLimit) {
    unordered_map<int, int> mp;
    int                     res = numeric_limits<int>::min();
    for (int i = lowLimit; i <= highLimit; ++i) {
      int sum = 0;
      int tmp = i;
      while (tmp > 0) {
        sum += tmp % 10;
        tmp /= 10;
      }
      ++mp[sum];
      res = max(res, mp[sum]);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= lowLimit <= highLimit <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: lowLimit = 1, highLimit = 10
// Output: 2
//
// Box Number: 1 2 3 4 5 6 7 8 9 10 11 ...
// Ball Count: 2 1 1 1 1 1 1 1 1 0 0 ...
// Box 1 has the most number of balls with 2 balls.

LEETCODE_SOLUTION_UNITTEST(1742, MaximumNumberOfBallsInABox, example_1) {
  auto solution  = MakeSolution();
  int  lowLimit  = 1;
  int  highLimit = 10;
  int  expect    = 2;
  int  actual    = solution->countBalls(lowLimit, highLimit);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: lowLimit = 5, highLimit = 15
// Output: 2
//
// Box Number: 1 2 3 4 5 6 7 8 9 10 11 ...
// Ball Count: 1 1 1 1 2 2 1 1 1 0 0 ...
// Boxes 5 and 6 have the most number of balls with 2 balls in each.

LEETCODE_SOLUTION_UNITTEST(1742, MaximumNumberOfBallsInABox, example_2) {
  auto solution  = MakeSolution();
  int  lowLimit  = 5;
  int  highLimit = 15;
  int  expect    = 2;
  int  actual    = solution->countBalls(lowLimit, highLimit);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: lowLimit = 19, highLimit = 28
// Output: 2
//
// Box Number: 1 2 3 4 5 6 7 8 9 10 11 12 ...
// Ball Count: 0 1 1 1 1 1 1 1 1 2 0 0 ...
// Box 10 has the most number of balls with 2 balls.

LEETCODE_SOLUTION_UNITTEST(1742, MaximumNumberOfBallsInABox, example_3) {
  auto solution  = MakeSolution();
  int  lowLimit  = 19;
  int  highLimit = 28;
  int  expect    = 2;
  int  actual    = solution->countBalls(lowLimit, highLimit);
  LCD_EXPECT_EQ(expect, actual);
}

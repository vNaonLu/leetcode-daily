// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Distribute Money to Maximum Children
//
// https://leetcode.com/problems/distribute-money-to-maximum-children/
//
// Question ID: 2591
// Difficult  : Easy
// Solve Date : 2023/12/04 19:27

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2591. Distribute Money to Maximum Children|:
//
// You are given an integer |money| denoting the amount of money (in dollars)
// that you have and another integer |children| denoting the number of children
// that you must distribute the money to. You have to distribute the money
// according to the following rules:
//
//  • All money must be distributed.
//
//  • Everyone must receive at least |1| dollar.
//
//  • Nobody receives |4| dollars.
// Return the maximum number of children who may receive exactly |8| dollars if
// you distribute the money according to the aforementioned rules. If there is
// no way to distribute the money, return |-1|.
//
//

LEETCODE_BEGIN_RESOLVING(2591, DistributeMoneyToMaximumChildren, Solution);

class Solution {
public:
  int distMoney(int money, int children) {
    int res = 0;
    if (children > money) {
      return -1;
    }

    vector<int> v(children, 1);
    money -= children;

    for (int i = 0; i < children - 1; ++i) {
      if (money > 6) {
        ++res;
        v[i] += 7;
        money -= 7;
      }
    }

    if (money == 7) {
      ++res;
    } else if (money == 3) {
      if (v[children - 2] == 8) {
        --res;
      }
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= money <= 200|
// * |2 <= children <= 30|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: money = 20, children = 3
// Output: 1
//
// The maximum number of children with 8 dollars will be 1. One of the ways to
// distribute the money is:
// - 8 dollars to the first child.
// - 9 dollars to the second child.
// - 3 dollars to the third child.
// It can be proven that no distribution exists such that number of children
// getting 8 dollars is greater than 1.

LEETCODE_SOLUTION_UNITTEST(2591, DistributeMoneyToMaximumChildren, example_1) {
  auto solution = MakeSolution();
  int  money    = 20;
  int  children = 3;
  int  expect   = 1;
  int  actual   = solution->distMoney(money, children);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: money = 16, children = 2
// Output: 2
//
// Each child can be given 8 dollars.

LEETCODE_SOLUTION_UNITTEST(2591, DistributeMoneyToMaximumChildren, example_2) {
  auto solution = MakeSolution();
  int  money    = 16;
  int  children = 2;
  int  expect   = 2;
  int  actual   = solution->distMoney(money, children);
  LCD_EXPECT_EQ(expect, actual);
}

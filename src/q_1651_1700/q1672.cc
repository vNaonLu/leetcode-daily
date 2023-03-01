// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Richest Customer Wealth
//
// https://leetcode.com/problems/richest-customer-wealth/
//
// Question ID: 1672
// Difficult  : Easy
// Solve Date : 2022/01/31 11:26

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1672. Richest Customer Wealth|:
//
// You are given an |m x n| integer grid |accounts| where |accounts[i][j]| is
// the amount of money the |i​​​​​^{​​​​​​th}​​​​|
// customer has in the |j​​​​​^{​​​​​​th}|​​​​
// bank. Return the wealth that the richest customer has. A customer's wealth is
// the amount of money they have in all their bank accounts. The richest
// customer is the customer that has the maximum wealth.  
//

LEETCODE_BEGIN_RESOLVING(1672, RichestCustomerWealth, Solution);

class Solution {
public:
  int maximumWealth(vector<vector<int>> &accounts) {
    int res = 0;
    for (const auto &v : accounts) {
      int curr = 0;
      for (const auto &x : v) {
        curr += x;
      }
      res = max(res, curr);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |m == accounts.length|
// * |n == accounts[i].length|
// * |1 <= m, n <= 50|
// * |1 <= accounts[i][j] <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: accounts = [[1,2,3],[3,2,1]]
// Output: 6
//
// :
// |1st customer has wealth = 1 + 2 + 3 = 6
// | |2nd customer has wealth = 3 + 2 + 1 = 6
// |Both customers are considered the richest with a wealth of 6 each, so
// return 6.

LEETCODE_SOLUTION_UNITTEST(1672, RichestCustomerWealth, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> accounts = {
      {1, 2, 3},
      {3, 2, 1}
  };
  int expect = 6;
  int actual = solution->maximumWealth(accounts);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: accounts = [[1,5],[7,3],[3,5]]
// Output: 10
//
// :
// 1st customer has wealth = 6
// 2nd customer has wealth = 10
// 3rd customer has wealth = 8
// The 2nd customer is the richest with a wealth of 10.

LEETCODE_SOLUTION_UNITTEST(1672, RichestCustomerWealth, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> accounts = {
      {1, 5},
      {7, 3},
      {3, 5}
  };
  int expect = 10;
  int actual = solution->maximumWealth(accounts);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: accounts = [[2,8,7],[7,1,3],[1,9,5]]
// Output: 17
//

LEETCODE_SOLUTION_UNITTEST(1672, RichestCustomerWealth, example_3) {
  auto                solution = MakeSolution();
  vector<vector<int>> accounts = {
      {2, 8, 7},
      {7, 1, 3},
      {1, 9, 5}
  };
  int expect = 17;
  int actual = solution->maximumWealth(accounts);
  LCD_EXPECT_EQ(expect, actual);
}

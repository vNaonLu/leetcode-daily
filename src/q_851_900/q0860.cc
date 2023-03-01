// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Lemonade Change
//
// https://leetcode.com/problems/lemonade-change/
//
// Question ID: 860
// Difficult  : Easy
// Solve Date : 2022/05/12 18:11

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |860. Lemonade Change|:
//
// At a lemonade stand, each lemonade costs |$5|. Customers are standing in a
// queue to buy from you and order one at a time (in the order specified by
// bills). Each customer will only buy one lemonade and pay with either a |$5|,
// |$10|, or |$20| bill. You must provide the correct change to each customer so
// that the net transaction is that the customer pays |$5|. Note that you do not
// have any change in hand at first. Given an integer array |bills| where
// |bills[i]| is the bill the |iᵗʰ| customer pays, return |true| if you can
// provide every customer with the correct change, or |false| otherwise.  
//

LEETCODE_BEGIN_RESOLVING(860, LemonadeChange, Solution);

class Solution {
public:
  bool lemonadeChange(vector<int> &bills) {
    vector<int> coins(20);
    for (auto &x : bills) {
      if (x == 5) {
        ++coins[5];
      } else if (x == 10) {
        if (coins[5] == 0) {
          return false;
        }
        --coins[5];
        ++coins[10];
      } else if (x == 20) {
        if (coins[10] > 0 && coins[5] > 0) {
          --coins[10];
          --coins[5];
        } else if (coins[5] >= 3) {
          coins[5] -= 3;
        } else {
          return false;
        }
      }
    }

    return true;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= bills.length <= 10⁵|
// * |bills[i]| is either |5|, |10|, or |20|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: bills = [5,5,5,10,20]
// Output: true
//
// From the first 3 customers, we collect three $5 bills in order.
// From the fourth customer, we collect a $10 bill and give back a $5.
// From the fifth customer, we give a $10 bill and a $5 bill.
// Since all customers got correct change, we output true.

LEETCODE_SOLUTION_UNITTEST(860, LemonadeChange, example_1) {
  auto        solution = MakeSolution();
  vector<int> bills    = {5, 5, 5, 10, 20};
  bool        expect   = true;
  bool        actual   = solution->lemonadeChange(bills);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: bills = [5,5,10,10,20]
// Output: false
//
// From the first two customers in order, we collect two $5 bills.
// For the next two customers in order, we collect a $10 bill and give back a $5
// bill. For the last customer, we can not give the change of $15 back because
// we only have two $10 bills. Since not every customer received the correct
// change, the answer is false.

LEETCODE_SOLUTION_UNITTEST(860, LemonadeChange, example_2) {
  auto        solution = MakeSolution();
  vector<int> bills    = {5, 5, 10, 10, 20};
  bool        expect   = false;
  bool        actual   = solution->lemonadeChange(bills);
  LCD_EXPECT_EQ(expect, actual);
}

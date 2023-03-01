// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Count All Valid Pickup and Delivery Options
//
// https://leetcode.com/problems/count-all-valid-pickup-and-delivery-options/
//
// Question ID: 1359
// Difficult  : Hard
// Solve Date : 2022/03/06 12:49

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1359. Count All Valid Pickup and Delivery Options|:
//
// Given |n| orders, each order consist in pickup and delivery services. 
// Count all valid pickup/delivery possible sequences such that delivery(i) is
// always after of pickup(i).  Since the answer may be too large, return it
// modulo 10^9 + 7.  
//

LEETCODE_BEGIN_RESOLVING(1359, CountAllValidPickupAndDeliveryOptions, Solution);

class Solution {
private:
  constexpr static int kMod = 1e9 + 7;
  vector<vector<int>>  memo;
  int                  helper(long unpicked, long undelivered) {
    if (unpicked == 0 && undelivered == 0) {
      return 1;
    }

    if (unpicked < 0 || undelivered < 0 || undelivered < unpicked) {
      return 0;
    }

    if (memo[unpicked][undelivered]) {
      return memo[unpicked][undelivered];
    }

    long res = 0;
    res += unpicked * helper(unpicked - 1, undelivered);
    res %= kMod;
    res += (undelivered - unpicked) * helper(unpicked, undelivered - 1);
    res %= kMod;
    return memo[unpicked][undelivered] = res;
  }

public:
  int countOrders(int n) {
    memo.resize(n + 1, vector<int>(n + 1, 0));
    return helper(n, n);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n <= 500|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 1
// Output: 1
//
// Unique order (P1, D1), Delivery 1 always is after of Pickup 1.

LEETCODE_SOLUTION_UNITTEST(1359, CountAllValidPickupAndDeliveryOptions,
                           example_1) {
  auto solution = MakeSolution();
  int  n        = 1;
  int  expect   = 1;
  int  actual   = solution->countOrders(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 2
// Output: 6
//
// All possible orders:
// (P1,P2,D1,D2), (P1,P2,D2,D1), (P1,D1,P2,D2), (P2,P1,D1,D2), (P2,P1,D2,D1) and
// (P2,D2,P1,D1). This is an invalid order (P1,D2,P2,D1) because Pickup 2 is
// after of Delivery 2.

LEETCODE_SOLUTION_UNITTEST(1359, CountAllValidPickupAndDeliveryOptions,
                           example_2) {
  auto solution = MakeSolution();
  int  n        = 2;
  int  expect   = 6;
  int  actual   = solution->countOrders(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: n = 3
// Output: 90
//

LEETCODE_SOLUTION_UNITTEST(1359, CountAllValidPickupAndDeliveryOptions,
                           example_3) {
  auto solution = MakeSolution();
  int  n        = 3;
  int  expect   = 90;
  int  actual   = solution->countOrders(n);
  LCD_EXPECT_EQ(expect, actual);
}

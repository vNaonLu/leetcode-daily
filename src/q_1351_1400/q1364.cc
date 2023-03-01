// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Number of Trusted Contacts of a Customer
//
// https://leetcode.com/problems/number-of-trusted-contacts-of-a-customer/
//
// Question ID: 1364
// Difficult  : Medium
// Solve Date : 2022/06/24 18:06

#include <queue>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1364. Number of Trusted Contacts of a Customer|:
//
// This question is marked as premium question.

LEETCODE_BEGIN_RESOLVING(1364, NumberOfTrustedContactsOfACustomer, Solution);

class Solution {
public:
  bool isPossible(vector<int> &target) {
    priority_queue<int> pq;
    int64_t             sum = 0;
    for (auto &x : target) {
      pq.emplace(x);
      sum += x;
    }

    while (pq.top() != 1) {
      sum -= pq.top();
      if (sum == 0 || sum >= pq.top()) {
        return false;
      }

      int64_t old = pq.top() % sum;
      if (sum != 1 && old == 0) {
        return false;
      }

      pq.pop();
      pq.emplace(old);
      sum += old;
    }

    return true;
  }
};

LEETCODE_END_RESOLVING(Solution);

LEETCODE_SOLUTION_UNITTEST(1364, NumberOfTrustedContactsOfACustomer,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> target   = {9, 3, 5};
  bool        exp      = true;
  int         act      = solution->isPossible(target);
  LCD_EXPECT_EQ(act, exp);
}

LEETCODE_SOLUTION_UNITTEST(1364, NumberOfTrustedContactsOfACustomer,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> target   = {1, 1, 1, 2};
  bool        exp      = false;
  int         act      = solution->isPossible(target);
  LCD_EXPECT_EQ(act, exp);
}

LEETCODE_SOLUTION_UNITTEST(1364, NumberOfTrustedContactsOfACustomer,
                           example_3) {
  auto        solution = MakeSolution();
  vector<int> target   = {8, 5};
  bool        exp      = true;
  int         act      = solution->isPossible(target);
  LCD_EXPECT_EQ(act, exp);
}

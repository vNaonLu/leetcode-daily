// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Time Needed to Buy Tickets
//
// https://leetcode.com/problems/time-needed-to-buy-tickets/
//
// Question ID: 2073
// Difficult  : Easy
// Solve Date : 2023/09/25 20:57

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2073. Time Needed to Buy Tickets|:
//
// There are |n| people in a line queuing to buy tickets, where the |0ᵗʰ| person
// is at the front of the line and the |(n - 1)ᵗʰ| person is at the back of the
// line. You are given a 0-indexed integer array |tickets| of length |n| where
// the number of tickets that the |iᵗʰ| person would like to buy is
// |tickets[i]|. Each person takes exactly 1 second to buy a ticket. A person
// can only buy 1 ticket at a time and has to go back to the end of the line
// (which happens instantaneously) in order to buy more tickets. If a person
// does not have any tickets left to buy, the person will leave the line. Return
// the time taken for the person at position |k| (0-indexed) to finish buying
// tickets.
//
//

LEETCODE_BEGIN_RESOLVING(2073, TimeNeededToBuyTickets, Solution);

class Solution {
public:
  int timeRequiredToBuy(vector<int> &tickets, int k) {
    int res = 0;
    while (true) {
      for (int i = 0; i < tickets.size(); ++i) {
        if (tickets[i] == 0) {
          continue;
        }

        --tickets[i];
        ++res;

        if (tickets[k] == 0) {
          return res;
        }
      }
    }
    return -1;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |n == tickets.length|
// * |1 <= n <= 100|
// * |1 <= tickets[i] <= 100|
// * |0 <= k < n|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: tickets = [2,3,2], k = 2
// Output: 6
//
// - In the first pass, everyone in the line buys a ticket and the line becomes
// [1, 2, 1].
// - In the second pass, everyone in the line buys a ticket and the line becomes
// [0, 1, 0]. The person at position 2 has successfully bought 2 tickets and it
// took 3 + 3 = 6 seconds.

LEETCODE_SOLUTION_UNITTEST(2073, TimeNeededToBuyTickets, example_1) {
  auto        solution = MakeSolution();
  vector<int> tickets  = {2, 3, 2};
  int         k        = 2;
  int         expect   = 6;
  int         actual   = solution->timeRequiredToBuy(tickets, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: tickets = [5,1,1,1], k = 0
// Output: 8
//
// - In the first pass, everyone in the line buys a ticket and the line becomes
// [4, 0, 0, 0].
// - In the next 4 passes, only the person in position 0 is buying tickets.
// The person at position 0 has successfully bought 5 tickets and it took 4 + 1
// + 1 + 1 + 1 = 8 seconds.

LEETCODE_SOLUTION_UNITTEST(2073, TimeNeededToBuyTickets, example_2) {
  auto        solution = MakeSolution();
  vector<int> tickets  = {5, 1, 1, 1};
  int         k        = 0;
  int         expect   = 8;
  int         actual   = solution->timeRequiredToBuy(tickets, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: [84,49,5,24,70,77,87,8]
// 3
// Output: 154
//

LEETCODE_SOLUTION_UNITTEST(2073, TimeNeededToBuyTickets, extra_testcase_1) {
  auto        solution = MakeSolution();
  vector<int> tickets  = {84, 49, 5, 24, 70, 77, 87, 8};
  int         k        = 3;
  int         expect   = 154;
  int         actual   = solution->timeRequiredToBuy(tickets, k);
  LCD_EXPECT_EQ(expect, actual);
}

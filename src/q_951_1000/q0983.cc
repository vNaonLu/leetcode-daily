// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimum Cost For Tickets
//
// https://leetcode.com/problems/minimum-cost-for-tickets/
//
// Question ID: 983
// Difficult  : Medium
// Solve Date : 2022/03/11 18:27

#include <iosfwd>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |983. Minimum Cost For Tickets|:
//
// You have planned some train traveling one year in advance. The days of the
// year in which you will travel are given as an integer array |days|. Each day
// is an integer from |1| to |365|. Train tickets are sold in three different
// ways:
//
//  • a 1-day pass is sold for |costs[0]| dollars,
//
//  • a 7-day pass is sold for |costs[1]| dollars, and
//
//  • a 30-day pass is sold for |costs[2]| dollars.
// The passes allow that many days of consecutive travel.
//
//  • For example, if we get a 7-day pass on day |2|, then we can travel for |7|
//  days: |2|, |3|, |4|, |5|, |6|, |7|, and |8|.
// Return the minimum number of dollars you need to travel every day in the
// given list of days.  
//

LEETCODE_BEGIN_RESOLVING(983, MinimumCostForTickets, Solution);

class Solution {
private:
  vector<int>             costs;
  unordered_set<int>      dayset;
  unordered_map<int, int> memos;

  int helper(int x) {
    if (x > 365)
      return 0;
    auto it = memos.find(x);
    if (it != memos.end())
      return it->second;

    int res;
    if (dayset.count(x)) {
      res = min({helper(x + 1) + costs[0], helper(x + 7) + costs[1],
                 helper(x + 30) + costs[2]});
    } else {
      res = helper(x + 1);
    }

    memos[x] = res;
    return res;
  }

public:
  int mincostTickets(vector<int> &days, vector<int> &costs) {
    this->costs = move(costs);
    for (const auto &x : days)
      dayset.insert(x);

    return helper(1);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= days.length <= 365|
// * |1 <= days[i] <= 365|
// * |days| is in strictly increasing order.
// * |costs.length == 3|
// * |1 <= costs[i] <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: days = [1,4,6,7,8,20], costs = [2,7,15]
// Output: 11
//
// For example, here is one way to buy passes that lets you travel your travel
// plan: On day 1, you bought a 1-day pass for costs[0] = $2, which covered
// day 1. On day 3, you bought a 7-day pass for costs[1] = $7, which covered
// days 3, 4, ..., 9. On day 20, you bought a 1-day pass for costs[0] = $2,
// which covered day 20. In total, you spent $11 and covered all the days of
// your travel.

LEETCODE_SOLUTION_UNITTEST(983, MinimumCostForTickets, example_1) {
  auto        solution = MakeSolution();
  vector<int> days     = {1, 4, 6, 7, 8, 20};
  vector<int> costs    = {2, 7, 15};
  int         expect   = 11;
  int         actual   = solution->mincostTickets(days, costs);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: days = [1,2,3,4,5,6,7,8,9,10,30,31], costs = [2,7,15]
// Output: 17
//
// For example, here is one way to buy passes that lets you travel your travel
// plan: On day 1, you bought a 30-day pass for costs[2] = $15 which covered
// days 1, 2, ..., 30. On day 31, you bought a 1-day pass for costs[0] = $2
// which covered day 31. In total, you spent $17 and covered all the days of
// your travel.

LEETCODE_SOLUTION_UNITTEST(983, MinimumCostForTickets, example_2) {
  auto        solution = MakeSolution();
  vector<int> days     = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 30, 31};
  vector<int> costs    = {2, 7, 15};
  int         expect   = 17;
  int         actual   = solution->mincostTickets(days, costs);
  LCD_EXPECT_EQ(expect, actual);
}

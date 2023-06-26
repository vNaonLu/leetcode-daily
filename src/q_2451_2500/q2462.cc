// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Total Cost to Hire K Workers
//
// https://leetcode.com/problems/total-cost-to-hire-k-workers/
//
// Question ID: 2462
// Difficult  : Medium
// Solve Date : 2023/06/26 13:35

#include <iosfwd>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2462. Total Cost to Hire K Workers|:
//
// You are given a 0-indexed integer array |costs| where |costs[i]| is the cost
// of hiring the |iᵗʰ| worker. You are also given two integers |k| and
// |candidates|. We want to hire exactly |k| workers according to the following
// rules:
//
//  • You will run |k| sessions and hire exactly one worker in each session.
//
//  • In each hiring session, choose the worker with the lowest cost from either
//  the first |candidates| workers or the last |candidates| workers. Break the
//  tie by the smallest index.
//
//
//    • For example, if |costs = [3,2,7,7,1,2]| and |candidates = 2|, then in
//    the first hiring session, we will choose the |4ᵗʰ| worker because they
//    have the lowest cost |[3,2,7,7,1,2]|.
//
//    • In the second hiring session, we will choose |1ˢᵗ| worker because they
//    have the same lowest cost as |4ᵗʰ| worker but they have the smallest index
//    |[3,2,7,7,2]|. Please note that the indexing may be changed in the
//    process.
//
//
//
//  • If there are fewer than candidates workers remaining, choose the worker
//  with the lowest cost among them. Break the tie by the smallest index.
//
//  • A worker can only be chosen once.
// Return the total cost to hire exactly |k| workers.
//
//

LEETCODE_BEGIN_RESOLVING(2462, TotalCostToHireKWorkers, Solution);

class Solution {
public:
  long long totalCost(vector<int> &costs, int k, int candidates) {
    int64_t                                        res = 0;
    priority_queue<int, vector<int>, greater<int>> pq1;
    priority_queue<int, vector<int>, greater<int>> pq2;
    int                                            lo = 0;
    int                                            hi = costs.size() - 1;
    while (k > 0) {
      while (pq1.size() < candidates && lo <= hi) {
        pq1.emplace(costs[lo++]);
      }
      while (pq2.size() < candidates && lo <= hi) {
        pq2.emplace(costs[hi--]);
      }
      if (pq1.empty()) {
        res += pq2.top();
        pq2.pop();
      } else if (pq2.empty()) {
        res += pq1.top();
        pq1.pop();
      } else {
        if (pq1.top() <= pq2.top()) {
          res += pq1.top();
          pq1.pop();
        } else {
          res += pq2.top();
          pq2.pop();
        }
      }
      --k;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= costs.length <= 10^{5 }|
// * |1 <= costs[i] <= 10⁵|
// * |1 <= k, candidates <= costs.length|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: costs = [17,12,10,2,7,2,11,20,8], k = 3, candidates = 4
// Output: 11
//
// We hire 3 workers in total. The total cost is initially 0.
// - In the first hiring round we choose the worker from
// [17,12,10,2,7,2,11,20,8]. The lowest cost is 2, and we break the tie by the
// smallest index, which is 3. The total cost = 0 + 2 = 2.
// - In the second hiring round we choose the worker from
// [17,12,10,7,2,11,20,8]. The lowest cost is 2 (index 4). The total cost = 2 +
// 2 = 4.
// - In the third hiring round we choose the worker from [17,12,10,7,11,20,8].
// The lowest cost is 7 (index 3). The total cost = 4 + 7 = 11. Notice that the
// worker with index 3 was common in the first and last four workers. The total
// hiring cost is 11.

LEETCODE_SOLUTION_UNITTEST(2462, TotalCostToHireKWorkers, example_1) {
  auto        solution   = MakeSolution();
  vector<int> costs      = {17, 12, 10, 2, 7, 2, 11, 20, 8};
  int         k          = 3;
  int         candidates = 4;
  long long   expect     = 11;
  long long   actual     = solution->totalCost(costs, k, candidates);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: costs = [1,2,4,1], k = 3, candidates = 3
// Output: 4
//
// We hire 3 workers in total. The total cost is initially 0.
// - In the first hiring round we choose the worker from [1,2,4,1]. The lowest
// cost is 1, and we break the tie by the smallest index, which is 0. The total
// cost = 0 + 1 = 1. Notice that workers with index 1 and 2 are common in the
// first and last 3 workers.
// - In the second hiring round we choose the worker from [2,4,1]. The lowest
// cost is 1 (index 2). The total cost = 1 + 1 = 2.
// - In the third hiring round there are less than three candidates. We choose
// the worker from the remaining workers [2,4]. The lowest cost is 2 (index 0).
// The total cost = 2 + 2 = 4. The total hiring cost is 4.

LEETCODE_SOLUTION_UNITTEST(2462, TotalCostToHireKWorkers, example_2) {
  auto        solution   = MakeSolution();
  vector<int> costs      = {1, 2, 4, 1};
  int         k          = 3;
  int         candidates = 3;
  long long   expect     = 4;
  long long   actual     = solution->totalCost(costs, k, candidates);
  LCD_EXPECT_EQ(expect, actual);
}

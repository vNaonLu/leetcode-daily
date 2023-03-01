// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Most Profit Assigning Work
//
// https://leetcode.com/problems/most-profit-assigning-work/
//
// Question ID: 826
// Difficult  : Medium
// Solve Date : 2022/07/24 14:52

#include <algorithm>
#include <iosfwd>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |826. Most Profit Assigning Work|:
//
// You have |n| jobs and |m| workers. You are given three arrays: |difficulty|,
// |profit|, and |worker| where:
//
//  • |difficulty[i]| and |profit[i]| are the difficulty and the profit of the
//  |iᵗʰ| job, and
//
//  • |worker[j]| is the ability of |jᵗʰ| worker (i.e., the |jᵗʰ| worker can
//  only complete a job with difficulty at most |worker[j]|).
// Every worker can be assigned at most one job, but one job can be completed
// multiple times.
//
//  • For example, if three workers attempt the same job that pays |$1|, then
//  the total profit will be |$3|. If a worker cannot complete any job, their
//  profit is |$0|.
// Return the maximum profit we can achieve after assigning the workers to the
// jobs.
//

LEETCODE_BEGIN_RESOLVING(826, MostProfitAssigningWork, Solution);

class Solution {
public:
  int maxProfitAssignment(vector<int> &difficulty, vector<int> &profit,
                          vector<int> &worker) {
    auto cmp = [](pair<int, int> const &a, pair<int, int> const &b) {
      return a.first > b.first;
    };
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> pq(
        cmp);
    for (int i = 0; i < difficulty.size(); ++i) {
      pq.emplace(difficulty[i], profit[i]);
    }

    sort(worker.begin(), worker.end());
    int res = 0, best = 0;
    for (auto &skill : worker) {
      while (!pq.empty()) {
        auto x = pq.top();
        if (skill < x.first) {
          break;
        } else {
          pq.pop();
          best = max(best, x.second);
        }
      }
      res += best;
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == difficulty.length|
// * |n == profit.length|
// * |m == worker.length|
// * |1 <= n, m <= 10⁴|
// * |1 <= difficulty[i], profit[i], worker[i] <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: difficulty = [2,4,6,8,10], profit = [10,20,30,40,50], worker =
//  [4,5,6,7]
// Output: 100
//
// Workers are assigned jobs of difficulty [4,4,6,6] and they get a profit of
// [20,20,30,30] separately.

LEETCODE_SOLUTION_UNITTEST(826, MostProfitAssigningWork, example_1) {
  auto        solution   = MakeSolution();
  vector<int> difficulty = {2, 4, 6, 8, 10};
  vector<int> profit     = {10, 20, 30, 40, 50};
  vector<int> worker     = {4, 5, 6, 7};
  int         expect     = 100;
  int actual = solution->maxProfitAssignment(difficulty, profit, worker);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: difficulty = [85,47,57], profit = [24,66,99], worker = [40,25,25]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(826, MostProfitAssigningWork, example_2) {
  auto        solution   = MakeSolution();
  vector<int> difficulty = {85, 47, 57};
  vector<int> profit     = {24, 66, 99};
  vector<int> worker     = {40, 25, 25};
  int         expect     = 0;
  int actual = solution->maxProfitAssignment(difficulty, profit, worker);
  LCD_EXPECT_EQ(expect, actual);
}

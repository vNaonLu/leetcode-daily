// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Minimum Cost to Hire K Workers
//
// https://leetcode.com/problems/minimum-cost-to-hire-k-workers/
//
// Question ID: 857
// Difficult  : Hard
// Solve Date : 2024/05/11 14:28

#include <algorithm>
#include <iosfwd>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |857. Minimum Cost to Hire K Workers|:
//
// There are |n| workers. You are given two integer arrays |quality| and |wage|
// where |quality[i]| is the quality of the |iᵗʰ| worker and |wage[i]| is the
// minimum wage expectation for the |iᵗʰ| worker. We want to hire exactly |k|
// workers to form a paid group. To hire a group of |k| workers, we must pay
// them according to the following rules:
//
//  1. Every worker in the paid group must be paid at least their minimum wage
//  expectation.
//
//  2. In the group, each worker's pay must be directly proportional to their
//  quality. This means if a worker’s quality is double that of another worker
//  in the group, then they must be paid twice as much as the other worker.
// Given the integer |k|, return the least amount of money needed to form a paid
// group satisfying the above conditions. Answers within |10⁻⁵| of the actual
// answer will be accepted.
//
//

LEETCODE_BEGIN_RESOLVING(857, MinimumCostToHireKWorkers, Solution);

class Solution {
public:
  double mincostToHireWorkers(vector<int> &quality, vector<int> &wage, int k) {
    vector<pair<double, int>> ratio;
    int                       n = quality.size();

    for (int i = 0; i < n; ++i) {
      ratio.emplace_back((1.0 * wage[i]) / quality[i], i);
    }

    sort(ratio.begin(), ratio.end());
    priority_queue<int> pq;
    int                 quality_sum = 0;
    double              mx          = 0.0;
    for (int i = 0; i < k; ++i) {
      quality_sum += quality[ratio[i].second];
      mx = max(mx, ratio[i].first);
      pq.push(quality[ratio[i].second]);
    }
    double res = mx * quality_sum;
    for (int i = k; i < n; ++i) {
      mx = max(mx, ratio[i].first);
      quality_sum -= pq.top();
      pq.pop();

      quality_sum += quality[ratio[i].second];
      pq.push(quality[ratio[i].second]);
      res = min(res, mx * quality_sum);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |n == quality.length == wage.length|
// * |1 <= k <= n <= 10⁴|
// * |1 <= quality[i], wage[i] <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: quality = [10,20,5], wage = [70,50,30], k = 2
// Output: 105.00000
//

LEETCODE_SOLUTION_UNITTEST(857, MinimumCostToHireKWorkers, example_1) {
  auto        solution = MakeSolution();
  vector<int> quality  = {10, 20, 5};
  vector<int> wage     = {70, 50, 30};
  int         k        = 2;
  double      expect   = 105.00000;
  double      actual   = solution->mincostToHireWorkers(quality, wage, k);
  EXPECT_NEAR(expect, actual, 1e-5);
}

// [Example #2]
//  Input: quality = [3,1,10,10,1], wage = [4,8,2,2,7], k = 3
// Output: 30.66667
//

LEETCODE_SOLUTION_UNITTEST(857, MinimumCostToHireKWorkers, example_2) {
  auto        solution = MakeSolution();
  vector<int> quality  = {3, 1, 10, 10, 1};
  vector<int> wage     = {4, 8, 2, 2, 7};
  int         k        = 3;
  double      expect   = 30.66667;
  double      actual   = solution->mincostToHireWorkers(quality, wage, k);
  EXPECT_NEAR(expect, actual, 1e-5);
}

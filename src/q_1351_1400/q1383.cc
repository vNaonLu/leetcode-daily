// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Maximum Performance of a Team
//
// https://leetcode.com/problems/maximum-performance-of-a-team/
//
// Question ID: 1383
// Difficult  : Hard
// Solve Date : 2022/09/11 14:17

#include <algorithm>
#include <iosfwd>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1383. Maximum Performance of a Team|:
//
// You are given two integers |n| and |k| and two integer arrays |speed| and
// |efficiency| both of length |n|. There are |n| engineers numbered from |1| to
// |n|. |speed[i]| and |efficiency[i]| represent the speed and efficiency of the
// |iᵗʰ| engineer respectively. Choose at most |k| different engineers out of
// the |n| engineers to form a team with the maximum performance. The
// performance of a team is the sum of their engineers' speeds multiplied by the
// minimum efficiency among their engineers. Return the maximum performance of
// this team. Since the answer can be a huge number, return it modulo |10⁹ + 7|.
//

LEETCODE_BEGIN_RESOLVING(1383, MaximumPerformanceOfATeam, Solution);

class Solution {
private:
  inline constexpr static int kMod = 1e9 + 7;

public:
  int maxPerformance(int n, vector<int> &speed, vector<int> &efficiency,
                     int k) {
    auto pq     = priority_queue<int, vector<int>, greater<int>>();
    auto worker = vector<vector<int>>();
    auto total  = (size_t)0;
    auto res    = (size_t)0;
    auto mn     = (size_t)0;
    for (size_t i = 0; i < n; ++i) {
      worker.emplace_back(vector<int>{speed[i], efficiency[i]});
    }
    sort(worker.begin(), worker.end(),
         [](auto &x, auto &y) { return x[1] > y[1]; });
    for (size_t i = 0; i < k; ++i) {
      total += worker[i][0];
      mn  = worker[i][1];
      res = max(res, total * mn);
      pq.emplace(worker[i][0]);
    }
    for (size_t i = k; i < n; ++i) {
      if (worker[i][0] > pq.top()) {
        total += (-pq.top() + worker[i][0]);
        mn  = worker[i][1];
        res = max(res, total * mn);
        pq.pop();
        pq.emplace(worker[i][0]);
      }
    }
    return (int)(res % kMod);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= k <= n <= 10⁵|
// * |speed.length == n|
// * |efficiency.length == n|
// * |1 <= speed[i] <= 10⁵|
// * |1 <= efficiency[i] <= 10⁸|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 6, speed = [2,10,3,1,5,8], efficiency = [5,4,3,9,7,2], k = 2
// Output: 60
//
// We have the maximum performance of the team by selecting engineer 2 (with
// speed=10 and efficiency=4) and engineer 5 (with speed=5 and efficiency=7).
// That is, performance = (10 + 5) * min(4, 7) = 60.

LEETCODE_SOLUTION_UNITTEST(1383, MaximumPerformanceOfATeam, example_1) {
  auto        solution   = MakeSolution();
  int         n          = 6;
  vector<int> speed      = {2, 10, 3, 1, 5, 8};
  vector<int> efficiency = {5, 4, 3, 9, 7, 2};
  int         k          = 2;
  int         expect     = 60;
  int         actual     = solution->maxPerformance(n, speed, efficiency, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 6, speed = [2,10,3,1,5,8], efficiency = [5,4,3,9,7,2], k = 3
// Output: 68
// Explanation:
// This is the same example as the first but k = 3. We can select engineer 1,
// engineer 2 and engineer 5 to get the maximum performance of the team. That
// is, performance = (2 + 10 + 5) * min(5, 4, 7) = 68.
//

LEETCODE_SOLUTION_UNITTEST(1383, MaximumPerformanceOfATeam, example_2) {
  auto        solution   = MakeSolution();
  int         n          = 6;
  vector<int> speed      = {2, 10, 3, 1, 5, 8};
  vector<int> efficiency = {5, 4, 3, 9, 7, 2};
  int         k          = 3;
  int         expect     = 68;
  int         actual     = solution->maxPerformance(n, speed, efficiency, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: n = 6, speed = [2,10,3,1,5,8], efficiency = [5,4,3,9,7,2], k = 4
// Output: 72
//

LEETCODE_SOLUTION_UNITTEST(1383, MaximumPerformanceOfATeam, example_3) {
  auto        solution   = MakeSolution();
  int         n          = 6;
  vector<int> speed      = {2, 10, 3, 1, 5, 8};
  vector<int> efficiency = {5, 4, 3, 9, 7, 2};
  int         k          = 4;
  int         expect     = 72;
  int         actual     = solution->maxPerformance(n, speed, efficiency, k);
  LCD_EXPECT_EQ(expect, actual);
}

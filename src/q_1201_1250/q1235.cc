// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Maximum Profit in Job Scheduling
//
// https://leetcode.com/problems/maximum-profit-in-job-scheduling/
//
// Question ID: 1235
// Difficult  : Hard
// Solve Date : 2024/01/06 15:21

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1235. Maximum Profit in Job Scheduling|:
//
// We have |n| jobs, where every job is scheduled to be done from |startTime[i]|
// to |endTime[i]|, obtaining a profit of |profit[i]|. You're given the
// |startTime|, |endTime| and |profit| arrays, return the maximum profit you can
// take such that there are no two jobs in the subset with overlapping time
// range. If you choose a job that ends at time |X| you will be able to start
// another job that starts at time |X|.
//
//

LEETCODE_BEGIN_RESOLVING(1235, MaximumProfitInJobScheduling, Solution);

class Solution {
public:
  int jobScheduling(vector<int> &startTime, vector<int> &endTime,
                    vector<int> &profit) {
    int                    n = startTime.size();
    vector<pair<int, int>> st;
    for (int i = 0; i < n; ++i) {
      st.emplace_back(startTime[i], i);
    }
    sort(st.begin(), st.end());
    vector<int> dp(n + 1, 0);
    for (int i = n - 1; i >= 0; --i) {
      dp[i] += max(dp[i + 1],
                   profit[st[i].second] +
                       dp[lower_bound(st.begin() + i, st.end(),
                                      make_pair(endTime[st[i].second], 0)) -
                          st.begin()]);
    }
    return dp.front();
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= startTime.length == endTime.length == profit.length <= 5 * 10⁴|
// * |1 <= startTime[i] < endTime[i] <= 10⁹|
// * |1 <= profit[i] <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: startTime = [1,2,3,3], endTime = [3,4,5,6], profit = [50,10,40,70]
// Output: 120
//
// The subset chosen is the first and fourth job.
// Time range [1-3]+[3-6] , we get profit of 120 = 50 + 70.

LEETCODE_SOLUTION_UNITTEST(1235, MaximumProfitInJobScheduling, example_1) {
  auto        solution  = MakeSolution();
  vector<int> startTime = {1, 2, 3, 3};
  vector<int> endTime   = {3, 4, 5, 6};
  vector<int> profit    = {50, 10, 40, 70};
  int         expect    = 120;
  int         actual    = solution->jobScheduling(startTime, endTime, profit);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: startTime = [1,2,3,4,6], endTime = [3,5,10,6,9], profit =
//  [20,20,100,70,60]
// Output: 150
//
// The subset chosen is the first, fourth and fifth job.
// Profit obtained 150 = 20 + 70 + 60.

LEETCODE_SOLUTION_UNITTEST(1235, MaximumProfitInJobScheduling, example_2) {
  auto        solution  = MakeSolution();
  vector<int> startTime = {1, 2, 3, 4, 6};
  vector<int> endTime   = {3, 5, 10, 6, 9};
  vector<int> profit    = {20, 20, 100, 70, 60};
  int         expect    = 150;
  int         actual    = solution->jobScheduling(startTime, endTime, profit);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: startTime = [1,1,1], endTime = [2,3,4], profit = [5,6,4]
// Output: 6
//

LEETCODE_SOLUTION_UNITTEST(1235, MaximumProfitInJobScheduling, example_3) {
  auto        solution  = MakeSolution();
  vector<int> startTime = {1, 1, 1};
  vector<int> endTime   = {2, 3, 4};
  vector<int> profit    = {5, 6, 4};
  int         expect    = 6;
  int         actual    = solution->jobScheduling(startTime, endTime, profit);
  LCD_EXPECT_EQ(expect, actual);
}

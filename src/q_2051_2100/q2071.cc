// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Maximum Number of Tasks You Can Assign
//
// https://leetcode.com/problems/maximum-number-of-tasks-you-can-assign/
//
// Question ID: 2071
// Difficult  : Hard
// Solve Date : 2025/05/01 09:44

#include <deque>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2071. Maximum Number of Tasks You Can Assign|:
//
// You have |n| tasks and |m| workers. Each task has a strength requirement
// stored in a 0-indexed integer array |tasks|, with the |iᵗʰ| task requiring
// |tasks[i]| strength to complete. The strength of each worker is stored in a
// 0-indexed integer array |workers|, with the |jᵗʰ| worker having |workers[j]|
// strength. Each worker can only be assigned to a single task and must have a
// strength greater than or equal to the task's strength requirement (i.e.,
// |workers[j] >= tasks[i]|). Additionally, you have |pills| magical pills that
// will increase a worker's strength by |strength|. You can decide which workers
// receive the magical pills, however, you may only give each worker at most one
// magical pill. Given the 0-indexed integer arrays |tasks| and |workers| and
// the integers |pills| and |strength|, return the maximum number of tasks that
// can be completed.
//
//

LEETCODE_BEGIN_RESOLVING(2071, MaximumNumberOfTasksYouCanAssign, Solution);

class Solution {
public:
  int  n, m, strength;
  bool doable(vector<int> &tasks, vector<int> &workers, int k, int pills) {
    deque<int> q; // monotonic deque for tasks
    int        t_idx = 0;
    for (int i = m - k; i < m; i++) {
      int W = workers[i];
      for (; t_idx < k && tasks[t_idx] <= W + strength; t_idx++)
        q.push_back(tasks[t_idx]);

      if (q.empty())
        return 0;
      if (q.front() <= W)
        q.pop_front(); // no need for pill for easiest task
      else {
        if (pills == 0)
          return 0;
        pills--;
        q.pop_back(); // take a pill for hardest task
      }
    }
    return 1;
  }

  int maxTaskAssign(vector<int> &tasks, vector<int> &workers, int pills,
                    int strength) {
    n = tasks.size(), m = workers.size();
    this->strength = strength;
    sort(tasks.begin(), tasks.end());
    sort(workers.begin(), workers.end());

    int l = 0, r = min(n, m);

    while (l < r) {
      int mid = (l + r + 1) / 2;
      if (doable(tasks, workers, mid, pills))
        l = mid;
      else
        r = mid - 1;
    }
    return l;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |n == tasks.length|
// * |m == workers.length|
// * |1 <= n, m <= 5 * 10⁴|
// * |0 <= pills <= m|
// * |0 <= tasks[i], workers[j], strength <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: tasks = [3,2,1], workers = [0,3,3], pills = 1, strength = 1
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(2071, MaximumNumberOfTasksYouCanAssign, example_1) {
  auto        solution = MakeSolution();
  vector<int> tasks    = {3, 2, 1};
  vector<int> workers  = {0, 3, 3};
  int         pills    = 1;
  int         strength = 1;
  int         expect   = 3;
  int         actual = solution->maxTaskAssign(tasks, workers, pills, strength);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: tasks = [5,4], workers = [0,0,0], pills = 1, strength = 5
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(2071, MaximumNumberOfTasksYouCanAssign, example_2) {
  auto        solution = MakeSolution();
  vector<int> tasks    = {5, 4};
  vector<int> workers  = {0, 0, 0};
  int         pills    = 1;
  int         strength = 5;
  int         expect   = 1;
  int         actual = solution->maxTaskAssign(tasks, workers, pills, strength);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: tasks = [10,15,30], workers = [0,10,10,10,10], pills = 3, strength =
//  10
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(2071, MaximumNumberOfTasksYouCanAssign, example_3) {
  auto        solution = MakeSolution();
  vector<int> tasks    = {10, 15, 30};
  vector<int> workers  = {0, 10, 10, 10, 10};
  int         pills    = 3;
  int         strength = 10;
  int         expect   = 2;
  int         actual = solution->maxTaskAssign(tasks, workers, pills, strength);
  LCD_EXPECT_EQ(expect, actual);
}

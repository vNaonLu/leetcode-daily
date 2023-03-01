// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Single-Threaded CPU
//
// https://leetcode.com/problems/single-threaded-cpu/
//
// Question ID: 1834
// Difficult  : Medium
// Solve Date : 2022/12/29 18:57

#include <algorithm>
#include <iosfwd>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1834. Single-Threaded CPU|:
//
// You are given |n|​​​​​​ tasks labeled from |0| to |n - 1|
// represented by a 2D integer array |tasks|, where |tasks[i] = [enqueueTimeᵢ,
// processingTimeᵢ]| means that the |i^{​​​​​​th}|​​​​ task
// will be available to process at |enqueueTimeᵢ| and will take
// |processingTimeᵢ|^{ }to finish processing. You have a single-threaded CPU
// that can process at most one task at a time and will act in the following
// way:
//
//  • If the CPU is idle and there are no available tasks to process, the CPU
//  remains idle.
//
//  • If the CPU is idle and there are available tasks, the CPU will choose the
//  one with the shortest processing time. If multiple tasks have the same
//  shortest processing time, it will choose the task with the smallest index.
//
//  • Once a task is started, the CPU will process the entire task without
//  stopping.
//
//  • The CPU can finish a task then start a new one instantly.
// Return the order in which the CPU will process the tasks.
//

LEETCODE_BEGIN_RESOLVING(1834, SingleThreadedCPU, Solution);

class Solution {
public:
  vector<int> getOrder(vector<vector<int>> &tasks) {
    for (int i = 0; i < tasks.size(); ++i) {
      tasks[i].emplace_back(i);
    }
    auto res = vector<int>();
    auto pq  = priority_queue<vector<int>, vector<vector<int>>,
                             greater<vector<int>>>();
    sort(tasks.begin(), tasks.end());

    int cur_time = 0;
    int cur_idx  = 0;
    while (res.size() < tasks.size()) {
      if (pq.empty() && cur_idx < tasks.size()) {
        cur_time = max(cur_time, tasks[cur_idx][0]);
      }

      while (cur_idx < tasks.size() && tasks[cur_idx][0] <= cur_time) {
        pq.emplace(vector<int>{tasks[cur_idx][1], tasks[cur_idx][2]});
        ++cur_idx;
      }

      auto next = pq.top();
      pq.pop();

      cur_time = min<int>(1e9, cur_time + next[0]);
      res.emplace_back(next[1]);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |tasks.length == n|
// * |1 <= n <= 10⁵|
// * |1 <= enqueueTimeᵢ, processingTimeᵢ <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: tasks = [[1,2],[2,4],[3,2],[4,1]]
// Output: [0,2,3,1]
//
// The events go as follows:
// - At time = 1, task 0 is available to process. Available tasks = {0}.
// - Also at time = 1, the idle CPU starts processing task 0. Available tasks =
// {}.
// - At time = 2, task 1 is available to process. Available tasks = {1}.
// - At time = 3, task 2 is available to process. Available tasks = {1, 2}.
// - Also at time = 3, the CPU finishes task 0 and starts processing task 2 as
// it is the shortest. Available tasks = {1}.
// - At time = 4, task 3 is available to process. Available tasks = {1, 3}.
// - At time = 5, the CPU finishes task 2 and starts processing task 3 as it is
// the shortest. Available tasks = {1}.
// - At time = 6, the CPU finishes task 3 and starts processing task 1.
// Available tasks = {}.
// - At time = 10, the CPU finishes task 1 and becomes idle.

LEETCODE_SOLUTION_UNITTEST(1834, SingleThreadedCPU, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> tasks    = {
      {1, 2},
      {2, 4},
      {3, 2},
      {4, 1}
  };
  vector<int> expect = {0, 2, 3, 1};
  vector<int> actual = solution->getOrder(tasks);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: tasks = [[7,10],[7,12],[7,5],[7,4],[7,2]]
// Output: [4,3,2,0,1]
//
// : The events go as follows:
// - At time = 7, all the tasks become available. Available tasks = {0,1,2,3,4}.
// - Also at time = 7, the idle CPU starts processing task 4. Available tasks =
// {0,1,2,3}.
// - At time = 9, the CPU finishes task 4 and starts processing task 3.
// Available tasks = {0,1,2}.
// - At time = 13, the CPU finishes task 3 and starts processing task 2.
// Available tasks = {0,1}.
// - At time = 18, the CPU finishes task 2 and starts processing task 0.
// Available tasks = {1}.
// - At time = 28, the CPU finishes task 0 and starts processing task 1.
// Available tasks = {}.
// - At time = 40, the CPU finishes task 1 and becomes idle.

LEETCODE_SOLUTION_UNITTEST(1834, SingleThreadedCPU, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> tasks    = {
      {7, 10},
      {7, 12},
      {7,  5},
      {7,  4},
      {7,  2}
  };
  vector<int> expect = {4, 3, 2, 0, 1};
  vector<int> actual = solution->getOrder(tasks);
  LCD_EXPECT_EQ(expect, actual);
}

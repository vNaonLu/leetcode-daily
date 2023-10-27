// Copyright 2023 Naon Lu
//
// This file describes the solution of
// The Employee That Worked on the Longest Task
//
// https://leetcode.com/problems/the-employee-that-worked-on-the-longest-task/
//
// Question ID: 2432
// Difficult  : Easy
// Solve Date : 2023/10/27 19:42

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2432. The Employee That Worked on the Longest Task|:
//
// There are |n| employees, each with a unique id from |0| to |n - 1|.
// You are given a 2D integer array |logs| where |logs[i] = [idᵢ, leaveTimeᵢ]|
// where:
//
//  • |idᵢ| is the id of the employee that worked on the |iᵗʰ| task, and
//
//  • |leaveTimeᵢ| is the time at which the employee finished the |iᵗʰ| task.
//  All the values |leaveTimeᵢ| are unique.
// Note that the |iᵗʰ| task starts the moment right after the |(i - 1)ᵗʰ| task
// ends, and the |0ᵗʰ| task starts at time |0|. Return the id of the employee
// that worked the task with the longest time. If there is a tie between two or
// more employees, return the smallest id among them.
//
//

LEETCODE_BEGIN_RESOLVING(2432, TheEmployeeThatWorkedOnTheLongestTask, Solution);

class Solution {
public:
  int hardestWorker(int n, vector<vector<int>> &logs) {
    int res  = n;
    int last = 0;
    int mx   = 0;
    for (int i = 0; i < logs.size(); ++i) {
      if ((logs[i][1] - last) > mx ||
          ((logs[i][1] - last) == mx && res > logs[i][0])) {
        mx  = logs[i][1] - last;
        res = logs[i][0];
      }
      last = logs[i][1];
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= n <= 500|
// * |1 <= logs.length <= 500|
// * |logs[i].length == 2|
// * |0 <= idᵢ <= n - 1|
// * |1 <= leaveTimeᵢ <= 500|
// * |idᵢ != idᵢ₊₁|
// * |leaveTimeᵢ| are sorted in a strictly increasing order.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 10, logs = [[0,3],[2,5],[0,9],[1,15]]
// Output: 1
//
// Task 0 started at 0 and ended at 3 with 3 units of times.
// Task 1 started at 3 and ended at 5 with 2 units of times.
// Task 2 started at 5 and ended at 9 with 4 units of times.
// Task 3 started at 9 and ended at 15 with 6 units of times.
// The task with the longest time is task 3 and the employee with id 1 is the
// one that worked on it, so we return 1.

LEETCODE_SOLUTION_UNITTEST(2432, TheEmployeeThatWorkedOnTheLongestTask,
                           example_1) {
  auto                solution = MakeSolution();
  int                 n        = 10;
  vector<vector<int>> logs     = {
      {0,  3},
      {2,  5},
      {0,  9},
      {1, 15}
  };
  int expect = 1;
  int actual = solution->hardestWorker(n, logs);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 26, logs = [[1,1],[3,7],[2,12],[7,17]]
// Output: 3
//
// Task 0 started at 0 and ended at 1 with 1 unit of times.
// Task 1 started at 1 and ended at 7 with 6 units of times.
// Task 2 started at 7 and ended at 12 with 5 units of times.
// Task 3 started at 12 and ended at 17 with 5 units of times.
// The tasks with the longest time is task 1. The employee that worked on it is
// 3, so we return 3.

LEETCODE_SOLUTION_UNITTEST(2432, TheEmployeeThatWorkedOnTheLongestTask,
                           example_2) {
  auto                solution = MakeSolution();
  int                 n        = 26;
  vector<vector<int>> logs     = {
      {1,  1},
      {3,  7},
      {2, 12},
      {7, 17}
  };
  int expect = 3;
  int actual = solution->hardestWorker(n, logs);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: n = 2, logs = [[0,10],[1,20]]
// Output: 0
//
// Task 0 started at 0 and ended at 10 with 10 units of times.
// Task 1 started at 10 and ended at 20 with 10 units of times.
// The tasks with the longest time are tasks 0 and 1. The employees that worked
// on them are 0 and 1, so we return the smallest id 0.

LEETCODE_SOLUTION_UNITTEST(2432, TheEmployeeThatWorkedOnTheLongestTask,
                           example_3) {
  auto                solution = MakeSolution();
  int                 n        = 2;
  vector<vector<int>> logs     = {
      {0, 10},
      {1, 20}
  };
  int expect = 0;
  int actual = solution->hardestWorker(n, logs);
  LCD_EXPECT_EQ(expect, actual);
}

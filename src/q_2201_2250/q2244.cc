// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimum Rounds to Complete All Tasks
//
// https://leetcode.com/problems/minimum-rounds-to-complete-all-tasks/
//
// Question ID: 2244
// Difficult  : Medium
// Solve Date : 2023/01/04 20:33

#include <iosfwd>
#include <map>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2244. Minimum Rounds to Complete All Tasks|:
//
// You are given a 0-indexed integer array |tasks|, where |tasks[i]| represents
// the difficulty level of a task. In each round, you can complete either 2 or 3
// tasks of the same difficulty level. Return the minimum rounds required to
// complete all the tasks, or |-1| if it is not possible to complete all the
// tasks.
//

LEETCODE_BEGIN_RESOLVING(2244, MinimumRoundsToCompleteAllTasks, Solution);

class Solution {
public:
  int minimumRounds(vector<int> &tasks) {
    int                     res = 0;
    unordered_map<int, int> freq;
    for (auto x : tasks) {
      ++freq[x];
    }
    for (auto [x, cnt] : freq) {
      auto k = cnt;
      if (k == 1) {
        return -1;
      }
      if (k % 3 == 0) {
        res += k / 3;
      } else {
        res += (k / 3) + 1;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= tasks.length <= 10⁵|
// * |1 <= tasks[i] <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: tasks = [2,2,3,3,2,4,4,4,4,4]
// Output: 4
//
// To complete all the tasks, a possible plan is:
// - In the first round, you complete 3 tasks of difficulty level 2.
// - In the second round, you complete 2 tasks of difficulty level 3.
// - In the third round, you complete 3 tasks of difficulty level 4.
// - In the fourth round, you complete 2 tasks of difficulty level 4.
// It can be shown that all the tasks cannot be completed in fewer than 4
// rounds, so the answer is 4.

LEETCODE_SOLUTION_UNITTEST(2244, MinimumRoundsToCompleteAllTasks, example_1) {
  auto        solution = MakeSolution();
  vector<int> tasks    = {2, 2, 3, 3, 2, 4, 4, 4, 4, 4};
  int         expect   = 4;
  int         actual   = solution->minimumRounds(tasks);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: tasks = [2,3,3]
// Output: -1
//
// There is only 1 task of difficulty level 2, but in each round, you can only
// complete either 2 or 3 tasks of the same difficulty level. Hence, you cannot
// complete all the tasks, and the answer is -1.

LEETCODE_SOLUTION_UNITTEST(2244, MinimumRoundsToCompleteAllTasks, example_2) {
  auto        solution = MakeSolution();
  vector<int> tasks    = {2, 3, 3};
  int         expect   = -1;
  int         actual   = solution->minimumRounds(tasks);
  LCD_EXPECT_EQ(expect, actual);
}

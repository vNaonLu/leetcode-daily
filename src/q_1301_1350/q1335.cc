// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimum Difficulty of a Job Schedule
//
// https://leetcode.com/problems/minimum-difficulty-of-a-job-schedule/
//
// Question ID: 1335
// Difficult  : Hard
// Solve Date : 2022/10/16 14:40

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1335. Minimum Difficulty of a Job Schedule|:
//
// You want to schedule a list of jobs in |d| days. Jobs are dependent (i.e To
// work on the |iᵗʰ| job, you have to finish all the jobs |j| where |0 <= j <
// i|). You have to finish at least one task every day. The difficulty of a job
// schedule is the sum of difficulties of each day of the |d| days. The
// difficulty of a day is the maximum difficulty of a job done on that day. You
// are given an integer array |jobDifficulty| and an integer |d|. The difficulty
// of the |iᵗʰ| job is |jobDifficulty[i]|. Return the minimum difficulty of a
// job schedule. If you cannot find a schedule for the jobs return |-1|.
//

LEETCODE_BEGIN_RESOLVING(1335, MinimumDifficultyOfAJobSchedule, Solution);

class Solution {
public:
  int minDifficulty(vector<int> &jobDifficulty, int d) {
    auto dp = vector<vector<int>>(12, vector<int>(305, 1e6));

    if (jobDifficulty.size() < d) {
      return -1;
    }

    for (int i = 0; i < jobDifficulty.size(); ++i) {
      dp[1][i] = *max_element(jobDifficulty.begin() + i, jobDifficulty.end());
    }

    for (int i = 2; i <= d; ++i) {
      for (int j = 0; j < jobDifficulty.size(); ++j) {
        if (jobDifficulty.size() - j < i) {
          dp[i][j] = 1e6;
        } else {
          for (int k = j; k < jobDifficulty.size(); ++k) {
            dp[i][j] =
                min(dp[i][j], dp[i - 1][k + 1] +
                                  *max_element(jobDifficulty.begin() + j,
                                               jobDifficulty.begin() + k + 1));
          }
        }
      }
    }

    return dp[d].front();
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= jobDifficulty.length <= 300|
// * |0 <= jobDifficulty[i] <= 1000|
// * |1 <= d <= 10|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: jobDifficulty = [6,5,4,3,2,1], d = 2
// Output: 7
//
// First day you can finish the first 5 jobs, total difficulty = 6.
// Second day you can finish the last job, total difficulty = 1.
// The difficulty of the schedule = 6 + 1 = 7

LEETCODE_SOLUTION_UNITTEST(1335, MinimumDifficultyOfAJobSchedule, example_1) {
  auto        solution      = MakeSolution();
  vector<int> jobDifficulty = {6, 5, 4, 3, 2, 1};
  int         d             = 2;
  int         expect        = 7;
  int         actual        = solution->minDifficulty(jobDifficulty, d);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: jobDifficulty = [9,9,9], d = 4
// Output: -1
//
// If you finish a job per day you will still have a free day. you cannot find a
// schedule for the given jobs.

LEETCODE_SOLUTION_UNITTEST(1335, MinimumDifficultyOfAJobSchedule, example_2) {
  auto        solution      = MakeSolution();
  vector<int> jobDifficulty = {9, 9, 9};
  int         d             = 4;
  int         expect        = -1;
  int         actual        = solution->minDifficulty(jobDifficulty, d);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: jobDifficulty = [1,1,1], d = 3
// Output: 3
//
// The schedule is one job per day. total difficulty will be 3.

LEETCODE_SOLUTION_UNITTEST(1335, MinimumDifficultyOfAJobSchedule, example_3) {
  auto        solution      = MakeSolution();
  vector<int> jobDifficulty = {1, 1, 1};
  int         d             = 3;
  int         expect        = 3;
  int         actual        = solution->minDifficulty(jobDifficulty, d);
  LCD_EXPECT_EQ(expect, actual);
}

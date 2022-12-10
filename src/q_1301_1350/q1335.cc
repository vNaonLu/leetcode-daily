#include <algorithm>
#include <gtest/gtest.h>
#include <iostream>
#include <vector>

using namespace std;

/**
 * This file is generated by leetcode_add.py
 *
 * 1335.
 *       Minimum Difficulty of a Job Schedule
 *
 * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
 *
 *   You want to schedule a list of jobs in ‘d’ days. Jobs are dependent
 *   (i.e To work on the ‘iᵗʰ’ job, you have to finish all the jobs ‘j’
 *   where ‘0 ≤ j < i’
 *   You have to finish “at least” one task every day. The difficulty of a
 *   job schedule is the sum of difficulties of each day of the ‘d’ days.
 *   The difficulty of a day is the maximum difficulty of a job done on
 *   that
 *   You are given an integer array ‘jobDifficulty’ and an integer ‘d’ .
 *   The difficulty of the ‘iᵗʰ’ job is ‘jobDifficulty[i]’
 *   Return “the minimum difficulty of a job schedule” . If you cannot find
 *   a schedule for the jobs return ‘-1’ .
 *
 * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
 *
 *   • ‘1 ≤ jobDifficulty.length ≤ 300’
 *   • ‘0 ≤ jobDifficulty[i] ≤ 1000’
 *   • ‘1 ≤ d ≤ 10’
 *
 */

struct q1335 : public ::testing::Test {
  // Leetcode answer here
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
              dp[i][j] = min(dp[i][j],
                             dp[i - 1][k + 1] +
                                 *max_element(jobDifficulty.begin() + j,
                                              jobDifficulty.begin() + k + 1));
            }
          }
        }
      }

      return dp[d].front();
    }
  };

  class Solution *solution;
};

TEST_F(q1335, sample_input01) {
  solution                  = new Solution();
  vector<int> jobDifficulty = {6, 5, 4, 3, 2, 1};
  int         d             = 2;
  int         exp           = 7;
  int         act           = solution->minDifficulty(jobDifficulty, d);
  EXPECT_EQ(act, exp);
  delete solution;
}

TEST_F(q1335, sample_input02) {
  solution                  = new Solution();
  vector<int> jobDifficulty = {9, 9, 9};
  int         d             = 4;
  int         exp           = -1;
  int         act           = solution->minDifficulty(jobDifficulty, d);
  EXPECT_EQ(act, exp);
  delete solution;
}

TEST_F(q1335, sample_input03) {
  solution                  = new Solution();
  vector<int> jobDifficulty = {1, 1, 1};
  int         d             = 3;
  int         exp           = 3;
  int         act           = solution->minDifficulty(jobDifficulty, d);
  EXPECT_EQ(act, exp);
  delete solution;
}
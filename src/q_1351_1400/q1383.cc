#include <algorithm>
#include <gtest/gtest.h>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

/**
 * This file is generated by leetcode_add.py
 *
 * 1383.
 *       Maximum Performance of a Team
 *
 * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
 *
 *   You are given two integers ‘n’ and ‘k’ and two integer arrays ‘speed’
 *   and ‘efficiency’ both of length ‘n’ . There are ‘n’ engineers numbered
 *   from ‘1’ to ‘n’ . ‘speed[i]’ and ‘efficiency[i]’ represent the speed
 *   and efficiency of the ‘iᵗʰ’ engineer
 *   Choose “at most” ‘k’ different engineers out of the ‘n’ engineers to
 *   form a team with the maximum “performance”
 *   The performance of a team is the sum of their engineers' speeds
 *   multiplied by the minimum efficiency among their
 *   Return “the maximum performance of this team” . Since the answer can
 *   be a huge number, return it “modulo” ‘10⁹ + 7’ .
 *
 * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
 *
 *   • ‘1 ≤ k ≤ n ≤ 10⁵’
 *   • ‘speed.length = n’
 *   • ‘efficiency.length = n’
 *   • ‘1 ≤ speed[i] ≤ 10⁵’
 *   • ‘1 ≤ efficiency[i] ≤ 10⁸’
 *
 */

struct q1383 : public ::testing::Test {
  // Leetcode answer here
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

  class Solution *solution;
};

TEST_F(q1383, sample_input01) {
  solution               = new Solution();
  int         n          = 6;
  vector<int> speed      = {2, 10, 3, 1, 5, 8};
  vector<int> efficiency = {5, 4, 3, 9, 7, 2};
  int         k          = 2;
  int         exp        = 60;
  int         act        = solution->maxPerformance(n, speed, efficiency, k);
  EXPECT_EQ(act, exp);
  delete solution;
}

TEST_F(q1383, sample_input02) {
  solution               = new Solution();
  int         n          = 6;
  vector<int> speed      = {2, 10, 3, 1, 5, 8};
  vector<int> efficiency = {5, 4, 3, 9, 7, 2};
  int         k          = 3;
  int         exp        = 68;
  int         act        = solution->maxPerformance(n, speed, efficiency, k);
  EXPECT_EQ(act, exp);
  delete solution;
}

TEST_F(q1383, sample_input03) {
  solution               = new Solution();
  int         n          = 6;
  vector<int> speed      = {2, 10, 3, 1, 5, 8};
  vector<int> efficiency = {5, 4, 3, 9, 7, 2};
  int         k          = 4;
  int         exp        = 72;
  int         act        = solution->maxPerformance(n, speed, efficiency, k);
  EXPECT_EQ(act, exp);
  delete solution;
}
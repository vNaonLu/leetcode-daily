#include <gtest/gtest.h>
#include <iostream>
#include <queue>

using namespace std;

/**
 * This file is generated by leetcode_add.py
 *
 * 1364.
 *       Number of Trusted Contacts of a Customer
 *
 * To unlock the question need a premium account.
 *
 */

struct q1364 : public ::testing::Test {
  // Leetcode answer here
  class Solution {
  public:
    bool isPossible(vector<int> &target) {
      priority_queue<int> pq;
      int64_t sum = 0;
      for (auto &x : target) {
        pq.emplace(x);
        sum += x;
      }

      while (pq.top() != 1) {
        sum -= pq.top();
        if (sum == 0 || sum >= pq.top()) {
          return false;
        }

        int64_t old = pq.top() % sum;
        if (sum != 1 && old == 0) {
          return false;
        }

        pq.pop();
        pq.emplace(old);
        sum += old;
      }

      return true;
    }
  };

  class Solution *solution;
};

TEST_F(q1364, sample_input01) {
  solution = new Solution();
  vector<int> target = {9, 3, 5};
  bool exp = true;
  int act = solution->isPossible(target);
  EXPECT_EQ(act, exp);
  delete solution;
}

TEST_F(q1364, sample_input02) {
  solution = new Solution();
  vector<int> target = {1, 1, 1, 2};
  bool exp = false;
  int act = solution->isPossible(target);
  EXPECT_EQ(act, exp);
  delete solution;
}

TEST_F(q1364, sample_input03) {
  solution = new Solution();
  vector<int> target = {8, 5};
  bool exp = true;
  int act = solution->isPossible(target);
  EXPECT_EQ(act, exp);
  delete solution;
}
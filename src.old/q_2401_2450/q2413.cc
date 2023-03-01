#include <gtest/gtest.h>
#include <iostream>

using namespace std;

/**
 * This file is generated by leetcode_add.py
 *
 * 2413.
 *       Smallest Even Multiple
 *
 * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
 *
 *   Given a “positive” integer ‘n’ , return “the smallest positive integer
 *   that is a multiple of “both” ” ‘2’ “ and ” ‘n’ .
 *
 * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
 *
 *   • ‘1 ≤ n ≤ 150’
 *
 */

struct q2413 : public ::testing::Test {
  // Leetcode answer here
  class Solution {
  public:
    int smallestEvenMultiple(int n) { return (n & 1) == 0 ? n : 2 * n; }
  };

  class Solution *solution;
};

TEST_F(q2413, sample_input01) {
  solution = new Solution();
  int n    = 5;
  int exp  = 10;
  int act  = solution->smallestEvenMultiple(n);
  EXPECT_EQ(act, exp);
  delete solution;
}

TEST_F(q2413, sample_input02) {
  solution = new Solution();
  int n    = 6;
  int exp  = 6;
  int act  = solution->smallestEvenMultiple(n);
  EXPECT_EQ(act, exp);
  delete solution;
}
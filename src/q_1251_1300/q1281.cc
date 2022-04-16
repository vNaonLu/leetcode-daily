#include <gtest/gtest.h>
#include <iostream>

using namespace std;

/**
 * This file is generated by leetcode_add.py
 *
 * 1281.
 *       Subtract the Product and Sum of Digits of an Integer
 *
 * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
 *
 *   Given an integer number ‘n’ , return the difference between the
 *   product of its digits and the sum of its digits.
 *
 * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
 *
 *   • ‘1 ≤ n ≤ 10^5’
 *
 */

struct q1281 : public ::testing::Test {
  // Leetcode answer here
  class Solution {
   public:
    int subtractProductAndSum(int n) {
      long long prod = 1, sum = 0;
      while (n != 0) {
        prod *= n % 10;
        sum += n % 10;

        n /= 10;
      }

      return prod - sum;
    }
  };

  class Solution *solution;
};

TEST_F(q1281, sample_input01) {
  solution = new Solution();
  int n = 234;
  int exp = 15;
  int act = solution->subtractProductAndSum(n);
  EXPECT_EQ(act, exp);
  delete solution;
}

TEST_F(q1281, sample_input02) {
  solution = new Solution();
  int n = 4421;
  int exp = 21;
  int act = solution->subtractProductAndSum(n);
  EXPECT_EQ(act, exp);
  delete solution;
}
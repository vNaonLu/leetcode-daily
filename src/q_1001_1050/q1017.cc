#include <gtest/gtest.h>
#include <iostream>
#include <string>

using namespace std;

/**
 * This file is generated by leetcode_add.py
 *
 * 1017.
 *       Convert to Base -2
 *
 * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
 *
 *   Given an integer ‘n’ , return “a binary string representing its
 *   representation in base” ‘-2’
 *    “Note” that the returned string should not have leading zeros unless
 *   the string is ‘'0'’ .
 *
 * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
 *
 *   • ‘0 ≤ n ≤ 10⁹’
 *
 */

struct q1017 : public ::testing::Test {
  // Leetcode answer here
  class Solution {
   public:
    string baseNeg2(int n) {
      if (n == 0) return "0";
      string res;
      while (0 != n) {
        if (n % 2 == 0) {
          res = "0" + res;
          n = n / -2;
        } else {
          res = "1" + res;
          n = (n - 1) / -2;
        }
      }
      return res;
    }
  };

  class Solution *solution;
};

TEST_F(q1017, sample_input01) {
  solution = new Solution();
  int n = 2;
  string exp = "110";
  string act = solution->baseNeg2(n);
  EXPECT_EQ(act, exp);
  delete solution;
}

TEST_F(q1017, sample_input02) {
  solution = new Solution();
  int n = 3;
  string exp = "111";
  string act = solution->baseNeg2(n);
  EXPECT_EQ(act, exp);
  delete solution;
}

TEST_F(q1017, sample_input03) {
  solution = new Solution();
  int n = 4;
  string exp = "100";
  string act = solution->baseNeg2(n);
  EXPECT_EQ(act, exp);
  delete solution;
}
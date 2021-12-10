#include <gtest/gtest.h>
#include <iostream>

using namespace std;

/**
 * This file is generated by leetcode_add.py v1.0
 *
 * 201.
 *      Bitwise AND of Numbers Range
 *
 * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
 *
 *   Given two integers ‘left’ and ‘right’ that represent the range ‘[left,
 *   right]’ , return “the bitwise AND of all numbers in this range,
 *   inclusive” .
 *
 * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
 *
 *   • ‘0 ≤ left ≤ right ≤ 2³¹ - 1’
 *
 */

struct q201 : public ::testing::Test {
  // Leetcode answer here
  class Solution {
   public:
    int rangeBitwiseAnd(int left, int right) {
      int cnt = 0;
      while(left != 0 && right != 0){
        if (left == right) return left << cnt;
        left >>= 1;
        right >>= 1;
        ++cnt;
      }
      return 0;
    }
  };

  class Solution *solution;
};

TEST_F(q201, sample_input01) {
  solution = new Solution();
  int left = 5;
  int right = 7;
  int exp = 4;
  EXPECT_EQ(solution->rangeBitwiseAnd(left, right), exp);
  delete solution;
}

TEST_F(q201, sample_input02) {
  solution = new Solution();
  int left = 0;
  int right = 0;
  int exp = 0;
  EXPECT_EQ(solution->rangeBitwiseAnd(left, right), exp);
  delete solution;
}

TEST_F(q201, sample_input03) {
  solution = new Solution();
  int left = 1;
  int right = 2147483647;
  int exp = 0;
  EXPECT_EQ(solution->rangeBitwiseAnd(left, right), exp);
  delete solution;
}
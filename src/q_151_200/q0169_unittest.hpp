
#ifndef Q169_UNITTEST_H__
#define Q169_UNITTEST_H__
#include <gtest/gtest.h>

#include "q0169.hpp"
using namespace std;

/**
  * this file is generated by gquestion.py
  *
  * 169. Majority Element
  *
  * Given an array nums of size n , return the
  * majority element .
  * The majority element is the element that appears
  * more than &lfloor;n / 2&rfloor; times. You may
  * assume that the majority element always exists in the
  * array.
  *
  * Constraints:
  * -  n == nums.length 
  * -  1 <= n <= 5 * 10^(4) 
  * -  -2^(31) <= nums[i] <= 2^(31) - 1 
  *  “Follow-up:“ Could you solve the problem in linear time and in O(1) space?
  *
*/

TEST(q169, sample_input01) {
  vector<int> nums = {3, 2, 3};
  int exp = 3;
  l169::Solution solver;
  EXPECT_EQ(solver.majorityElement(nums), exp);
}

TEST(q169, sample_input02) {
  vector<int> nums = {2, 2, 1, 1, 1, 2, 2};
  int exp = 2;
  l169::Solution solver;
  EXPECT_EQ(solver.majorityElement(nums), exp);
}

#endif
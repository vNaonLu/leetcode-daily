
#ifndef Q1480_UNITTEST_H__
#define Q1480_UNITTEST_H__
#include <gtest/gtest.h>

#include "q1480.hpp"
using namespace std;

/**
 * This file is generated by leetcode_add.py
 *
 * 1480.
 *       Running Sum of 1d Array
 *
 * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
 *
 *   Given an array ‘nums’ . We define a running sum of an array as
 *   ‘runningSum[i] = sum(nums[0]&hellip;nums[i])’
 *   Return the running sum of ‘nums’
 *   
 *
 * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
 *
 *   • ‘1 ≤ nums.length ≤ 1000’
 *   • ‘-10^6≤ nums[i] ≤10^6’
 *
 */

TEST(q1480, sample_input01) {
  l1480::Solution solver;
  vector<int> nums = {1, 2, 3, 4};
  vector<int> exp = {1, 3, 6, 10};
  EXPECT_EQ(solver.runningSum(nums), exp);
}

TEST(q1480, sample_input02) {
  l1480::Solution solver;
  vector<int> nums = {1, 1, 1, 1, 1};
  vector<int> exp = {1, 2, 3, 4, 5};
  EXPECT_EQ(solver.runningSum(nums), exp);
}

TEST(q1480, sample_input03) {
  l1480::Solution solver;
  vector<int> nums = {3, 1, 2, 10, 1};
  vector<int> exp = {3, 4, 6, 16, 17};
  EXPECT_EQ(solver.runningSum(nums), exp);
}

#endif
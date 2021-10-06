
#ifndef Q343_UNITTEST_H__
#define Q343_UNITTEST_H__
#include <gtest/gtest.h>

#include "q0343.hpp"
using namespace std;

/**
  * This file is generated by leetcode_add.py
  *
  * 343.
  *      Integer Break
  *
  * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
  *
  *   Given an integer ‘n’ , break it into the sum of ‘k’ “positive
  *   integers” , where ‘k ≥ 2’ , and maximize the product of those integers.
  *   
  *   Return “the maximum product you can get”.
  *
  * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
  *
  *   • ‘2 ≤ n ≤ 58’
  *
*/

TEST(q343, sample_input01) {
  l343::Solution solver;
  int n = 2;
  int exp = 1;
  EXPECT_EQ(solver.integerBreak(n), exp);
}

TEST(q343, sample_input02) {
  l343::Solution solver;
  int n = 10;
  int exp = 36;
  EXPECT_EQ(solver.integerBreak(n), exp);
}

#endif
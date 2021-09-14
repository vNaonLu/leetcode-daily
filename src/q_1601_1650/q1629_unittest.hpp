
#ifndef Q1629_UNITTEST_H__
#define Q1629_UNITTEST_H__

#include <gtest/gtest.h>

#include <iostream>
#include <vector>
#include <string>

#include "q1629.hpp"

using namespace std;

TEST(q1629, sample_input_01) {
  vector<int> t{9, 29, 49, 50};
  string k = "cbcd";
  l1629::Solution solver;
  EXPECT_EQ(solver.slowestKey(t, k), 'c');
}

TEST(q1629, sample_input_02) {
  vector<int> t{12, 23, 36, 46, 62};
  string k = "spuda";
  l1629::Solution solver;
  EXPECT_EQ(solver.slowestKey(t, k), 'a');
}

#endif
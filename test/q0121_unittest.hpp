
#ifndef Q121_UNITTEST_H__
#define Q121_UNITTEST_H__

#include <gtest/gtest.h>

#include "../src/q0121.hpp"

using namespace std;

TEST(q121, sample_input01) {
  vector<int> prices{7, 1, 5, 3, 6, 4};
  int exp = 5;
  l121::Solution solver;
  EXPECT_EQ(solver.maxProfit(prices), exp);
}

TEST(q121, sample_input02) {
  vector<int> prices{7, 6, 4, 3, 1};
  int exp = 0;
  l121::Solution solver;
  EXPECT_EQ(solver.maxProfit(prices), exp);
}

#endif
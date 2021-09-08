
#ifndef Q344_UNITTEST_H__
#define Q344_UNITTEST_H__

#include <gtest/gtest.h>

#include "../src/q0344.hpp"

using namespace std;

TEST(q344, sample_input01){
  vector<char> s{'h', 'e', 'l', 'l', 'o'};
  vector<char> exp{'o', 'l', 'l', 'e', 'h'};
  l344::Solution solver;
  solver.reverseString(s);
  EXPECT_EQ(s, exp);
}

TEST(q344, sample_input02){
  vector<char> s{'H', 'a', 'n', 'n', 'a', 'h'};
  vector<char> exp{'h', 'a', 'n', 'n', 'a', 'H'};
  l344::Solution solver;
  solver.reverseString(s);
  EXPECT_EQ(s, exp);
}

#endif
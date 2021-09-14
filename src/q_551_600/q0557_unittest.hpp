
#ifndef Q557_UNITTEST_H__
#define Q557_UNITTEST_H__

#include <gtest/gtest.h>

#include "q0557.hpp"

using namespace std;

TEST(q557, sample_input01){
  string s = "Let's take LeetCode contest";
  string exp = "s'teL ekat edoCteeL tsetnoc";
  l557::Solution solver;
  EXPECT_EQ(solver.reverseWords(s), exp);
}

TEST(q557, sample_input02){
  string s = "God Ding";
  string exp = "doG gniD";
  l557::Solution solver;
  EXPECT_EQ(solver.reverseWords(s), exp);
}

#endif
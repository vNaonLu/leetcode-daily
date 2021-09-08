
#ifndef Q848_UNITTEST_H__
#define Q848_UNITTEST_H__

#include <gtest/gtest.h>

#include "../src/q0848.hpp"

using namespace std;

TEST(q848, sample_input01) {
  string s = "abc";
  vector<int> shifts{3, 5, 9};
  string exp = "rpl";
  l848::Solution solver;
  EXPECT_EQ(solver.shiftingLetters(s, shifts), exp);
}

TEST(q848, sample_input02) {
  string s = "aaa";
  vector<int> shifts{1,2,3};
  string exp = "gfd";
  l848::Solution solver;
  EXPECT_EQ(solver.shiftingLetters(s, shifts), exp);
}

TEST(q848, input01) {
  string s = "mkgfzkkuxownxvfvxasy";
  vector<int> shifts{505870226, 437526072, 266740649, 224336793, 532917782, 311122363, 567754492, 595798950, 81520022, 684110326, 137742843, 275267355, 856903962, 148291585, 919054234, 467541837, 622939912, 116899933, 983296461, 536563513};
  string exp = "wqqwlcjnkphhsyvrkdod";
  l848::Solution solver;
  EXPECT_EQ(solver.shiftingLetters(s, shifts), exp);
}

#endif
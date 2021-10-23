
#ifndef Q6_UNITTEST_H__
#define Q6_UNITTEST_H__
#include <gtest/gtest.h>

#include "q0006.hpp"
using namespace std;

/**
  * This file is generated by leetcode_add.py
  *
  * 6.
  *    ZigZag Conversion
  *
  * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
  *
  *   The string ‘"PAYPALISHIRING"’ is written in a zigzag pattern on a
  *   given number of rows like this: (you may want to display this pattern
  *   in a fixed font for better.
  *   
  *   P   A   H.
  *   
  *   A P L S I I.
  *   
  *   Y   I.
  *   
  *   And then read line by line: ‘"PAHNAPLSIIGYIR"’.
  *   
  *   Write the code that will take a string and make this conversion given
  *   a number of.
  *   
  *   string convert(string s, int.
  *
  * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
  *
  *   • ‘1 ≤ s.length ≤ 1000’
  *   • ‘s’ consists of English letters (lower-case and upper-case), ‘','’ and ‘'.'’ .
  *   • ‘1 ≤ numRows ≤ 1000’
  *
*/

TEST(q6, sample_input01) {
  l6::Solution solver;
  string s = "PAYPALISHIRING";
  int numRows = 3;
  string exp = "PAHNAPLSIIGYIR";
  EXPECT_EQ(solver.convert(s, numRows), exp);
}

TEST(q6, sample_input02) {
  l6::Solution solver;
  string s = "PAYPALISHIRING";
  int numRows = 4;
  string exp = "PINALSIGYAHRPI";
  EXPECT_EQ(solver.convert(s, numRows), exp);
}

TEST(q6, sample_input03) {
  l6::Solution solver;
  string s = "A";
  int numRows = 1;
  string exp = "A";
  EXPECT_EQ(solver.convert(s, numRows), exp);
}

#endif
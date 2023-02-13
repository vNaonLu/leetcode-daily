#include <gtest/gtest.h>
#include <iostream>
#include <string>

using namespace std;

/**
 * This file is generated by leetcode_add.py
 *
 * 2315.
 *       Count Asterisks
 *
 * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
 *
 *   You are given a string ‘s’ , where every “two” consecutive vertical
 *   bars ‘'|'’ are grouped into a “pair” . In other words, the 1ˢᵗ and 2ⁿᵈ
 *   ‘'|'’ make a pair, the 3ʳᵈ and 4ᵗʰ ‘'|'’ make a pair, and so
 *   Return “the number of ” ‘'×'’ “ in ” ‘s’ “, “excluding” the ” ‘'×'’ “
 *   between each pair of ” ‘'|'’
 *    “Note” that each ‘'|'’ will belong to “exactly” one pair.
 *
 * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
 *
 *   • ‘1 ≤ s.length ≤ 1000’
 *   • ‘s’ consists of lowercase English letters, vertical bars ‘'|'’ , and
 * asterisks ‘'×'’ . • ‘s’ contains an “even” number of vertical bars ‘'|'’ .
 *
 * see more details: https://leetcode.com/problems/count-asterisks/
 */

struct q2315 : public ::testing::Test {
  // Leetcode answer here
  class Solution {
  public:
    int countAsterisks(string s) {
      int  res      = 0;
      bool in_block = false;
      for (auto c : s) {
        if (c == '|') {
          in_block ^= true;
        }
        if (!in_block && c == '*') {
          ++res;
        }
      }
      return res;
    }
  };

  class Solution *solution;
};

TEST_F(q2315, sample_input01) {
  solution   = new Solution();
  string s   = "l|*e*et|c**o|*de|";
  int    exp = 2;
  int    act = solution->countAsterisks(s);
  EXPECT_EQ(act, exp);
  delete solution;
}

TEST_F(q2315, sample_input02) {
  solution   = new Solution();
  string s   = "iamprogrammer";
  int    exp = 0;
  int    act = solution->countAsterisks(s);
  EXPECT_EQ(act, exp);
  delete solution;
}

TEST_F(q2315, sample_input03) {
  solution   = new Solution();
  string s   = "yo|uar|e**|b|e***au|tifu|l";
  int    exp = 5;
  int    act = solution->countAsterisks(s);
  EXPECT_EQ(act, exp);
  delete solution;
}

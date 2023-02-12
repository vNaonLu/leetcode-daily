#include <gtest/gtest.h>
#include <iostream>
#include <string>

using namespace std;

/**
 * This file is generated by leetcode_add.py
 *
 * 2243.
 *       Calculate Digit Sum of a String
 *
 * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
 *
 *   You are given a string ‘s’ consisting of digits and an integer ‘k’
 *   A “round” can be completed if the length of ‘s’ is greater than ‘k’ .
 *   In one round, do the
 *       1.  “Divide” ‘s’ into “consecutive groups” of size ‘k’ such that
 *   the first ‘k’ characters are in the first group, the next ‘k’
 *   characters are in the second group, and so on. “Note” that the size of
 *   the last group can be smaller than ‘k’
 *       2.  “Replace” each group of ‘s’ with a string representing the sum
 *   of all its digits. For example, ‘'346'’ is replaced with ‘'13'’
 *   because ‘3 + 4 + 6 = 13’
 *       3.  “Merge” consecutive groups together to form a new string. If
 *   the length of the string is greater than ‘k’ , repeat from step ‘1’
 *   Return ‘s’ “after all rounds have been completed” .
 *
 * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
 *
 *   • ‘1 ≤ s.length ≤ 100’
 *   • ‘2 ≤ k ≤ 100’
 *   • ‘s’ consists of digits only.
 *
 */

struct q2243 : public ::testing::Test {
  // Leetcode answer here
  class Solution {
  private:
    template <typename It>
    string combine(It beg, It end) {
      int res = 0;
      while (beg != end) {
        res += *beg++ - '0';
      }
      return to_string(res);
    }

  public:
    string digitSum(string s, int k) {
      string res = std::move(s);
      while (res.size() > k) {
        string tmp;
        auto   beg = res.begin();
        while (beg != res.end()) {
          auto it = beg;
          while (it != res.end() && distance(beg, it) < k) {
            ++it;
          }
          tmp += combine(beg, it);
          beg = it;
        }
        res.swap(tmp);
      }
      return res;
    }
  };

  class Solution *solution;
};

TEST_F(q2243, sample_input01) {
  solution   = new Solution();
  string s   = "11111222223";
  int    k   = 3;
  string exp = "135";
  string act = solution->digitSum(s, k);
  EXPECT_EQ(act, exp);
  delete solution;
}

TEST_F(q2243, sample_input02) {
  solution   = new Solution();
  string s   = "00000000";
  int    k   = 3;
  string exp = "000";
  string act = solution->digitSum(s, k);
  EXPECT_EQ(act, exp);
  delete solution;
}
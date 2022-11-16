#include <gtest/gtest.h>
#include <iostream>
#include <vector>

using namespace std;

/**
 * This file is generated by leetcode_add.py
 *
 * 372.
 *      Super Pow
 *
 * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
 *
 *   Your task is to calculate ‘aᵇ’ mod ‘1337’ where ‘a’ is a positive
 *   integer and ‘b’ is an extremely large positive integer given in the
 *   form of an array.
 *
 * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
 *
 *   • ‘1 ≤ a ≤ 2³¹ - 1’
 *   • ‘1 ≤ b.length ≤ 2000’
 *   • ‘0 ≤ b[i] ≤ 9’
 *   • ‘b’ does not contain leading zeros.
 *
 */

struct q372 : public ::testing::Test {
  // Leetcode answer here
  class Solution {
  private:
    inline constexpr static int kMod = 1337;

    int calcPow(int a, int b) {
      auto res = (long)1;
      while (b--) {
        res = (res * a) % kMod;
      }
      return res;
    }

  public:
    int superPow(int a, vector<int> &b) {
      if (b.empty()) {
        return 1;
      }
      auto bk = b.back();
      b.pop_back();
      return calcPow(superPow(a, b), 10) * calcPow(a, bk) % kMod;
    }
  };

  class Solution *solution;
};

TEST_F(q372, sample_input01) {
  solution        = new Solution();
  int         a   = 2;
  vector<int> b   = {3};
  int         exp = 8;
  int         act = solution->superPow(a, b);
  EXPECT_EQ(exp, act);
  delete solution;
}

TEST_F(q372, sample_input02) {
  solution        = new Solution();
  int         a   = 2;
  vector<int> b   = {1, 0};
  int         exp = 1024;
  int         act = solution->superPow(a, b);
  EXPECT_EQ(exp, act);
  delete solution;
}

TEST_F(q372, sample_input03) {
  solution        = new Solution();
  int         a   = 1;
  vector<int> b   = {4, 3, 3, 8, 5, 2};
  int         exp = 1;
  int         act = solution->superPow(a, b);
  EXPECT_EQ(exp, act);
  delete solution;
}
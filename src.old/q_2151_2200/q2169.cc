#include <gtest/gtest.h>
#include <iostream>

using namespace std;

/**
 * This file is generated by leetcode_add.py
 *
 * 2169.
 *       Count Operations to Obtain Zero
 *
 * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
 *
 *   You are given two “non-negative” integers ‘num1’ and ‘num2’
 *   In one “operation” , if ‘num1 ≥ num2’ , you must subtract ‘num2’ from
 *   ‘num1’ , otherwise subtract ‘num1’ from ‘num2’
 *       - For example, if ‘num1 = 5’ and ‘num2 = 4’ , subtract ‘num2’ from
 *   ‘num1’ , thus obtaining ‘num1 = 1’ and ‘num2 = 4’ . However, if ‘num1
 *   = 4’ and ‘num2 = 5’ , after one operation, ‘num1 = 4’ and ‘num2 = 1’
 *   Return “the “number of operations” required to make either” ‘num1 = 0’
 *   “or” ‘num2 = 0’ .
 *
 * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
 *
 *   • ‘0 ≤ num1, num2 ≤ 10⁵’
 *
 * see more details:
 * https://leetcode.com/problems/count-operations-to-obtain-zero/
 */

struct q2169 : public ::testing::Test {
  // Leetcode answer here
  class Solution {
  public:
    int countOperations(int num1, int num2) {
      if (num1 == 0 || num2 == 0) {
        return 0;
      }
      return 1 + countOperations(min(num1, num2), abs(num1 - num2));
    }
  };

  class Solution *solution;
};

TEST_F(q2169, sample_input01) {
  solution = new Solution();
  int num1 = 2;
  int num2 = 3;
  int exp  = 3;
  int act  = solution->countOperations(num1, num2);
  EXPECT_EQ(act, exp);
  delete solution;
}

TEST_F(q2169, sample_input02) {
  solution = new Solution();
  int num1 = 10;
  int num2 = 10;
  int exp  = 1;
  int act  = solution->countOperations(num1, num2);
  EXPECT_EQ(act, exp);
  delete solution;
}
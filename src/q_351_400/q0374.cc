#include <gtest/gtest.h>
#include <iostream>

using namespace std;

/**
 * This file is generated by leetcode_add.py v1.0
 *
 * 374.
 *      Guess Number Higher or Lower
 *
 * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
 *
 *   We are playing the Guess Game. The game is as
 *   I pick a number from ‘1’ to ‘n’ . You have to guess which number I
 *   Every time you guess wrong, I will tell you whether the number I
 *   picked is higher or lower than your
 *   You call a pre-defined API ‘int guess(int num)’ , which returns 3
 *   possible
 *       -  ‘-1’ : The number I picked is lower than your guess (i.e. ‘pick
 *   < num’
 *       -  ‘1’ : The number I picked is higher than your guess (i.e. ‘pick
 *   > num’
 *       -  ‘0’ : The number I picked is equal to your guess (i.e. ‘pick =
 *   num’
 *   Return “the number that I picked” .
 *
 * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
 *
 *   • ‘1 ≤ n ≤ 2³¹ - 1’
 *   • ‘1 ≤ pick ≤ n’
 *
 */

int pick = 0;

int guess(const int &guess) noexcept {
  if (guess == pick)
    return 0;
  else if (guess > pick)
    return -1;
  else
    return 1;
}

struct q374 : public ::testing::Test {
  // Leetcode answer here
  class Solution {
   public:
    int guessNumber(int n) {
      int l = 1, r = n;
      int mid = 0;
      while (l <= r) {
        mid = l + (r - l) / 2;
        int g = guess(mid);
        if (g < 0) {
          r = mid - 1;
        } else if (g > 0) {
          l = mid + 1;
        } else
          break;
      }
      return mid;
    }
  };

  class Solution *solution;

};

TEST_F(q374, sample_input01) {
  solution = new Solution();
  int n = 10;
  pick = 6;
  int exp = 6;
  EXPECT_EQ(solution->guessNumber(n), exp);
  delete solution;
}

TEST_F(q374, sample_input02) {
  solution = new Solution();
  int n = 1;
  pick = 1;
  int exp = 1;
  EXPECT_EQ(solution->guessNumber(n), exp);
  delete solution;
}

TEST_F(q374, sample_input03) {
  solution = new Solution();
  int n = 2;
  pick = 1;
  int exp = 1;
  EXPECT_EQ(solution->guessNumber(n), exp);
  delete solution;
}

TEST_F(q374, sample_input04) {
  solution = new Solution();
  int n = 2;
  pick = 2;
  int exp = 2;
  EXPECT_EQ(solution->guessNumber(n), exp);
  delete solution;
}
#include <gtest/gtest.h>
#include <iostream>
#include <vector>

using namespace std;

/**
 * This file is generated by leetcode_add.py
 *
 * 1552.
 *       Magnetic Force Between Two Balls
 *
 * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
 *
 *   In the universe Earth C-137, Rick discovered a special form of
 *   magnetic force between two balls if they are put in his new invented
 *   basket. Rick has ‘n’ empty baskets, the ‘iᵗʰ’ basket is at
 *   ‘position[i]’ , Morty has ‘m’ balls and needs to distribute the balls
 *   into the baskets such that the “minimum magnetic force” between any
 *   two balls is “maximum”
 *   Rick stated that magnetic force between two different balls at
 *   positions ‘x’ and ‘y’ is ‘|x - y|’
 *   Given the integer array ‘position’ and the integer ‘m’ . Return “the
 *   required force” .
 *
 * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
 *
 *   • ‘n = position.length’
 *   • ‘2 ≤ n ≤ 10⁵’
 *   • ‘1 ≤ position[i] ≤ 10⁹’
 *   • All integers in ‘position’ are “distinct” .
 *   • ‘2 ≤ m ≤ position.length’
 *
 */

struct q1552 : public ::testing::Test {
  // Leetcode answer here
  class Solution {
  private:
    bool helper(vector<int> &ps, int F, int m) {
      auto prev = ps.front();
      --m;

      for (auto it = ps.begin(); it != ps.end(); ++it) {
        while (it != ps.end() && *it - prev < F) {
          ++it;
        }

        if (it == ps.end()) {
          break;
        }

        prev = *it;
        --m;
      }

      return m <= 0;
    }

  public:
    int maxDistance(vector<int> &position, int m) {
      sort(position.begin(), position.end());

      int L = 1,
          R = position.back();
      while (L <= R) {
        int mid = L + (R - L) / 2;

        if (helper(position, mid, m)) {
          L = mid + 1;
        } else {
          R = mid - 1;
        }
      }

      return L - 1;
    }
  };

  class Solution *solution;
};

TEST_F(q1552, sample_input01) {
  solution = new Solution();
  vector<int> position = {1, 2, 3, 4, 7};
  int m = 3;
  int exp = 3;
  int act = solution->maxDistance(position, m);
  EXPECT_EQ(act, exp);
  delete solution;
}

TEST_F(q1552, sample_input02) {
  solution = new Solution();
  vector<int> position = {5, 4, 3, 2, 1, 1000000000};
  int m = 2;
  int exp = 999999999;
  int act = solution->maxDistance(position, m);
  EXPECT_EQ(act, exp);
  delete solution;
}
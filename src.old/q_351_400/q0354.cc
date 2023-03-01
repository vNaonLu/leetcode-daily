#include <gtest/gtest.h>
#include <iostream>
#include <vector>

using namespace std;

/**
 * This file is generated by leetcode_add.py
 *
 * 354.
 *      Russian Doll Envelopes
 *
 * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
 *
 *   You are given a 2D array of integers ‘envelopes’ where ‘envelopes[i] =
 *   [wᵢ, hᵢ]’ represents the width and the height of an
 *   One envelope can fit into another if and only if both the width and
 *   height of one envelope are greater than the other envelope's width and
 *   Return “the maximum number of envelopes you can Russian doll (i.e.,
 *   put one inside the other)”
 *    “Note:” You cannot rotate an envelope.
 *
 * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
 *
 *   • ‘1 ≤ envelopes.length ≤ 10⁵’
 *   • ‘envelopes[i].length = 2’
 *   • ‘1 ≤ wᵢ, hᵢ ≤ 10⁵’
 *
 */

struct q354 : public ::testing::Test {
  // Leetcode answer here
  class Solution {
   public:
    int maxEnvelopes(vector<vector<int>> &envelopes) {
      sort(envelopes.begin(), envelopes.end(), [](auto &a, auto &b) {
        return a[0] == b[0] ? a[1] > b[1] : a[0] < b[0];
      });

      vector<int> res;
      for (auto &v : envelopes) {
        auto e = v[1];

        auto f = lower_bound(res.begin(), res.end(), e);
        if (f == res.end()) {
          res.emplace_back(e);
        } else {
          *f = e;
        }
      }

      return res.size();
    }
  };

  class Solution *solution;
};

TEST_F(q354, sample_input01) {
  solution = new Solution();
  vector<vector<int>> envelopes = {{5, 4}, {6, 4}, {6, 7}, {2, 3}};
  int exp = 3;
  int act = solution->maxEnvelopes(envelopes);
  EXPECT_EQ(act, exp);
  delete solution;
}

TEST_F(q354, sample_input02) {
  solution = new Solution();
  vector<vector<int>> envelopes = {{1, 1}, {1, 1}, {1, 1}};
  int exp = 1;
  int act = solution->maxEnvelopes(envelopes);
  EXPECT_EQ(act, exp);
  delete solution;
}
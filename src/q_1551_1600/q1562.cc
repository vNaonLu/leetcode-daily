#include <gtest/gtest.h>
#include <iostream>
#include <vector>

using namespace std;

/**
 * This file is generated by leetcode_add.py
 *
 * 1562.
 *       Find Latest Group of Size M
 *
 * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
 *
 *   Given an array ‘arr’ that represents a permutation of numbers from ‘1’
 *   to ‘n’
 *   You have a binary string of size ‘n’ that initially has all its bits
 *   set to zero. At each step ‘i’ (assuming both the binary string and
 *   ‘arr’ are 1-indexed) from ‘1’ to ‘n’ , the bit at position ‘arr[i]’ is
 *   set to ‘1’
 *   You are also given an integer ‘m’ . Find the latest step at which
 *   there exists a group of ones of length ‘m’ . A group of ones is a
 *   contiguous substring of ‘1’ 's such that it cannot be extended in
 *   either
 *   Return “the latest step at which there exists a group of ones of
 *   length “exactly” ” ‘m’ . “If no such group exists, return” ‘-1’ .
 *
 * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
 *
 *   • ‘n = arr.length’
 *   • ‘1 ≤ m ≤ n ≤ 10⁵’
 *   • ‘1 ≤ arr[i] ≤ n’
 *   • All integers in ‘arr’ are “distinct” .
 *
 */

struct q1562 : public ::testing::Test {
  // Leetcode answer here
  class Solution {
  public:
    int findLatestStep(vector<int> &arr, int m) {
      auto n = int(arr.size());
      auto res = -1;
      auto cnt = vector<int>(n + 2),
           ind = vector<int>(n + 2);
      for (int i = 0; i < n; ++i) {
        int lo = ind[arr[i] - 1],
            hi = ind[arr[i] + 1],
            nl = lo + hi + 1;
        ind[arr[i]] = nl;
        ind[arr[i] - lo] = nl;
        ind[arr[i] + hi] = nl;
        --cnt[lo];
        --cnt[hi];
        ++cnt[nl];
        if (cnt[m] > 0) {
          res = i + 1;
        }
      }
      return res;
    }
  };

  class Solution *solution;
};

TEST_F(q1562, sample_input01) {
  solution = new Solution();
  vector<int> arr = {3, 5, 1, 2, 4};
  int m = 1;
  int exp = 4;
  int act = solution->findLatestStep(arr, m);
  EXPECT_EQ(act, exp);
  delete solution;
}

TEST_F(q1562, sample_input02) {
  solution = new Solution();
  vector<int> arr = {3, 1, 5, 4, 2};
  int m = 2;
  int exp = -1;
  int act = solution->findLatestStep(arr, m);
  EXPECT_EQ(act, exp);
  delete solution;
}
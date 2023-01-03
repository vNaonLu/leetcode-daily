#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
 * This file is generated by leetcode_add.py
 *
 * 944.
 *      Delete Columns to Make Sorted
 *
 * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
 *
 *   You are given an array of ‘n’ strings ‘strs’ , all of the same
 *   The strings can be arranged such that there is one on each line,
 *   making a grid. For example, ‘strs = ['abc', 'bce', 'cae']’ can be
 *   arranged
 *   You want to “delete” the columns that are “not sorted
 *   lexicographically” . In the above example (0-indexed), columns 0 (
 *   ‘'a'’ , ‘'b'’ , ‘'c'’ ) and 2 ( ‘'c'’ , ‘'e'’ , ‘'e'’ ) are sorted
 *   while column 1 ( ‘'b'’ , ‘'c'’ , ‘'a'’ ) is not, so you would delete
 *   column
 *   Return “the number of columns that you will delete” .
 *
 * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
 *
 *   • ‘n = strs.length’
 *   • ‘1 ≤ n ≤ 100’
 *   • ‘1 ≤ strs[i].length ≤ 1000’
 *   • ‘strs[i]’ consists of lowercase English letters.
 *
 */

struct q944 : public ::testing::Test {
  // Leetcode answer here
  class Solution {
  public:
    int minDeletionSize(vector<string> &strs) {
      auto n   = strs.size();
      auto m   = strs.front().size();
      auto res = (int)0;
      for (int i = 0; i < m; ++i) {
        for (int j = 1; j < n; ++j) {
          if (strs[j][i] < strs[j - 1][i]) {
            ++res;
            break;
          }
        }
      }
      return res;
    }
  };

  class Solution *solution;
};

TEST_F(q944, sample_input01) {
  solution            = new Solution();
  vector<string> strs = {"cba", "daf", "ghi"};
  int            exp  = 1;
  int            act  = solution->minDeletionSize(strs);
  EXPECT_EQ(act, exp);
  delete solution;
}

TEST_F(q944, sample_input02) {
  solution            = new Solution();
  vector<string> strs = {"a", "b"};
  int            exp  = 0;
  int            act  = solution->minDeletionSize(strs);
  EXPECT_EQ(act, exp);
  delete solution;
}

TEST_F(q944, sample_input03) {
  solution            = new Solution();
  vector<string> strs = {"zyx", "wvu", "tsr"};
  int            exp  = 3;
  int            act  = solution->minDeletionSize(strs);
  EXPECT_EQ(act, exp);
  delete solution;
}

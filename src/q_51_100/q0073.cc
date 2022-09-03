#include <gtest/gtest.h>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

/**
 * This file is generated by leetcode_add.py
 *
 * 73.
 *     Set Matrix Zeroes
 *
 * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
 *
 *   Given an ‘m x n’ integer matrix ‘matrix’ , if an element is ‘0’ , set
 *   its entire row and column to ‘0’
 *   You must do it <a
 *   href="https://en.wikipedia.org/wiki/In-place_algorithm"
 *   target="_blank">in place</a>.
 *
 * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
 *
 *   • ‘m = matrix.length’
 *   • ‘n = matrix[0].length’
 *   • ‘1 ≤ m, n ≤ 200’
 *   • ‘-2³¹ ≤ matrix[i][j] ≤ 2³¹ - 1’
 *   • A straightforward solution using ‘O(mn)’ space is probably a bad idea.
 *   • A simple improvement uses ‘O(m + n)’ space, but still not the best
 * solution. • Could you devise a constant space solution?
 *
 */

struct q73 : public ::testing::Test {
  // Leetcode answer here
  class Solution {
  public:
    void setZeroes(vector<vector<int>> &matrix) {
      auto m         = (int)matrix.size();
      auto n         = (int)matrix.front().size();
      auto zero_cols = unordered_set<int>();
      auto zero_rows = unordered_set<int>();
      /// keep the columns and rows which contain zero.
      for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
          if (matrix[i][j] == 0) {
            zero_cols.emplace(j);
            zero_rows.emplace(i);
          }
        }
      }
      /// deal with columns
      for (auto x : zero_cols) {
        for (int i = 0; i < m; ++i) {
          matrix[i][x] = 0;
        }
      }
      /// deal with rows
      for (auto x : zero_rows) {
        for (int i = 0; i < n; ++i) {
          matrix[x][i] = 0;
        }
      }
    }
  };

  class Solution *solution;
};

TEST_F(q73, sample_input01) {
  solution                   = new Solution();
  vector<vector<int>> matrix = {
      {1, 1, 1},
      {1, 0, 1},
      {1, 1, 1}
  };
  vector<vector<int>> exp = {
      {1, 0, 1},
      {0, 0, 0},
      {1, 0, 1}
  };
  solution->setZeroes(matrix);
  // Assume the first argument is answer.
  EXPECT_EQ(matrix, exp);
  delete solution;
}

TEST_F(q73, sample_input02) {
  solution                   = new Solution();
  vector<vector<int>> matrix = {
      {0, 1, 2, 0},
      {3, 4, 5, 2},
      {1, 3, 1, 5}
  };
  vector<vector<int>> exp = {
      {0, 0, 0, 0},
      {0, 4, 5, 0},
      {0, 3, 1, 0}
  };
  solution->setZeroes(matrix);
  // Assume the first argument is answer.
  EXPECT_EQ(matrix, exp);
  delete solution;
}
#include <gtest/gtest.h>
#include <iostream>
#include <vector>

using namespace std;

/**
 * This file is generated by leetcode_add.py
 *
 * 867.
 *      Transpose Matrix
 *
 * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
 *
 *   Given a 2D integer array ‘matrix’ , return “the “transpose” of”
 *   ‘matrix’
 *   The “transpose” of a matrix is the matrix flipped over its main
 *   diagonal, switching the matrix's row and column
 *
 * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
 *
 *   • ‘m = matrix.length’
 *   • ‘n = matrix[i].length’
 *   • ‘1 ≤ m, n ≤ 1000’
 *   • ‘1 ≤ m × n ≤ 10⁵’
 *   • ‘-10⁹ ≤ matrix[i][j] ≤ 10⁹’
 *
 */

struct q867 : public ::testing::Test {
  // Leetcode answer here
  class Solution {
   public:
    vector<vector<int>> transpose(vector<vector<int>>& matrix) {
      vector<vector<int>> res(matrix[0].size(), vector<int>(matrix.size()));

      for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[i].size(); ++j) {
          res[j][i] = matrix[i][j];
        }
      }

      return res;
    }
  };

  class Solution *solution;
};

TEST_F(q867, sample_input01) {
  solution = new Solution();
  vector<vector<int>> matrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  vector<vector<int>> exp = {{1, 4, 7}, {2, 5, 8}, {3, 6, 9}};
  vector<vector<int>> act = solution->transpose(matrix);
  EXPECT_EQ(act, exp);
  delete solution;
}

TEST_F(q867, sample_input02) {
  solution = new Solution();
  vector<vector<int>> matrix = {{1, 2, 3}, {4, 5, 6}};
  vector<vector<int>> exp = {{1, 4}, {2, 5}, {3, 6}};
  vector<vector<int>> act = solution->transpose(matrix);
  EXPECT_EQ(act, exp);
  delete solution;
}
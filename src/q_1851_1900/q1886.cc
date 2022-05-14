#include <gtest/gtest.h>
#include <iostream>
#include <vector>

using namespace std;

/**
 * This file is generated by leetcode_add.py
 *
 * 1886.
 *       Determine Whether Matrix Can Be Obtained By Rotation
 *
 * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
 *
 *   Given two ‘n x n’ binary matrices ‘mat’ and ‘target’ , return ‘true’ “
 *   if it is possible to make ” ‘mat’ “ equal to ” ‘target’ “ by
 *   “rotating” ” ‘mat’ “ in “90-degree increments” , or ” ‘false’ “
 *   otherwise.” 
 *
 * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
 *
 *   • ‘n = mat.length = target.length’
 *   • ‘n = mat[i].length = target[i].length’
 *   • ‘1 ≤ n ≤ 10’
 *   • ‘mat[i][j]’ and ‘target[i][j]’ are either ‘0’ or ‘1’ .
 *
 */

struct q1886 : public ::testing::Test {
  // Leetcode answer here
  class Solution {
   private:
    void rotate(vector<vector<int>>& matrix) {
      int rows = matrix.size();
      int cols = matrix[0].size();
      for (int i = 0; i < rows; i++) {
        for (int j = 0; j < i; j++) {
          swap(matrix[i][j], matrix[j][i]);
        }
      }
      for (auto& row : matrix) {
        reverse(row.begin(), row.end());
      }
    }

   public:
    bool findRotation(vector<vector<int>>& mat, vector<vector<int>>& target) {
      for (int i = 0; i < 4; ++i) {
        if (mat == target) {
          return true;
        }

        rotate(mat);
      }
      return false;
    }
  };

  class Solution *solution;
};

TEST_F(q1886, sample_input01) {
  solution = new Solution();
  vector<vector<int>> mat = {{0, 1}, {1, 0}};
  vector<vector<int>> target = {{1, 0}, {0, 1}};
  bool exp = true;
  bool act = solution->findRotation(mat, target);
  EXPECT_EQ(act, exp);
  delete solution;
}

TEST_F(q1886, sample_input02) {
  solution = new Solution();
  vector<vector<int>> mat = {{0, 1}, {1, 1}};
  vector<vector<int>> target = {{1, 0}, {0, 1}};
  bool exp = false;
  bool act = solution->findRotation(mat, target);
  EXPECT_EQ(act, exp);
  delete solution;
}

TEST_F(q1886, sample_input03) {
  solution = new Solution();
  vector<vector<int>> mat = {{0, 0, 0}, {0, 1, 0}, {1, 1, 1}};
  vector<vector<int>> target = {{1, 1, 1}, {0, 1, 0}, {0, 0, 0}};
  bool exp = true;
  bool act = solution->findRotation(mat, target);
  EXPECT_EQ(act, exp);
  delete solution;
}
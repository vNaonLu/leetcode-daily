#include <gtest/gtest.h>
#include <iostream>
#include <vector>

using namespace std;

/**
 * This file is generated by leetcode_add.py
 *
 * 661.
 *      Image Smoother
 *
 * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
 *
 *   An “image smoother” is a filter of the size ‘3 x 3’ that can be
 *   applied to each cell of an image by rounding down the average of the
 *   cell and the eight surrounding cells (i.e., the average of the nine
 *   cells in the blue smoother). If one or more of the surrounding cells
 *   of a cell is not present, we do not consider it in the average (i.e.,
 *   the average of the four cells in the red
 *   Given an ‘m x n’ integer matrix ‘img’ representing the grayscale of an
 *   image, return “the image after applying the smoother on each cell of
 *   it” .
 *
 * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
 *
 *   • ‘m = img.length’
 *   • ‘n = img[i].length’
 *   • ‘1 ≤ m, n ≤ 200’
 *   • ‘0 ≤ img[i][j] ≤ 255’
 *
 */

struct q661 : public ::testing::Test {
  // Leetcode answer here
  class Solution {
  private:
    int avg(vector<vector<int>> &img, int x, int y) {
      auto res = (int)0;
      auto cnt = (int)0;
      auto m   = (int)img.size();
      auto n   = (int)img.front().size();
      for (int i = max(0, x - 1); i <= min(m - 1, x + 1); ++i) {
        for (int j = max(0, y - 1); j <= min(n - 1, y + 1); ++j) {
          res += img[i][j];
          ++cnt;
        }
      }
      return res / cnt;
    }

  public:
    vector<vector<int>> imageSmoother(vector<vector<int>> &img) {
      auto m   = img.size();
      auto n   = img.front().size();
      auto res = vector<vector<int>>(m, vector<int>(n));
      for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
          res[i][j] = avg(img, i, j);
        }
      }
      return res;
    }
  };

  class Solution *solution;
};

TEST_F(q661, sample_input01) {
  solution                = new Solution();
  vector<vector<int>> img = {
      {1, 1, 1},
      {1, 0, 1},
      {1, 1, 1}
  };
  vector<vector<int>> exp = {
      {0, 0, 0},
      {0, 0, 0},
      {0, 0, 0}
  };
  vector<vector<int>> act = solution->imageSmoother(img);
  EXPECT_EQ(act, exp);
  delete solution;
}

TEST_F(q661, sample_input02) {
  solution                = new Solution();
  vector<vector<int>> img = {
      {100, 200, 100},
      {200,  50, 200},
      {100, 200, 100}
  };
  vector<vector<int>> exp = {
      {137, 141, 137},
      {141, 138, 141},
      {137, 141, 137}
  };
  vector<vector<int>> act = solution->imageSmoother(img);
  EXPECT_EQ(act, exp);
  delete solution;
}
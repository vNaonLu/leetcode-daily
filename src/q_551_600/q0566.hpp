
#ifndef LEETCODE_Q566_H__
#define LEETCODE_Q566_H__

#include <iostream>
#include <vector>

namespace l566 {
using namespace std;
class Solution {
 public:
  vector<vector<int>> matrixReshape(vector<vector<int>>& mat, int r, int c) {
    int m = mat.size(), n = mat[0].size();
    if (m * n != r * c) {
      return mat;
    } else {
      vector<vector<int>> res(r, vector<int>(c));
      for (int i = 0; i < m * n; ++i) {
        res[i / c][i % c] = mat[i / n][i % n];
      }
      return res;
    }
  }
};
}

#endif
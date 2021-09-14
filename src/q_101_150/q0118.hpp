
#ifndef LEETCODE_Q118_H__
#define LEETCODE_Q118_H__

#include <iostream>
#include <vector>

namespace l118 {
using namespace std;
class Solution {
 public:
  vector<vector<int>> generate(int numRows) {
    vector<vector<int>> res(numRows);
    for (int i = 0; i < numRows; ++i) {
      res[i].resize(i + 1, 1);
      for (int j = 1; j < i; ++j) {
        res[i][j] = res[i - 1][j - 1] + res[i - 1][j];
      }
    }
    return res;
  }
};
}

#endif
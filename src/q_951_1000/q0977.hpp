
#ifndef LEETCODE_Q977_H__
#define LEETCODE_Q977_H__

#include <algorithm>
#include <iostream>
#include <vector>

namespace l977 {
using namespace std;
class Solution {
 public:
  vector<int> sortedSquares(vector<int>& nums) {
    int k = nums.size();
    vector<int> res(k);
    int l = 0, r = k - 1;
    while (l <= r) {
      int ls = nums[l] * nums[l];
      int rs = nums[r] * nums[r];
      if (ls > rs) {
        res[--k] = ls;
        ++l;
      } else {
        res[--k] = rs;
        --r;
      }
    }
    return res;
  }
};
}  // namespace leetcode

#endif
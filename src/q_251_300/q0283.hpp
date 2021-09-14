
#ifndef LEETCODE_Q283_H__
#define LEETCODE_Q283_H__

#include <iostream>
#include <vector>

namespace l283 {
using namespace std;
class Solution {
 public:
  void moveZeroes(vector<int>& nums) {
    int fillindex = -1;
    for (int i = 0; i < nums.size(); ++i) {
      if (nums[i] != 0) {
        nums[++fillindex] = nums[i];
      }
    }
    while (fillindex < nums.size() - 1) {
      nums[++fillindex] = 0;
    }
  }
};
}  // namespace l183

#endif
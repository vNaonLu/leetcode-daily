
#ifndef LEETCODE_Q189_H__
#define LEETCODE_Q189_H__

#include <iostream>
#include <vector>

namespace l189 {
using namespace std;
class Solution {
 public:
  void rotate(vector<int>& nums, int k) {
    int n = nums.size();
    vector<int> tmp(nums.end() - k % n, nums.end());
    nums.insert(nums.begin(), tmp.begin(), tmp.end());
    nums.resize(n);
  }
};
}  // namespace l189

#endif
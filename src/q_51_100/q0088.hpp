
#ifndef LEETCODE_Q88_H__
#define LEETCODE_Q88_H__

#include <iostream>
#include <vector>

namespace l88 {
using namespace std;
class Solution {
 public:
  void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    int i = -1;
    int i1 = 0, i2 = 0;
    vector<int> n1(nums1.begin(), nums1.begin() + m);
    while (i1 < m && i2 < n) {
      if (n1[i1] <= nums2[i2]) {
        nums1[++i] = n1[i1++];
      } else {
        nums1[++i] = nums2[i2++];
      }
    }
    while (i1 < m) {
      nums1[++i] = n1[i1++];
    }
    while (i2 < n) {
      nums1[++i] = nums2[i2++];
    }
  }
};
}  // namespace l88
#endif
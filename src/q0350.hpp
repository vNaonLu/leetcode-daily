
#ifndef LEETCODE_Q350_H__
#define LEETCODE_Q350_H__

#include <algorithm>
#include <iostream>
#include <vector>

namespace l350 {
using namespace std;
class Solution {
 public:
  vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
    sort(nums1.begin(), nums1.end());
    sort(nums2.begin(), nums2.end());
    vector<int> res;
    res.reserve(min(nums1.size(), nums2.size()));
    while (!nums1.empty() && !nums2.empty()) {
      if (nums1.back() == nums2.back()) {
        res.push_back(nums1.back());
        nums1.pop_back();
        nums2.pop_back();
      } else if (nums1.back() > nums2.back()) {
        nums1.pop_back();
      } else {
        nums2.pop_back();
      }
    }
    return res;
  }
};
}  // namespace l350

#endif
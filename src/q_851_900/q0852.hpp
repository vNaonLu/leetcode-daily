
#ifndef LEETCODE_Q852_H__
#define LEETCODE_Q852_H__
#include <iostream>
#include <vector>

namespace l852 {
using namespace std;

class Solution {
 public:
  int peakIndexInMountainArray(vector<int>& arr) {
    int l = 0, r = arr.size() - 1;
    while (l <= r) {
      int mid = l + (r - l) / 2;
      if (mid > 0 && mid < arr.size() - 1) {
        if (arr[mid] > arr[mid - 1] && arr[mid] > arr[mid + 1]) {
          return mid;
        } else if (arr[mid] < arr[mid + 1]) {
          l = mid + 1;
        } else {
          r = mid - 1;
        }
      } else if (mid == 0) {
        return arr[mid] > arr[mid] ? mid : mid + 1;
      } else {
        return arr[mid] > arr[mid - 1] ? mid : mid - 1;
      }
    }
    return -1;
  }
};
}  // namespace l852

#endif
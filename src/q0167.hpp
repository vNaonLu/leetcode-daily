
#ifndef LEETCODE_Q167_H__
#define LEETCODE_Q167_H__

#include <iostream>
#include <vector>

namespace l167 {
using namespace std;
class Solution {
 public:
  vector<int> twoSum(vector<int>& numbers, int target) {
    int l = 0, r = numbers.size() - 1;
    while (l < r) {
      int cur = numbers[l] + numbers[r];
      if (cur > target) {
        --r;
      } else if (cur < target) {
        ++l;
      } else {
        return {l + 1, r + 1};
      }
    }
    return {-1, -1};
  }
};
}  // namespace l167

#endif
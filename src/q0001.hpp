
#ifndef LEETCODE_Q1_H__
#define LEETCODE_Q1_H__

#include <iostream>
#include <unordered_map>
#include <vector>

namespace l1 {
using namespace std;
class Solution {
 public:
  vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> mark;
    for (int i = 0; i < nums.size(); ++i) {
      if (mark.count(target - nums[i])) {
        return {mark[target - nums[i]], i};
      }
      mark[nums[i]] = i;
    }
    return {-1, -1};
  }
};
}  // namespace l1

#endif
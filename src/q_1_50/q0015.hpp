
#ifndef LEETCODE_Q15_H__
#define LEETCODE_Q15_H__
#include <algorithm>
#include <iostream>
#include <vector>

namespace l15 {
using namespace std;

/**
  * this file is generated by gquestion.py
  *
  * 15. 3Sum
  *
  * Given an integer array nums, return all the
  * triplets [nums[i], nums[j], nums[k]] such that i != j ,
  * i != k , and j != k , and nums[i] + nums[j] +
  * nums[k] == 0 .
  * Notice that the solution set must not contain
  * duplicate triplets.
  *
  * Constraints:
  * -  0 <= nums.length <= 3000 
  * -  -10^(5) <= nums[i] <= 10^(5) 
  *
*/
class Solution {
 public:
  vector<vector<int>> threeSum(vector<int>& nums) {
    vector<vector<int>> res;
    sort(nums.begin(), nums.end());
    for (int k = 0; k < (int)nums.size() - 2; ++k) {
      if (nums[k] > 0) break;
      if (k > 0 && nums[k] == nums[k - 1]) continue;
      int target = 0 - nums[k], i = k + 1, j = (int)nums.size() - 1;
      while (i < j) {
        if (nums[i] + nums[j] == target) {
          res.push_back({nums[k], nums[i], nums[j]});
          while (i < j && nums[i] == nums[i + 1]) ++i;
          while (i < j && nums[j] == nums[j - 1]) --j;
          ++i;
          --j;
        } else if (nums[i] + nums[j] < target)
          ++i;
        else
          --j;
      }
    }
    return res;
  }
};
}  // namespace l15
#endif
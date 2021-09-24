
#ifndef LEETCODE_Q560_H__
#define LEETCODE_Q560_H__
#include <iostream>
#include <unordered_map>
#include <vector>

namespace l560 {
using namespace std;

/**
  * this file is generated by gquestion.py
  *
  * 560. Subarray Sum Equals K
  * Given an array of integers nums and an integer k
  * , return the total number of continuous subarrays
  * whose sum equals to k .
  *
  * Constraints:
  * -  1 <= nums.length <= 2 * 10^(4) 
  * -  -1000 <= nums[i] <= 1000 
  * -  -10^(7) <= k <= 10^(7) 
  *
*/
class Solution {
 public:
  int subarraySum(vector<int>& nums, int k) {
    int res = 0, sum = 0;
    unordered_map<int, int> hash;

    hash[sum] = 1;
    for (int i = 0; i < nums.size(); ++i) {
      sum += nums[i];
      if (hash.count(sum - k))
        res += hash.at(sum - k);
      ++hash[sum];
    }

    return res;
  }
};
}  // namespace l560
#endif

#ifndef LEETCODE_Q136_H__
#define LEETCODE_Q136_H__
#include <iostream>
#include <vector>

namespace l136 {
using namespace std;

/**
  * this file is generated by gquestion.py
  *
  * 136. Single Number
  *
  * Given a “non-empty“ array of integers nums ,
  * every element appears twice except for one. Find that
  * single one.
  * You mustimplement a solution with a linear
  * runtime complexity and useonly constantextra space.
  *
  * Constraints:
  * -  1 <= nums.length <= 3 * 10^(4) 
  * -  -3 * 10^(4) <= nums[i] <= 3 * 10^(4) 
  * - Each element in the array appears twice except for one element which appears only once.
  *
*/
class Solution {
 public:
  int singleNumber(vector<int>& nums) {
    int res = 0;
    for (const auto& n : nums) {
      res ^= n;
    }
    return res;
  }
};
}  // namespace l136
#endif
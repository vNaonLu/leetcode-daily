
#ifndef LEETCODE_Q18_H__
#define LEETCODE_Q18_H__
#include <iostream>
#include <set>
#include <vector>

namespace l18 {
using namespace std;

/**
 * This file is generated by leetcode_add.py
 *
 * 18.
 *     4Sum
 *
 * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
 *
 *   Given an array ‘nums’ of ‘n’ integers, return “an array of all the
 *   “unique” quadruplets” ‘[nums[a], nums[b], nums[c], nums[d]]’ such
 *       -  ‘0 ≤ a, b, c, d< n’
 *       -  ‘a’ , ‘b’ , ‘c’ , and ‘d’ are “distinct”
 *       -  ‘nums[a] + nums[b] + nums[c] + nums[d] = target’
 *   You may return the answer in “any order” .
 *
 * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
 *
 *   • ‘1 ≤ nums.length ≤ 200’
 *   • ‘-10⁹ ≤ nums[i] ≤ 10⁹’
 *   • ‘-10⁹ ≤ target ≤ 10⁹’
 *
 */

class Solution {
 public:
  vector<vector<int>> fourSum(vector<int> &nums, int target) {
    set<vector<int>> res;
    sort(nums.begin(), nums.end());
    for (int i = 0; i < int(nums.size() - 3); ++i) {
      for (int j = i + 1; j < int(nums.size() - 2); ++j) {
        if (j > i + 1 && nums[j] == nums[j - 1]) continue;
        int left = j + 1, right = nums.size() - 1;
        int cur = target - nums[i] - nums[j];
        while (left < right) {
          long sum = nums[left] + nums[right];
          if (sum == cur) {
            vector<int> out{nums[i], nums[j], nums[left], nums[right]};
            res.insert(out);
            ++left;
            --right;
          } else if (sum < cur)
            ++left;
          else
            --right;
        }
      }
    }
    return vector<vector<int>>(res.begin(), res.end());
  }
};
}  // namespace l18

#endif
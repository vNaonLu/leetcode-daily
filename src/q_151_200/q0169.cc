// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Majority Element
//
// https://leetcode.com/problems/majority-element/
//
// Question ID: 169
// Difficult  : Easy
// Solve Date : 2021/09/19 08:00

#include <iosfwd>
#include <map>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |169. Majority Element|:
//
// Given an array |nums| of size |n|, return the majority element.
// The majority element is the element that appears more than |⌊n / 2⌋| times.
// You may assume that the majority element always exists in the array.  
//

LEETCODE_BEGIN_RESOLVING(169, MajorityElement, Solution);

class Solution {
public:
  int majorityElement(vector<int> &nums) {
    unordered_map<int, int> cnt;
    for (const auto &n : nums)
      ++cnt[n];
    int res     = 0;
    int cur_cnt = 0;
    for (auto it = cnt.begin(); it != cnt.end(); ++it) {
      if (cur_cnt < it->second) {
        res     = it->first;
        cur_cnt = it->second;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == nums.length|
// * |1 <= n <= 5 * 10⁴|
// * |-10⁹ <= nums[i] <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [3,2,3]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(169, MajorityElement, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 2, 3};
  int         expect   = 3;
  int         actual   = solution->majorityElement(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [2,2,1,1,1,2,2]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(169, MajorityElement, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 2, 1, 1, 1, 2, 2};
  int         expect   = 2;
  int         actual   = solution->majorityElement(nums);
  LCD_EXPECT_EQ(expect, actual);
}

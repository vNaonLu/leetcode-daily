// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Third Maximum Number
//
// https://leetcode.com/problems/third-maximum-number/
//
// Question ID: 414
// Difficult  : Easy
// Solve Date : 2022/08/31 18:23

#include <iosfwd>
#include <set>
#include <unordered_set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |414. Third Maximum Number|:
//
// Given an integer array |nums|, return the third distinct maximum number in
// this array. If the third maximum does not exist, return the maximum number.
//

LEETCODE_BEGIN_RESOLVING(414, ThirdMaximumNumber, Solution);

class Solution {
public:
  int thirdMax(vector<int> &nums) {
    auto exist    = unordered_set<int64_t>();
    auto distinct = vector<int64_t>();
    for (auto x : nums) {
      auto [it, suc] = exist.emplace(x);
      if (suc) {
        distinct.emplace_back(x);
      }
    }
    if (distinct.size() < 3) {
      return *max_element(distinct.begin(), distinct.end());
    } else {
      auto it = distinct.begin() + 2;
      nth_element(distinct.begin(), it, distinct.end(), greater<int>{});
      return *it;
    }
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁴|
// * |-2³¹ <= nums[i] <= 2³¹ - 1|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [3,2,1]
// Output: 1
//
// The first distinct maximum is 3.
// The second distinct maximum is 2.
// The third distinct maximum is 1.

LEETCODE_SOLUTION_UNITTEST(414, ThirdMaximumNumber, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 2, 1};
  int         expect   = 1;
  int         actual   = solution->thirdMax(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,2]
// Output: 2
//
// The first distinct maximum is 2.
// The second distinct maximum is 1.
// The third distinct maximum does not exist, so the maximum (2) is returned
// instead.

LEETCODE_SOLUTION_UNITTEST(414, ThirdMaximumNumber, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2};
  int         expect   = 2;
  int         actual   = solution->thirdMax(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [2,2,3,1]
// Output: 1
//
// The first distinct maximum is 3.
// The second distinct maximum is 2 (both 2's are counted together since they
// have the same value). The third distinct maximum is 1.

LEETCODE_SOLUTION_UNITTEST(414, ThirdMaximumNumber, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 2, 3, 1};
  int         expect   = 1;
  int         actual   = solution->thirdMax(nums);
  LCD_EXPECT_EQ(expect, actual);
}

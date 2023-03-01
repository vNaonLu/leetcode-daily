// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Continuous Subarray Sum
//
// https://leetcode.com/problems/continuous-subarray-sum/
//
// Question ID: 523
// Difficult  : Medium
// Solve Date : 2022/10/26 11:03

#include <array>
#include <iosfwd>
#include <map>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |523. Continuous Subarray Sum|:
//
// Given an integer array nums and an integer k, return |true| if |nums| has a
// good subarray or |false| otherwise. A good subarray is a subarray where:
//
//  • its length is at least two, and
//
//  • the sum of the elements of the subarray is a multiple of |k|.
// Note that:
//
//  • A subarray is a contiguous part of the array.
//
//  • An integer |x| is a multiple of |k| if there exists an integer |n| such
//  that |x = n * k|. |0| is always a multiple of |k|.
//

LEETCODE_BEGIN_RESOLVING(523, ContinuousSubarraySum, Solution);

class Solution {
public:
  bool checkSubarraySum(vector<int> &nums, int k) {
    auto mp = unordered_map<int, int>{
        {0, 0}
    };
    auto sum = (int)0;
    for (int i = 0; i < nums.size(); ++i) {
      sum += nums[i];
      auto it = mp.find(sum % k);
      if (it == mp.end()) {
        mp[sum % k] = i + 1;
      } else if (it->second < i) {
        return true;
      }
    }
    return false;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁵|
// * |0 <= nums[i] <= 10⁹|
// * |0 <= sum(nums[i]) <= 2³¹ - 1|
// * |1 <= k <= 2³¹ - 1|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [23,2,4,6,7], k = 6
// Output: true
//
// [2, 4] is a continuous subarray of size 2 whose elements sum up to 6.

LEETCODE_SOLUTION_UNITTEST(523, ContinuousSubarraySum, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {23, 2, 4, 6, 7};
  int         k        = 6;
  bool        expect   = true;
  bool        actual   = solution->checkSubarraySum(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [23,2,6,4,7], k = 6
// Output: true
//
// [23, 2, 6, 4, 7] is an continuous subarray of size 5 whose elements sum up
// to 42. 42 is a multiple of 6 because 42 = 7 * 6 and 7 is an integer.

LEETCODE_SOLUTION_UNITTEST(523, ContinuousSubarraySum, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {23, 2, 6, 4, 7};
  int         k        = 6;
  bool        expect   = true;
  bool        actual   = solution->checkSubarraySum(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [23,2,6,4,7], k = 13
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(523, ContinuousSubarraySum, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {23, 2, 6, 4, 7};
  int         k        = 13;
  bool        expect   = false;
  bool        actual   = solution->checkSubarraySum(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

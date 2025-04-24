// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Count Complete Subarrays in an Array
//
// https://leetcode.com/problems/count-complete-subarrays-in-an-array/
//
// Question ID: 2799
// Difficult  : Medium
// Solve Date : 2025/04/24 21:11

#include <iosfwd>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2799. Count Complete Subarrays in an Array|:
//
// You are given an array |nums| consisting of positive integers.
// We call a subarray of an array complete if the following condition is
// satisfied:
//
//  • The number of distinct elements in the subarray is equal to the number of
//  distinct elements in the whole array.
// Return the number of complete subarrays.
// A subarray is a contiguous non-empty part of an array.
//
//

LEETCODE_BEGIN_RESOLVING(2799, CountCompleteSubarraysInAnArray, Solution);

class Solution {
public:
  int countCompleteSubarrays(vector<int> &nums, int left = 0, int res = 0) {
    int k = unordered_set<int>(nums.begin(), nums.end()).size();
    unordered_map<int, int> mp;

    for (int i = 0; i < nums.size(); ++i) {
      ++mp[nums[i]];
      while (mp.size() == k) {
        res += nums.size() - i;
        --mp[nums[left]];
        if (mp[nums[left]] == 0) {
          mp.erase(nums[left]);
        }
        ++left;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 1000|
// * |1 <= nums[i] <= 2000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,3,1,2,2]
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(2799, CountCompleteSubarraysInAnArray, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 3, 1, 2, 2};
  int         expect   = 4;
  int         actual   = solution->countCompleteSubarrays(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [5,5,5,5]
// Output: 10
//

LEETCODE_SOLUTION_UNITTEST(2799, CountCompleteSubarraysInAnArray, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {5, 5, 5, 5};
  int         expect   = 10;
  int         actual   = solution->countCompleteSubarrays(nums);
  LCD_EXPECT_EQ(expect, actual);
}

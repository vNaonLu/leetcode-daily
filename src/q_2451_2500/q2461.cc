// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Maximum Sum of Distinct Subarrays With Length K
//
// https://leetcode.com/problems/maximum-sum-of-distinct-subarrays-with-length-k/
//
// Question ID: 2461
// Difficult  : Medium
// Solve Date : 2024/11/19 19:10

#include <iosfwd>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2461. Maximum Sum of Distinct Subarrays With Length K|:
//
// You are given an integer array |nums| and an integer |k|. Find the maximum
// subarray sum of all the subarrays of |nums| that meet the following
// conditions:
//
//  • The length of the subarray is |k|, and
//
//  • All the elements of the subarray are distinct.
// Return the maximum subarray sum of all the subarrays that meet the
// conditions. If no subarray meets the conditions, return |0|. A subarray is a
// contiguous non-empty sequence of elements within an array.
//
//

LEETCODE_BEGIN_RESOLVING(2461, MaximumSumOfDistinctSubarraysWithLengthK,
                         Solution);

class Solution {
public:
  long long maximumSubarraySum(vector<int> &nums, int k) {
    int64_t                 res = 0;
    int64_t                 cur = 0;
    unordered_map<int, int> freq;
    auto                    lo = nums.begin();
    auto                    hi = nums.begin();
    while (hi != nums.end()) {
      ++freq[*hi];
      cur += *hi;

      if (distance(lo, hi) >= k) {
        cur -= *lo;
        if (--freq[*lo] == 0) {
          freq.erase(*lo);
        }
        ++lo;
      }

      if (distance(lo, hi) == k - 1 && freq.size() == k) {
        res = max(res, cur);
      }
      ++hi;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= k <= nums.length <= 10⁵|
// * |1 <= nums[i] <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,5,4,2,9,9,9], k = 3
// Output: 15
//

LEETCODE_SOLUTION_UNITTEST(2461, MaximumSumOfDistinctSubarraysWithLengthK,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 5, 4, 2, 9, 9, 9};
  int         k        = 3;
  long long   expect   = 15;
  long long   actual   = solution->maximumSubarraySum(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [4,4,4], k = 3
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(2461, MaximumSumOfDistinctSubarraysWithLengthK,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {4, 4, 4};
  int         k        = 3;
  long long   expect   = 0;
  long long   actual   = solution->maximumSubarraySum(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

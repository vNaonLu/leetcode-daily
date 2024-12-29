// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Maximum Sum of 3 Non-Overlapping Subarrays
//
// https://leetcode.com/problems/maximum-sum-of-3-non-overlapping-subarrays/
//
// Question ID: 689
// Difficult  : Hard
// Solve Date : 2024/12/28 12:45

#include <iosfwd>
#include <numeric>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |689. Maximum Sum of 3 Non-Overlapping Subarrays|:
//
// Given an integer array |nums| and an integer |k|, find three non-overlapping
// subarrays of length |k| with maximum sum and return them. Return the result
// as a list of indices representing the starting position of each interval
// (0-indexed). If there are multiple answers, return the lexicographically
// smallest one.
//
//

LEETCODE_BEGIN_RESOLVING(689, MaximumSumOf3NonOverlappingSubarrays, Solution);

class Solution {
public:
  vector<int> maxSumOfThreeSubarrays(vector<int> &nums, int k) {
    const int   n = nums.size();
    vector<int> ksum(n - k + 1, 0), L(n - 3 * k + 1, -1);
    int maxKsum = ksum[0] = accumulate(nums.begin(), nums.begin() + k, 0);
    L[0]                  = 0;
    for (int i = 1; i < n - k + 1; i++) {
      ksum[i] = ksum[i - 1] - nums[i - 1] + nums[i + k - 1];
      if (i > n - 3 * k)
        continue;
      if (maxKsum < ksum[i]) {
        maxKsum = ksum[i];
        L[i]    = i;
      } else {
        L[i] = L[i - 1];
      }
    }
    vector<int> R(n - 3 * k + 1, -1);
    maxKsum  = ksum.back();
    R.back() = n - k;
    for (int i = n - k - 1; i >= 2 * k; i--) {
      if (maxKsum <= ksum[i]) {
        maxKsum      = ksum[i];
        R[i - 2 * k] = i;
      } else {
        R[i - 2 * k] = R[i + 1 - 2 * k];
      }
    }
    vector<int> ans(3, -1);
    int         max3K = 0;
    for (int i = 0; i <= n - 3 * k; i++) {
      int sum3K = ksum[L[i]] + ksum[i + k] + ksum[R[i]];
      if (sum3K > max3K) {
        max3K = sum3K;
        ans   = {L[i], i + k, R[i]};
      }
    }
    return ans;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 2 * 10⁴|
// * |1 <= nums[i] < 2¹⁶|
// * |1 <= k <= floor(nums.length / 3)|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,1,2,6,7,5,1], k = 2
// Output: [0,3,5]
//

LEETCODE_SOLUTION_UNITTEST(689, MaximumSumOf3NonOverlappingSubarrays,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 1, 2, 6, 7, 5, 1};
  int         k        = 2;
  vector<int> expect   = {0, 3, 5};
  vector<int> actual   = solution->maxSumOfThreeSubarrays(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,2,1,2,1,2,1,2,1], k = 2
// Output: [0,2,4]
//

LEETCODE_SOLUTION_UNITTEST(689, MaximumSumOf3NonOverlappingSubarrays,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 1, 2, 1, 2, 1, 2, 1};
  int         k        = 2;
  vector<int> expect   = {0, 2, 4};
  vector<int> actual   = solution->maxSumOfThreeSubarrays(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Maximum Subarray Sum With Length Divisible by K
//
// https://leetcode.com/problems/maximum-subarray-sum-with-length-divisible-by-k/
//
// Question ID: 3381
// Difficult  : Medium
// Solve Date : 2025/11/28 19:13

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3381. Maximum Subarray Sum With Length Divisible by K|:
//
// You are given an array of integers |nums| and an integer |k|.
// Return the maximum sum of a subarray of |nums|, such that the size of the
// subarray is divisible by |k|.
//
//

LEETCODE_BEGIN_RESOLVING(3381, MaximumSubarraySumWithLengthDivisibleByK,
                         Solution);

class Solution {
public:
  using ll = long long;
  static long long maxSubarraySum(vector<int> &nums, int k) {
    const int  n = nums.size();
    vector<ll> minS(k, numeric_limits<ll>::max() / 2);
    ll         prefix = 0, ans = numeric_limits<ll>::min();
    minS[k - 1] = 0;
    for (int i = 0; i < n; i++) {
      prefix += nums[i];
      ll &ksum = minS[i % k];
      ans      = max(ans, prefix - ksum);
      ksum     = min(prefix, ksum);
    }
    return ans;
  }
};
LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= k <= nums.length <= 2 * 10⁵|
// * |-10⁹ <= nums[i] <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2], k = 1
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(3381, MaximumSubarraySumWithLengthDivisibleByK,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2};
  int         k        = 1;
  long long   expect   = 3;
  long long   actual   = solution->maxSubarraySum(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [-1,-2,-3,-4,-5], k = 4
// Output: -10
//

LEETCODE_SOLUTION_UNITTEST(3381, MaximumSubarraySumWithLengthDivisibleByK,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {-1, -2, -3, -4, -5};
  int         k        = 4;
  long long   expect   = -10;
  long long   actual   = solution->maxSubarraySum(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [-5,1,2,-3,4], k = 2
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(3381, MaximumSubarraySumWithLengthDivisibleByK,
                           example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {-5, 1, 2, -3, 4};
  int         k        = 2;
  long long   expect   = 4;
  long long   actual   = solution->maxSubarraySum(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

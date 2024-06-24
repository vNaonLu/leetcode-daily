// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Count Number of Nice Subarrays
//
// https://leetcode.com/problems/count-number-of-nice-subarrays/
//
// Question ID: 1248
// Difficult  : Medium
// Solve Date : 2024/06/22 17:11

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1248. Count Number of Nice Subarrays|:
//
// Given an array of integers |nums| and an integer |k|. A continuous subarray
// is called nice if there are |k| odd numbers on it. Return the number of nice
// sub-arrays.
//
//

LEETCODE_BEGIN_RESOLVING(1248, CountNumberOfNiceSubarrays, Solution);

class Solution {
public:
  int numberOfSubarrays(vector<int> &nums, int k) {
    int         n = nums.size();
    vector<int> cnt(n + 1, 0);
    int         res = 0;
    int         t   = 0;
    cnt[0]          = 1;
    for (auto x : nums) {
      t += x & 1;
      if (t - k >= 0) {
        res += cnt[t - k];
      }
      ++cnt[t];
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 50000|
// * |1 <= nums[i] <= 10^5|
// * |1 <= k <= nums.length|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,1,2,1,1], k = 3
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(1248, CountNumberOfNiceSubarrays, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 1, 2, 1, 1};
  int         k        = 3;
  int         expect   = 2;
  int         actual   = solution->numberOfSubarrays(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [2,4,6], k = 1
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(1248, CountNumberOfNiceSubarrays, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 4, 6};
  int         k        = 1;
  int         expect   = 0;
  int         actual   = solution->numberOfSubarrays(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [2,2,2,1,2,2,1,2,2,2], k = 2
// Output: 16
//

LEETCODE_SOLUTION_UNITTEST(1248, CountNumberOfNiceSubarrays, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 2, 2, 1, 2, 2, 1, 2, 2, 2};
  int         k        = 2;
  int         expect   = 16;
  int         actual   = solution->numberOfSubarrays(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

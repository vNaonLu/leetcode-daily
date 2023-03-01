// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Range Sum of Sorted Subarray Sums
//
// https://leetcode.com/problems/range-sum-of-sorted-subarray-sums/
//
// Question ID: 1508
// Difficult  : Medium
// Solve Date : 2022/07/27 18:31

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1508. Range Sum of Sorted Subarray Sums|:
//
// You are given the array |nums| consisting of |n| positive integers. You
// computed the sum of all non-empty continuous subarrays from the array and
// then sorted them in non-decreasing order, creating a new array of |n * (n +
// 1) / 2| numbers. Return the sum of the numbers from index |left| to index
// |right| (indexed from 1), inclusive, in the new array. Since the answer can
// be a huge number return it modulo |10⁹ + 7|.
//

LEETCODE_BEGIN_RESOLVING(1508, RangeSumOfSortedSubarraySums, Solution);

class Solution {
private:
  inline constexpr static int kMod = 1e9 + 7;

public:
  int rangeSum(vector<int> &nums, int n, int left, int right) {
    vector<int> presum = nums;
    for (auto it = presum.begin() + 1; it != presum.end(); ++it) {
      *it += *(it - 1);
    }

    vector<int> subsum(presum.begin(), presum.begin() + n);
    for (int i = 0; i < n - 1; ++i) {
      for (int j = i + 1; j < n; ++j) {
        subsum.emplace_back(presum[j] - presum[i]);
      }
    }

    sort(subsum.begin(), subsum.end());

    int res = 0;
    for (int i = left - 1; i <= right - 1; ++i) {
      res += subsum[i] % kMod;
      res %= kMod;
    }

    return res % kMod;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == nums.length|
// * |1 <= nums.length <= 1000|
// * |1 <= nums[i] <= 100|
// * |1 <= left <= right <= n * (n + 1) / 2|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,3,4], n = 4, left = 1, right = 5
// Output: 13
//
// All subarray sums are 1, 3, 6, 10, 2, 5, 9, 3, 7, 4. After sorting them in
// non-decreasing order we have the new array [1, 2, 3, 3, 4, 5, 6, 7, 9, 10].
// The sum of the numbers from index le = 1 to ri = 5 is 1 + 2 + 3 + 3 + 4 = 13.

LEETCODE_SOLUTION_UNITTEST(1508, RangeSumOfSortedSubarraySums, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 4};
  int         n        = 4;
  int         left     = 1;
  int         right    = 5;
  int         expect   = 13;
  int         actual   = solution->rangeSum(nums, n, left, right);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,2,3,4], n = 4, left = 3, right = 4
// Output: 6
//
// The given array is the same as example 1. We have the new array [1, 2, 3, 3,
// 4, 5, 6, 7, 9, 10]. The sum of the numbers from index le = 3 to ri = 4 is 3 +
// 3 = 6.

LEETCODE_SOLUTION_UNITTEST(1508, RangeSumOfSortedSubarraySums, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 4};
  int         n        = 4;
  int         left     = 3;
  int         right    = 4;
  int         expect   = 6;
  int         actual   = solution->rangeSum(nums, n, left, right);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [1,2,3,4], n = 4, left = 1, right = 10
// Output: 50
//

LEETCODE_SOLUTION_UNITTEST(1508, RangeSumOfSortedSubarraySums, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 4};
  int         n        = 4;
  int         left     = 1;
  int         right    = 10;
  int         expect   = 50;
  int         actual   = solution->rangeSum(nums, n, left, right);
  LCD_EXPECT_EQ(expect, actual);
}

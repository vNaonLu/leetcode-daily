// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Maximum Average Subarray I
//
// https://leetcode.com/problems/maximum-average-subarray-i/
//
// Question ID: 643
// Difficult  : Easy
// Solve Date : 2022/05/20 18:17

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |643. Maximum Average Subarray I|:
//
// You are given an integer array |nums| consisting of |n| elements, and an
// integer |k|. Find a contiguous subarray whose length is equal to |k| that has
// the maximum average value and return this value. Any answer with a
// calculation error less than |10⁻⁵| will be accepted.
//

LEETCODE_BEGIN_RESOLVING(643, MaximumAverageSubarrayI, Solution);

class Solution {
public:
  double findMaxAverage(vector<int> &nums, int k) {
    vector<int> sum = nums;
    double      res = 0;

    for (int i = 1; i < sum.size(); ++i) {
      sum[i] += sum[i - 1];
    }

    res = static_cast<double>(sum[k - 1]) / k;

    for (int i = k; i < sum.size(); ++i) {
      res = max(res, static_cast<double>(sum[i] - sum[i - k]) / k);
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == nums.length|
// * |1 <= k <= n <= 10⁵|
// * |-10⁴ <= nums[i] <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,12,-5,-6,50,3], k = 4
// Output: 12.75000
//
// Maximum average is (12 - 5 - 6 + 50) / 4 = 51 / 4 = 12.75

LEETCODE_SOLUTION_UNITTEST(643, MaximumAverageSubarrayI, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 12, -5, -6, 50, 3};
  int         k        = 4;
  double      expect   = 12.75000;
  double      actual   = solution->findMaxAverage(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [5], k = 1
// Output: 5.00000
//

LEETCODE_SOLUTION_UNITTEST(643, MaximumAverageSubarrayI, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {5};
  int         k        = 1;
  double      expect   = 5.00000;
  double      actual   = solution->findMaxAverage(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Maximum Beauty of an Array After Applying Operation
//
// https://leetcode.com/problems/maximum-beauty-of-an-array-after-applying-operation/
//
// Question ID: 2779
// Difficult  : Medium
// Solve Date : 2024/12/11 20:13

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2779. Maximum Beauty of an Array After Applying Operation|:
//
// You are given a 0-indexed array |nums| and a non-negative integer |k|.
// In one operation, you can do the following:
//
//  • Choose an index |i| that hasn't been chosen before from the range |[0,
//  nums.length - 1]|.
//
//  • Replace |nums[i]| with any integer from the range |[nums[i] - k, nums[i] +
//  k]|.
// The beauty of the array is the length of the longest subsequence consisting
// of equal elements. Return the maximum possible beauty of the array |nums|
// after applying the operation any number of times. Note that you can apply the
// operation to each index only once. A subsequence of an array is a new array
// generated from the original array by deleting some elements (possibly none)
// without changing the order of the remaining elements.
//
//

LEETCODE_BEGIN_RESOLVING(2779, MaximumBeautyOfAnArrayAfterApplyingOperation,
                         Solution);

class Solution {
public:
  int maximumBeauty(vector<int> &nums, int k) {
    vector<int> freq(100001);
    int         res = 0;
    int         cnt = 0;
    int         mx  = 0;
    int         mn  = 1e6;
    for (auto x : nums) {
      ++freq[x];
      mx = max(mx, x);
      mn = min(mn, x);
    }
    for (int l = mn, r = mn; r <= mx; ++r) {
      cnt += freq[r];
      while (r - l > 2 * k) {
        cnt -= freq[l];
        ++l;
      }
      res = max(res, cnt);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁵|
// * |0 <= nums[i], k <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [4,6,1,2], k = 2
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(2779, MaximumBeautyOfAnArrayAfterApplyingOperation,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {4, 6, 1, 2};
  int         k        = 2;
  int         expect   = 3;
  int         actual   = solution->maximumBeauty(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,1,1,1], k = 10
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(2779, MaximumBeautyOfAnArrayAfterApplyingOperation,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 1, 1, 1};
  int         k        = 10;
  int         expect   = 4;
  int         actual   = solution->maximumBeauty(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: [100000]
// 0
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(2779, MaximumBeautyOfAnArrayAfterApplyingOperation,
                           extra_testcase_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {100000};
  int         k        = 0;
  int         expect   = 1;
  int         actual   = solution->maximumBeauty(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Number of Zero-Filled Subarrays
//
// https://leetcode.com/problems/number-of-zero-filled-subarrays/
//
// Question ID: 2348
// Difficult  : Medium
// Solve Date : 2023/03/21 18:38

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2348. Number of Zero-Filled Subarrays|:
//
// Given an integer array |nums|, return the number of subarrays filled with
// |0|. A subarray is a contiguous non-empty sequence of elements within an
// array.
//
//

LEETCODE_BEGIN_RESOLVING(2348, NumberOfZeroFilledSubarrays, Solution);

class Solution {
public:
  long long zeroFilledSubarray(vector<int> &nums) {
    int64_t res      = 0;
    int64_t cont_cnt = 0;
    for (auto x : nums) {
      if (x == 0) {
        ++cont_cnt;
      } else {
        res += ((1 + cont_cnt) * cont_cnt) / 2;
        cont_cnt = 0;
      }
    }
    res += ((1 + cont_cnt) * cont_cnt) / 2;
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁵|
// * |-10⁹ <= nums[i] <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,3,0,0,2,0,0,4]
// Output: 6
//
// There are 4 occurrences of [0] as a subarray.
// There are 2 occurrences of [0,0] as a subarray.
// There is no occurrence of a subarray with a size more than 2 filled with 0.
// Therefore, we return 6.

LEETCODE_SOLUTION_UNITTEST(2348, NumberOfZeroFilledSubarrays, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 3, 0, 0, 2, 0, 0, 4};
  long long   expect   = 6;
  long long   actual   = solution->zeroFilledSubarray(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [0,0,0,2,0,0]
// Output: 9
// Explanation:
// There are 5 occurrences of [0] as a subarray.
// There are 3 occurrences of [0,0] as a subarray.
// There is 1 occurrence of [0,0,0] as a subarray.
// There is no occurrence of a subarray with a size more than 3 filled with 0.
// Therefore, we return 9.
//

LEETCODE_SOLUTION_UNITTEST(2348, NumberOfZeroFilledSubarrays, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {0, 0, 0, 2, 0, 0};
  long long   expect   = 9;
  long long   actual   = solution->zeroFilledSubarray(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [2,10,2019]
// Output: 0
//
// There is no subarray filled with 0. Therefore, we return 0.

LEETCODE_SOLUTION_UNITTEST(2348, NumberOfZeroFilledSubarrays, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 10, 2019};
  long long   expect   = 0;
  long long   actual   = solution->zeroFilledSubarray(nums);
  LCD_EXPECT_EQ(expect, actual);
}

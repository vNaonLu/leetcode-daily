// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Count Subarrays Where Max Element Appears at Least K Times
//
// https://leetcode.com/problems/count-subarrays-where-max-element-appears-at-least-k-times/
//
// Question ID: 2962
// Difficult  : Medium
// Solve Date : 2024/03/29 21:16

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2962. Count Subarrays Where Max Element Appears at Least K
// Times|:
//
// You are given an integer array |nums| and a positive integer |k|.
// Return the number of subarrays where the maximum element of |nums| appears at
// least |k| times in that subarray. A subarray is a contiguous sequence of
// elements within an array.
//
//

LEETCODE_BEGIN_RESOLVING(2962,
                         CountSubarraysWhereMaxElementAppearsAtLeastKTimes,
                         Solution);

class Solution {
public:
  long long countSubarrays(vector<int> &nums, int k) {
    int     mx  = *max_element(nums.begin(), nums.end());
    int64_t res = 0;
    int     l   = 0;
    int     r   = 0;
    while (r < nums.size()) {
      k -= (nums[r++] == mx);
      while (!k) {
        k += (nums[l++] == mx);
      }
      res += l;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁵|
// * |1 <= nums[i] <= 10⁶|
// * |1 <= k <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,3,2,3,3], k = 2
// Output: 6
//

LEETCODE_SOLUTION_UNITTEST(2962,
                           CountSubarraysWhereMaxElementAppearsAtLeastKTimes,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 3, 2, 3, 3};
  int         k        = 2;
  long long   expect   = 6;
  long long   actual   = solution->countSubarrays(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,4,2,1], k = 3
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(2962,
                           CountSubarraysWhereMaxElementAppearsAtLeastKTimes,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 4, 2, 1};
  int         k        = 3;
  long long   expect   = 0;
  long long   actual   = solution->countSubarrays(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

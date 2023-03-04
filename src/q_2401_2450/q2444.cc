// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Count Subarrays With Fixed Bounds
//
// https://leetcode.com/problems/count-subarrays-with-fixed-bounds/
//
// Question ID: 2444
// Difficult  : Hard
// Solve Date : 2023/03/04 13:39

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2444. Count Subarrays With Fixed Bounds|:
//
// You are given an integer array |nums| and two integers |minK| and |maxK|.
// A fixed-bound subarray of |nums| is a subarray that satisfies the following
// conditions:
//
//  • The minimum value in the subarray is equal to |minK|.
//
//  • The maximum value in the subarray is equal to |maxK|.
// Return the number of fixed-bound subarrays.
// A subarray is a contiguous part of an array.
//

LEETCODE_BEGIN_RESOLVING(2444, CountSubarraysWithFixedBounds, Solution);

class Solution {
public:
  long long countSubarrays(vector<int> &nums, int minK, int maxK) {
    int64_t res   = 0;
    int     idx   = 0;
    int     min_i = -1;
    int     max_i = -1;
    for (int i = 0; i < nums.size(); ++i) {
      if (nums[i] < minK || nums[i] > maxK) {
        idx   = i + 1;
        min_i = -1;
        max_i = -1;
      } else {
        if (nums[i] == minK) {
          min_i = i;
        }
        if (nums[i] == maxK) {
          max_i = i;
        }
        if (max_i != -1 && min_i != -1) {
          res += min(max_i, min_i) - idx + 1;
        }
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |2 <= nums.length <= 10⁵|
// * |1 <= nums[i], minK, maxK <= 10⁶|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,3,5,2,7,5], minK = 1, maxK = 5
// Output: 2
//
// The fixed-bound subarrays are [1,3,5] and [1,3,5,2].

LEETCODE_SOLUTION_UNITTEST(2444, CountSubarraysWithFixedBounds, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 3, 5, 2, 7, 5};
  int         minK     = 1;
  int         maxK     = 5;
  long long   expect   = 2;
  long long   actual   = solution->countSubarrays(nums, minK, maxK);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,1,1,1], minK = 1, maxK = 1
// Output: 10
//
// Every subarray of nums is a fixed-bound subarray. There are 10 possible
// subarrays.

LEETCODE_SOLUTION_UNITTEST(2444, CountSubarraysWithFixedBounds, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 1, 1, 1};
  int         minK     = 1;
  int         maxK     = 1;
  long long   expect   = 10;
  long long   actual   = solution->countSubarrays(nums, minK, maxK);
  LCD_EXPECT_EQ(expect, actual);
}

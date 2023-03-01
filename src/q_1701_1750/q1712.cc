// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Ways to Split Array Into Three Subarrays
//
// https://leetcode.com/problems/ways-to-split-array-into-three-subarrays/
//
// Question ID: 1712
// Difficult  : Medium
// Solve Date : 2022/07/23 17:35

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1712. Ways to Split Array Into Three Subarrays|:
//
// A split of an integer array is good if:
//
//  • The array is split into three non-empty contiguous subarrays - named
//  |left|, |mid|, |right| respectively from left to right.
//
//  • The sum of the elements in |left| is less than or equal to the sum of the
//  elements in |mid|, and the sum of the elements in |mid| is less than or
//  equal to the sum of the elements in |right|.
// Given |nums|, an array of non-negative integers, return the number of good
// ways to split |nums|. As the number may be too large, return it modulo |10^{9
// }+ 7|.
//

LEETCODE_BEGIN_RESOLVING(1712, WaysToSplitArrayIntoThreeSubarrays, Solution);

class Solution {
private:
  inline constexpr static int kMod = 1e9 + 7;

public:
  int waysToSplit(vector<int> &nums) {
    for (auto it = nums.begin() + 1; it != nums.end(); ++it) {
      *it += *(it - 1);
    }

    int res = 0;
    for (int i = 0; i < nums.size() - 1; ++i) {
      int left = -1, right = -1;

      int lo = i + 1, hi = nums.size() - 2;
      while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (nums[mid] - nums[i] <= nums.back() - nums[mid]) {
          right = mid;
          lo    = mid + 1;
        } else {
          hi = mid - 1;
        }
      }

      lo = i + 1;
      hi = nums.size() - 2;
      while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (nums[i] <= nums[mid] - nums[i]) {
          left = mid;
          hi   = mid - 1;
        } else {
          lo = mid + 1;
        }
      }

      if (left == -1 || right == -1 || left > right) {
        continue;
      }

      res = (res + (right - left + 1) % kMod) % kMod;
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |3 <= nums.length <= 10⁵|
// * |0 <= nums[i] <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,1,1]
// Output: 1
//
// The only good way to split nums is [1] [1] [1].

LEETCODE_SOLUTION_UNITTEST(1712, WaysToSplitArrayIntoThreeSubarrays,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 1, 1};
  int         expect   = 1;
  int         actual   = solution->waysToSplit(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,2,2,2,5,0]
// Output: 3
//
// There are three good ways of splitting nums:
// [1] [2] [2,2,5,0]
// [1] [2,2] [2,5,0]
// [1,2] [2,2] [5,0]

LEETCODE_SOLUTION_UNITTEST(1712, WaysToSplitArrayIntoThreeSubarrays,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 2, 2, 5, 0};
  int         expect   = 3;
  int         actual   = solution->waysToSplit(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [3,2,1]
// Output: 0
//
// There is no good way to split nums.

LEETCODE_SOLUTION_UNITTEST(1712, WaysToSplitArrayIntoThreeSubarrays,
                           example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 2, 1};
  int         expect   = 0;
  int         actual   = solution->waysToSplit(nums);
  LCD_EXPECT_EQ(expect, actual);
}

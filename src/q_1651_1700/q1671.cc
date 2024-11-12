// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Minimum Number of Removals to Make Mountain Array
//
// https://leetcode.com/problems/minimum-number-of-removals-to-make-mountain-array/
//
// Question ID: 1671
// Difficult  : Hard
// Solve Date : 2024/10/30 19:09

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1671. Minimum Number of Removals to Make Mountain Array|:
//
// You may recall that an array |arr| is a mountain array if and only if:
//
//  • |arr.length >= 3|
//
//  • There exists some index |i| (0-indexed) with |0 < i < arr.length - 1| such
//  that:
//
//
//    • |arr[0] < arr[1] < ... < arr[i - 1] < arr[i]|
//
//    • |arr[i] > arr[i + 1] > ... > arr[arr.length - 1]|
//
//
// Given an integer array |nums|​​​, return the minimum number of elements
// to remove to make |nums​​​| a mountain array.
//
//

LEETCODE_BEGIN_RESOLVING(1671, MinimumNumberOfRemovalsToMakeMountainArray,
                         Solution);

class Solution {
public:
  int minimumMountainRemovals(vector<int> &nums) {
    int         n = nums.size();
    vector<int> lis(n, 1);
    vector<int> lds(n, 1);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < i; ++j) {
        if (nums[i] > nums[j]) {
          lis[i] = max(lis[i], lis[j] + 1);
        }
      }
    }

    for (int i = n; i >= 0; --i) {
      for (int j = n - 1; j > i; --j) {
        if (nums[i] > nums[j]) {
          lds[i] = max(lds[i], lds[j] + 1);
        }
      }
    }

    int res = 0;
    for (int i = 1; i < n - 1; ++i) {
      if (lis[i] > 1 && lds[i] > 1) {
        res = max(res, lis[i] + lds[i] - 1);
      }
    }
    return n - res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |3 <= nums.length <= 1000|
// * |1 <= nums[i] <= 10⁹|
// * It is guaranteed that you can make a mountain array out of |nums|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,3,1]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(1671, MinimumNumberOfRemovalsToMakeMountainArray,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 3, 1};
  int         expect   = 0;
  int         actual   = solution->minimumMountainRemovals(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [2,1,1,5,6,2,3,1]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(1671, MinimumNumberOfRemovalsToMakeMountainArray,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 1, 1, 5, 6, 2, 3, 1};
  int         expect   = 3;
  int         actual   = solution->minimumMountainRemovals(nums);
  LCD_EXPECT_EQ(expect, actual);
}

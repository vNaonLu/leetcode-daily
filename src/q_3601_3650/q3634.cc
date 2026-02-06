// Copyright 2026 Naon Lu
//
// This file describes the solution of
// Minimum Removals to Balance Array
//
// https://leetcode.com/problems/minimum-removals-to-balance-array/
//
// Question ID: 3634
// Difficult  : Medium
// Solve Date : 2026/02/06 19:19

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3634. Minimum Removals to Balance Array|:
//
// You are given an integer array |nums| and an integer |k|.
// An array is considered balanced if the value of its maximum element is at
// most |k| times the minimum element. You may remove any number of elements
// from |nums|​​​​​​​ without making it empty. Return the minimum
// number of elements to remove so that the remaining array is balanced. Note:
// An array of size 1 is considered balanced as its maximum and minimum are
// equal, and the condition always holds true.
//
//

LEETCODE_BEGIN_RESOLVING(3634, MinimumRemovalsToBalanceArray, Solution);

class Solution {
public:
  int minRemoval(vector<int> &nums, int k) {
    sort(nums.begin(), nums.end());
    int n      = nums.size();
    int i      = 0;
    int maxLen = 0;

    for (int j = 0; j < n; j++) {
      while ((long long)nums[j] > (long long)nums[i] * k) {
        i++;
      }
      maxLen = max(maxLen, j - i + 1);
    }

    return n - maxLen;
  }
};
LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁵|
// * |1 <= nums[i] <= 10⁹|
// * |1 <= k <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [2,1,5], k = 2
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(3634, MinimumRemovalsToBalanceArray, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 1, 5};
  int         k        = 2;
  int         expect   = 1;
  int         actual   = solution->minRemoval(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,6,2,9], k = 3
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(3634, MinimumRemovalsToBalanceArray, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 6, 2, 9};
  int         k        = 3;
  int         expect   = 2;
  int         actual   = solution->minRemoval(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [4,6], k = 2
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(3634, MinimumRemovalsToBalanceArray, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {4, 6};
  int         k        = 2;
  int         expect   = 0;
  int         actual   = solution->minRemoval(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

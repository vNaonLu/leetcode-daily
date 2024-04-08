// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Shortest Subarray With OR at Least K I
//
// https://leetcode.com/problems/shortest-subarray-with-or-at-least-k-i/
//
// Question ID: 3095
// Difficult  : Easy
// Solve Date : 2024/04/02 20:23

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3095. Shortest Subarray With OR at Least K I|:
//
// You are given an array |nums| of non-negative integers and an integer |k|.
// An array is called special if the bitwise |OR| of all of its elements is at
// least |k|. Return the length of the shortest special non-empty subarray of
// |nums|, or return |-1| if no special subarray exists.
//
//

LEETCODE_BEGIN_RESOLVING(3095, ShortestSubarrayWithORAtLeastKI, Solution);

class Solution {
public:
  int minimumSubarrayLength(vector<int> &nums, int k) {
    int n   = nums.size();
    int res = numeric_limits<int>::max();
    for (int i = 0; i < n; ++i) {
      int tmp = 0;
      for (int j = i; j < n; ++j) {
        tmp |= nums[j];
        if (tmp >= k) {
          res = min(res, j - i + 1);
          break;
        }
      }
    }
    return res == numeric_limits<int>::max() ? -1 : res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 50|
// * |0 <= nums[i] <= 50|
// * |0 <= k < 64|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,3], k = 2
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(3095, ShortestSubarrayWithORAtLeastKI, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3};
  int         k        = 2;
  int         expect   = 1;
  int         actual   = solution->minimumSubarrayLength(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [2,1,8], k = 10
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(3095, ShortestSubarrayWithORAtLeastKI, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 1, 8};
  int         k        = 10;
  int         expect   = 3;
  int         actual   = solution->minimumSubarrayLength(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [1,2], k = 0
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(3095, ShortestSubarrayWithORAtLeastKI, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2};
  int         k        = 0;
  int         expect   = 1;
  int         actual   = solution->minimumSubarrayLength(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

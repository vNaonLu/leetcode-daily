// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Kth Largest Element in an Array
//
// https://leetcode.com/problems/kth-largest-element-in-an-array/
//
// Question ID: 215
// Difficult  : Medium
// Solve Date : 2021/10/08 12:56

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |215. Kth Largest Element in an Array|:
//
// Given an integer array |nums| and an integer |k|, return the |kᵗʰ| largest
// element in the array. Note that it is the |kᵗʰ| largest element in the sorted
// order, not the |kᵗʰ| distinct element. You must solve it in |O(n)| time
// complexity.  
//

LEETCODE_BEGIN_RESOLVING(215, KthLargestElementInAnArray, Solution);

class Solution {
public:
  int findKthLargest(vector<int> &nums, int k) {
    sort(nums.begin(), nums.end());
    return *(nums.end() - k);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= k <= nums.length <= 10⁵|
// * |-10⁴ <= nums[i] <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [3,2,1,5,6,4], k = 2
// Output: 5
//

LEETCODE_SOLUTION_UNITTEST(215, KthLargestElementInAnArray, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 2, 1, 5, 6, 4};
  int         k        = 2;
  int         expect   = 5;
  int         actual   = solution->findKthLargest(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [3,2,3,1,2,4,5,5,6], k = 4
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(215, KthLargestElementInAnArray, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 2, 3, 1, 2, 4, 5, 5, 6};
  int         k        = 4;
  int         expect   = 4;
  int         actual   = solution->findKthLargest(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

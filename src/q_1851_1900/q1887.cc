// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Reduction Operations to Make the Array Elements Equal
//
// https://leetcode.com/problems/reduction-operations-to-make-the-array-elements-equal/
//
// Question ID: 1887
// Difficult  : Medium
// Solve Date : 2021/10/12 12:18

#include <iosfwd>
#include <map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1887. Reduction Operations to Make the Array Elements Equal|:
//
// Given an integer array |nums|, your goal is to make all elements in |nums|
// equal. To complete one operation, follow these steps:
//
//  1. Find the largest value in |nums|. Let its index be |i| (0-indexed) and
//  its value be |largest|. If there are multiple elements with the largest
//  value, pick the smallest |i|.
//
//  2. Find the next largest value in |nums| strictly smaller than |largest|.
//  Let its value be |nextLargest|.
//
//  3. Reduce |nums[i]| to |nextLargest|.
// Return the number of operations to make all elements in |nums| equal.
//  
//

LEETCODE_BEGIN_RESOLVING(1887, ReductionOperationsToMakeTheArrayElementsEqual,
                         Solution);

class Solution {
public:
  int reductionOperations(vector<int> &nums) {
    map<int, int> freq;
    for (const auto &x : nums)
      ++freq[x];
    int size   = freq.size() - 1;
    int presum = 0;
    int res    = 0;
    for (auto it = freq.rbegin(); it != freq.rend() && size; ++it, --size) {
      presum += it->second;
      res += presum;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 5 * 10⁴|
// * |1 <= nums[i] <= 5 * 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [5,1,3]
// Output: 3
//
//  It takes 3 operations to make all elements in nums equal:
// 1. largest = 5 at index 0. nextLargest = 3. Reduce nums[0] to 3. nums =
// [3,1,3].
// 2. largest = 3 at index 0. nextLargest = 1. Reduce nums[0] to 1. nums =
// [1,1,3].
// 3. largest = 3 at index 2. nextLargest = 1. Reduce nums[2] to 1. nums =
// [1,1,1].

LEETCODE_SOLUTION_UNITTEST(1887, ReductionOperationsToMakeTheArrayElementsEqual,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {5, 1, 3};
  int         expect   = 3;
  int         actual   = solution->reductionOperations(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,1,1]
// Output: 0
//
//  All elements in nums are already equal.

LEETCODE_SOLUTION_UNITTEST(1887, ReductionOperationsToMakeTheArrayElementsEqual,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 1, 1};
  int         expect   = 0;
  int         actual   = solution->reductionOperations(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [1,1,2,2,3]
// Output: 4
//
//  It takes 4 operations to make all elements in nums equal:
// 1. largest = 3 at index 4. nextLargest = 2. Reduce nums[4] to 2. nums =
// [1,1,2,2,2].
// 2. largest = 2 at index 2. nextLargest = 1. Reduce nums[2] to 1. nums =
// [1,1,1,2,2].
// 3. largest = 2 at index 3. nextLargest = 1. Reduce nums[3] to 1. nums =
// [1,1,1,1,2].
// 4. largest = 2 at index 4. nextLargest = 1. Reduce nums[4] to 1. nums =
// [1,1,1,1,1].

LEETCODE_SOLUTION_UNITTEST(1887, ReductionOperationsToMakeTheArrayElementsEqual,
                           example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 1, 2, 2, 3};
  int         expect   = 4;
  int         actual   = solution->reductionOperations(nums);
  LCD_EXPECT_EQ(expect, actual);
}

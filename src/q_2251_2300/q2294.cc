// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Partition Array Such That Maximum Difference Is K
//
// https://leetcode.com/problems/partition-array-such-that-maximum-difference-is-k/
//
// Question ID: 2294
// Difficult  : Medium
// Solve Date : 2025/06/19 19:05

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2294. Partition Array Such That Maximum Difference Is K|:
//
// You are given an integer array |nums| and an integer |k|. You may partition
// |nums| into one or more subsequences such that each element in |nums| appears
// in exactly one of the subsequences. Return the minimum number of subsequences
// needed such that the difference between the maximum and minimum values in
// each subsequence is at most |k|. A subsequence is a sequence that can be
// derived from another sequence by deleting some or no elements without
// changing the order of the remaining elements.
//
//

LEETCODE_BEGIN_RESOLVING(2294, PartitionArraySuchThatMaximumDifferenceIsK,
                         Solution);

class Solution {
public:
  int partitionArray(vector<int> &nums, int k) {
    sort(nums.begin(), nums.end());
    int res = 1;
    int mn  = nums[0];
    for (int i = 1; i < nums.size(); ++i) {
      if (nums[i] - mn > k) {
        ++res;
        mn = nums[i];
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁵|
// * |0 <= nums[i] <= 10⁵|
// * |0 <= k <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [3,6,1,2,5], k = 2
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(2294, PartitionArraySuchThatMaximumDifferenceIsK,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 6, 1, 2, 5};
  int         k        = 2;
  int         expect   = 2;
  int         actual   = solution->partitionArray(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,2,3], k = 1
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(2294, PartitionArraySuchThatMaximumDifferenceIsK,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3};
  int         k        = 1;
  int         expect   = 2;
  int         actual   = solution->partitionArray(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [2,2,4,5], k = 0
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(2294, PartitionArraySuchThatMaximumDifferenceIsK,
                           example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 2, 4, 5};
  int         k        = 0;
  int         expect   = 3;
  int         actual   = solution->partitionArray(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

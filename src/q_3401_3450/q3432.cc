// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Count Partitions with Even Sum Difference
//
// https://leetcode.com/problems/count-partitions-with-even-sum-difference/
//
// Question ID: 3432
// Difficult  : Easy
// Solve Date : 2025/12/05 14:51

#include <iosfwd>
#include <numeric>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3432. Count Partitions with Even Sum Difference|:
//
// You are given an integer array |nums| of length |n|.
// A partition is defined as an index |i| where |0 <= i < n - 1|, splitting the
// array into two non-empty subarrays such that:
//
//  • Left subarray contains indices |[0, i]|.
//
//  • Right subarray contains indices |[i + 1, n - 1]|.
// Return the number of partitions where the difference between the sum of the
// left and right subarrays is even.
//
//

LEETCODE_BEGIN_RESOLVING(3432, CountPartitionsWithEvenSumDifference, Solution);

class Solution {
public:
  int countPartitions(vector<int> &nums) {
    int  res  = 0;
    int  rsum = accumulate(nums.begin(), nums.end(), 0);
    int  lsum = 0;
    auto beg  = nums.begin();
    while (beg != nums.end()) {
      rsum -= *beg;
      lsum += *beg;
      ++beg;

      if (rsum && lsum && !((lsum - rsum) & 1)) {
        ++res;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= n == nums.length <= 100|
// * |1 <= nums[i] <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [10,10,3,7,6]
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(3432, CountPartitionsWithEvenSumDifference,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {10, 10, 3, 7, 6};
  int         expect   = 4;
  int         actual   = solution->countPartitions(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,2,2]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(3432, CountPartitionsWithEvenSumDifference,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 2};
  int         expect   = 0;
  int         actual   = solution->countPartitions(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [2,4,6,8]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(3432, CountPartitionsWithEvenSumDifference,
                           example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 4, 6, 8};
  int         expect   = 3;
  int         actual   = solution->countPartitions(nums);
  LCD_EXPECT_EQ(expect, actual);
}

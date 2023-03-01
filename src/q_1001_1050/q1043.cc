// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Partition Array for Maximum Sum
//
// https://leetcode.com/problems/partition-array-for-maximum-sum/
//
// Question ID: 1043
// Difficult  : Medium
// Solve Date : 2021/11/10 17:52

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1043. Partition Array for Maximum Sum|:
//
// Given an integer array |arr|, partition the array into (contiguous) subarrays
// of length at most |k|. After partitioning, each subarray has their values
// changed to become the maximum value of that subarray. Return the largest sum
// of the given array after partitioning. Test cases are generated so that the
// answer fits in a 32-bit integer.  
//

LEETCODE_BEGIN_RESOLVING(1043, PartitionArrayForMaximumSum, Solution);

class Solution {
public:
  int maxSumAfterPartitioning(vector<int> &arr, int k) {
    vector<int> dp(arr.size(), 0);
    dp.front() = arr.front();
    for (int i = 1; i < arr.size(); ++i) {
      int M = arr[i];
      for (int j = i; j > (i - k) && j >= 0; --j) {
        M     = max(M, arr[j]);
        dp[i] = max(dp[i], M * (i - j + 1) + (j - 1 >= 0 ? dp[j - 1] : 0));
      }
    }
    return dp.back();
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= arr.length <= 500|
// * |0 <= arr[i] <= 10⁹|
// * |1 <= k <= arr.length|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: arr = [1,15,7,9,2,5,10], k = 3
// Output: 84
//
// arr becomes [15,15,15,9,10,10,10]

LEETCODE_SOLUTION_UNITTEST(1043, PartitionArrayForMaximumSum, example_1) {
  auto        solution = MakeSolution();
  vector<int> arr      = {1, 15, 7, 9, 2, 5, 10};
  int         k        = 3;
  int         expect   = 84;
  int         actual   = solution->maxSumAfterPartitioning(arr, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: arr = [1,4,1,5,7,3,6,1,9,9,3], k = 4
// Output: 83
//

LEETCODE_SOLUTION_UNITTEST(1043, PartitionArrayForMaximumSum, example_2) {
  auto        solution = MakeSolution();
  vector<int> arr      = {1, 4, 1, 5, 7, 3, 6, 1, 9, 9, 3};
  int         k        = 4;
  int         expect   = 83;
  int         actual   = solution->maxSumAfterPartitioning(arr, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: arr = [1], k = 1
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(1043, PartitionArrayForMaximumSum, example_3) {
  auto        solution = MakeSolution();
  vector<int> arr      = {1};
  int         k        = 1;
  int         expect   = 1;
  int         actual   = solution->maxSumAfterPartitioning(arr, k);
  LCD_EXPECT_EQ(expect, actual);
}

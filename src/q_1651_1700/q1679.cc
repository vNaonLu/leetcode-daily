// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Max Number of K-Sum Pairs
//
// https://leetcode.com/problems/max-number-of-k-sum-pairs/
//
// Question ID: 1679
// Difficult  : Medium
// Solve Date : 2022/05/04 17:59

#include <iosfwd>
#include <map>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1679. Max Number of K-Sum Pairs|:
//
// You are given an integer array |nums| and an integer |k|.
// In one operation, you can pick two numbers from the array whose sum equals
// |k| and remove them from the array. Return the maximum number of operations
// you can perform on the array.  
//

LEETCODE_BEGIN_RESOLVING(1679, MaxNumberOfKSumPairs, Solution);

class Solution {
public:
  int maxOperations(vector<int> &nums, int k) {
    unordered_map<int, int> cnt;
    int                     res = 0;
    for (auto &x : nums) {
      auto f = cnt.find(k - x);
      if (f != cnt.end() && f->second > 0) {
        --f->second;
        ++res;
      } else {
        ++cnt[x];
      }
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁵|
// * |1 <= nums[i] <= 10⁹|
// * |1 <= k <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,3,4], k = 5
// Output: 2
//
// Starting with nums = [1,2,3,4]:
// - Remove numbers 1 and 4, then nums = [2,3]
// - Remove numbers 2 and 3, then nums = []
// There are no more pairs that sum up to 5, hence a total of 2 operations.

LEETCODE_SOLUTION_UNITTEST(1679, MaxNumberOfKSumPairs, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 4};
  int         k        = 5;
  int         expect   = 2;
  int         actual   = solution->maxOperations(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [3,1,3,4,3], k = 6
// Output: 1
//
// Starting with nums = [3,1,3,4,3]:
// - Remove the first two 3's, then nums = [1,4,3]
// There are no more pairs that sum up to 6, hence a total of 1 operation.

LEETCODE_SOLUTION_UNITTEST(1679, MaxNumberOfKSumPairs, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 1, 3, 4, 3};
  int         k        = 6;
  int         expect   = 1;
  int         actual   = solution->maxOperations(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

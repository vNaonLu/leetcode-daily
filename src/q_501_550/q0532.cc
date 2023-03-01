// Copyright 2023 Naon Lu
//
// This file describes the solution of
// K-diff Pairs in an Array
//
// https://leetcode.com/problems/k-diff-pairs-in-an-array/
//
// Question ID: 532
// Difficult  : Medium
// Solve Date : 2022/02/09 18:16

#include <iosfwd>
#include <map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |532. K-diff Pairs in an Array|:
//
// Given an array of integers |nums| and an integer |k|, return the number of
// unique k-diff pairs in the array. A k-diff pair is an integer pair |(nums[i],
// nums[j])|, where the following are true:
//
//  • |0 <= i, j < nums.length|
//
//  • |i != j|
//
//  • |nums[i] - nums[j] == k|
// Notice that ||val|| denotes the absolute value of |val|.
//  
//

LEETCODE_BEGIN_RESOLVING(532, KDiffPairsInAnArray, Solution);

class Solution {
public:
  int findPairs(vector<int> &nums, int k) {
    map<int, int> cnt;
    for (const auto &x : nums)
      ++cnt[x];
    int res = 0;
    for (auto &[num, remain] : cnt) {
      --remain;
      if (cnt.count(num + k) && cnt.at(num + k) > 0) {
        --cnt[num + k];
        remain = 0;
        ++res;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁴|
// * |-10⁷ <= nums[i] <= 10⁷|
// * |0 <= k <= 10⁷|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [3,1,4,1,5], k = 2
// Output: 2
//
// There are two 2-diff pairs in the array, (1, 3) and (3, 5).
// Although we have two 1s in the input, we should only return the number of
// unique pairs.

LEETCODE_SOLUTION_UNITTEST(532, KDiffPairsInAnArray, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 1, 4, 1, 5};
  int         k        = 2;
  int         expect   = 2;
  int         actual   = solution->findPairs(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,2,3,4,5], k = 1
// Output: 4
//
// There are four 1-diff pairs in the array, (1, 2), (2, 3), (3, 4) and (4, 5).

LEETCODE_SOLUTION_UNITTEST(532, KDiffPairsInAnArray, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 4, 5};
  int         k        = 1;
  int         expect   = 4;
  int         actual   = solution->findPairs(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [1,3,1,5,4], k = 0
// Output: 1
//
// There is one 0-diff pair in the array, (1, 1).

LEETCODE_SOLUTION_UNITTEST(532, KDiffPairsInAnArray, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 3, 1, 5, 4};
  int         k        = 0;
  int         expect   = 1;
  int         actual   = solution->findPairs(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Maximum Frequency of an Element After Performing Operations I
//
// https://leetcode.com/problems/maximum-frequency-of-an-element-after-performing-operations-i/
//
// Question ID: 3346
// Difficult  : Medium
// Solve Date : 2025/10/21 18:55

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3346. Maximum Frequency of an Element After Performing
// Operations I|:
//
// You are given an integer array |nums| and two integers |k| and
// |numOperations|. You must perform an operation |numOperations| times on
// |nums|, where in each operation you:
//
//  • Select an index |i| that was not selected in any previous operations.
//
//  • Add an integer in the range |[-k, k]| to |nums[i]|.
// Return the maximum possible frequency of any element in |nums| after
// performing the operations.
//
//

LEETCODE_BEGIN_RESOLVING(3346,
                         MaximumFrequencyOfAnElementAfterPerformingOperationsI,
                         Solution);

class Solution {
public:
  int maxFrequency(vector<int> &nums, int k, int numOperations) {
    int         mx = *max_element(nums.begin(), nums.end()) + k + 2;
    vector<int> count(mx);

    for (auto x : nums) {
      ++count[x];
    }

    for (int i = 1; i < mx; ++i) {
      count[i] += count[i - 1];
    }

    int res = 0;
    for (int i = 0; i < mx; ++i) {
      int left  = max(0, i - k);
      int right = min(mx - 1, i + k);
      int total = count[right] - (left ? count[left - 1] : 0);
      int freq  = count[i] - (i ? count[i - 1] : 0);
      res       = max(res, freq + min(numOperations, total - freq));
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁵|
// * |1 <= nums[i] <= 10⁵|
// * |0 <= k <= 10⁵|
// * |0 <= numOperations <= nums.length|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,4,5], k = 1, numOperations = 2
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(
    3346, MaximumFrequencyOfAnElementAfterPerformingOperationsI, example_1) {
  auto        solution      = MakeSolution();
  vector<int> nums          = {1, 4, 5};
  int         k             = 1;
  int         numOperations = 2;
  int         expect        = 2;
  int         actual        = solution->maxFrequency(nums, k, numOperations);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [5,11,20,20], k = 5, numOperations = 1
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(
    3346, MaximumFrequencyOfAnElementAfterPerformingOperationsI, example_2) {
  auto        solution      = MakeSolution();
  vector<int> nums          = {5, 11, 20, 20};
  int         k             = 5;
  int         numOperations = 1;
  int         expect        = 2;
  int         actual        = solution->maxFrequency(nums, k, numOperations);
  LCD_EXPECT_EQ(expect, actual);
}

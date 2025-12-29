// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Maximum Frequency of an Element After Performing Operations II
//
// https://leetcode.com/problems/maximum-frequency-of-an-element-after-performing-operations-ii/
//
// Question ID: 3347
// Difficult  : Hard
// Solve Date : 2025/10/22 20:42

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3347. Maximum Frequency of an Element After Performing
// Operations II|:
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

LEETCODE_BEGIN_RESOLVING(3347,
                         MaximumFrequencyOfAnElementAfterPerformingOperationsII,
                         Solution);

class Solution {
public:
  int check(vector<int> &nums, int n, int t, int m) {
    long long nL = n;
    long long tL = t;
    int       l  = lower_bound(nums.begin(), nums.end(), nL) - nums.begin();
    int       h  = upper_bound(nums.begin(), nums.end(), nL) - nums.begin();
    int ll  = lower_bound(nums.begin(), nums.end(), nL - tL) - nums.begin();
    int hh  = upper_bound(nums.begin(), nums.end(), nL + tL) - nums.begin();
    int res = (hh - h) + (l - ll);
    return min(m, res) + (h - l);
  }

  int maxFrequency(vector<int> &nums, int k, int numOperations) {
    int m = numOperations;
    sort(nums.begin(), nums.end());
    int ans = 1;
    for (int i = 0; i < nums.size() - 1; i++) {
      ans = max(check(nums, nums[i], k, m), ans);
      ans = max(check(nums, nums[i] - k, k, m), ans);
      ans = max(check(nums, nums[i] + k, k, m), ans);
    }
    return ans;
  }
};
LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁵|
// * |1 <= nums[i] <= 10⁹|
// * |0 <= k <= 10⁹|
// * |0 <= numOperations <= nums.length|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,4,5], k = 1, numOperations = 2
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(
    3347, MaximumFrequencyOfAnElementAfterPerformingOperationsII, example_1) {
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
    3347, MaximumFrequencyOfAnElementAfterPerformingOperationsII, example_2) {
  auto        solution      = MakeSolution();
  vector<int> nums          = {5, 11, 20, 20};
  int         k             = 5;
  int         numOperations = 1;
  int         expect        = 2;
  int         actual        = solution->maxFrequency(nums, k, numOperations);
  LCD_EXPECT_EQ(expect, actual);
}

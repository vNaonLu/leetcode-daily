// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Minimum Operations to Make Array Values Equal to K
//
// https://leetcode.com/problems/minimum-operations-to-make-array-values-equal-to-k/
//
// Question ID: 3375
// Difficult  : Easy
// Solve Date : 2024/12/18 22:19

#include <algorithm>
#include <iosfwd>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3375. Minimum Operations to Make Array Values Equal to K|:
//
// You are given an integer array |nums| and an integer |k|.
// An integer |h| is called valid if all values in the array that are strictly
// greater than |h| are identical. For example, if |nums = [10, 8, 10, 8]|, a
// valid integer is |h = 9| because all |nums[i] > 9| are equal to 10, but 5 is
// not a valid integer. You are allowed to perform the following operation on
// |nums|:
//
//  • Select an integer |h| that is valid for the current values in |nums|.
//
//  • For each index |i| where |nums[i] > h|, set |nums[i]| to |h|.
// Return the minimum number of operations required to make every element in
// |nums| equal to |k|. If it is impossible to make all elements equal to |k|,
// return -1.
//
//

LEETCODE_BEGIN_RESOLVING(3375, MinimumOperationsToMakeArrayValuesEqualToK,
                         Solution);

class Solution {
public:
  int minOperations(vector<int> &nums, int k) {
    int mn = *min_element(nums.begin(), nums.end());
    if (mn < k) {
      return -1;
    }
    unordered_map<int, int> mp;
    for (auto x : nums) {
      mp[x] = 1;
    }

    int res = mp.size();
    if (mp[k]) {
      --res;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 100 |
// * |1 <= nums[i] <= 100|
// * |1 <= k <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [5,2,5,4,5], k = 2
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(3375, MinimumOperationsToMakeArrayValuesEqualToK,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {5, 2, 5, 4, 5};
  int         k        = 2;
  int         expect   = 2;
  int         actual   = solution->minOperations(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [2,1,2], k = 2
// Output: -1
//

LEETCODE_SOLUTION_UNITTEST(3375, MinimumOperationsToMakeArrayValuesEqualToK,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 1, 2};
  int         k        = 2;
  int         expect   = -1;
  int         actual   = solution->minOperations(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [9,7,5,3], k = 1
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(3375, MinimumOperationsToMakeArrayValuesEqualToK,
                           example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {9, 7, 5, 3};
  int         k        = 1;
  int         expect   = 4;
  int         actual   = solution->minOperations(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

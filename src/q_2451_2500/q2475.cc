// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Number of Unequal Triplets in Array
//
// https://leetcode.com/problems/number-of-unequal-triplets-in-array/
//
// Question ID: 2475
// Difficult  : Easy
// Solve Date : 2023/10/28 13:42

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2475. Number of Unequal Triplets in Array|:
//
// You are given a 0-indexed array of positive integers |nums|. Find the number
// of triplets |(i, j, k)| that meet the following conditions:
//
//  • |0 <= i < j < k < nums.length|
//
//  • |nums[i]|, |nums[j]|, and |nums[k]| are pairwise distinct.
//
//
//    • In other words, |nums[i] != nums[j]|, |nums[i] != nums[k]|, and |nums[j]
//    != nums[k]|.
//
//
// Return the number of triplets that meet the conditions.
//
//

LEETCODE_BEGIN_RESOLVING(2475, NumberOfUnequalTripletsInArray, Solution);

class Solution {
public:
  int unequalTriplets(vector<int> &nums) {
    int         res = 0;
    vector<int> v(1001, 0);
    vector<int> tmp;
    for (auto x : nums) {
      ++v[x];
    }
    for (auto x : v) {
      if (x) {
        tmp.emplace_back(x);
      }
    }

    int n = tmp.size();
    for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        for (int k = j + 1; k < n; ++k) {
          res += tmp[i] * tmp[j] * tmp[k];
        }
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |3 <= nums.length <= 100|
// * |1 <= nums[i] <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [4,4,2,4,3]
// Output: 3
//
// The following triplets meet the conditions:
// - (0, 2, 4) because 4 != 2 != 3
// - (1, 2, 4) because 4 != 2 != 3
// - (2, 3, 4) because 2 != 4 != 3
// Since there are 3 triplets, we return 3.
// Note that (2, 0, 4) is not a valid triplet because 2 > 0.

LEETCODE_SOLUTION_UNITTEST(2475, NumberOfUnequalTripletsInArray, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {4, 4, 2, 4, 3};
  int         expect   = 3;
  int         actual   = solution->unequalTriplets(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,1,1,1,1]
// Output: 0
//
// No triplets meet the conditions so we return 0.

LEETCODE_SOLUTION_UNITTEST(2475, NumberOfUnequalTripletsInArray, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 1, 1, 1, 1};
  int         expect   = 0;
  int         actual   = solution->unequalTriplets(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: [1000,1000,1000]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST_WITH_TIMED_OUT(2475, NumberOfUnequalTripletsInArray,
                                          extra_testcase_1, 4016) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1000, 1000, 1000};
  int         expect   = 0;
  int         actual   = solution->unequalTriplets(nums);
  LCD_EXPECT_EQ(expect, actual);
}

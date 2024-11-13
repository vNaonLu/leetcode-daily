// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Count the Number of Fair Pairs
//
// https://leetcode.com/problems/count-the-number-of-fair-pairs/
//
// Question ID: 2563
// Difficult  : Medium
// Solve Date : 2024/11/13 19:40

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2563. Count the Number of Fair Pairs|:
//
// Given a 0-indexed integer array |nums| of size |n| and two integers |lower|
// and |upper|, return the number of fair pairs. A pair |(i, j)| is fair if:
//
//  • |0 <= i < j < n|, and
//
//  • |lower <= nums[i] + nums[j] <= upper|
//
//

LEETCODE_BEGIN_RESOLVING(2563, CountTheNumberOfFairPairs, Solution);

class Solution {
public:
  long long countFairPairs(vector<int> &nums, int lower, int upper) {
    sort(nums.begin(), nums.end());
    int64_t res = 0;
    for (int i = 0; i < nums.size() - 1; ++i) {
      auto lo = lower_bound(nums.begin() + i + 1, nums.end(), lower - nums[i]);
      auto hi = upper_bound(nums.begin() + i + 1, nums.end(), upper - nums[i]);
      if (lo != hi) {
        // count of |lo, hi - 1|, here omits |--hi| and |distance() + 1|
        res += distance(lo, hi);
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
// * |nums.length == n|
// * |-10⁹ <= nums[i] <= 10⁹|
// * |-10⁹ <= lower <= upper <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [0,1,7,4,4,5], lower = 3, upper = 6
// Output: 6
//

LEETCODE_SOLUTION_UNITTEST(2563, CountTheNumberOfFairPairs, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {0, 1, 7, 4, 4, 5};
  int         lower    = 3;
  int         upper    = 6;
  long long   expect   = 6;
  long long   actual   = solution->countFairPairs(nums, lower, upper);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,7,9,2,5], lower = 11, upper = 11
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(2563, CountTheNumberOfFairPairs, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 7, 9, 2, 5};
  int         lower    = 11;
  int         upper    = 11;
  long long   expect   = 1;
  long long   actual   = solution->countFairPairs(nums, lower, upper);
  LCD_EXPECT_EQ(expect, actual);
}

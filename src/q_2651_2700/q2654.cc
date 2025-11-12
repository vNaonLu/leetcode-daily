// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Minimum Number of Operations to Make All Array Elements Equal to 1
//
// https://leetcode.com/problems/minimum-number-of-operations-to-make-all-array-elements-equal-to-1/
//
// Question ID: 2654
// Difficult  : Medium
// Solve Date : 2025/11/12 19:47

#include <iosfwd>
#include <numeric>
#include <optional>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2654. Minimum Number of Operations to Make All Array Elements
// Equal to 1|:
//
// You are given a 0-indexed array |nums| consisiting of positive integers. You
// can do the following operation on the array any number of times:
//
//  • Select an index |i| such that |0 <= i < n - 1| and replace either of
//  |nums[i]| or |nums[i+1]| with their gcd value.
// Return the minimum number of operations to make all elements of |nums| equal
// to |1|. If it is impossible, return |-1|. The gcd of two integers is the
// greatest common divisor of the two integers.
//
//

LEETCODE_BEGIN_RESOLVING(
    2654, MinimumNumberOfOperationsToMakeAllArrayElementsEqualTo1, Solution);

class Solution {
public:
  int minOperations(vector<int> &nums) {
    int           n = nums.size();
    optional<int> res;
    if (int cnt1 =
            count_if(nums.begin(), nums.end(), [](auto x) { return x == 1; });
        cnt1) {
      return n - cnt1;
    }
    for (int i = 0; i < n; ++i) {
      int g = nums[i];
      for (int j = i + 1; j < n; ++j) {
        g = std::gcd(g, nums[j]);
        if (g == 1) {
          res = min(j - i + n - 1, res.value_or(10 * n));
          break;
        }
      }
    }
    return res.value_or(-1);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= nums.length <= 50|
// * |1 <= nums[i] <= 10⁶|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [2,6,3,4]
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(
    2654, MinimumNumberOfOperationsToMakeAllArrayElementsEqualTo1, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 6, 3, 4};
  int         expect   = 4;
  int         actual   = solution->minOperations(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [2,10,6,14]
// Output: -1
//

LEETCODE_SOLUTION_UNITTEST(
    2654, MinimumNumberOfOperationsToMakeAllArrayElementsEqualTo1, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 10, 6, 14};
  int         expect   = -1;
  int         actual   = solution->minOperations(nums);
  LCD_EXPECT_EQ(expect, actual);
}

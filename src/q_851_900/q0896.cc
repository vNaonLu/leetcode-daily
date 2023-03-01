// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Monotonic Array
//
// https://leetcode.com/problems/monotonic-array/
//
// Question ID: 896
// Difficult  : Easy
// Solve Date : 2022/04/26 19:02

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |896. Monotonic Array|:
//
// An array is monotonic if it is either monotone increasing or monotone
// decreasing. An array |nums| is monotone increasing if for all |i <= j|,
// |nums[i] <= nums[j]|. An array |nums| is monotone decreasing if for all |i <=
// j|, |nums[i] >= nums[j]|. Given an integer array |nums|, return |true| if the
// given array is monotonic, or |false| otherwise.  
//

LEETCODE_BEGIN_RESOLVING(896, MonotonicArray, Solution);

class Solution {
private:
  template <typename type>
  bool is_increasing(type beg, type end) {
    while (beg + 1 != end) {
      auto &first = *beg++;

      if (first > *beg) {
        return false;
      }
    }

    return true;
  }
  template <typename type>
  bool is_decreasing(type beg, type end) {
    while (beg + 1 != end) {
      auto &first = *beg++;

      if (first < *beg) {
        return false;
      }
    }

    return true;
  }

public:
  bool isMonotonic(vector<int> &nums) {
    return is_increasing(nums.begin(), nums.end()) ||
           is_decreasing(nums.begin(), nums.end());
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁵|
// * |-10⁵ <= nums[i] <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,2,3]
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(896, MonotonicArray, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 2, 3};
  bool        expect   = true;
  bool        actual   = solution->isMonotonic(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [6,5,4,4]
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(896, MonotonicArray, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {6, 5, 4, 4};
  bool        expect   = true;
  bool        actual   = solution->isMonotonic(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [1,3,2]
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(896, MonotonicArray, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 3, 2};
  bool        expect   = false;
  bool        actual   = solution->isMonotonic(nums);
  LCD_EXPECT_EQ(expect, actual);
}

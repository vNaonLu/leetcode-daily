// Copyright 2026 Naon Lu
//
// This file describes the solution of
// Trionic Array I
//
// https://leetcode.com/problems/trionic-array-i/
//
// Question ID: 3637
// Difficult  : Easy
// Solve Date : 2026/02/03 18:41

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3637. Trionic Array I|:
//
// You are given an integer array |nums| of length |n|.
// An array is trionic if there exist indices |0 < p < q < n − 1| such that:
//
//  • |nums[0...p]| is strictly increasing,
//
//  • |nums[p...q]| is strictly decreasing,
//
//  • |nums[q...n − 1]| is strictly increasing.
// Return |true| if |nums| is trionic, otherwise return |false|.
//
//

LEETCODE_BEGIN_RESOLVING(3637, TrionicArrayI, Solution);

class Solution {
public:
  bool isTrionic(vector<int> &nums) {
    auto it = nums.begin();
    if (auto f = is_sorted_until(it, nums.end(), less_equal<int>{});
        f == nums.end() || f == it + 1) {
      return false;
    } else {
      it = f - 1;
    }

    if (auto f = is_sorted_until(it, nums.end(), greater_equal<int>{});
        f == nums.end() || f == it + 1) {
      return false;
    } else {
      it = f - 1;
    }

    return is_sorted_until(it, nums.end(), less_equal<int>{}) == nums.end();
  }
};

LEETCODE_END_RESOLVING(Solution);

// [Example #1]
//  Input: nums = [1,3,5,4,2,6]
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(3637, TrionicArrayI, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 3, 5, 4, 2, 6};
  bool        expect   = true;
  bool        actual   = solution->isTrionic(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [2,1,3]
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(3637, TrionicArrayI, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 1, 3};
  bool        expect   = false;
  bool        actual   = solution->isTrionic(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: [6,5,1]
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(3637, TrionicArrayI, extra_testcase_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {6, 5, 1};
  bool        expect   = false;
  bool        actual   = solution->isTrionic(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #2]
//  Input: [5,9,1,7]
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(3637, TrionicArrayI, extra_testcase_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {5, 9, 1, 7};
  bool        expect   = true;
  bool        actual   = solution->isTrionic(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #3]
//  Input: [8,8,2,6]
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(3637, TrionicArrayI, extra_testcase_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {8, 8, 2, 6};
  bool        expect   = false;
  bool        actual   = solution->isTrionic(nums);
  LCD_EXPECT_EQ(expect, actual);
}

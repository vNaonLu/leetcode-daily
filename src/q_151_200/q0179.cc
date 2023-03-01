// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Largest Number
//
// https://leetcode.com/problems/largest-number/
//
// Question ID: 179
// Difficult  : Medium
// Solve Date : 2022/08/22 00:21

#include <algorithm>
#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |179. Largest Number|:
//
// Given a list of non-negative integers |nums|, arrange them such that they
// form the largest number and return it. Since the result may be very large, so
// you need to return a string instead of an integer.
//

LEETCODE_BEGIN_RESOLVING(179, LargestNumber, Solution);

class Solution {
public:
  string largestNumber(vector<int> &nums) {
    auto strs = vector<string>();
    auto res  = string();
    for (auto x : nums) {
      strs.emplace_back(to_string(x));
    }

    sort(strs.begin(), strs.end(), [](auto &x, auto &y) {
      auto xy = x + y;
      auto yx = y + x;
      return xy > yx;
    });

    if (strs.front() != "0") {
      for (auto &x : strs) {
        res += x;
      }
    } else {
      res = "0";
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 100|
// * |0 <= nums[i] <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [10,2]
// Output: "210"
//

LEETCODE_SOLUTION_UNITTEST(179, LargestNumber, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {10, 2};
  string      expect   = "210";
  string      actual   = solution->largestNumber(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [3,30,34,5,9]
// Output: "9534330"
//

LEETCODE_SOLUTION_UNITTEST(179, LargestNumber, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 30, 34, 5, 9};
  string      expect   = "9534330";
  string      actual   = solution->largestNumber(nums);
  LCD_EXPECT_EQ(expect, actual);
}

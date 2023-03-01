// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Missing Number
//
// https://leetcode.com/problems/missing-number/
//
// Question ID: 268
// Difficult  : Easy
// Solve Date : 2022/05/28 12:20

#include <iosfwd>
#include <set>
#include <unordered_set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |268. Missing Number|:
//
// Given an array |nums| containing |n| distinct numbers in the range |[0, n]|,
// return the only number in the range that is missing from the array.
//

LEETCODE_BEGIN_RESOLVING(268, MissingNumber, Solution);

class Solution {
public:
  int missingNumber(vector<int> &nums) {
    unordered_set<int> exist;
    for (int i = 0; i < nums.size(); ++i) {
      exist.emplace(i);
    }

    for (auto &x : nums) {
      exist.erase(x);
    }

    return exist.empty() ? nums.size() : *exist.begin();
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == nums.length|
// * |1 <= n <= 10⁴|
// * |0 <= nums[i] <= n|
// * All the numbers of |nums| are unique.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [3,0,1]
// Output: 2
//
// n = 3 since there are 3 numbers, so all numbers are in the range [0,3]. 2 is
// the missing number in the range since it does not appear in nums.

LEETCODE_SOLUTION_UNITTEST(268, MissingNumber, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 0, 1};
  int         expect   = 2;
  int         actual   = solution->missingNumber(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [0,1]
// Output: 2
//
// n = 2 since there are 2 numbers, so all numbers are in the range [0,2]. 2 is
// the missing number in the range since it does not appear in nums.

LEETCODE_SOLUTION_UNITTEST(268, MissingNumber, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {0, 1};
  int         expect   = 2;
  int         actual   = solution->missingNumber(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [9,6,4,2,3,5,7,0,1]
// Output: 8
//
// n = 9 since there are 9 numbers, so all numbers are in the range [0,9]. 8 is
// the missing number in the range since it does not appear in nums.

LEETCODE_SOLUTION_UNITTEST(268, MissingNumber, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {9, 6, 4, 2, 3, 5, 7, 0, 1};
  int         expect   = 8;
  int         actual   = solution->missingNumber(nums);
  LCD_EXPECT_EQ(expect, actual);
}

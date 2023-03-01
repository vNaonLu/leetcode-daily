// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Contains Duplicate
//
// https://leetcode.com/problems/contains-duplicate/
//
// Question ID: 217
// Difficult  : Easy
// Solve Date : 2022/09/07 22:07

#include <iosfwd>
#include <set>
#include <unordered_set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |217. Contains Duplicate|:
//
// Given an integer array |nums|, return |true| if any value appears at least
// twice in the array, and return |false| if every element is distinct.
//

LEETCODE_BEGIN_RESOLVING(217, ContainsDuplicate, Solution);

class Solution {
public:
  bool containsDuplicate(vector<int> &nums) {
    auto memo = unordered_set<int>();
    for (auto x : nums) {
      if (false == memo.emplace(x).second) {
        return true;
      }
    }
    return false;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁵|
// * |-10⁹ <= nums[i] <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,3,1]
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(217, ContainsDuplicate, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 1};
  bool        expect   = true;
  bool        actual   = solution->containsDuplicate(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,2,3,4]
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(217, ContainsDuplicate, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 4};
  bool        expect   = false;
  bool        actual   = solution->containsDuplicate(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [1,1,1,3,3,4,3,2,4,2]
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(217, ContainsDuplicate, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 1, 1, 3, 3, 4, 3, 2, 4, 2};
  bool        expect   = true;
  bool        actual   = solution->containsDuplicate(nums);
  LCD_EXPECT_EQ(expect, actual);
}

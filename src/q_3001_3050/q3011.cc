// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Find if Array Can Be Sorted
//
// https://leetcode.com/problems/find-if-array-can-be-sorted/
//
// Question ID: 3011
// Difficult  : Medium
// Solve Date : 2024/11/06 19:23

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3011. Find if Array Can Be Sorted|:
//
// You are given a 0-indexed array of positive integers |nums|.
// In one operation, you can swap any two adjacent elements if they have the
// same number of set bits. You are allowed to do this operation any number of
// times (including zero). Return |true| if you can sort the array, else return
// |false|.
//
//

LEETCODE_BEGIN_RESOLVING(3011, FindIfArrayCanBeSorted, Solution);

class Solution {
public:
  bool canSortArray(vector<int> &nums) {
    int pmax = 0;
    int cmin = 0;
    int cmax = 0;
    int pcnt = 0;
    for (auto x : nums) {
      if (auto cnt = __builtin_popcount(x); pcnt == cnt) {
        cmin = min(cmin, x);
        cmax = max(cmax, x);
      } else if (cmin < pmax) {
        return false;
      } else {
        pmax = cmax;
        cmin = cmax = x;
        pcnt        = cnt;
      }
    }
    return cmin >= pmax;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 100|
// * |1 <= nums[i] <= 2⁸|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [8,4,2,30,15]
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(3011, FindIfArrayCanBeSorted, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {8, 4, 2, 30, 15};
  bool        expect   = true;
  bool        actual   = solution->canSortArray(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,2,3,4,5]
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(3011, FindIfArrayCanBeSorted, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 4, 5};
  bool        expect   = true;
  bool        actual   = solution->canSortArray(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [3,16,8,4,2]
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(3011, FindIfArrayCanBeSorted, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 16, 8, 4, 2};
  bool        expect   = false;
  bool        actual   = solution->canSortArray(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Special Array I
//
// https://leetcode.com/problems/special-array-i/
//
// Question ID: 3151
// Difficult  : Easy
// Solve Date : 2024/05/22 22:35

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3151. Special Array I|:
//
// An array is considered special if every pair of its adjacent elements
// contains two numbers with different parity. You are given an array of
// integers |nums|. Return |true| if |nums| is a special array, otherwise,
// return |false|.
//
//

LEETCODE_BEGIN_RESOLVING(3151, SpecialArrayI, Solution);

class Solution {
public:
  bool isArraySpecial(vector<int> &nums) {
    for (int i = 1; i < nums.size(); ++i) {
      if ((nums[i] & 1) == (nums[i - 1] & 1)) {
        return false;
      }
    }
    return true;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 100|
// * |1 <= nums[i] <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1]
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(3151, SpecialArrayI, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1};
  bool        expect   = true;
  bool        actual   = solution->isArraySpecial(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [2,1,4]
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(3151, SpecialArrayI, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 1, 4};
  bool        expect   = true;
  bool        actual   = solution->isArraySpecial(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [4,3,1,6]
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(3151, SpecialArrayI, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {4, 3, 1, 6};
  bool        expect   = false;
  bool        actual   = solution->isArraySpecial(nums);
  LCD_EXPECT_EQ(expect, actual);
}

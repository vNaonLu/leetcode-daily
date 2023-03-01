// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Special Array With X Elements Greater Than or Equal X
//
// https://leetcode.com/problems/special-array-with-x-elements-greater-than-or-equal-x/
//
// Question ID: 1608
// Difficult  : Easy
// Solve Date : 2022/04/09 12:00

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1608. Special Array With X Elements Greater Than or Equal X|:
//
// You are given an array |nums| of non-negative integers. |nums| is considered
// special if there exists a number |x| such that there are exactly |x| numbers
// in |nums| that are greater than or equal to |x|. Notice that |x| does not
// have to be an element in |nums|. Return |x| if the array is special,
// otherwise, return |-1|. It can be proven that if |nums| is special, the value
// for |x| is unique.  
//

LEETCODE_BEGIN_RESOLVING(1608, SpecialArrayWithXElementsGreaterThanOrEqualX,
                         Solution);

class Solution {
private:
  int helper(vector<int> &nums, int x) {
    int count = 0;
    for (auto &y : nums) {
      if (y >= x) {
        ++count;
      }
    }
    return count - x;
  }

public:
  int specialArray(vector<int> &nums) {
    int l = 0, r = nums.size();
    while (l <= r) {
      int m = l + (r - l) / 2, result = helper(nums, m);
      if (result == 0) {
        return m;
      } else if (result > 0) {
        l = m + 1;
      } else {
        r = m - 1;
      }
    }

    return -1;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 100|
// * |0 <= nums[i] <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [3,5]
// Output: 2
//
// There are 2 values (3 and 5) that are greater than or equal to 2.

LEETCODE_SOLUTION_UNITTEST(1608, SpecialArrayWithXElementsGreaterThanOrEqualX,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 5};
  int         expect   = 2;
  int         actual   = solution->specialArray(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [0,0]
// Output: -1
//
// No numbers fit the criteria for x.
// If x = 0, there should be 0 numbers >= x, but there are 2.
// If x = 1, there should be 1 number >= x, but there are 0.
// If x = 2, there should be 2 numbers >= x, but there are 0.
// x cannot be greater since there are only 2 numbers in nums.

LEETCODE_SOLUTION_UNITTEST(1608, SpecialArrayWithXElementsGreaterThanOrEqualX,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {0, 0};
  int         expect   = -1;
  int         actual   = solution->specialArray(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [0,4,3,0,4]
// Output: 3
//
// There are 3 values that are greater than or equal to 3.

LEETCODE_SOLUTION_UNITTEST(1608, SpecialArrayWithXElementsGreaterThanOrEqualX,
                           example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {0, 4, 3, 0, 4};
  int         expect   = 3;
  int         actual   = solution->specialArray(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// Copyright 2023 Naon Lu
//
// This file describes the solution of
// First Missing Positive
//
// https://leetcode.com/problems/first-missing-positive/
//
// Question ID: 41
// Difficult  : Hard
// Solve Date : 2021/12/01 22:24

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |41. First Missing Positive|:
//
// Given an unsorted integer array |nums|, return the smallest missing positive
// integer. You must implement an algorithm that runs in |O(n)| time and uses
// constant extra space.  
//

LEETCODE_BEGIN_RESOLVING(41, FirstMissingPositive, Solution);

class Solution {
public:
  int firstMissingPositive(vector<int> &nums) {
    int n   = nums.size();
    int beg = 0, R = n - 1;
    while (beg <= R) {
      if (nums[beg] <= 0) {
        ++beg;
      } else if (nums[R] > 0) {
        --R;
      } else {
        swap(nums[beg++], nums[R--]);
      }
    }
    for (int i = beg; i < n; ++i) {
      int val = abs(nums[i]);
      if (val > n - beg)
        continue;
      if (nums[beg + val - 1] > 0) {
        nums[beg + val - 1] *= -1;
      }
    }
    for (int i = beg; i < n; ++i) {
      if (nums[i] > 0) {
        return i - beg + 1;
      }
    }
    return n - beg + 1;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁵|
// * |-2³¹ <= nums[i] <= 2³¹ - 1|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,0]
// Output: 3
//
// The numbers in the range [1,2] are all in the array.

LEETCODE_SOLUTION_UNITTEST(41, FirstMissingPositive, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 0};
  int         expect   = 3;
  int         actual   = solution->firstMissingPositive(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [3,4,-1,1]
// Output: 2
//
// 1 is in the array but 2 is missing.

LEETCODE_SOLUTION_UNITTEST(41, FirstMissingPositive, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 4, -1, 1};
  int         expect   = 2;
  int         actual   = solution->firstMissingPositive(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [7,8,9,11,12]
// Output: 1
//
// The smallest positive integer 1 is missing.

LEETCODE_SOLUTION_UNITTEST(41, FirstMissingPositive, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {7, 8, 9, 11, 12};
  int         expect   = 1;
  int         actual   = solution->firstMissingPositive(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Global and Local Inversions
//
// https://leetcode.com/problems/global-and-local-inversions/
//
// Question ID: 775
// Difficult  : Medium
// Solve Date : 2024/07/10 21:12

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |775. Global and Local Inversions|:
//
// You are given an integer array |nums| of length |n| which represents a
// permutation of all the integers in the range |[0, n - 1]|. The number of
// global inversions is the number of the different pairs |(i, j)| where:
//
//  • |0 <= i < j < n|
//
//  • |nums[i] > nums[j]|
// The number of local inversions is the number of indices |i| where:
//
//  • |0 <= i < n - 1|
//
//  • |nums[i] > nums[i + 1]|
// Return |true| if the number of global inversions is equal to the number of
// local inversions.
//
//

LEETCODE_BEGIN_RESOLVING(775, GlobalAndLocalInversions, Solution);

class Solution {
public:
  bool isIdealPermutation(vector<int> &nums) {
    int mx = 0;
    int n  = nums.size();
    for (int i = 0; i < n - 2; ++i) {
      mx = max(mx, nums[i]);
      if (mx > nums[i + 2]) {
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
// * |n == nums.length|
// * |1 <= n <= 10⁵|
// * |0 <= nums[i] < n|
// * All the integers of |nums| are unique.
// * |nums| is a permutation of all the numbers in the range |[0, n - 1]|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,0,2]
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(775, GlobalAndLocalInversions, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 0, 2};
  bool        expect   = true;
  bool        actual   = solution->isIdealPermutation(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,2,0]
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(775, GlobalAndLocalInversions, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 0};
  bool        expect   = false;
  bool        actual   = solution->isIdealPermutation(nums);
  LCD_EXPECT_EQ(expect, actual);
}

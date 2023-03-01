// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Sort Array By Parity II
//
// https://leetcode.com/problems/sort-array-by-parity-ii/
//
// Question ID: 922
// Difficult  : Easy
// Solve Date : 2021/09/28 18:22

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |922. Sort Array By Parity II|:
//
// Given an array of integers |nums|, half of the integers in |nums| are odd,
// and the other half are even. Sort the array so that whenever |nums[i]| is
// odd, |i| is odd, and whenever |nums[i]| is even, |i| is even. Return any
// answer array that satisfies this condition.  
//

LEETCODE_BEGIN_RESOLVING(922, SortArrayByParityII, Solution);

class Solution {
public:
  vector<int> sortArrayByParityII(vector<int> &nums) {
    int n = nums.size();
    int i = 0, j = 1;
    while (i < n && j < n) {
      if (nums[i] % 2 == 0) {
        i += 2;
      } else if (nums[j] % 2 == 1) {
        j += 2;
      } else {
        swap(nums[i], nums[j]);
      }
    }
    return nums;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |2 <= nums.length <= 2 * 10⁴|
// * |nums.length| is even.
// * Half of the integers in |nums| are even.
// * |0 <= nums[i] <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [4,2,5,7]
// Output: [4,5,2,7]
//
// [4,7,2,5], [2,5,4,7], [2,7,4,5] would also have been accepted.

LEETCODE_SOLUTION_UNITTEST(922, SortArrayByParityII, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {4, 2, 5, 7};
  vector<int> expect   = {4, 5, 2, 7};
  vector<int> actual   = solution->sortArrayByParityII(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [2,3]
// Output: [2,3]
//

LEETCODE_SOLUTION_UNITTEST(922, SortArrayByParityII, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 3};
  vector<int> expect   = {2, 3};
  vector<int> actual   = solution->sortArrayByParityII(nums);
  LCD_EXPECT_EQ(expect, actual);
}

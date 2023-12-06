// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Form Smallest Number From Two Digit Arrays
//
// https://leetcode.com/problems/form-smallest-number-from-two-digit-arrays/
//
// Question ID: 2605
// Difficult  : Easy
// Solve Date : 2023/12/06 19:10

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2605. Form Smallest Number From Two Digit Arrays|:
//
// Given two arrays of unique digits |nums1| and |nums2|, return the smallest
// number that contains at least one digit from each array.
//
//

LEETCODE_BEGIN_RESOLVING(2605, FormSmallestNumberFromTwoDigitArrays, Solution);

class Solution {
public:
  int minNumber(vector<int> &nums1, vector<int> &nums2) {
    vector<int> v1(10, 0);
    vector<int> v2(10, 0);
    for (auto x : nums1) {
      ++v1[x];
    }
    for (auto x : nums2) {
      ++v2[x];
    }
    for (int i = 1; i < 10; ++i) {
      if (v1[i] && v2[i]) {
        return i;
      }
    }
    int res = 100;
    for (int i = 1; i < 10; ++i) {
      if (!v1[i]) {
        continue;
      }

      for (int j = 1; j < 10; ++j) {
        if (v2[j]) {
          res = min({res, i * 10 + j, j * 10 + i});
        }
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums1.length, nums2.length <= 9|
// * |1 <= nums1[i], nums2[i] <= 9|
// * All digits in each array are unique.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums1 = [4,1,3], nums2 = [5,7]
// Output: 15
//
// The number 15 contains the digit 1 from nums1 and the digit 5 from nums2. It
// can be proven that 15 is the smallest number we can have.

LEETCODE_SOLUTION_UNITTEST(2605, FormSmallestNumberFromTwoDigitArrays,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums1    = {4, 1, 3};
  vector<int> nums2    = {5, 7};
  int         expect   = 15;
  int         actual   = solution->minNumber(nums1, nums2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums1 = [3,5,2,6], nums2 = [3,1,7]
// Output: 3
//
// The number 3 contains the digit 3 which exists in both arrays.

LEETCODE_SOLUTION_UNITTEST(2605, FormSmallestNumberFromTwoDigitArrays,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums1    = {3, 5, 2, 6};
  vector<int> nums2    = {3, 1, 7};
  int         expect   = 3;
  int         actual   = solution->minNumber(nums1, nums2);
  LCD_EXPECT_EQ(expect, actual);
}

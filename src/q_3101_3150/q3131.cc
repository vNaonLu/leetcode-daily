// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Find the Integer Added to Array I
//
// https://leetcode.com/problems/find-the-integer-added-to-array-i/
//
// Question ID: 3131
// Difficult  : Easy
// Solve Date : 2024/05/08 22:50

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3131. Find the Integer Added to Array I|:
//
// You are given two arrays of equal length, |nums1| and |nums2|.
// Each element in |nums1| has been increased (or decreased in the case of
// negative) by an integer, represented by the variable |x|. As a result,
// |nums1| becomes equal to |nums2|. Two arrays are considered equal when they
// contain the same integers with the same frequencies. Return the integer |x|.
//
//

LEETCODE_BEGIN_RESOLVING(3131, FindTheIntegerAddedToArrayI, Solution);

class Solution {
public:
  int addedInteger(vector<int> &nums1, vector<int> &nums2) {
    return *max_element(nums2.begin(), nums2.end()) -
           *max_element(nums1.begin(), nums1.end());
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums1.length == nums2.length <= 100|
// * |0 <= nums1[i], nums2[i] <= 1000|
// * The test cases are generated in a way that there is an integer |x| such
// that |nums1| can become equal to |nums2| by adding |x| to each element of
// |nums1|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums1 = [2,6,4], nums2 = [9,7,5]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(3131, FindTheIntegerAddedToArrayI, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums1    = {2, 6, 4};
  vector<int> nums2    = {9, 7, 5};
  int         expect   = 3;
  int         actual   = solution->addedInteger(nums1, nums2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums1 = [10], nums2 = [5]
// Output: -5
//

LEETCODE_SOLUTION_UNITTEST(3131, FindTheIntegerAddedToArrayI, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums1    = {10};
  vector<int> nums2    = {5};
  int         expect   = -5;
  int         actual   = solution->addedInteger(nums1, nums2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums1 = [1,1,1,1], nums2 = [1,1,1,1]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(3131, FindTheIntegerAddedToArrayI, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums1    = {1, 1, 1, 1};
  vector<int> nums2    = {1, 1, 1, 1};
  int         expect   = 0;
  int         actual   = solution->addedInteger(nums1, nums2);
  LCD_EXPECT_EQ(expect, actual);
}

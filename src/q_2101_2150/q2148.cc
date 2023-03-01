// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Count Elements With Strictly Smaller and Greater Elements
//
// https://leetcode.com/problems/count-elements-with-strictly-smaller-and-greater-elements/
//
// Question ID: 2148
// Difficult  : Easy
// Solve Date : 2023/02/25 13:24

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2148. Count Elements With Strictly Smaller and Greater
// Elements |:
//
// Given an integer array |nums|, return the number of elements that have both a
// strictly smaller and a strictly greater element appear in |nums|.
//

LEETCODE_BEGIN_RESOLVING(2148,
                         CountElementsWithStrictlySmallerAndGreaterElements,
                         Solution);

class Solution {
public:
  int countElements(vector<int> &nums) {
    int  res = 0;
    auto mx  = *max_element(nums.begin(), nums.end());
    auto mn  = *min_element(nums.begin(), nums.end());
    for (auto x : nums) {
      if (x > mn && x < mx) {
        ++res;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 100|
// * |-10⁵ <= nums[i] <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [11,7,2,15]
// Output: 2
//
// The element 7 has the element 2 strictly smaller than it and the element 11
// strictly greater than it. Element 11 has element 7 strictly smaller than it
// and element 15 strictly greater than it. In total there are 2 elements having
// both a strictly smaller and a strictly greater element appear in |nums|.

LEETCODE_SOLUTION_UNITTEST(2148,
                           CountElementsWithStrictlySmallerAndGreaterElements,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {11, 7, 2, 15};
  int         expect   = 2;
  int         actual   = solution->countElements(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [-3,3,3,90]
// Output: 2
//
// The element 3 has the element -3 strictly smaller than it and the element 90
// strictly greater than it. Since there are two elements with the value 3, in
// total there are 2 elements having both a strictly smaller and a strictly
// greater element appear in |nums|.

LEETCODE_SOLUTION_UNITTEST(2148,
                           CountElementsWithStrictlySmallerAndGreaterElements,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {-3, 3, 3, 90};
  int         expect   = 2;
  int         actual   = solution->countElements(nums);
  LCD_EXPECT_EQ(expect, actual);
}

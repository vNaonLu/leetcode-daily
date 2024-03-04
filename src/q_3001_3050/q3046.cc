// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Split the Array
//
// https://leetcode.com/problems/split-the-array/
//
// Question ID: 3046
// Difficult  : Easy
// Solve Date : 2024/03/04 22:30

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3046. Split the Array|:
//
// You are given an integer array |nums| of even length. You have to split the
// array into two parts |nums1| and |nums2| such that:
//
//  • |nums1.length == nums2.length == nums.length / 2|.
//
//  • |nums1| should contain distinct elements.
//
//  • |nums2| should also contain distinct elements.
// Return |true| if it is possible to split the array, and |false| otherwise.
//
//

LEETCODE_BEGIN_RESOLVING(3046, SplitTheArray, Solution);

class Solution {
public:
  bool isPossibleToSplit(vector<int> &nums) {
    vector<int> freq(101);
    for (auto x : nums) {
      ++freq[x];
    }
    for (auto c : freq) {
      if (c > 2) {
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
// * |nums.length % 2 == 0 |
// * |1 <= nums[i] <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,1,2,2,3,4]
// Output: true
//
// One of the possible ways to split nums is nums1 = [1,2,3] and nums2 =
// [1,2,4].

LEETCODE_SOLUTION_UNITTEST(3046, SplitTheArray, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 1, 2, 2, 3, 4};
  bool        expect   = true;
  bool        actual   = solution->isPossibleToSplit(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,1,1,1]
// Output: false
//
// The only possible way to split nums is nums1 = [1,1] and nums2 = [1,1]. Both
// nums1 and nums2 do not contain distinct elements. Therefore, we return false.

LEETCODE_SOLUTION_UNITTEST(3046, SplitTheArray, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 1, 1, 1};
  bool        expect   = false;
  bool        actual   = solution->isPossibleToSplit(nums);
  LCD_EXPECT_EQ(expect, actual);
}

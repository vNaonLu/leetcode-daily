// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Single Element in a Sorted Array
//
// https://leetcode.com/problems/single-element-in-a-sorted-array/
//
// Question ID: 540
// Difficult  : Medium
// Solve Date : 2021/10/13 12:32

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |540. Single Element in a Sorted Array|:
//
// You are given a sorted array consisting of only integers where every element
// appears exactly twice, except for one element which appears exactly once.
// Return the single element that appears only once.
// Your solution must run in |O(log n)| time and |O(1)| space.
//  
//

LEETCODE_BEGIN_RESOLVING(540, SingleElementInASortedArray, Solution);

class Solution {
public:
  int singleNonDuplicate(vector<int> &nums) {
    if (nums.size() == 1)
      return nums[0];
    int l = 0, r = nums.size() - 1;
    while (l <= r) {
      int mid = l + (r - l) / 2;
      if ((mid % 2 == 0 && nums[mid] != nums[mid + 1]) ||
          (mid % 2 == 1 && nums[mid] != nums[mid - 1])) {
        r = mid - 1;
      } else {
        l = mid + 1;
      }
    }
    return nums[l];
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁵|
// * |0 <= nums[i] <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,1,2,3,3,4,4,8,8]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(540, SingleElementInASortedArray, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 1, 2, 3, 3, 4, 4, 8, 8};
  int         expect   = 2;
  int         actual   = solution->singleNonDuplicate(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [3,3,7,7,10,11,11]
// Output: 10
//

LEETCODE_SOLUTION_UNITTEST(540, SingleElementInASortedArray, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 3, 7, 7, 10, 11, 11};
  int         expect   = 10;
  int         actual   = solution->singleNonDuplicate(nums);
  LCD_EXPECT_EQ(expect, actual);
}

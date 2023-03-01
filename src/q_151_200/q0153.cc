// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Find Minimum in Rotated Sorted Array
//
// https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/
//
// Question ID: 153
// Difficult  : Medium
// Solve Date : 2021/09/20 08:00

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |153. Find Minimum in Rotated Sorted Array|:
//
// Suppose an array of length |n| sorted in ascending order is rotated between
// |1| and |n| times. For example, the array |nums = [0,1,2,4,5,6,7]| might
// become:
//
//  • |[4,5,6,7,0,1,2]| if it was rotated |4| times.
//
//  • |[0,1,2,4,5,6,7]| if it was rotated |7| times.
// Notice that rotating an array |[a[0], a[1], a[2], ..., a[n-1]]| 1 time
// results in the array |[a[n-1], a[0], a[1], a[2], ..., a[n-2]]|. Given the
// sorted rotated array |nums| of unique elements, return the minimum element of
// this array. You must write an algorithm that runs in  |O(log n) time.|  
//

LEETCODE_BEGIN_RESOLVING(153, FindMinimumInRotatedSortedArray, Solution);

class Solution {
public:
  int findMin(vector<int> &nums) {
    int beg = 0, end = nums.size() - 1;
    if (nums[end] >= nums[beg])
      return nums[beg];
    else {
      while (beg <= end) {
        int mid = beg + (end - beg) / 2;
        if (mid + 1 < nums.size() && nums[mid] > nums[mid + 1])
          return nums[mid + 1];
        if (mid - 1 >= 0 && nums[mid - 1] > nums[mid])
          return nums[mid];
        if (nums[mid] > nums[0])
          beg = mid + 1;
        else
          end = mid - 1;
      }
      return -1;
    }
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == nums.length|
// * |1 <= n <= 5000|
// * |-5000 <= nums[i] <= 5000|
// * All the integers of |nums| are unique.
// * |nums| is sorted and rotated between |1| and |n| times.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [3,4,5,1,2]
// Output: 1
//
// The original array was [1,2,3,4,5] rotated 3 times.

LEETCODE_SOLUTION_UNITTEST(153, FindMinimumInRotatedSortedArray, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 4, 5, 1, 2};
  int         expect   = 1;
  int         actual   = solution->findMin(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [4,5,6,7,0,1,2]
// Output: 0
//
// The original array was [0,1,2,4,5,6,7] and it was rotated 4 times.

LEETCODE_SOLUTION_UNITTEST(153, FindMinimumInRotatedSortedArray, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {4, 5, 6, 7, 0, 1, 2};
  int         expect   = 0;
  int         actual   = solution->findMin(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [11,13,15,17]
// Output: 11
//
// The original array was [11,13,15,17] and it was rotated 4 times.

LEETCODE_SOLUTION_UNITTEST(153, FindMinimumInRotatedSortedArray, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {11, 13, 15, 17};
  int         expect   = 11;
  int         actual   = solution->findMin(nums);
  LCD_EXPECT_EQ(expect, actual);
}

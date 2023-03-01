// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Search in Rotated Sorted Array
//
// https://leetcode.com/problems/search-in-rotated-sorted-array/
//
// Question ID: 33
// Difficult  : Medium
// Solve Date : 2021/09/19 08:00

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |33. Search in Rotated Sorted Array|:
//
// There is an integer array |nums| sorted in ascending order (with distinct
// values). Prior to being passed to your function, |nums| is possibly rotated
// at an unknown pivot index |k| ( |1 <= k < nums.length|) such that the
// resulting array is |[nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1],
// ..., nums[k-1]]| (0-indexed). For example, |[0,1,2,4,5,6,7]| might be rotated
// at pivot index |3| and become |[4,5,6,7,0,1,2]|. Given the array |nums| after
// the possible rotation and an integer |target|, return the index of |target|
// if it is in |nums|, or |-1| if it is not in |nums|. You must write an
// algorithm with |O(log n)| runtime complexity.  
//

LEETCODE_BEGIN_RESOLVING(33, SearchInRotatedSortedArray, Solution);

class Solution {
public:
  int search(vector<int> &nums, int target) {
    int l = 0, r = nums.size() - 1;
    while (l <= r) {
      int mid = l + (r - l) / 2;
      if (nums[mid] == target)
        return mid;
      if (nums[mid] < nums[r]) {
        if (nums[mid] < target && nums[r] >= target) {
          l = mid + 1;
        } else {
          r = mid - 1;
        }
      } else {
        if (nums[mid] > target && nums[l] <= target) {
          r = mid - 1;
        } else {
          l = mid + 1;
        }
      }
    }
    return -1;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 5000|
// * |-10⁴ <= nums[i] <= 10⁴|
// * All values of |nums| are unique.
// * |nums| is an ascending array that is possibly rotated.
// * |-10⁴ <= target <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [4,5,6,7,0,1,2], target = 0
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(33, SearchInRotatedSortedArray, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {4, 5, 6, 7, 0, 1, 2};
  int         target   = 0;
  int         expect   = 4;
  int         actual   = solution->search(nums, target);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [4,5,6,7,0,1,2], target = 3
// Output: -1
//

LEETCODE_SOLUTION_UNITTEST(33, SearchInRotatedSortedArray, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {4, 5, 6, 7, 0, 1, 2};
  int         target   = 3;
  int         expect   = -1;
  int         actual   = solution->search(nums, target);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [1], target = 0
// Output: -1
//

LEETCODE_SOLUTION_UNITTEST(33, SearchInRotatedSortedArray, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1};
  int         target   = 0;
  int         expect   = -1;
  int         actual   = solution->search(nums, target);
  LCD_EXPECT_EQ(expect, actual);
}

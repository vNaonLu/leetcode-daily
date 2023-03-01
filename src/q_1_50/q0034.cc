// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Find First and Last Position of Element in Sorted Array
//
// https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/
//
// Question ID: 34
// Difficult  : Medium
// Solve Date : 2021/09/19 08:00

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |34. Find First and Last Position of Element in Sorted Array|:
//
// Given an array of integers |nums| sorted in non-decreasing order, find the
// starting and ending position of a given |target| value. If |target| is not
// found in the array, return |[-1, -1]|. You must write an algorithm with 
// |O(log n)| runtime complexity.  
//

LEETCODE_BEGIN_RESOLVING(34, FindFirstAndLastPositionOfElementInSortedArray,
                         Solution);

class Solution {
public:
  vector<int> searchRange(vector<int> &nums, int target) {
    vector<int> res(2, -1);
    auto        find = lower_bound(nums.begin(), nums.end(), target);

    if (find != nums.end() && *find == target) {
      res[0] = res[1] = find - nums.begin();

      int lo = 0, hi = res[0];

      while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (nums[mid] != target) {
          lo = mid + 1;
        } else {
          res[0] = mid;
          hi     = mid - 1;
        }
      }

      lo = res[1];
      hi = nums.size() - 1;
      while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (nums[mid] != target) {
          hi = mid - 1;
        } else {
          res[1] = mid;
          lo     = mid + 1;
        }
      }
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |0 <= nums.length <= 10⁵|
// * |-10⁹ <= nums[i] <= 10⁹|
// * |nums| is a non-decreasing array.
// * |-10⁹ <= target <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [5,7,7,8,8,10], target = 8
// Output: [3,4]
//

LEETCODE_SOLUTION_UNITTEST(34, FindFirstAndLastPositionOfElementInSortedArray,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {5, 7, 7, 8, 8, 10};
  int         target   = 8;
  vector<int> expect   = {3, 4};
  vector<int> actual   = solution->searchRange(nums, target);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [5,7,7,8,8,10], target = 6
// Output: [-1,-1]
//

LEETCODE_SOLUTION_UNITTEST(34, FindFirstAndLastPositionOfElementInSortedArray,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {5, 7, 7, 8, 8, 10};
  int         target   = 6;
  vector<int> expect   = {-1, -1};
  vector<int> actual   = solution->searchRange(nums, target);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [], target = 0
// Output: [-1,-1]
//

LEETCODE_SOLUTION_UNITTEST(34, FindFirstAndLastPositionOfElementInSortedArray,
                           example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {};
  int         target   = 0;
  vector<int> expect   = {-1, -1};
  vector<int> actual   = solution->searchRange(nums, target);
  LCD_EXPECT_EQ(expect, actual);
}

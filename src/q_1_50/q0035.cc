// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Search Insert Position
//
// https://leetcode.com/problems/search-insert-position/
//
// Question ID: 35
// Difficult  : Easy
// Solve Date : 2021/11/26 21:37

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |35. Search Insert Position|:
//
// Given a sorted array of distinct integers and a target value, return the
// index if the target is found. If not, return the index where it would be if
// it were inserted in order. You must write an algorithm with  |O(log n)|
// runtime complexity.  
//

LEETCODE_BEGIN_RESOLVING(35, SearchInsertPosition, Solution);

class Solution {
public:
  int searchInsert(vector<int> &nums, int target) {
    int l = 0, r = nums.size() - 1;
    while (l <= r) {
      int mid = l + (r - l) / 2;
      if (nums[mid] == target)
        return mid;
      else if (nums[mid] > target)
        r = mid - 1;
      else
        l = mid + 1;
    }
    return l;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁴|
// * |-10⁴ <= nums[i] <= 10⁴|
// * |nums| contains distinct values sorted in ascending order.
// * |-10⁴ <= target <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,3,5,6], target = 5
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(35, SearchInsertPosition, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 3, 5, 6};
  int         target   = 5;
  int         expect   = 2;
  int         actual   = solution->searchInsert(nums, target);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,3,5,6], target = 2
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(35, SearchInsertPosition, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 3, 5, 6};
  int         target   = 2;
  int         expect   = 1;
  int         actual   = solution->searchInsert(nums, target);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [1,3,5,6], target = 7
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(35, SearchInsertPosition, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 3, 5, 6};
  int         target   = 7;
  int         expect   = 4;
  int         actual   = solution->searchInsert(nums, target);
  LCD_EXPECT_EQ(expect, actual);
}

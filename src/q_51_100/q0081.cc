// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Search in Rotated Sorted Array II
//
// https://leetcode.com/problems/search-in-rotated-sorted-array-ii/
//
// Question ID: 81
// Difficult  : Medium
// Solve Date : 2022/03/28 18:20

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |81. Search in Rotated Sorted Array II|:
//
// There is an integer array |nums| sorted in non-decreasing order (not
// necessarily with distinct values). Before being passed to your function,
// |nums| is rotated at an unknown pivot index |k| ( |0 <= k < nums.length|)
// such that the resulting array is |[nums[k], nums[k+1], ..., nums[n-1],
// nums[0], nums[1], ..., nums[k-1]]| (0-indexed). For example,
// |[0,1,2,4,4,4,5,6,6,7]| might be rotated at pivot index |5| and become
// |[4,5,6,6,7,0,1,2,4,4]|. Given the array |nums| after the rotation and an
// integer |target|, return |true| if |target| is in |nums|, or |false| if it is
// not in |nums|. You must decrease the overall operation steps as much as
// possible.  
//

LEETCODE_BEGIN_RESOLVING(81, SearchInRotatedSortedArrayII, Solution);

class Solution {
public:
  bool search(vector<int> &nums, int target) {
    int n = nums.size();
    if (n == 0)
      return false;
    int l = 0, r = n - 1;

    while (l <= r) {
      int mid = l + (r - l) / 2;

      if (nums[mid] == target) {
        return true;
      }

      if (nums[l] == nums[mid]) {
        ++l;
        continue;
      }

      bool pivot = nums[l] <= nums[mid], tar = nums[l] <= target;

      if (pivot ^ tar) {
        if (pivot) {
          l = mid + 1;
        } else {
          r = mid - 1;
        }
      } else {
        if (nums[mid] < target) {
          l = mid + 1;
        } else {
          r = mid - 1;
        }
      }
    }

    return false;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 5000|
// * |-10⁴ <= nums[i] <= 10⁴|
// * |nums| is guaranteed to be rotated at some pivot.
// * |-10⁴ <= target <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [2,5,6,0,0,1,2], target = 0
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(81, SearchInRotatedSortedArrayII, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 5, 6, 0, 0, 1, 2};
  int         target   = 0;
  bool        expect   = true;
  bool        actual   = solution->search(nums, target);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [2,5,6,0,0,1,2], target = 3
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(81, SearchInRotatedSortedArrayII, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 5, 6, 0, 0, 1, 2};
  int         target   = 3;
  bool        expect   = false;
  bool        actual   = solution->search(nums, target);
  LCD_EXPECT_EQ(expect, actual);
}

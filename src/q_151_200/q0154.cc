// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Find Minimum in Rotated Sorted Array II
//
// https://leetcode.com/problems/find-minimum-in-rotated-sorted-array-ii/
//
// Question ID: 154
// Difficult  : Hard
// Solve Date : 2021/10/23 09:55

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |154. Find Minimum in Rotated Sorted Array II|:
//
// Suppose an array of length |n| sorted in ascending order is rotated between
// |1| and |n| times. For example, the array |nums = [0,1,4,4,5,6,7]| might
// become:
//
//  • |[4,5,6,7,0,1,4]| if it was rotated |4| times.
//
//  • |[0,1,4,4,5,6,7]| if it was rotated |7| times.
// Notice that rotating an array |[a[0], a[1], a[2], ..., a[n-1]]| 1 time
// results in the array |[a[n-1], a[0], a[1], a[2], ..., a[n-2]]|. Given the
// sorted rotated array |nums| that may contain duplicates, return the minimum
// element of this array. You must decrease the overall operation steps as much
// as possible.  
//

LEETCODE_BEGIN_RESOLVING(154, FindMinimumInRotatedSortedArrayII, Solution);

class Solution {
private:
  template <typename iterator>
  iterator solve(iterator beg, iterator end) {
    auto len = distance(beg, --end);
    while (len != 0) {
      auto half = len / 2;
      auto mid  = beg + half;

      if (*mid > *end) {
        beg = mid + 1;
        len -= half + 1;
      } else if (*mid < *end) {
        end = mid;
        len = half;
      } else {
        --end;
        --len;
      }
    }

    return end;
  }

public:
  int findMin(vector<int> &nums) { return *solve(nums.begin(), nums.end()); }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == nums.length|
// * |1 <= n <= 5000|
// * |-5000 <= nums[i] <= 5000|
// * |nums| is sorted and rotated between |1| and |n| times.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,3,5]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(154, FindMinimumInRotatedSortedArrayII, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 3, 5};
  int         expect   = 1;
  int         actual   = solution->findMin(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [2,2,2,0,1]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(154, FindMinimumInRotatedSortedArrayII, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 2, 2, 0, 1};
  int         expect   = 0;
  int         actual   = solution->findMin(nums);
  LCD_EXPECT_EQ(expect, actual);
}

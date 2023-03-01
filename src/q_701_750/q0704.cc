// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Binary Search
//
// https://leetcode.com/problems/binary-search/
//
// Question ID: 704
// Difficult  : Easy
// Solve Date : 2022/04/03 15:39

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |704. Binary Search|:
//
// Given an array of integers |nums| which is sorted in ascending order, and an
// integer |target|, write a function to search |target| in |nums|. If |target|
// exists, then return its index. Otherwise, return |-1|. You must write an
// algorithm with |O(log n)| runtime complexity.  
//

LEETCODE_BEGIN_RESOLVING(704, BinarySearch, Solution);

class Solution {
private:
  template <typename iterator, typename type>
  iterator solve(iterator beg, iterator end, type &&val) {
    auto not_found = end;
    auto len       = distance(beg, end);
    while (len != 0) {
      auto half = len / 2;
      auto mid  = beg + half;

      if (*mid == val) {

        return mid;
      } else if (*mid > val) {
        len = half;
        end = mid;
      } else {
        len -= half + 1;
        beg = ++mid;
      }
    }

    return not_found;
  }

public:
  int search(vector<int> &nums, int target) {
    auto find = solve(nums.begin(), nums.end(), target);

    return find == nums.end() ? -1 : distance(nums.begin(), find);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁴|
// * |-10⁴ < nums[i], target < 10⁴|
// * All the integers in |nums| are unique.
// * |nums| is sorted in ascending order.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [-1,0,3,5,9,12], target = 9
// Output: 4
//
// 9 exists in nums and its index is 4

LEETCODE_SOLUTION_UNITTEST(704, BinarySearch, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {-1, 0, 3, 5, 9, 12};
  int         target   = 9;
  int         expect   = 4;
  int         actual   = solution->search(nums, target);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [-1,0,3,5,9,12], target = 2
// Output: -1
//
// 2 does not exist in nums so return -1

LEETCODE_SOLUTION_UNITTEST(704, BinarySearch, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {-1, 0, 3, 5, 9, 12};
  int         target   = 2;
  int         expect   = -1;
  int         actual   = solution->search(nums, target);
  LCD_EXPECT_EQ(expect, actual);
}

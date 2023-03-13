// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Median of Two Sorted Arrays
//
// https://leetcode.com/problems/median-of-two-sorted-arrays/
//
// Question ID: 4
// Difficult  : Hard
// Solve Date : 2021/10/08 16:27

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |4. Median of Two Sorted Arrays|:
//
// Given two sorted arrays |nums1| and |nums2| of size |m| and |n| respectively,
// return the median of the two sorted arrays. The overall run time complexity
// should be |O(log (m+n))|.  
//

LEETCODE_BEGIN_RESOLVING(4, MedianOfTwoSortedArrays, Solution);

class Solution {
public:
  double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2) {
    int    m = nums1.size(), n = nums2.size();
    int    mid = (m + n) / 2;
    auto   i1 = nums1.begin(), i2 = nums2.begin();
    double last = 0.0, second = 0.0;
    while (mid >= 0) {
      second = last;
      --mid;
      if (i1 == nums1.end()) {
        last = *(i2++);
      } else if (i2 == nums2.end()) {
        last = *(i1++);
      } else {
        if (*i1 > *i2) {
          last = *(i2++);
        } else {
          last = *(i1++);
        }
      }
    }
    return (m + n) % 2 ? last : ((last + second) * 0.5);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |nums1.length == m|
// * |nums2.length == n|
// * |0 <= m <= 1000|
// * |0 <= n <= 1000|
// * |1 <= m + n <= 2000|
// * |-10⁶ <= nums1[i], nums2[i] <= 10⁶|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums1 = [1,3], nums2 = [2]
// Output: 2.00000
//
// merged array = [1,2,3] and median is 2.

LEETCODE_SOLUTION_UNITTEST(4, MedianOfTwoSortedArrays, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums1    = {1, 3};
  vector<int> nums2    = {2};
  double      expect   = 2.00000;
  double      actual   = solution->findMedianSortedArrays(nums1, nums2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums1 = [1,2], nums2 = [3,4]
// Output: 2.50000
//
// merged array = [1,2,3,4] and median is (2 + 3) / 2 = 2.5.

LEETCODE_SOLUTION_UNITTEST(4, MedianOfTwoSortedArrays, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums1    = {1, 2};
  vector<int> nums2    = {3, 4};
  double      expect   = 2.50000;
  double      actual   = solution->findMedianSortedArrays(nums1, nums2);
  LCD_EXPECT_EQ(expect, actual);
}

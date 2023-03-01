// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Merge Sorted Array
//
// https://leetcode.com/problems/merge-sorted-array/
//
// Question ID: 88
// Difficult  : Easy
// Solve Date : 2021/09/06 08:00

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |88. Merge Sorted Array|:
//
// You are given two integer arrays |nums1| and |nums2|, sorted in
// non-decreasing order, and two integers |m| and |n|, representing the number
// of elements in |nums1| and |nums2| respectively. Merge |nums1| and |nums2|
// into a single array sorted in non-decreasing order. The final sorted array
// should not be returned by the function, but instead be stored inside the
// array |nums1|. To accommodate this, |nums1| has a length of |m + n|, where
// the first |m| elements denote the elements that should be merged, and the
// last |n| elements are set to |0| and should be ignored. |nums2| has a length
// of |n|.  
//

LEETCODE_BEGIN_RESOLVING(88, MergeSortedArray, Solution);

class Solution {
public:
  void merge(vector<int> &nums1, int m, vector<int> &nums2, int n) {
    int         i  = -1;
    int         i1 = 0, i2 = 0;
    vector<int> n1(nums1.begin(), nums1.begin() + m);
    while (i1 < m && i2 < n) {
      if (n1[i1] <= nums2[i2]) {
        nums1[++i] = n1[i1++];
      } else {
        nums1[++i] = nums2[i2++];
      }
    }
    while (i1 < m) {
      nums1[++i] = n1[i1++];
    }
    while (i2 < n) {
      nums1[++i] = nums2[i2++];
    }
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |nums1.length == m + n|
// * |nums2.length == n|
// * |0 <= m, n <= 200|
// * |1 <= m + n <= 200|
// * |-10⁹ <= nums1[i], nums2[j] <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3
// Output: [1,2,2,3,5,6]
//
// The arrays we are merging are [1,2,3] and [2,5,6].
// The result of the merge is [1,2,2,3,5,6] with the underlined elements coming
// from nums1.

LEETCODE_SOLUTION_UNITTEST(88, MergeSortedArray, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums1    = {1, 2, 3, 0, 0, 0};
  int         m        = 3;
  vector<int> nums2    = {2, 5, 6};
  int         n        = 3;
  vector<int> expect   = {1, 2, 2, 3, 5, 6};
  solution->merge(nums1, m, nums2, n);
  EXPECT_EQ(expect, nums1);
}

// [Example #2]
//  Input: nums1 = [1], m = 1, nums2 = [], n = 0
// Output: [1]
//
// The arrays we are merging are [1] and [].
// The result of the merge is [1].

LEETCODE_SOLUTION_UNITTEST(88, MergeSortedArray, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums1    = {1};
  int         m        = 1;
  vector<int> nums2    = {};
  int         n        = 0;
  vector<int> expect   = {1};
  solution->merge(nums1, m, nums2, n);
  EXPECT_EQ(expect, nums1);
}

// [Example #3]
//  Input: nums1 = [0], m = 0, nums2 = [1], n = 1
// Output: [1]
//
// The arrays we are merging are [] and [1].
// The result of the merge is [1].
// Note that because m = 0, there are no elements in nums1. The 0 is only there
// to ensure the merge result can fit in nums1.

LEETCODE_SOLUTION_UNITTEST(88, MergeSortedArray, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums1    = {0};
  int         m        = 0;
  vector<int> nums2    = {1};
  int         n        = 1;
  vector<int> expect   = {1};
  solution->merge(nums1, m, nums2, n);
  EXPECT_EQ(expect, nums1);
}

// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Maximum Distance Between a Pair of Values
//
// https://leetcode.com/problems/maximum-distance-between-a-pair-of-values/
//
// Question ID: 1855
// Difficult  : Medium
// Solve Date : 2022/04/13 19:07

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1855. Maximum Distance Between a Pair of Values|:
//
// You are given two non-increasing 0-indexed integer arrays
// |nums1|​​​​​​ and |nums2|​​​​​​. A pair of indices
// |(i, j)|, where |0 <= i < nums1.length| and |0 <= j < nums2.length|, is valid
// if both |i <= j| and |nums1[i] <= nums2[j]|. The distance of the pair is |j -
// i|​​​​. Return the maximum distance of any valid pair |(i, j)|. If
// there are no valid pairs, return |0|. An array |arr| is non-increasing if
// |arr[i-1] >= arr[i]| for every |1 <= i < arr.length|.  
//

LEETCODE_BEGIN_RESOLVING(1855, MaximumDistanceBetweenAPairOfValues, Solution);

class Solution {
public:
  int maxDistance(vector<int> &nums1, vector<int> &nums2) {
    int res = 0;
    for (int i = 0; i < nums1.size(); ++i) {
      auto curr = nums1[i];
      int  l = i, r = nums2.size() - 1;
      while (l <= r) {
        int m = l + (r - l) / 2;
        if (nums2[m] < curr) {
          r = m - 1;
        } else {
          l = m + 1;
        }
      }
      res = max(res, r - i);
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums1.length, nums2.length <= 10⁵|
// * |1 <= nums1[i], nums2[j] <= 10⁵|
// * Both |nums1| and |nums2| are non-increasing.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums1 = [55,30,5,4,2], nums2 = [100,20,10,10,5]
// Output: 2
//
// The valid pairs are (0,0), (2,2), (2,3), (2,4), (3,3), (3,4), and (4,4).
// The maximum distance is 2 with pair (2,4).

LEETCODE_SOLUTION_UNITTEST(1855, MaximumDistanceBetweenAPairOfValues,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums1    = {55, 30, 5, 4, 2};
  vector<int> nums2    = {100, 20, 10, 10, 5};
  int         expect   = 2;
  int         actual   = solution->maxDistance(nums1, nums2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums1 = [2,2,2], nums2 = [10,10,1]
// Output: 1
//
// The valid pairs are (0,0), (0,1), and (1,1).
// The maximum distance is 1 with pair (0,1).

LEETCODE_SOLUTION_UNITTEST(1855, MaximumDistanceBetweenAPairOfValues,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums1    = {2, 2, 2};
  vector<int> nums2    = {10, 10, 1};
  int         expect   = 1;
  int         actual   = solution->maxDistance(nums1, nums2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums1 = [30,29,19,5], nums2 = [25,25,25,25,25]
// Output: 2
//
// The valid pairs are (2,2), (2,3), (2,4), (3,3), and (3,4).
// The maximum distance is 2 with pair (2,4).

LEETCODE_SOLUTION_UNITTEST(1855, MaximumDistanceBetweenAPairOfValues,
                           example_3) {
  auto        solution = MakeSolution();
  vector<int> nums1    = {30, 29, 19, 5};
  vector<int> nums2    = {25, 25, 25, 25, 25};
  int         expect   = 2;
  int         actual   = solution->maxDistance(nums1, nums2);
  LCD_EXPECT_EQ(expect, actual);
}

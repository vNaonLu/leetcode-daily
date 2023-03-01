// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Maximum Length of Repeated Subarray
//
// https://leetcode.com/problems/maximum-length-of-repeated-subarray/
//
// Question ID: 718
// Difficult  : Medium
// Solve Date : 2022/09/20 17:12

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |718. Maximum Length of Repeated Subarray|:
//
// Given two integer arrays |nums1| and |nums2|, return the maximum length of a
// subarray that appears in both arrays.
//

LEETCODE_BEGIN_RESOLVING(718, MaximumLengthOfRepeatedSubarray, Solution);

class Solution {
public:
  int findLength(vector<int> &nums1, vector<int> &nums2) {
    auto res = (int)0;
    auto dp =
        vector<vector<int>>(nums1.size() + 1, vector<int>(nums2.size() + 1));
    for (int i = nums1.size() - 1; i >= 0; --i) {
      for (int j = nums2.size() - 1; j >= 0; --j) {
        if (nums1[i] == nums2[j]) {
          dp[i][j] = dp[i + 1][j + 1] + 1;
          res      = max(res, dp[i][j]);
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
// * |1 <= nums1.length, nums2.length <= 1000|
// * |0 <= nums1[i], nums2[i] <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums1 = [1,2,3,2,1], nums2 = [3,2,1,4,7]
// Output: 3
//
// The repeated subarray with maximum length is [3,2,1].

LEETCODE_SOLUTION_UNITTEST(718, MaximumLengthOfRepeatedSubarray, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums1    = {1, 2, 3, 2, 1};
  vector<int> nums2    = {3, 2, 1, 4, 7};
  int         expect   = 3;
  int         actual   = solution->findLength(nums1, nums2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums1 = [0,0,0,0,0], nums2 = [0,0,0,0,0]
// Output: 5
//
// The repeated subarray with maximum length is [0,0,0,0,0].

LEETCODE_SOLUTION_UNITTEST(718, MaximumLengthOfRepeatedSubarray, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums1    = {0, 0, 0, 0, 0};
  vector<int> nums2    = {0, 0, 0, 0, 0};
  int         expect   = 5;
  int         actual   = solution->findLength(nums1, nums2);
  LCD_EXPECT_EQ(expect, actual);
}

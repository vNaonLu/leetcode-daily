// Copyright 2023 Naon Lu
//
// This file describes the solution of
// 4Sum II
//
// https://leetcode.com/problems/4sum-ii/
//
// Question ID: 454
// Difficult  : Medium
// Solve Date : 2022/02/03 13:29

#include <iosfwd>
#include <map>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |454. 4Sum II|:
//
// Given four integer arrays |nums1|, |nums2|, |nums3|, and |nums4| all of
// length |n|, return the number of tuples |(i, j, k, l)| such that:
//
//  • |0 <= i, j, k, l < n|
//
//  • |nums1[i] + nums2[j] + nums3[k] + nums4[l] == 0|
//  
//

LEETCODE_BEGIN_RESOLVING(454, 4SumII, Solution);

class Solution {
public:
  int fourSumCount(vector<int> &nums1, vector<int> &nums2, vector<int> &nums3,
                   vector<int> &nums4) {
    unordered_map<int, int> keep;
    for (const auto &x : nums1) {
      for (const auto &y : nums2) {
        ++keep[x + y];
      }
    }
    int res = 0;
    for (const auto &x : nums3) {
      for (const auto &y : nums4) {
        res += keep[-x - y];
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == nums1.length|
// * |n == nums2.length|
// * |n == nums3.length|
// * |n == nums4.length|
// * |1 <= n <= 200|
// * |-2²⁸ <= nums1[i], nums2[i], nums3[i], nums4[i] <= 2²⁸|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums1 = [1,2], nums2 = [-2,-1], nums3 = [-1,2], nums4 = [0,2]
// Output: 2
//
// The two tuples are:
// 1. (0, 0, 0, 1) -> nums1[0] + nums2[0] + nums3[0] + nums4[1] = 1 + (-2) +
// (-1) + 2 = 0
// 2. (1, 1, 0, 0) -> nums1[1] + nums2[1] + nums3[0] + nums4[0] = 2 + (-1) +
// (-1) + 0 = 0

LEETCODE_SOLUTION_UNITTEST(454, 4SumII, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums1    = {1, 2};
  vector<int> nums2    = {-2, -1};
  vector<int> nums3    = {-1, 2};
  vector<int> nums4    = {0, 2};
  int         expect   = 2;
  int         actual   = solution->fourSumCount(nums1, nums2, nums3, nums4);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums1 = [0], nums2 = [0], nums3 = [0], nums4 = [0]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(454, 4SumII, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums1    = {0};
  vector<int> nums2    = {0};
  vector<int> nums3    = {0};
  vector<int> nums4    = {0};
  int         expect   = 1;
  int         actual   = solution->fourSumCount(nums1, nums2, nums3, nums4);
  LCD_EXPECT_EQ(expect, actual);
}

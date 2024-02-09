// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Find Common Elements Between Two Arrays
//
// https://leetcode.com/problems/find-common-elements-between-two-arrays/
//
// Question ID: 2956
// Difficult  : Easy
// Solve Date : 2024/02/09 12:08

#include <iosfwd>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2956. Find Common Elements Between Two Arrays|:
//
// You are given two 0-indexed integer arrays |nums1| and |nums2| of sizes |n|
// and |m|, respectively. Consider calculating the following values:
//
//  • The number of indices |i| such that |0 <= i < n| and |nums1[i]| occurs at
//  least once in |nums2|.
//
//  • The number of indices |i| such that |0 <= i < m| and |nums2[i]| occurs at
//  least once in |nums1|.
// Return an integer array |answer| of size |2| containing the two values in the
// above order.
//
//

LEETCODE_BEGIN_RESOLVING(2956, FindCommonElementsBetweenTwoArrays, Solution);

class Solution {
public:
  vector<int> findIntersectionValues(vector<int> &nums1, vector<int> &nums2) {
    vector<int>                     res(2, 0);
    unordered_map<int, vector<int>> mp1;
    unordered_map<int, vector<int>> mp2;
    for (int i = 0; i < nums1.size(); ++i) {
      mp1[nums1[i]].emplace_back(i);
    }
    for (int i = 0; i < nums2.size(); ++i) {
      mp2[nums2[i]].emplace_back(i);
    }
    for (auto x : nums1) {
      if (mp2.count(x)) {
        ++res[0];
      }
    }
    for (auto x : nums2) {
      if (mp1.count(x)) {
        ++res[1];
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |n == nums1.length|
// * |m == nums2.length|
// * |1 <= n, m <= 100|
// * |1 <= nums1[i], nums2[i] <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums1 = [4,3,2,3,1], nums2 = [2,2,5,2,3,6]
// Output: [3,4]
//
// We calculate the values as follows:
// - The elements at indices 1, 2, and 3 in nums1 occur at least once in nums2.
// So the first value is 3.
// - The elements at indices 0, 1, 3, and 4 in nums2 occur at least once in
// nums1. So the second value is 4.

LEETCODE_SOLUTION_UNITTEST(2956, FindCommonElementsBetweenTwoArrays,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums1    = {4, 3, 2, 3, 1};
  vector<int> nums2    = {2, 2, 5, 2, 3, 6};
  vector<int> expect   = {3, 4};
  vector<int> actual   = solution->findIntersectionValues(nums1, nums2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums1 = [3,4,2,3], nums2 = [1,5]
// Output: [0,0]
//
// There are no common elements between the two arrays, so the two values will
// be 0.

LEETCODE_SOLUTION_UNITTEST(2956, FindCommonElementsBetweenTwoArrays,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums1    = {3, 4, 2, 3};
  vector<int> nums2    = {1, 5};
  vector<int> expect   = {0, 0};
  vector<int> actual   = solution->findIntersectionValues(nums1, nums2);
  LCD_EXPECT_EQ(expect, actual);
}

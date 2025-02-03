// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Bitwise XOR of All Pairings
//
// https://leetcode.com/problems/bitwise-xor-of-all-pairings/
//
// Question ID: 2425
// Difficult  : Medium
// Solve Date : 2025/01/16 21:16

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2425. Bitwise XOR of All Pairings|:
//
// You are given two 0-indexed arrays, |nums1| and |nums2|, consisting of
// non-negative integers. There exists another array, |nums3|, which contains
// the bitwise XOR of all pairings of integers between |nums1| and |nums2|
// (every integer in |nums1| is paired with every integer in |nums2| exactly
// once). Return the bitwise XOR of all integers in |nums3|.
//
//

LEETCODE_BEGIN_RESOLVING(2425, BitwiseXOROfAllPairings, Solution);

class Solution {
public:
  int xorAllNums(vector<int> &nums1, vector<int> &nums2) {
    int c1 = nums1.size();
    int c2 = nums2.size();
    int x1 = 0;
    int x2 = 0;

    if (c1 % 2 != 0) {
      for (auto x : nums2) {
        x2 ^= x;
      }
    }

    if (c2 % 2 != 0) {
      for (auto x : nums1) {
        x1 ^= x;
      }
    }

    return x1 ^ x2;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums1.length, nums2.length <= 10⁵|
// * |0 <= nums1[i], nums2[j] <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums1 = [2,1,3], nums2 = [10,2,5,0]
// Output: 13
//

LEETCODE_SOLUTION_UNITTEST(2425, BitwiseXOROfAllPairings, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums1    = {2, 1, 3};
  vector<int> nums2    = {10, 2, 5, 0};
  int         expect   = 13;
  int         actual   = solution->xorAllNums(nums1, nums2);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums1 = [1,2], nums2 = [3,4]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(2425, BitwiseXOROfAllPairings, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums1    = {1, 2};
  vector<int> nums2    = {3, 4};
  int         expect   = 0;
  int         actual   = solution->xorAllNums(nums1, nums2);
  LCD_EXPECT_EQ(expect, actual);
}

// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Find Subarrays With Equal Sum
//
// https://leetcode.com/problems/find-subarrays-with-equal-sum/
//
// Question ID: 2395
// Difficult  : Easy
// Solve Date : 2023/01/22 12:29

#include <array>
#include <iosfwd>
#include <set>
#include <unordered_set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2395. Find Subarrays With Equal Sum|:
//
// Given a 0-indexed integer array |nums|, determine whether there exist two
// subarrays of length |2| with equal sum. Note that the two subarrays must
// begin at different indices. Return |true| if these subarrays exist, and
// |false| otherwise. A subarray is a contiguous non-empty sequence of elements
// within an array.
//

LEETCODE_BEGIN_RESOLVING(2395, FindSubarraysWithEqualSum, Solution);

class Solution {
public:
  bool findSubarrays(vector<int> &nums) {
    unordered_set<int> memo;
    for (int i = 1; i < nums.size(); ++i) {
      if (!memo.emplace(nums[i] + nums[i - 1]).second) {
        return true;
      }
    }
    return false;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |2 <= nums.length <= 1000|
// * |-10⁹ <= nums[i] <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [4,2,4]
// Output: true
//
// The subarrays with elements [4,2] and [2,4] have the same sum of 6.

LEETCODE_SOLUTION_UNITTEST(2395, FindSubarraysWithEqualSum, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {4, 2, 4};
  bool        expect   = true;
  bool        actual   = solution->findSubarrays(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,2,3,4,5]
// Output: false
//
// No two subarrays of size 2 have the same sum.

LEETCODE_SOLUTION_UNITTEST(2395, FindSubarraysWithEqualSum, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 4, 5};
  bool        expect   = false;
  bool        actual   = solution->findSubarrays(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [0,0,0]
// Output: true
//
// The subarrays [nums[0],nums[1]] and [nums[1],nums[2]] have the same sum of 0.
// Note that even though the subarrays have the same content, the two subarrays
// are considered different because they are in different positions in the
// original array.

LEETCODE_SOLUTION_UNITTEST(2395, FindSubarraysWithEqualSum, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {0, 0, 0};
  bool        expect   = true;
  bool        actual   = solution->findSubarrays(nums);
  LCD_EXPECT_EQ(expect, actual);
}

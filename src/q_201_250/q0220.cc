// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Contains Duplicate III
//
// https://leetcode.com/problems/contains-duplicate-iii/
//
// Question ID: 220
// Difficult  : Hard
// Solve Date : 2022/08/22 16:34

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |220. Contains Duplicate III|:
//
// You are given an integer array |nums| and two integers |indexDiff| and
// |valueDiff|. Find a pair of indices |(i, j)| such that:
//
//  • |i != j|,
//
//  • |abs(i - j) <= indexDiff|.
//
//  • |abs(nums[i] - nums[j]) <= valueDiff|, and
// Return |true| if such pair exists or |false| otherwise.
//

LEETCODE_BEGIN_RESOLVING(220, ContainsDuplicateIII, Solution);

class Solution {
public:
  bool containsNearbyAlmostDuplicate(vector<int> &nums, int k, int t) {
    auto vt = vector<pair<int64_t, int>>();
    for (auto i = 0; i < nums.size(); ++i) {
      vt.emplace_back(nums[i], i);
    }

    sort(vt.begin(), vt.end());

    for (auto i = 0; i < vt.size(); ++i) {
      for (auto j = i + 1; j < vt.size(); ++j) {
        if (abs(vt[i].first - vt[j].first) <= t) {
          if (abs(vt[i].second - vt[j].second) <= k) {
            return true;
          }
        } else {
          break;
        }
      }
    }

    return false;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |2 <= nums.length <= 10⁵|
// * |-10⁹ <= nums[i] <= 10⁹|
// * |1 <= indexDiff <= nums.length|
// * |0 <= valueDiff <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,3,1], indexDiff = 3, valueDiff = 0
// Output: true
//
// We can choose (i, j) = (0, 3).
// We satisfy the three conditions:
// i != j --> 0 != 3
// abs(i - j) <= indexDiff --> abs(0 - 3) <= 3
// abs(nums[i] - nums[j]) <= valueDiff --> abs(1 - 1) <= 0

LEETCODE_SOLUTION_UNITTEST(220, ContainsDuplicateIII, example_1) {
  auto        solution  = MakeSolution();
  vector<int> nums      = {1, 2, 3, 1};
  int         indexDiff = 3;
  int         valueDiff = 0;
  bool        expect    = true;
  bool        actual =
      solution->containsNearbyAlmostDuplicate(nums, indexDiff, valueDiff);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,5,9,1,5,9], indexDiff = 2, valueDiff = 3
// Output: false
//
// After trying all the possible pairs (i, j), we cannot satisfy the three
// conditions, so we return false.

LEETCODE_SOLUTION_UNITTEST(220, ContainsDuplicateIII, example_2) {
  auto        solution  = MakeSolution();
  vector<int> nums      = {1, 5, 9, 1, 5, 9};
  int         indexDiff = 2;
  int         valueDiff = 3;
  bool        expect    = false;
  bool        actual =
      solution->containsNearbyAlmostDuplicate(nums, indexDiff, valueDiff);
  LCD_EXPECT_EQ(expect, actual);
}

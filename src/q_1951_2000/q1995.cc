// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Count Special Quadruplets
//
// https://leetcode.com/problems/count-special-quadruplets/
//
// Question ID: 1995
// Difficult  : Easy
// Solve Date : 2023/09/20 18:53

#include <iosfwd>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1995. Count Special Quadruplets|:
//
// Given a 0-indexed integer array |nums|, return the number of distinct
// quadruplets |(a, b, c, d)| such that:
//
//  • |nums[a] + nums[b] + nums[c] == nums[d]|, and
//
//  • |a < b < c < d|
//
//

LEETCODE_BEGIN_RESOLVING(1995, CountSpecialQuadruplets, Solution);

class Solution {
public:
  int countQuadruplets(vector<int> &nums) {
    int                     res = 0;
    unordered_map<int, int> cnt;
    cnt[nums.back() - *(nums.end() - 2)] = 1;
    for (int i = nums.size() - 3; i >= 1; --i) {
      for (int j = i - 1; j >= 0; --j) {
        res += cnt[nums[i] + nums[j]];
      }
      for (int j = nums.size() - 1; j > i; --j) {
        ++cnt[nums[j] - nums[i]];
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |4 <= nums.length <= 50|
// * |1 <= nums[i] <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,3,6]
// Output: 1
//
// The only quadruplet that satisfies the requirement is (0, 1, 2, 3) because 1
// + 2 + 3 == 6.

LEETCODE_SOLUTION_UNITTEST(1995, CountSpecialQuadruplets, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 6};
  int         expect   = 1;
  int         actual   = solution->countQuadruplets(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [3,3,6,4,5]
// Output: 0
//
// There are no such quadruplets in [3,3,6,4,5].

LEETCODE_SOLUTION_UNITTEST(1995, CountSpecialQuadruplets, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 3, 6, 4, 5};
  int         expect   = 0;
  int         actual   = solution->countQuadruplets(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [1,1,1,3,5]
// Output: 4
//
// The 4 quadruplets that satisfy the requirement are:
// - (0, 1, 2, 3): 1 + 1 + 1 == 3
// - (0, 1, 3, 4): 1 + 1 + 3 == 5
// - (0, 2, 3, 4): 1 + 1 + 3 == 5
// - (1, 2, 3, 4): 1 + 1 + 3 == 5

LEETCODE_SOLUTION_UNITTEST(1995, CountSpecialQuadruplets, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 1, 1, 3, 5};
  int         expect   = 4;
  int         actual   = solution->countQuadruplets(nums);
  LCD_EXPECT_EQ(expect, actual);
}

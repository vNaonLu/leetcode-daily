// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Divide Array Into Equal Pairs
//
// https://leetcode.com/problems/divide-array-into-equal-pairs/
//
// Question ID: 2206
// Difficult  : Easy
// Solve Date : 2023/02/01 20:07

#include <iosfwd>
#include <map>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2206. Divide Array Into Equal Pairs|:
//
// You are given an integer array |nums| consisting of |2 * n| integers.
// You need to divide |nums| into |n| pairs such that:
//
//  • Each element belongs to exactly one pair.
//
//  • The elements present in a pair are equal.
// Return |true| if nums can be divided into |n| pairs, otherwise return
// |false|.
//

LEETCODE_BEGIN_RESOLVING(2206, DivideArrayIntoEqualPairs, Solution);

class Solution {
public:
  bool divideArray(vector<int> &nums) {
    unordered_map<int, int> freq;
    for (auto x : nums) {
      ++freq[x];
    }

    for (auto [x, cnt] : freq) {
      if (cnt & 1) {
        return false;
      }
    }

    return true;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |nums.length == 2 * n|
// * |1 <= n <= 500|
// * |1 <= nums[i] <= 500|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [3,2,3,2,2,2]
// Output: true
//
// There are 6 elements in nums, so they should be divided into 6 / 2 = 3 pairs.
// If nums is divided into the pairs (2, 2), (3, 3), and (2, 2), it will satisfy
// all the conditions.

LEETCODE_SOLUTION_UNITTEST(2206, DivideArrayIntoEqualPairs, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 2, 3, 2, 2, 2};
  bool        expect   = true;
  bool        actual   = solution->divideArray(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,2,3,4]
// Output: false
//
// There is no way to divide nums into 4 / 2 = 2 pairs such that the pairs
// satisfy every condition.

LEETCODE_SOLUTION_UNITTEST(2206, DivideArrayIntoEqualPairs, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 4};
  bool        expect   = false;
  bool        actual   = solution->divideArray(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Number of Subsequences That Satisfy the Given Sum Condition
//
// https://leetcode.com/problems/number-of-subsequences-that-satisfy-the-given-sum-condition/
//
// Question ID: 1498
// Difficult  : Medium
// Solve Date : 2022/07/28 18:56

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1498. Number of Subsequences That Satisfy the Given Sum
// Condition|:
//
// You are given an array of integers |nums| and an integer |target|.
// Return the number of non-empty subsequences of |nums| such that the sum of
// the minimum and maximum element on it is less or equal to |target|. Since the
// answer may be too large, return it modulo |10⁹ + 7|.
//

LEETCODE_BEGIN_RESOLVING(1498,
                         NumberOfSubsequencesThatSatisfyTheGivenSumCondition,
                         Solution);

class Solution {
private:
  inline constexpr static int kMod = 1e9 + 7;
  int64_t                     binaryExp(int64_t a, int64_t b) {
    int res = 1;
    while (b) {
      if (b & 1) {
        res = (res * a) % kMod;
      }
      a = (a * a) % kMod;
      b >>= 1;
    }
    return res % kMod;
  }

public:
  int numSubseq(vector<int> &nums, int target) {
    int res = 0, single = 0;
    for (auto &x : nums) {
      single += (x + x) <= target ? 1 : 0;
    }
    sort(nums.begin(), nums.end());

    for (auto it = nums.begin(); it != nums.end(); ++it) {
      auto find = --upper_bound(it + 1, nums.end(), target - *it);
      if (find != nums.end()) {
        res += binaryExp(2, distance(it, find)) - 1;
        res %= kMod;
      }
    }

    return res + single;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁵|
// * |1 <= nums[i] <= 10⁶|
// * |1 <= target <= 10⁶|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [3,5,6,7], target = 9
// Output: 4
//
// There are 4 subsequences that satisfy the condition.
// [3] -> Min value + max value <= target (3 + 3 <= 9)
// [3,5] -> (3 + 5 <= 9)
// [3,5,6] -> (3 + 6 <= 9)
// [3,6] -> (3 + 6 <= 9)

LEETCODE_SOLUTION_UNITTEST(1498,
                           NumberOfSubsequencesThatSatisfyTheGivenSumCondition,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 5, 6, 7};
  int         target   = 9;
  int         expect   = 4;
  int         actual   = solution->numSubseq(nums, target);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [3,3,6,8], target = 10
// Output: 6
//
// There are 6 subsequences that satisfy the condition. (nums can have repeated
// numbers). [3] , [3] , [3,3], [3,6] , [3,6] , [3,3,6]

LEETCODE_SOLUTION_UNITTEST(1498,
                           NumberOfSubsequencesThatSatisfyTheGivenSumCondition,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 3, 6, 8};
  int         target   = 10;
  int         expect   = 6;
  int         actual   = solution->numSubseq(nums, target);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [2,3,3,4,6,7], target = 12
// Output: 61
//
// There are 63 non-empty subsequences, two of them do not satisfy the condition
// ([6,7], [7]). Number of valid subsequences (63 - 2 = 61).

LEETCODE_SOLUTION_UNITTEST(1498,
                           NumberOfSubsequencesThatSatisfyTheGivenSumCondition,
                           example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 3, 3, 4, 6, 7};
  int         target   = 12;
  int         expect   = 61;
  int         actual   = solution->numSubseq(nums, target);
  LCD_EXPECT_EQ(expect, actual);
}

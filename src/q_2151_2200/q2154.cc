// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Keep Multiplying Found Values by Two
//
// https://leetcode.com/problems/keep-multiplying-found-values-by-two/
//
// Question ID: 2154
// Difficult  : Easy
// Solve Date : 2023/01/07 14:40

#include <iosfwd>
#include <set>
#include <unordered_set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2154. Keep Multiplying Found Values by Two|:
//
// You are given an array of integers |nums|. You are also given an integer
// |original| which is the first number that needs to be searched for in |nums|.
// You then do the following steps:
//
//  1. If |original| is found in |nums|, multiply it by two (i.e., set |original
//  = 2 * original|).
//
//  2. Otherwise, stop the process.
//
//  3. Repeat this process with the new number as long as you keep finding the
//  number.
// Return the final value of |original|.
//

LEETCODE_BEGIN_RESOLVING(2154, KeepMultiplyingFoundValuesByTwo, Solution);

class Solution {
public:
  int findFinalValue(vector<int> &nums, int original) {
    unordered_set<int> memo(nums.begin(), nums.end());
    while (true) {
      if (!memo.count(original)) {
        break;
      }
      original *= 2;
    }
    return original;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 1000|
// * |1 <= nums[i], original <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [5,3,6,1,12], original = 3
// Output: 24
//
// - 3 is found in nums. 3 is multiplied by 2 to obtain 6.
// - 6 is found in nums. 6 is multiplied by 2 to obtain 12.
// - 12 is found in nums. 12 is multiplied by 2 to obtain 24.
// - 24 is not found in nums. Thus, 24 is returned.

LEETCODE_SOLUTION_UNITTEST(2154, KeepMultiplyingFoundValuesByTwo, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {5, 3, 6, 1, 12};
  int         original = 3;
  int         expect   = 24;
  int         actual   = solution->findFinalValue(nums, original);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [2,7,9], original = 4
// Output: 4
//
// - 4 is not found in nums. Thus, 4 is returned.

LEETCODE_SOLUTION_UNITTEST(2154, KeepMultiplyingFoundValuesByTwo, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 7, 9};
  int         original = 4;
  int         expect   = 4;
  int         actual   = solution->findFinalValue(nums, original);
  LCD_EXPECT_EQ(expect, actual);
}

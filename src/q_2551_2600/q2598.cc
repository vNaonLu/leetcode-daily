// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Smallest Missing Non-negative Integer After Operations
//
// https://leetcode.com/problems/smallest-missing-non-negative-integer-after-operations/
//
// Question ID: 2598
// Difficult  : Medium
// Solve Date : 2025/10/16 18:53

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2598. Smallest Missing Non-negative Integer After
// Operations|:
//
// You are given a 0-indexed integer array |nums| and an integer |value|.
// In one operation, you can add or subtract |value| from any element of |nums|.
//
//  • For example, if |nums = [1,2,3]| and |value = 2|, you can choose to
//  subtract |value| from |nums[0]| to make |nums = [-1,2,3]|.
// The MEX (minimum excluded) of an array is the smallest missing non-negative
// integer in it.
//
//  • For example, the MEX of |[-1,2,3]| is |0| while the MEX of |[1,0,3]| is
//  |2|.
// Return the maximum MEX of |nums| after applying the mentioned operation any
// number of times.
//
//

LEETCODE_BEGIN_RESOLVING(2598, SmallestMissingNonNegativeIntegerAfterOperations,
                         Solution);

class Solution {
public:
  int findSmallestInteger(vector<int> &nums, int value) {
    int64_t     res = 0;
    int64_t     n   = nums.size();
    vector<int> rem(value, 0);
    for (int i = 0; i < n; ++i) {
      auto x = ((nums[i] % value) + value) % value;
      ++rem[x];
    }
    while (rem[res % value]--) {
      ++res;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length, value <= 10⁵|
// * |-10⁹ <= nums[i] <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,-10,7,13,6,8], value = 5
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(2598,
                           SmallestMissingNonNegativeIntegerAfterOperations,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, -10, 7, 13, 6, 8};
  int         value    = 5;
  int         expect   = 4;
  int         actual   = solution->findSmallestInteger(nums, value);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,-10,7,13,6,8], value = 7
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(2598,
                           SmallestMissingNonNegativeIntegerAfterOperations,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, -10, 7, 13, 6, 8};
  int         value    = 7;
  int         expect   = 2;
  int         actual   = solution->findSmallestInteger(nums, value);
  LCD_EXPECT_EQ(expect, actual);
}

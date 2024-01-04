// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Minimum Number of Operations to Make Array Empty
//
// https://leetcode.com/problems/minimum-number-of-operations-to-make-array-empty/
//
// Question ID: 2870
// Difficult  : Medium
// Solve Date : 2024/01/04 23:34

#include <iosfwd>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2870. Minimum Number of Operations to Make Array Empty|:
//
// You are given a 0-indexed array |nums| consisting of positive integers.
// There are two types of operations that you can apply on the array any number
// of times:
//
//  • Choose two elements with equal values and delete them from the array.
//
//  • Choose three elements with equal values and delete them from the array.
// Return the minimum number of operations required to make the array empty, or
// |-1| if it is not possible.
//
//

LEETCODE_BEGIN_RESOLVING(2870, MinimumNumberOfOperationsToMakeArrayEmpty,
                         Solution);

class Solution {
public:
  int minOperations(vector<int> &nums) {
    unordered_map<int, int> freq;
    for (auto x : nums) {
      ++freq[x];
    }
    int res = 0;
    for (auto [x, cnt] : freq) {
      if (cnt == 1) {
        res = -1;
        break;
      }
      res += cnt / 3;
      if (cnt % 3) {
        ++res;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= nums.length <= 10⁵|
// * |1 <= nums[i] <= 10⁶|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [2,3,3,2,2,4,2,3,4]
// Output: 4
//
// We can apply the following operations to make the array empty:
// - Apply the first operation on the elements at indices 0 and 3. The resulting
// array is nums = [3,3,2,4,2,3,4].
// - Apply the first operation on the elements at indices 2 and 4. The resulting
// array is nums = [3,3,4,3,4].
// - Apply the second operation on the elements at indices 0, 1, and 3. The
// resulting array is nums = [4,4].
// - Apply the first operation on the elements at indices 0 and 1. The resulting
// array is nums = []. It can be shown that we cannot make the array empty in
// less than 4 operations.

LEETCODE_SOLUTION_UNITTEST(2870, MinimumNumberOfOperationsToMakeArrayEmpty,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 3, 3, 2, 2, 4, 2, 3, 4};
  int         expect   = 4;
  int         actual   = solution->minOperations(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [2,1,2,2,3,3]
// Output: -1
//
// It is impossible to empty the array.

LEETCODE_SOLUTION_UNITTEST(2870, MinimumNumberOfOperationsToMakeArrayEmpty,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 1, 2, 2, 3, 3};
  int         expect   = -1;
  int         actual   = solution->minOperations(nums);
  LCD_EXPECT_EQ(expect, actual);
}

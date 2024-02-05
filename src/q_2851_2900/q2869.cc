// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Minimum Operations to Collect Elements
//
// https://leetcode.com/problems/minimum-operations-to-collect-elements/
//
// Question ID: 2869
// Difficult  : Easy
// Solve Date : 2024/01/23 19:55

#include <iosfwd>
#include <unordered_set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2869. Minimum Operations to Collect Elements|:
//
// You are given an array |nums| of positive integers and an integer |k|.
// In one operation, you can remove the last element of the array and add it to
// your collection. Return the minimum number of operations needed to collect
// elements |1, 2, ..., k|.
//
//

LEETCODE_BEGIN_RESOLVING(2869, MinimumOperationsToCollectElements, Solution);

class Solution {
public:
  int minOperations(vector<int> &nums, int k) {
    int                res = 0;
    unordered_set<int> memo;
    for (auto it = nums.rbegin(); it != nums.rend(); ++it) {
      ++res;
      if (*it <= k) {
        memo.emplace(*it);
      }

      if (memo.size() == k) {
        break;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 50|
// * |1 <= nums[i] <= nums.length|
// * |1 <= k <= nums.length|
// * The input is generated such that you can collect elements |1, 2, ..., k|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [3,1,5,4,2], k = 2
// Output: 4
//
// After 4 operations, we collect elements 2, 4, 5, and 1, in this order. Our
// collection contains elements 1 and 2. Hence, the answer is 4.

LEETCODE_SOLUTION_UNITTEST(2869, MinimumOperationsToCollectElements,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 1, 5, 4, 2};
  int         k        = 2;
  int         expect   = 4;
  int         actual   = solution->minOperations(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [3,1,5,4,2], k = 5
// Output: 5
//
// After 5 operations, we collect elements 2, 4, 5, 1, and 3, in this order. Our
// collection contains elements 1 through 5. Hence, the answer is 5.

LEETCODE_SOLUTION_UNITTEST(2869, MinimumOperationsToCollectElements,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 1, 5, 4, 2};
  int         k        = 5;
  int         expect   = 5;
  int         actual   = solution->minOperations(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [3,2,5,3,1], k = 3
// Output: 4
//
// After 4 operations, we collect elements 1, 3, 5, and 2, in this order. Our
// collection contains elements 1 through 3. Hence, the answer is 4.

LEETCODE_SOLUTION_UNITTEST(2869, MinimumOperationsToCollectElements,
                           example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 2, 5, 3, 1};
  int         k        = 3;
  int         expect   = 4;
  int         actual   = solution->minOperations(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

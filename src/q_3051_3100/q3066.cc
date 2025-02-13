// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Minimum Operations to Exceed Threshold Value II
//
// https://leetcode.com/problems/minimum-operations-to-exceed-threshold-value-ii/
//
// Question ID: 3066
// Difficult  : Medium
// Solve Date : 2025/02/13 19:31

#include <iosfwd>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3066. Minimum Operations to Exceed Threshold Value II|:
//
// You are given a 0-indexed integer array |nums|, and an integer |k|.
// In one operation, you will:
//
//  • Take the two smallest integers |x| and |y| in |nums|.
//
//  • Remove |x| and |y| from |nums|.
//
//  • Add |min(x, y) * 2 + max(x, y)| anywhere in the array.
// Note that you can only apply the described operation if |nums| contains at
// least two elements. Return the minimum number of operations needed so that
// all elements of the array are greater than or equal to |k|.
//
//

LEETCODE_BEGIN_RESOLVING(3066, MinimumOperationsToExceedThresholdValueII,
                         Solution);

class Solution {
public:
  int minOperations(vector<int> &nums, int k) {
    priority_queue<int64_t, vector<int64_t>, greater<int64_t>> pq(nums.begin(),
                                                                  nums.end());
    int                                                        res = 0;

    while (pq.size() >= 2 && pq.top() < k) {
      auto fst = pq.top();
      pq.pop();
      auto sec = pq.top();
      pq.pop();

      pq.emplace(2 * fst + sec);
      ++res;
    }

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= nums.length <= 2 * 10⁵|
// * |1 <= nums[i] <= 10⁹|
// * |1 <= k <= 10⁹|
// * The input is generated such that an answer always exists. That is, there
// exists some sequence of operations after which all elements of the array are
// greater than or equal to |k|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [2,11,10,1,3], k = 10
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(3066, MinimumOperationsToExceedThresholdValueII,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 11, 10, 1, 3};
  int         k        = 10;
  int         expect   = 2;
  int         actual   = solution->minOperations(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,1,2,4,9], k = 20
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(3066, MinimumOperationsToExceedThresholdValueII,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 1, 2, 4, 9};
  int         k        = 20;
  int         expect   = 4;
  int         actual   = solution->minOperations(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: [999999999,999999999,999999999]
// 1000000000
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(3066, MinimumOperationsToExceedThresholdValueII,
                           extra_testcase_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {999999999, 999999999, 999999999};
  int         k        = 1000000000;
  int         expect   = 2;
  int         actual   = solution->minOperations(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

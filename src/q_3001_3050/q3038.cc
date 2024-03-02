// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Maximum Number of Operations With the Same Score I
//
// https://leetcode.com/problems/maximum-number-of-operations-with-the-same-score-i/
//
// Question ID: 3038
// Difficult  : Easy
// Solve Date : 2024/03/02 12:37

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3038. Maximum Number of Operations With the Same Score I|:
//
// Given an array of integers called |nums|, you can perform the following
// operation while |nums| contains at least |2| elements:
//
//  • Choose the first two elements of |nums| and delete them.
// The score of the operation is the sum of the deleted elements.
// Your task is to find the maximum number of operations that can be performed,
// such that all operations have the same score. Return the maximum number of
// operations possible that satisfy the condition mentioned above.
//
//

LEETCODE_BEGIN_RESOLVING(3038, MaximumNumberOfOperationsWithTheSameScoreI,
                         Solution);

class Solution {
public:
  int maxOperations(vector<int> &nums) {
    int sum = nums[0] + nums[1];
    int res = 1;
    int n   = nums.size();
    for (int i = 2; i < n; i += 2) {
      if (i + 1 < n && nums[i] + nums[i + 1] == sum) {
        ++res;
      } else {
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
// * |2 <= nums.length <= 100|
// * |1 <= nums[i] <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [3,2,1,4,5]
// Output: 2
//
// We perform the following operations:
// - Delete the first two elements, with score 3 + 2 = 5, nums = [1,4,5].
// - Delete the first two elements, with score 1 + 4 = 5, nums = [5].
// We are unable to perform any more operations as nums contain only 1 element.

LEETCODE_SOLUTION_UNITTEST(3038, MaximumNumberOfOperationsWithTheSameScoreI,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 2, 1, 4, 5};
  int         expect   = 2;
  int         actual   = solution->maxOperations(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [3,2,6,1,4]
// Output: 1
//
// We perform the following operations:
// - Delete the first two elements, with score 3 + 2 = 5, nums = [6,1,4].
// We are unable to perform any more operations as the score of the next
// operation isn't the same as the previous one.

LEETCODE_SOLUTION_UNITTEST(3038, MaximumNumberOfOperationsWithTheSameScoreI,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 2, 6, 1, 4};
  int         expect   = 1;
  int         actual   = solution->maxOperations(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: [3,2,1,4,1]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(3038, MaximumNumberOfOperationsWithTheSameScoreI,
                           extra_testcase_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 2, 1, 4, 1};
  int         expect   = 2;
  int         actual   = solution->maxOperations(nums);
  LCD_EXPECT_EQ(expect, actual);
}

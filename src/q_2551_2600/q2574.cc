// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Left and Right Sum Differences
//
// https://leetcode.com/problems/left-and-right-sum-differences/
//
// Question ID: 2574
// Difficult  : Easy
// Solve Date : 2023/03/10 13:23

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2574. Left and Right Sum Differences|:
//
// Given a 0-indexed integer array |nums|, find a 0-indexed integer array
// |answer| where:
//
//  • |answer.length == nums.length|.
//
//  • |answer[i] = |leftSum[i] - rightSum[i]||.
// Where:
//
//  • |leftSum[i]| is the sum of elements to the left of the index |i| in the
//  array |nums|. If there is no such element, |leftSum[i] = 0|.
//
//  • |rightSum[i]| is the sum of elements to the right of the index |i| in the
//  array |nums|. If there is no such element, |rightSum[i] = 0|.
// Return the array |answer|.
//

LEETCODE_BEGIN_RESOLVING(2574, LeftAndRightSumDifferences, Solution);

class Solution {
public:
  vector<int> leftRigthDifference(vector<int> &nums) {
    vector<int> right(nums.size(), 0);
    vector<int> res(nums.size(), 0);
    for (int i = 1; i < nums.size(); ++i) {
      res[i] = nums[i - 1] + res[i - 1];
    }
    for (int i = nums.size() - 2; i >= 0; --i) {
      right[i] = right[i + 1] + nums[i + 1];
      res[i]   = abs(res[i] - right[i]);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 1000|
// * |1 <= nums[i] <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [10,4,8,3]
// Output: [15,1,11,22]
//
// The array leftSum is [0,10,14,22] and the array rightSum is [15,11,3,0].
// The array answer is [|0 - 15|,|10 - 11|,|14 - 3|,|22 - 0|] = [15,1,11,22].

LEETCODE_SOLUTION_UNITTEST(2574, LeftAndRightSumDifferences, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {10, 4, 8, 3};
  vector<int> expect   = {15, 1, 11, 22};
  vector<int> actual   = solution->leftRigthDifference(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1]
// Output: [0]
//
// The array leftSum is [0] and the array rightSum is [0].
// The array answer is [|0 - 0|] = [0].

LEETCODE_SOLUTION_UNITTEST(2574, LeftAndRightSumDifferences, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1};
  vector<int> expect   = {0};
  vector<int> actual   = solution->leftRigthDifference(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Find Indices With Index and Value Difference I
//
// https://leetcode.com/problems/find-indices-with-index-and-value-difference-i/
//
// Question ID: 2903
// Difficult  : Easy
// Solve Date : 2024/01/28 16:43

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2903. Find Indices With Index and Value Difference I|:
//
// You are given a 0-indexed integer array |nums| having length |n|, an integer
// |indexDifference|, and an integer |valueDifference|. Your task is to find two
// indices |i| and |j|, both in the range |[0, n - 1]|, that satisfy the
// following conditions:
//
//  • |abs(i - j) >= indexDifference|, and
//
//  • |abs(nums[i] - nums[j]) >= valueDifference|
// Return an integer array |answer|, where |answer = [i, j]| if there are two
// such indices, and |answer = [-1, -1]| otherwise. If there are multiple
// choices for the two indices, return any of them. Note: |i| and |j| may be
// equal.
//
//

LEETCODE_BEGIN_RESOLVING(2903, FindIndicesWithIndexAndValueDifferenceI,
                         Solution);

class Solution {
public:
  vector<int> findIndices(vector<int> &nums, int indexDifference,
                          int valueDifference) {
    for (int i = 0; i < nums.size(); ++i) {
      for (int j = i + indexDifference; j < nums.size(); ++j) {
        if (abs(nums[j] - nums[i]) >= valueDifference) {
          return {i, j};
        }
      }
    }
    return {-1, -1};
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n == nums.length <= 100|
// * |0 <= nums[i] <= 50|
// * |0 <= indexDifference <= 100|
// * |0 <= valueDifference <= 50|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [5,1,4,1], indexDifference = 2, valueDifference = 4
// Output: [0,3]
//
// In this example, i = 0 and j = 3 can be selected.
// abs(0 - 3) >= 2 and abs(nums[0] - nums[3]) >= 4.
// Hence, a valid answer is [0,3].
// [3,0] is also a valid answer.

LEETCODE_SOLUTION_UNITTEST(2903, FindIndicesWithIndexAndValueDifferenceI,
                           example_1) {
  auto        solution        = MakeSolution();
  vector<int> nums            = {5, 1, 4, 1};
  int         indexDifference = 2;
  int         valueDifference = 4;
  vector<int> expect          = {0, 3};
  vector<int> actual =
      solution->findIndices(nums, indexDifference, valueDifference);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [2,1], indexDifference = 0, valueDifference = 0
// Output: [0,0]
//
// In this example, i = 0 and j = 0 can be selected.
// abs(0 - 0) >= 0 and abs(nums[0] - nums[0]) >= 0.
// Hence, a valid answer is [0,0].
// Other valid answers are [0,1], [1,0], and [1,1].

LEETCODE_SOLUTION_UNITTEST(2903, FindIndicesWithIndexAndValueDifferenceI,
                           example_2) {
  auto        solution        = MakeSolution();
  vector<int> nums            = {2, 1};
  int         indexDifference = 0;
  int         valueDifference = 0;
  vector<int> expect          = {0, 0};
  vector<int> actual =
      solution->findIndices(nums, indexDifference, valueDifference);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [1,2,3], indexDifference = 2, valueDifference = 4
// Output: [-1,-1]
//
// In this example, it can be shown that it is impossible to find two indices
// that satisfy both conditions. Hence, [-1,-1] is returned.

LEETCODE_SOLUTION_UNITTEST(2903, FindIndicesWithIndexAndValueDifferenceI,
                           example_3) {
  auto        solution        = MakeSolution();
  vector<int> nums            = {1, 2, 3};
  int         indexDifference = 2;
  int         valueDifference = 4;
  vector<int> expect          = {-1, -1};
  vector<int> actual =
      solution->findIndices(nums, indexDifference, valueDifference);
  LCD_EXPECT_EQ(expect, actual);
}

// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Apply Operations to an Array
//
// https://leetcode.com/problems/apply-operations-to-an-array/
//
// Question ID: 2460
// Difficult  : Easy
// Solve Date : 2023/03/03 14:31

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2460. Apply Operations to an Array|:
//
// You are given a 0-indexed array |nums| of size |n| consisting of non-negative
// integers. You need to apply |n - 1| operations to this array where, in the
// |iᵗʰ| operation (0-indexed), you will apply the following on the |iᵗʰ|
// element of |nums|:
//
//  • If |nums[i] == nums[i + 1]|, then multiply |nums[i]| by |2| and set
//  |nums[i + 1]| to |0|. Otherwise, you skip this operation.
// After performing all the operations, shift all the |0|'s to the end of the
// array.
//
//  • For example, the array |[1,0,2,0,0,1]| after shifting all its |0|'s to the
//  end, is |[1,2,1,0,0,0]|.
// Return the resulting array.
// Note that the operations are applied sequentially, not all at once.
//

LEETCODE_BEGIN_RESOLVING(2460, ApplyOperationsToAnArray, Solution);

class Solution {
public:
  vector<int> applyOperations(vector<int> &nums) {
    vector<int> res;
    for (int i = 0; i < nums.size() - 1; ++i) {
      if (nums[i] == nums[i + 1]) {
        nums[i + 1] = 0;
        nums[i] *= 2;
      }
    }
    for (auto x : nums) {
      if (x != 0) {
        res.emplace_back(x);
      }
    }
    res.resize(nums.size(), 0);
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |2 <= nums.length <= 2000|
// * |0 <= nums[i] <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,2,1,1,0]
// Output: [1,4,2,0,0,0]
//
// We do the following operations:
// - i = 0: nums[0] and nums[1] are not equal, so we skip this operation.
// - i = 1: nums[1] and nums[2] are equal, we multiply nums[1] by 2 and change
// nums[2] to 0. The array becomes [1,4,0,1,1,0].
// - i = 2: nums[2] and nums[3] are not equal, so we skip this operation.
// - i = 3: nums[3] and nums[4] are equal, we multiply nums[3] by 2 and change
// nums[4] to 0. The array becomes [1,4,0,2,0,0].
// - i = 4: nums[4] and nums[5] are equal, we multiply nums[4] by 2 and change
// nums[5] to 0. The array becomes [1,4,0,2,0,0]. After that, we shift the 0's
// to the end, which gives the array [1,4,2,0,0,0].

LEETCODE_SOLUTION_UNITTEST(2460, ApplyOperationsToAnArray, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 2, 1, 1, 0};
  vector<int> expect   = {1, 4, 2, 0, 0, 0};
  vector<int> actual   = solution->applyOperations(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [0,1]
// Output: [1,0]
//
// No operation can be applied, we just shift the 0 to the end.

LEETCODE_SOLUTION_UNITTEST(2460, ApplyOperationsToAnArray, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {0, 1};
  vector<int> expect   = {1, 0};
  vector<int> actual   = solution->applyOperations(nums);
  LCD_EXPECT_EQ(expect, actual);
}

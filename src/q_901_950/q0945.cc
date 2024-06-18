// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Minimum Increment to Make Array Unique
//
// https://leetcode.com/problems/minimum-increment-to-make-array-unique/
//
// Question ID: 945
// Difficult  : Medium
// Solve Date : 2024/06/14 14:05

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |945. Minimum Increment to Make Array Unique|:
//
// You are given an integer array |nums|. In one move, you can pick an index |i|
// where |0 <= i < nums.length| and increment |nums[i]| by |1|. Return the
// minimum number of moves to make every value in |nums| unique. The test cases
// are generated so that the answer fits in a 32-bit integer.
//
//

LEETCODE_BEGIN_RESOLVING(945, MinimumIncrementToMakeArrayUnique, Solution);

class Solution {
public:
  int minIncrementForUnique(vector<int> &nums) {
    sort(nums.begin(), nums.end());
    int res   = 0;
    int track = 0;
    for (auto x : nums) {
      track = max(track, x);
      res += track - x;
      ++track;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁵|
// * |0 <= nums[i] <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,2]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(945, MinimumIncrementToMakeArrayUnique, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 2};
  int         expect   = 1;
  int         actual   = solution->minIncrementForUnique(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [3,2,1,2,1,7]
// Output: 6
//

LEETCODE_SOLUTION_UNITTEST(945, MinimumIncrementToMakeArrayUnique, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3, 2, 1, 2, 1, 7};
  int         expect   = 6;
  int         actual   = solution->minIncrementForUnique(nums);
  LCD_EXPECT_EQ(expect, actual);
}

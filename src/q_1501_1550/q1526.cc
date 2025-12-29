// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Minimum Number of Increments on Subarrays to Form a Target Array
//
// https://leetcode.com/problems/minimum-number-of-increments-on-subarrays-to-form-a-target-array/
//
// Question ID: 1526
// Difficult  : Hard
// Solve Date : 2025/10/30 19:52

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1526. Minimum Number of Increments on Subarrays to Form a
// Target Array|:
//
// You are given an integer array |target|. You have an integer array |initial|
// of the same size as |target| with all elements initially zeros. In one
// operation you can choose any subarray from |initial| and increment each value
// by one. Return the minimum number of operations to form a |target| array from
// |initial|. The test cases are generated so that the answer fits in a 32-bit
// integer.
//
//

LEETCODE_BEGIN_RESOLVING(1526,
                         MinimumNumberOfIncrementsOnSubarraysToFormATargetArray,
                         Solution);

class Solution {
public:
  int minNumberOperations(vector<int> &target) {
    int res = target[0];
    for (int i = 1; i < target.size(); ++i) {
      if (target[i] > target[i - 1]) {
        res += target[i] - target[i - 1];
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= target.length <= 10⁵|
// * |1 <= target[i] <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: target = [1,2,3,2,1]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(
    1526, MinimumNumberOfIncrementsOnSubarraysToFormATargetArray, example_1) {
  auto        solution = MakeSolution();
  vector<int> target   = {1, 2, 3, 2, 1};
  int         expect   = 3;
  int         actual   = solution->minNumberOperations(target);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: target = [3,1,1,2]
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(
    1526, MinimumNumberOfIncrementsOnSubarraysToFormATargetArray, example_2) {
  auto        solution = MakeSolution();
  vector<int> target   = {3, 1, 1, 2};
  int         expect   = 4;
  int         actual   = solution->minNumberOperations(target);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: target = [3,1,5,4,2]
// Output: 7
//

LEETCODE_SOLUTION_UNITTEST(
    1526, MinimumNumberOfIncrementsOnSubarraysToFormATargetArray, example_3) {
  auto        solution = MakeSolution();
  vector<int> target   = {3, 1, 5, 4, 2};
  int         expect   = 7;
  int         actual   = solution->minNumberOperations(target);
  LCD_EXPECT_EQ(expect, actual);
}

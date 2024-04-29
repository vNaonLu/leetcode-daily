// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Minimum Number of Operations to Make Array XOR Equal to K
//
// https://leetcode.com/problems/minimum-number-of-operations-to-make-array-xor-equal-to-k/
//
// Question ID: 2997
// Difficult  : Medium
// Solve Date : 2024/04/29 21:19

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2997. Minimum Number of Operations to Make Array XOR Equal to
// K|:
//
// You are given a 0-indexed integer array |nums| and a positive integer |k|.
// You can apply the following operation on the array any number of times:
//
//  • Choose any element of the array and flip a bit in its binary
//  representation. Flipping a bit means changing a |0| to |1| or vice versa.
// Return the minimum number of operations required to make the bitwise |XOR| of
// all elements of the final array equal to |k|. Note that you can flip leading
// zero bits in the binary representation of elements. For example, for the
// number |(101)₂| you can flip the fourth bit and obtain |(1101)₂|.
//
//

LEETCODE_BEGIN_RESOLVING(2997, MinimumNumberOfOperationsToMakeArrayXOREqualToK,
                         Solution);

class Solution {
public:
  int minOperations(vector<int> &nums, int k) {
    for (auto x : nums) {
      k ^= x;
    }
    return __builtin_popcount(k);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁵|
// * |0 <= nums[i] <= 10⁶|
// * |0 <= k <= 10⁶|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [2,1,3,4], k = 1
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(2997,
                           MinimumNumberOfOperationsToMakeArrayXOREqualToK,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 1, 3, 4};
  int         k        = 1;
  int         expect   = 2;
  int         actual   = solution->minOperations(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [2,0,2,0], k = 0
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(2997,
                           MinimumNumberOfOperationsToMakeArrayXOREqualToK,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 0, 2, 0};
  int         k        = 0;
  int         expect   = 0;
  int         actual   = solution->minOperations(nums, k);
  LCD_EXPECT_EQ(expect, actual);
}

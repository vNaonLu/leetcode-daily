// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Sum of Squares of Special Elements
//
// https://leetcode.com/problems/sum-of-squares-of-special-elements/
//
// Question ID: 2778
// Difficult  : Easy
// Solve Date : 2023/12/29 21:14

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2778. Sum of Squares of Special Elements |:
//
// You are given a 1-indexed integer array |nums| of length |n|.
// An element |nums[i]| of |nums| is called special if |i| divides |n|, i.e. |n
// % i == 0|. Return the sum of the squares of all special elements of |nums|.
//
//

LEETCODE_BEGIN_RESOLVING(2778, SumOfSquaresOfSpecialElements, Solution);

class Solution {
public:
  int sumOfSquares(vector<int> &nums) {
    int n   = nums.size();
    int res = 0;
    for (int i = 0; i < n; ++i) {
      if (n % (i + 1) != 0) {
        continue;
      }

      res += nums[i] * nums[i];
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length == n <= 50|
// * |1 <= nums[i] <= 50|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,3,4]
// Output: 21
//
// There are exactly 3 special elements in nums: nums[1] since 1 divides 4,
// nums[2] since 2 divides 4, and nums[4] since 4 divides 4. Hence, the sum of
// the squares of all special elements of nums is nums[1] * nums[1] + nums[2] *
// nums[2] + nums[4] * nums[4] = 1 * 1 + 2 * 2 + 4 * 4 = 21.

LEETCODE_SOLUTION_UNITTEST(2778, SumOfSquaresOfSpecialElements, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 4};
  int         expect   = 21;
  int         actual   = solution->sumOfSquares(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [2,7,1,19,18,3]
// Output: 63
//
// There are exactly 4 special elements in nums: nums[1] since 1 divides 6,
// nums[2] since 2 divides 6, nums[3] since 3 divides 6, and nums[6] since 6
// divides 6. Hence, the sum of the squares of all special elements of nums is
// nums[1] * nums[1] + nums[2] * nums[2] + nums[3] * nums[3] + nums[6] * nums[6]
// = 2 * 2 + 7 * 7 + 1 * 1 + 3 * 3 = 63.

LEETCODE_SOLUTION_UNITTEST(2778, SumOfSquaresOfSpecialElements, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 7, 1, 19, 18, 3};
  int         expect   = 63;
  int         actual   = solution->sumOfSquares(nums);
  LCD_EXPECT_EQ(expect, actual);
}

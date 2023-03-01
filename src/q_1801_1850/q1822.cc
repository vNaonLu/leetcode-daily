// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Sign of the Product of an Array
//
// https://leetcode.com/problems/sign-of-the-product-of-an-array/
//
// Question ID: 1822
// Difficult  : Easy
// Solve Date : 2021/10/13 12:46

#include <array>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1822. Sign of the Product of an Array|:
//
// There is a function |signFunc(x)| that returns:
//
//  • |1| if |x| is positive.
//
//  • |-1| if |x| is negative.
//
//  • |0| if |x| is equal to |0|.
// You are given an integer array |nums|. Let |product| be the product of all
// values in the array |nums|. Return |signFunc(product)|.  
//

LEETCODE_BEGIN_RESOLVING(1822, SignOfTheProductOfAnArray, Solution);

class Solution {
public:
  int arraySign(vector<int> &nums) {
    bool res = true;
    for (const auto &x : nums) {
      if (x < 0)
        res = !res;
      else if (x == 0)
        return 0;
    }
    return res ? 1 : -1;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 1000|
// * |-100 <= nums[i] <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [-1,-2,-3,-4,3,2,1]
// Output: 1
//
// The product of all values in the array is 144, and signFunc(144) = 1

LEETCODE_SOLUTION_UNITTEST(1822, SignOfTheProductOfAnArray, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {-1, -2, -3, -4, 3, 2, 1};
  int         expect   = 1;
  int         actual   = solution->arraySign(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,5,0,2,-3]
// Output: 0
//
// The product of all values in the array is 0, and signFunc(0) = 0

LEETCODE_SOLUTION_UNITTEST(1822, SignOfTheProductOfAnArray, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 5, 0, 2, -3};
  int         expect   = 0;
  int         actual   = solution->arraySign(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [-1,1,-1,1,-1]
// Output: -1
//
// The product of all values in the array is -1, and signFunc(-1) = -1

LEETCODE_SOLUTION_UNITTEST(1822, SignOfTheProductOfAnArray, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {-1, 1, -1, 1, -1};
  int         expect   = -1;
  int         actual   = solution->arraySign(nums);
  LCD_EXPECT_EQ(expect, actual);
}

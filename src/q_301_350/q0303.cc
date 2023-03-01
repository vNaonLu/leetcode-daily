// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Range Sum Query - Immutable
//
// https://leetcode.com/problems/range-sum-query-immutable/
//
// Question ID: 303
// Difficult  : Easy
// Solve Date : 2022/04/25 18:49

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |303. Range Sum Query - Immutable|:
//
// Given an integer array |nums|, handle multiple queries of the following type:
//
//  1. Calculate the sum of the elements of |nums| between indices |left| and
//  |right| inclusive where |left <= right|.
// Implement the |NumArray| class:
//
//  • |NumArray(int[] nums)| Initializes the object with the integer array
//  |nums|.
//
//  • |int sumRange(int left, int right)| Returns the sum of the elements of
//  |nums| between indices |left| and |right| inclusive (i.e. |nums[left] +
//  nums[left + 1] + ... + nums[right]|).
//  
//

LEETCODE_BEGIN_RESOLVING(303, RangeSumQueryImmutable, NumArray);

class NumArray {
private:
  vector<int> sums;

public:
  NumArray(vector<int> &nums) : sums(nums.size() + 1, 0) {
    for (int i = 0; i < nums.size(); ++i) {
      sums[i + 1] = nums[i] + sums[i];
    }
  }

  int sumRange(int left, int right) { return sums[right + 1] - sums[left]; }
};

LEETCODE_END_RESOLVING(NumArray);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁴|
// * |-10⁵ <= nums[i] <= 10⁵|
// * |0 <= left <= right < nums.length|
// * At most |10⁴| calls will be made to |sumRange|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: ["NumArray", "sumRange", "sumRange", "sumRange"]
// [[[-2, 0, 3, -5, 2, -1]], [0, 2], [2, 5], [0, 5]]
// Output: [null, 1, -1, -3]
//
// NumArray numArray = new NumArray([-2, 0, 3, -5, 2, -1]);
// numArray.sumRange(0, 2); // return (-2) + 0 + 3 = 1
// numArray.sumRange(2, 5); // return 3 + (-5) + 2 + (-1) = -1
// numArray.sumRange(0, 5); // return (-2) + 0 + 3 + (-5) + 2 + (-1) = -3

LEETCODE_SOLUTION_UNITTEST(303, RangeSumQueryImmutable, example_1) {
  vector<int> s0_nums   = {-2, 0, 3, -5, 2, -1};
  auto        num_array = MakeNumArray(s0_nums);
  int         s1_left   = 0;
  int         s1_right  = 2;
  int         s1_expect = 1;
  int         s1_actual = num_array->sumRange(s1_left, s1_right);
  LCD_EXPECT_EQ(s1_expect, s1_actual);
  int s2_left   = 2;
  int s2_right  = 5;
  int s2_expect = -1;
  int s2_actual = num_array->sumRange(s2_left, s2_right);
  LCD_EXPECT_EQ(s2_expect, s2_actual);
  int s3_left   = 0;
  int s3_right  = 5;
  int s3_expect = -3;
  int s3_actual = num_array->sumRange(s3_left, s3_right);
  LCD_EXPECT_EQ(s3_expect, s3_actual);
}

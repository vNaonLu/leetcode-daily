// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Count Subarrays of Length Three With a Condition
//
// https://leetcode.com/problems/count-subarrays-of-length-three-with-a-condition/
//
// Question ID: 3392
// Difficult  : Easy
// Solve Date : 2025/04/27 13:28

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3392. Count Subarrays of Length Three With a Condition|:
//
// Given an integer array |nums|, return the number of subarrays of length 3
// such that the sum of the first and third numbers equals exactly half of the
// second number.
//
//

LEETCODE_BEGIN_RESOLVING(3392, CountSubarraysOfLengthThreeWithACondition,
                         Solution);

class Solution {
public:
  int countSubarrays(vector<int> &nums) {
    int res = 0;
    for (int i = 2; i < nums.size(); ++i) {
      if ((nums[i] + nums[i - 2]) << 1 == nums[i - 1]) {
        ++res;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |3 <= nums.length <= 100|
// * |-100 <= nums[i] <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,1,4,1]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(3392, CountSubarraysOfLengthThreeWithACondition,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 1, 4, 1};
  int         expect   = 1;
  int         actual   = solution->countSubarrays(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,1,1]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(3392, CountSubarraysOfLengthThreeWithACondition,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 1, 1};
  int         expect   = 0;
  int         actual   = solution->countSubarrays(nums);
  LCD_EXPECT_EQ(expect, actual);
}

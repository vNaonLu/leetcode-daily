// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Max Consecutive Ones
//
// https://leetcode.com/problems/max-consecutive-ones/
//
// Question ID: 485
// Difficult  : Easy
// Solve Date : 2021/09/21 08:00

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |485. Max Consecutive Ones|:
//
// Given a binary array |nums|, return the maximum number of consecutive |1|'s
// in the array.  
//

LEETCODE_BEGIN_RESOLVING(485, MaxConsecutiveOnes, Solution);

class Solution {
public:
  int findMaxConsecutiveOnes(vector<int> &nums) {
    int res = 0;
    int cnt = 0;
    for (const auto &n : nums) {
      if (n == 1) {
        res = max(res, ++cnt);
      } else {
        cnt = 0;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁵|
// * |nums[i]| is either |0| or |1|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,1,0,1,1,1]
// Output: 3
//
// The first two digits or the last three digits are consecutive 1s. The maximum
// number of consecutive 1s is 3.

LEETCODE_SOLUTION_UNITTEST(485, MaxConsecutiveOnes, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 1, 0, 1, 1, 1};
  int         expect   = 3;
  int         actual   = solution->findMaxConsecutiveOnes(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,0,1,1,0,1]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(485, MaxConsecutiveOnes, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 0, 1, 1, 0, 1};
  int         expect   = 2;
  int         actual   = solution->findMaxConsecutiveOnes(nums);
  LCD_EXPECT_EQ(expect, actual);
}

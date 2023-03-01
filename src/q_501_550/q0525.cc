// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Contiguous Array
//
// https://leetcode.com/problems/contiguous-array/
//
// Question ID: 525
// Difficult  : Medium
// Solve Date : 2022/02/04 12:02

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |525. Contiguous Array|:
//
// Given a binary array |nums|, return the maximum length of a contiguous
// subarray with an equal number of |0| and |1|.  
//

LEETCODE_BEGIN_RESOLVING(525, ContiguousArray, Solution);

class Solution {
public:
  int findMaxLength(vector<int> &nums) {
    vector<int> vs(2 * nums.size() + 1, -2);
    vs[nums.size()] = -1;
    int res = 0, cnt = 0;
    for (int i = 0; i < nums.size(); ++i) {
      cnt += nums[i] == 0 ? -1 : 1;
      if (vs[cnt + nums.size()] >= -1) {
        res = max(res, i - vs[cnt + nums.size()]);
      } else {
        vs[cnt + nums.size()] = i;
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
//  Input: nums = [0,1]
// Output: 2
//
// [0, 1] is the longest contiguous subarray with an equal number of 0 and 1.

LEETCODE_SOLUTION_UNITTEST(525, ContiguousArray, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {0, 1};
  int         expect   = 2;
  int         actual   = solution->findMaxLength(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [0,1,0]
// Output: 2
//
// [0, 1] (or [1, 0]) is a longest contiguous subarray with equal number of 0
// and 1.

LEETCODE_SOLUTION_UNITTEST(525, ContiguousArray, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {0, 1, 0};
  int         expect   = 2;
  int         actual   = solution->findMaxLength(nums);
  LCD_EXPECT_EQ(expect, actual);
}

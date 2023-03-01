// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Move Zeroes
//
// https://leetcode.com/problems/move-zeroes/
//
// Question ID: 283
// Difficult  : Easy
// Solve Date : 2021/09/07 08:00

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |283. Move Zeroes|:
//
// Given an integer array |nums|, move all |0|'s to the end of it while
// maintaining the relative order of the non-zero elements. Note that you must
// do this in-place without making a copy of the array.  
//

LEETCODE_BEGIN_RESOLVING(283, MoveZeroes, Solution);

class Solution {
public:
  void moveZeroes(vector<int> &nums) {
    int fillindex = -1;
    for (int i = 0; i < nums.size(); ++i) {
      if (nums[i] != 0) {
        nums[++fillindex] = nums[i];
      }
    }
    while (fillindex < nums.size() - 1) {
      nums[++fillindex] = 0;
    }
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10⁴|
// * |-2³¹ <= nums[i] <= 2³¹ - 1|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [0,1,0,3,12]
// Output: [1,3,12,0,0]
//

LEETCODE_SOLUTION_UNITTEST(283, MoveZeroes, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {0, 1, 0, 3, 12};
  vector<int> expect   = {1, 3, 12, 0, 0};
  solution->moveZeroes(nums);
  EXPECT_EQ(expect, nums);
}

// [Example #2]
//  Input: nums = [0]
// Output: [0]
//

LEETCODE_SOLUTION_UNITTEST(283, MoveZeroes, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {0};
  vector<int> expect   = {0};
  solution->moveZeroes(nums);
  EXPECT_EQ(expect, nums);
}

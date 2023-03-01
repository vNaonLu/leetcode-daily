// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Set Mismatch
//
// https://leetcode.com/problems/set-mismatch/
//
// Question ID: 645
// Difficult  : Easy
// Solve Date : 2022/10/02 12:30

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |645. Set Mismatch|:
//
// You have a set of integers |s|, which originally contains all the numbers
// from |1| to |n|. Unfortunately, due to some error, one of the numbers in |s|
// got duplicated to another number in the set, which results in repetition of
// one number and loss of another number. You are given an integer array |nums|
// representing the data status of this set after the error. Find the number
// that occurs twice and the number that is missing and return them in the form
// of an array.
//

LEETCODE_BEGIN_RESOLVING(645, SetMismatch, Solution);

class Solution {
public:
  vector<int> findErrorNums(vector<int> &nums) {
    auto dup     = (int)-1;
    auto missing = (int)1;
    for (auto x : nums) {
      if (nums[abs(x) - 1] < 0) {
        dup = abs(x);
      } else {
        nums[abs(x) - 1] *= -1;
      }
    }
    for (int i = 0; i < nums.size(); ++i) {
      if (nums[i] > 0) {
        missing = i + 1;
      }
    }
    return vector<int>{dup, missing};
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |2 <= nums.length <= 10⁴|
// * |1 <= nums[i] <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,2,4]
// Output: [2,3]
//

LEETCODE_SOLUTION_UNITTEST(645, SetMismatch, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 2, 4};
  vector<int> expect   = {2, 3};
  vector<int> actual   = solution->findErrorNums(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,1]
// Output: [1,2]
//

LEETCODE_SOLUTION_UNITTEST(645, SetMismatch, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 1};
  vector<int> expect   = {1, 2};
  vector<int> actual   = solution->findErrorNums(nums);
  LCD_EXPECT_EQ(expect, actual);
}

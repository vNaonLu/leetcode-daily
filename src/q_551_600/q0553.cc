// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Optimal Division
//
// https://leetcode.com/problems/optimal-division/
//
// Question ID: 553
// Difficult  : Medium
// Solve Date : 2024/04/23 20:02

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |553. Optimal Division|:
//
// You are given an integer array |nums|. The adjacent integers in |nums| will
// perform the float division.
//
//  • For example, for |nums = [2,3,4]|, we will evaluate the expression
//  |"2/3/4"|.
// However, you can add any number of parenthesis at any position to change the
// priority of operations. You want to add these parentheses such the value of
// the expression after the evaluation is maximum. Return the corresponding
// expression that has the maximum value in string format. Note: your expression
// should not contain redundant parenthesis.
//
//

LEETCODE_BEGIN_RESOLVING(553, OptimalDivision, Solution);

class Solution {
public:
  string optimalDivision(vector<int> &nums) {
    string res = to_string(nums.front());
    if (nums.size() == 1) {
      return res;
    }

    if (nums.size() == 2) {
      res += "/" + to_string(nums[1]);
      return res;
    }

    res += "/(" + to_string(nums[1]);
    for (int i = 2; i < nums.size(); ++i) {
      res += "/" + to_string(nums[i]);
    }
    res += ")";
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 10|
// * |2 <= nums[i] <= 1000|
// * There is only one optimal division for the given input.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1000,100,10,2]
// Output: "1000/(100/10/2)"
//

LEETCODE_SOLUTION_UNITTEST(553, OptimalDivision, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1000, 100, 10, 2};
  string      expect   = "1000/(100/10/2)";
  string      actual   = solution->optimalDivision(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [2,3,4]
// Output: "2/(3/4)"
//

LEETCODE_SOLUTION_UNITTEST(553, OptimalDivision, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 3, 4};
  string      expect   = "2/(3/4)";
  string      actual   = solution->optimalDivision(nums);
  LCD_EXPECT_EQ(expect, actual);
}

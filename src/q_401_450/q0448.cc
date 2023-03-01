// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Find All Numbers Disappeared in an Array
//
// https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/
//
// Question ID: 448
// Difficult  : Easy
// Solve Date : 2021/11/18 18:27

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |448. Find All Numbers Disappeared in an Array|:
//
// Given an array |nums| of |n| integers where |nums[i]| is in the range |[1,
// n]|, return an array of all the integers in the range |[1, n]| that do not
// appear in |nums|.  
//

LEETCODE_BEGIN_RESOLVING(448, FindAllNumbersDisappearedInAnArray, Solution);

class Solution {
public:
  vector<int> findDisappearedNumbers(vector<int> &nums) {
    vector<bool> appear(nums.size() + 1, false);
    for (const auto x : nums)
      appear[x] = true;
    vector<int> res;
    for (int i = 1; i < appear.size(); ++i) {
      if (!appear[i])
        res.emplace_back(i);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == nums.length|
// * |1 <= n <= 10⁵|
// * |1 <= nums[i] <= n|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [4,3,2,7,8,2,3,1]
// Output: [5,6]
//

LEETCODE_SOLUTION_UNITTEST(448, FindAllNumbersDisappearedInAnArray, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {4, 3, 2, 7, 8, 2, 3, 1};
  vector<int> expect   = {5, 6};
  vector<int> actual   = solution->findDisappearedNumbers(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,1]
// Output: [2]
//

LEETCODE_SOLUTION_UNITTEST(448, FindAllNumbersDisappearedInAnArray, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 1};
  vector<int> expect   = {2};
  vector<int> actual   = solution->findDisappearedNumbers(nums);
  LCD_EXPECT_EQ(expect, actual);
}

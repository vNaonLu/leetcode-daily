// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Create Target Array in the Given Order
//
// https://leetcode.com/problems/create-target-array-in-the-given-order/
//
// Question ID: 1389
// Difficult  : Easy
// Solve Date : 2023/06/10 16:29

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1389. Create Target Array in the Given Order|:
//
// Given two arrays of integers |nums| and |index|. Your task is to create
// target array under the following rules:
//
//  • Initially target array is empty.
//
//  • From left to right read nums[i] and index[i], insert at index |index[i]|
//  the value |nums[i]| in target array.
//
//  • Repeat the previous step until there are no elements to read in |nums| and
//  |index.|
// Return the target array.
// It is guaranteed that the insertion operations will be valid.
//
//

LEETCODE_BEGIN_RESOLVING(1389, CreateTargetArrayInTheGivenOrder, Solution);

class Solution {
public:
  vector<int> createTargetArray(vector<int> &nums, vector<int> &index) {
    vector<int> res;
    for (int i = 0; i < nums.size(); ++i) {
      auto idx = index[i];
      if (idx >= res.size()) {
        res.emplace_back(nums[i]);
      } else {
        res.insert(res.begin() + idx, nums[i]);
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length, index.length <= 100|
// * |nums.length == index.length|
// * |0 <= nums[i] <= 100|
// * |0 <= index[i] <= i|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [0,1,2,3,4], index = [0,1,2,2,1]
// Output: [0,4,1,3,2]
//
// nums index target
// 0 0 [0]
// 1 1 [0,1]
// 2 2 [0,1,2]
// 3 2 [0,1,3,2]
// 4 1 [0,4,1,3,2]

LEETCODE_SOLUTION_UNITTEST(1389, CreateTargetArrayInTheGivenOrder, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {0, 1, 2, 3, 4};
  vector<int> index    = {0, 1, 2, 2, 1};
  vector<int> expect   = {0, 4, 1, 3, 2};
  vector<int> actual   = solution->createTargetArray(nums, index);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,2,3,4,0], index = [0,1,2,3,0]
// Output: [0,1,2,3,4]
//
// nums index target
// 1 0 [1]
// 2 1 [1,2]
// 3 2 [1,2,3]
// 4 3 [1,2,3,4]
// 0 0 [0,1,2,3,4]

LEETCODE_SOLUTION_UNITTEST(1389, CreateTargetArrayInTheGivenOrder, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 4, 0};
  vector<int> index    = {0, 1, 2, 3, 0};
  vector<int> expect   = {0, 1, 2, 3, 4};
  vector<int> actual   = solution->createTargetArray(nums, index);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [1], index = [0]
// Output: [1]
//

LEETCODE_SOLUTION_UNITTEST(1389, CreateTargetArrayInTheGivenOrder, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1};
  vector<int> index    = {0};
  vector<int> expect   = {1};
  vector<int> actual   = solution->createTargetArray(nums, index);
  LCD_EXPECT_EQ(expect, actual);
}

// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Find All Duplicates in an Array
//
// https://leetcode.com/problems/find-all-duplicates-in-an-array/
//
// Question ID: 442
// Difficult  : Medium
// Solve Date : 2021/10/06 12:29

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |442. Find All Duplicates in an Array|:
//
// Given an integer array |nums| of length |n| where all the integers of |nums|
// are in the range |[1, n]| and each integer appears once or twice, return an
// array of all the integers that appears twice. You must write an algorithm
// that runs in  |O(n) |time and uses only constant extra space.  
//

LEETCODE_BEGIN_RESOLVING(442, FindAllDuplicatesInAnArray, Solution);

class Solution {
public:
  vector<int> findDuplicates(vector<int> &nums) {
    vector<int> res;
    for (const auto &x : nums) {
      int i = abs(x) - 1;
      if (nums[i] < 0)
        res.push_back(i + 1);
      nums[i] *= -1;
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
// * Each element in |nums| appears once or twice.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [4,3,2,7,8,2,3,1]
// Output: [2,3]
//

LEETCODE_SOLUTION_UNITTEST(442, FindAllDuplicatesInAnArray, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {4, 3, 2, 7, 8, 2, 3, 1};
  vector<int> expect   = {2, 3};
  vector<int> actual   = solution->findDuplicates(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,1,2]
// Output: [1]
//

LEETCODE_SOLUTION_UNITTEST(442, FindAllDuplicatesInAnArray, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 1, 2};
  vector<int> expect   = {1};
  vector<int> actual   = solution->findDuplicates(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [1]
// Output: []
//

LEETCODE_SOLUTION_UNITTEST(442, FindAllDuplicatesInAnArray, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1};
  vector<int> expect   = {};
  vector<int> actual   = solution->findDuplicates(nums);
  LCD_EXPECT_EQ(expect, actual);
}

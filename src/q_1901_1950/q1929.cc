// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Concatenation of Array
//
// https://leetcode.com/problems/concatenation-of-array/
//
// Question ID: 1929
// Difficult  : Easy
// Solve Date : 2022/02/10 16:31

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1929. Concatenation of Array|:
//
// Given an integer array |nums| of length |n|, you want to create an array
// |ans| of length |2n| where |ans[i] == nums[i]| and |ans[i + n] == nums[i]|
// for |0 <= i < n| (0-indexed). Specifically, |ans| is the concatenation of two
// |nums| arrays. Return the array |ans|.  
//

LEETCODE_BEGIN_RESOLVING(1929, ConcatenationOfArray, Solution);

class Solution {
public:
  vector<int> getConcatenation(vector<int> &nums) {
    vector<int> res(nums.size() * 2);
    for (int i = 0; i < nums.size(); ++i) {
      res[i] = res[i + nums.size()] = nums[i];
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == nums.length|
// * |1 <= n <= 1000|
// * |1 <= nums[i] <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,2,1]
// Output: [1,2,1,1,2,1]
//
// The array ans is formed as follows:
// - ans = [nums[0],nums[1],nums[2],nums[0],nums[1],nums[2]]
// - ans = [1,2,1,1,2,1]

LEETCODE_SOLUTION_UNITTEST(1929, ConcatenationOfArray, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 1};
  vector<int> expect   = {1, 2, 1, 1, 2, 1};
  vector<int> actual   = solution->getConcatenation(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,3,2,1]
// Output: [1,3,2,1,1,3,2,1]
//
// The array ans is formed as follows:
// - ans = [nums[0],nums[1],nums[2],nums[3],nums[0],nums[1],nums[2],nums[3]]
// - ans = [1,3,2,1,1,3,2,1]

LEETCODE_SOLUTION_UNITTEST(1929, ConcatenationOfArray, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 3, 2, 1};
  vector<int> expect   = {1, 3, 2, 1, 1, 3, 2, 1};
  vector<int> actual   = solution->getConcatenation(nums);
  LCD_EXPECT_EQ(expect, actual);
}

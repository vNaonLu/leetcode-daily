// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Shuffle the Array
//
// https://leetcode.com/problems/shuffle-the-array/
//
// Question ID: 1470
// Difficult  : Easy
// Solve Date : 2022/11/26 16:08

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1470. Shuffle the Array|:
//
// Given the array |nums| consisting of |2n| elements in the form
// |[x₁,x₂,...,xₙ,y₁,y₂,...,yₙ]|.
//
// Return the array in the form |[x₁,y₁,x₂,y₂,...,xₙ,yₙ]|.
//
//
//

LEETCODE_BEGIN_RESOLVING(1470, ShuffleTheArray, Solution);

class Solution {
public:
  vector<int> shuffle(vector<int> &nums, int n) {
    auto res  = vector<int>(2 * n);
    auto xbeg = nums.begin();
    auto ybeg = nums.begin() + n;
    auto iter = res.begin();
    while (iter != res.end()) {
      *iter++ = *xbeg++;
      *iter++ = *ybeg++;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n <= 500|
// * |nums.length == 2n|
// * |1 <= nums[i] <= 10^3|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [2,5,1,3,4,7], n = 3
// Output: [2,3,5,4,1,7]
//
// Since x₁=2, x₂=5, x₃=1, y₁=3, y₂=4, y₃=7 then the answer is [2,3,5,4,1,7].

LEETCODE_SOLUTION_UNITTEST(1470, ShuffleTheArray, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {2, 5, 1, 3, 4, 7};
  int         n        = 3;
  vector<int> expect   = {2, 3, 5, 4, 1, 7};
  vector<int> actual   = solution->shuffle(nums, n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [1,2,3,4,4,3,2,1], n = 4
// Output: [1,4,2,3,3,2,4,1]
//

LEETCODE_SOLUTION_UNITTEST(1470, ShuffleTheArray, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 2, 3, 4, 4, 3, 2, 1};
  int         n        = 4;
  vector<int> expect   = {1, 4, 2, 3, 3, 2, 4, 1};
  vector<int> actual   = solution->shuffle(nums, n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: nums = [1,1,2,2], n = 2
// Output: [1,2,1,2]
//

LEETCODE_SOLUTION_UNITTEST(1470, ShuffleTheArray, example_3) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 1, 2, 2};
  int         n        = 2;
  vector<int> expect   = {1, 2, 1, 2};
  vector<int> actual   = solution->shuffle(nums, n);
  LCD_EXPECT_EQ(expect, actual);
}

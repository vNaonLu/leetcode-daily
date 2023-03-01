// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Min Max Game
//
// https://leetcode.com/problems/min-max-game/
//
// Question ID: 2293
// Difficult  : Easy
// Solve Date : 2023/01/09 18:53

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2293. Min Max Game|:
//
// You are given a 0-indexed integer array |nums| whose length is a power of
// |2|. Apply the following algorithm on |nums|:
//
//  1. Let |n| be the length of |nums|. If |n == 1|, end the process. Otherwise,
//  create a new 0-indexed integer array |newNums| of length |n / 2|.
//
//  2. For every even index |i| where |0 <= i < n / 2|, assign the value of
//  |newNums[i]| as |min(nums[2 * i], nums[2 * i + 1])|.
//
//  3. For every odd index |i| where |0 <= i < n / 2|, assign the value of
//  |newNums[i]| as |max(nums[2 * i], nums[2 * i + 1])|.
//
//  4. Replace the array |nums| with |newNums|.
//
//  5. Repeat the entire process starting from step 1.
// Return the last number that remains in |nums| after applying the algorithm.
//

LEETCODE_BEGIN_RESOLVING(2293, MinMaxGame, Solution);

class Solution {
public:
  int minMaxGame(vector<int> &nums) {
    vector<int> tmp;
    while (nums.size() != 1) {
      for (int i = 0; i < nums.size(); ++ ++i) {
        tmp.emplace_back(((i / 2) & 1) == 0 ? min(nums[i], nums[i + 1])
                                            : max(nums[i], nums[i + 1]));
      }
      nums = std::move(tmp);
    }
    return nums.front();
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= nums.length <= 1024|
// * |1 <= nums[i] <= 10⁹|
// * |nums.length| is a power of |2|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [1,3,5,2,4,8,2,2]
// Output: 1
//
// The following arrays are the results of applying the algorithm repeatedly.
// First: nums = [1,5,4,2]
// Second: nums = [1,4]
// Third: nums = [1]
// 1 is the last remaining number, so we return 1.

LEETCODE_SOLUTION_UNITTEST(2293, MinMaxGame, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {1, 3, 5, 2, 4, 8, 2, 2};
  int         expect   = 1;
  int         actual   = solution->minMaxGame(nums);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [3]
// Output: 3
//
// 3 is already the last remaining number, so we return 3.

LEETCODE_SOLUTION_UNITTEST(2293, MinMaxGame, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {3};
  int         expect   = 3;
  int         actual   = solution->minMaxGame(nums);
  LCD_EXPECT_EQ(expect, actual);
}

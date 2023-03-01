// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Number of Arithmetic Triplets
//
// https://leetcode.com/problems/number-of-arithmetic-triplets/
//
// Question ID: 2367
// Difficult  : Easy
// Solve Date : 2023/03/01 17:24

#include <iosfwd>
#include <unordered_set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2367. Number of Arithmetic Triplets|:
//
// You are given a 0-indexed, strictly increasing integer array |nums| and a
// positive integer |diff|. A triplet |(i, j, k)| is an arithmetic triplet if
// the following conditions are met:
//
//  • |i < j < k|,
//
//  • |nums[j] - nums[i] == diff|, and
//
//  • |nums[k] - nums[j] == diff|.
// Return the number of unique arithmetic triplets.
//

LEETCODE_BEGIN_RESOLVING(2367, NumberOfArithmeticTriplets, Solution);

class Solution {
public:
  int arithmeticTriplets(vector<int> &nums, int diff) {
    int                res = 0;
    unordered_set<int> memo(nums.begin(), nums.end());
    for (auto x : nums) {
      if (memo.count(x + diff) && memo.count(x + diff + diff)) {
        ++res;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |3 <= nums.length <= 200|
// * |0 <= nums[i] <= 200|
// * |1 <= diff <= 50|
// * |nums| is strictly increasing.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [0,1,4,6,7,10], diff = 3
// Output: 2
//
// (1, 2, 4) is an arithmetic triplet because both 7 - 4 == 3 and 4 - 1 == 3.
// (2, 4, 5) is an arithmetic triplet because both 10 - 7 == 3 and 7 - 4 == 3.

LEETCODE_SOLUTION_UNITTEST(2367, NumberOfArithmeticTriplets, example_1) {
  auto        solution = MakeSolution();
  vector<int> nums     = {0, 1, 4, 6, 7, 10};
  int         diff     = 3;
  int         expect   = 2;
  int         actual   = solution->arithmeticTriplets(nums, diff);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [4,5,6,7,8,9], diff = 2
// Output: 2
//
// (0, 2, 4) is an arithmetic triplet because both 8 - 6 == 2 and 6 - 4 == 2.
// (1, 3, 5) is an arithmetic triplet because both 9 - 7 == 2 and 7 - 5 == 2.

LEETCODE_SOLUTION_UNITTEST(2367, NumberOfArithmeticTriplets, example_2) {
  auto        solution = MakeSolution();
  vector<int> nums     = {4, 5, 6, 7, 8, 9};
  int         diff     = 2;
  int         expect   = 2;
  int         actual   = solution->arithmeticTriplets(nums, diff);
  LCD_EXPECT_EQ(expect, actual);
}

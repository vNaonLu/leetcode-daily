// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Largest Combination With Bitwise AND Greater Than Zero
//
// https://leetcode.com/problems/largest-combination-with-bitwise-and-greater-than-zero/
//
// Question ID: 2275
// Difficult  : Medium
// Solve Date : 2024/11/07 20:51

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2275. Largest Combination With Bitwise AND Greater Than
// Zero|:
//
// The bitwise AND of an array |nums| is the bitwise AND of all integers in
// |nums|.
//
//  • For example, for |nums = [1, 5, 3]|, the bitwise AND is equal to |1 & 5 &
//  3 = 1|.
//
//  • Also, for |nums = [7]|, the bitwise AND is |7|.
// You are given an array of positive integers |candidates|. Evaluate the
// bitwise AND of every combination of numbers of |candidates|. Each number in
// |candidates| may only be used once in each combination. Return the size of
// the largest combination of |candidates| with a bitwise AND greater than |0|.
//
//

LEETCODE_BEGIN_RESOLVING(2275, LargestCombinationWithBitwiseANDGreaterThanZero,
                         Solution);

class Solution {
public:
  int largestCombination(vector<int> &candidates) {
    int res = 0;
    for (char b = 0; b <= 24; ++b) {
      int bs = 0;
      for (auto x : candidates) {
        bs += (x >> b & 1);
      }
      res = max(res, bs);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= candidates.length <= 10⁵|
// * |1 <= candidates[i] <= 10⁷|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: candidates = [16,17,71,62,12,24,14]
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(2275,
                           LargestCombinationWithBitwiseANDGreaterThanZero,
                           example_1) {
  auto        solution   = MakeSolution();
  vector<int> candidates = {16, 17, 71, 62, 12, 24, 14};
  int         expect     = 4;
  int         actual     = solution->largestCombination(candidates);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: candidates = [8,8]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(2275,
                           LargestCombinationWithBitwiseANDGreaterThanZero,
                           example_2) {
  auto        solution   = MakeSolution();
  vector<int> candidates = {8, 8};
  int         expect     = 2;
  int         actual     = solution->largestCombination(candidates);
  LCD_EXPECT_EQ(expect, actual);
}

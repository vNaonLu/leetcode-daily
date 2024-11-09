// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Minimum Array End
//
// https://leetcode.com/problems/minimum-array-end/
//
// Question ID: 3133
// Difficult  : Medium
// Solve Date : 2024/11/09 15:35

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3133. Minimum Array End|:
//
// You are given two integers |n| and |x|. You have to construct an array of
// positive integers |nums| of size |n| where for every |0 <= i < n - 1|,
// |nums[i + 1]| is greater than |nums[i]|, and the result of the bitwise |AND|
// operation between all elements of |nums| is |x|. Return the minimum possible
// value of |nums[n - 1]|.
//
//

LEETCODE_BEGIN_RESOLVING(3133, MinimumArrayEnd, Solution);

class Solution {
public:
  long long minEnd(int n, int x) {
    int64_t res    = x;
    int64_t remain = n - 1;
    int64_t pos    = 1;
    while (remain) {
      if (!(x & pos)) {
        res |= (remain & 1) * pos;
        remain >>= 1;
      }
      pos <<= 1;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n, x <= 10⁸|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 3, x = 4
// Output: 6
//

LEETCODE_SOLUTION_UNITTEST(3133, MinimumArrayEnd, example_1) {
  auto      solution = MakeSolution();
  int       n        = 3;
  int       x        = 4;
  long long expect   = 6;
  long long actual   = solution->minEnd(n, x);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 2, x = 7
// Output: 15
//

LEETCODE_SOLUTION_UNITTEST(3133, MinimumArrayEnd, example_2) {
  auto      solution = MakeSolution();
  int       n        = 2;
  int       x        = 7;
  long long expect   = 15;
  long long actual   = solution->minEnd(n, x);
  LCD_EXPECT_EQ(expect, actual);
}

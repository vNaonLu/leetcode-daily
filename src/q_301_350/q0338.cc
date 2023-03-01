// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Counting Bits
//
// https://leetcode.com/problems/counting-bits/
//
// Question ID: 338
// Difficult  : Easy
// Solve Date : 2021/10/06 00:06

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |338. Counting Bits|:
//
// Given an integer |n|, return an array |ans| of length |n + 1| such that for
// each |i| ( |0 <= i <= n|), |ans[i]| is the number of |1|'s in the binary
// representation of |i|.  
//

LEETCODE_BEGIN_RESOLVING(338, CountingBits, Solution);

class Solution {
public:
  vector<int> countBits(int n) {
    vector<int> res(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
      int tmp = i;
      while (tmp != 0) {
        tmp &= tmp - 1;
        ++res[i];
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |0 <= n <= 10⁵|
// * It is very easy to come up with a solution with a runtime of |O(n log n)|.
// Can you do it in linear time |O(n)| and possibly in a single pass?
// * Can you do it without using any built-in function (i.e., like
// |__builtin_popcount| in C++)?
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 2
// Output: [0,1,1]
//
// 0 --> 0
// 1 --> 1
// 2 --> 10

LEETCODE_SOLUTION_UNITTEST(338, CountingBits, example_1) {
  auto        solution = MakeSolution();
  int         n        = 2;
  vector<int> expect   = {0, 1, 1};
  vector<int> actual   = solution->countBits(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 5
// Output: [0,1,1,2,1,2]
//
// 0 --> 0
// 1 --> 1
// 2 --> 10
// 3 --> 11
// 4 --> 100
// 5 --> 101

LEETCODE_SOLUTION_UNITTEST(338, CountingBits, example_2) {
  auto        solution = MakeSolution();
  int         n        = 5;
  vector<int> expect   = {0, 1, 1, 2, 1, 2};
  vector<int> actual   = solution->countBits(n);
  LCD_EXPECT_EQ(expect, actual);
}

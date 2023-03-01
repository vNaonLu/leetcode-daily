// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Integer Replacement
//
// https://leetcode.com/problems/integer-replacement/
//
// Question ID: 397
// Difficult  : Medium
// Solve Date : 2022/02/11 23:41

#include <iosfwd>
#include <queue>
#include <set>
#include <unordered_set>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |397. Integer Replacement|:
//
// Given a positive integer |n|, you can apply one of the following operations:
//
//  1. If |n| is even, replace |n| with |n / 2|.
//
//  2. If |n| is odd, replace |n| with either |n + 1| or |n - 1|.
// Return the minimum number of operations needed for |n| to become |1|.
//  
//

LEETCODE_BEGIN_RESOLVING(397, IntegerReplacement, Solution);

class Solution {
public:
  int integerReplacement(int n) {
    unordered_set<uint32_t> memos;
    queue<uint32_t>         step;
    int                     res = 0;
    step.push(n);
    memos.insert(n);
    while (step.empty() != true) {
      queue<uint32_t> curr = move(step);
      while (curr.empty() != true) {
        auto x = curr.front();
        curr.pop();
        if (x == 1)
          return res;
        if (x & 1) {
          if (memos.find(x + 1) == memos.end()) {
            memos.insert(x + 1);
            step.push(x + 1);
          }
          if (memos.find(x - 1) == memos.end()) {
            memos.insert(x - 1);
            step.push(x - 1);
          }
        } else {
          step.push(x / 2);
        }
      }
      ++res;
    }
    return -1;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n <= 2³¹ - 1|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 8
// Output: 3
//
// 8 -> 4 -> 2 -> 1

LEETCODE_SOLUTION_UNITTEST(397, IntegerReplacement, example_1) {
  auto solution = MakeSolution();
  int  n        = 8;
  int  expect   = 3;
  int  actual   = solution->integerReplacement(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 7
// Output: 4
//
// 7 -> 8 -> 4 -> 2 -> 1
// or 7 -> 6 -> 3 -> 2 -> 1

LEETCODE_SOLUTION_UNITTEST(397, IntegerReplacement, example_2) {
  auto solution = MakeSolution();
  int  n        = 7;
  int  expect   = 4;
  int  actual   = solution->integerReplacement(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: n = 4
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(397, IntegerReplacement, example_3) {
  auto solution = MakeSolution();
  int  n        = 4;
  int  expect   = 2;
  int  actual   = solution->integerReplacement(n);
  LCD_EXPECT_EQ(expect, actual);
}

// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Next Greater Element III
//
// https://leetcode.com/problems/next-greater-element-iii/
//
// Question ID: 556
// Difficult  : Medium
// Solve Date : 2022/05/05 18:24

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |556. Next Greater Element III|:
//
// Given a positive integer |n|, find the smallest integer which has exactly the
// same digits existing in the integer |n| and is greater in value than |n|. If
// no such positive integer exists, return |-1|. Note that the returned integer
// should fit in 32-bit integer, if there is a valid answer but it does not fit
// in 32-bit integer, return |-1|.  
//

LEETCODE_BEGIN_RESOLVING(556, NextGreaterElementIII, Solution);

class Solution {
public:
  int nextGreaterElement(int n) {
    vector<int> dig;
    while (n != 0) {
      dig.emplace_back(n % 10);
      n /= 10;
    }
    int i = 1;
    while (i < dig.size() && dig[i - 1] <= dig[i]) {
      ++i;
    }

    if (i != dig.size()) {
      for (int j = 0; j < i; ++j) {
        if (dig[j] > dig[i]) {
          swap(dig[i], dig[j]);
          break;
        }
      }

      reverse(dig.begin(), dig.begin() + i);

      int64_t res = 0;
      for (auto it = dig.rbegin(); it != dig.rend(); ++it) {
        res = 10 * res + *it;
      }

      if (res <= 0x7fffffff) {
        return res;
      }
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
//  Input: n = 12
// Output: 21
//

LEETCODE_SOLUTION_UNITTEST(556, NextGreaterElementIII, example_1) {
  auto solution = MakeSolution();
  int  n        = 12;
  int  expect   = 21;
  int  actual   = solution->nextGreaterElement(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 21
// Output: -1
//

LEETCODE_SOLUTION_UNITTEST(556, NextGreaterElementIII, example_2) {
  auto solution = MakeSolution();
  int  n        = 21;
  int  expect   = -1;
  int  actual   = solution->nextGreaterElement(n);
  LCD_EXPECT_EQ(expect, actual);
}

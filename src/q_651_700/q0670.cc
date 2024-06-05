// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Maximum Swap
//
// https://leetcode.com/problems/maximum-swap/
//
// Question ID: 670
// Difficult  : Medium
// Solve Date : 2024/06/05 19:49

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |670. Maximum Swap|:
//
// You are given an integer |num|. You can swap two digits at most once to get
// the maximum valued number. Return the maximum valued number you can get.
//
//

LEETCODE_BEGIN_RESOLVING(670, MaximumSwap, Solution);

class Solution {
public:
  int maximumSwap(int num) {
    string s   = to_string(num);
    string st  = s;
    int    res = num;
    int    n   = s.size();
    for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        swap(st[i], st[j]);
        int x = stoi(st);
        res   = max(res, x);
        swap(st[i], st[j]);
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |0 <= num <= 10⁸|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: num = 2736
// Output: 7236
//

LEETCODE_SOLUTION_UNITTEST(670, MaximumSwap, example_1) {
  auto solution = MakeSolution();
  int  num      = 2736;
  int  expect   = 7236;
  int  actual   = solution->maximumSwap(num);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: num = 9973
// Output: 9973
//

LEETCODE_SOLUTION_UNITTEST(670, MaximumSwap, example_2) {
  auto solution = MakeSolution();
  int  num      = 9973;
  int  expect   = 9973;
  int  actual   = solution->maximumSwap(num);
  LCD_EXPECT_EQ(expect, actual);
}

// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Check Balanced String
//
// https://leetcode.com/problems/check-balanced-string/
//
// Question ID: 3340
// Difficult  : Easy
// Solve Date : 2024/11/08 20:04

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3340. Check Balanced String|:
//
//

LEETCODE_BEGIN_RESOLVING(3340, CheckBalancedString, Solution);

class Solution {
public:
  bool isBalanced(string num) {
    int  odd = 0;
    int  evn = 0;
    auto beg = num.begin();
    while (beg != num.end()) {
      odd += *beg++ - '0';
      if (beg != num.end()) {
        evn += *beg++ - '0';
      }
    }
    return odd == evn;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= num.length <= 100|
// * |num| consists of digits only
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: nums = [2,3,5,7]
// Output: [-1,1,4,3]
//

LEETCODE_SOLUTION_UNITTEST(3340, CheckBalancedString, example_1) {
  auto   solution = MakeSolution();
  string num      = "1234";
  bool   expect   = false;
  bool   actual   = solution->isBalanced(num);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: nums = [11,13,31]
// Output: [9,12,15]
//

LEETCODE_SOLUTION_UNITTEST(3340, CheckBalancedString, example_2) {
  auto   solution = MakeSolution();
  string num      = "24123";
  bool   expect   = true;
  bool   actual   = solution->isBalanced(num);
  LCD_EXPECT_EQ(expect, actual);
}

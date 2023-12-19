// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Check if The Number is Fascinating
//
// https://leetcode.com/problems/check-if-the-number-is-fascinating/
//
// Question ID: 2729
// Difficult  : Easy
// Solve Date : 2023/12/19 20:11

#include <iosfwd>
#include <set>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2729. Check if The Number is Fascinating|:
//
// You are given an integer |n| that consists of exactly |3| digits.
// We call the number |n| fascinating if, after the following modification, the
// resulting number contains all the digits from |1| to |9| exactly once and
// does not contain any |0|'s:
//
//  • Concatenate |n| with the numbers |2 * n| and |3 * n|.
// Return |true| if |n| is fascinating, or |false| otherwise.
// Concatenating two numbers means joining them together. For example, the
// concatenation of |121| and |371| is |121371|.
//
//

LEETCODE_BEGIN_RESOLVING(2729, CheckIfTheNumberIsFascinating, Solution);

class Solution {
public:
  bool isFascinating(int n) {
    string s1 = to_string(n) + to_string(n * 2) + to_string(n * 3);
    string s2 = "123456789";
    return set(s1.begin(), s1.end()) == set(s2.begin(), s2.end()) &&
           s1.size() == 9;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |100 <= n <= 999|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 192
// Output: true
//
// We concatenate the numbers n = 192 and 2 * n = 384 and 3 * n = 576. The
// resulting number is 192384576. This number contains all the digits from 1 to
// 9 exactly once.

LEETCODE_SOLUTION_UNITTEST(2729, CheckIfTheNumberIsFascinating, example_1) {
  auto solution = MakeSolution();
  int  n        = 192;
  bool expect   = true;
  bool actual   = solution->isFascinating(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 100
// Output: false
//
// We concatenate the numbers n = 100 and 2 * n = 200 and 3 * n = 300. The
// resulting number is 100200300. This number does not satisfy any of the
// conditions.

LEETCODE_SOLUTION_UNITTEST(2729, CheckIfTheNumberIsFascinating, example_2) {
  auto solution = MakeSolution();
  int  n        = 100;
  bool expect   = false;
  bool actual   = solution->isFascinating(n);
  LCD_EXPECT_EQ(expect, actual);
}

// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Max Difference You Can Get From Changing an Integer
//
// https://leetcode.com/problems/max-difference-you-can-get-from-changing-an-integer/
//
// Question ID: 1432
// Difficult  : Medium
// Solve Date : 2025/06/15 13:04

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1432. Max Difference You Can Get From Changing an Integer|:
//
// You are given an integer |num|. You will apply the following steps to |num|
// two separate times:
//
//  • Pick a digit |x (0 <= x <= 9)|.
//
//  • Pick another digit |y (0 <= y <= 9)|. Note |y| can be equal to |x|.
//
//  • Replace all the occurrences of |x| in the decimal representation of |num|
//  by |y|.
// Let |a| and |b| be the two results from applying the operation to |num|
// independently. Return the max difference between |a| and |b|. Note that
// neither |a| nor |b| may have any leading zeros, and must not be 0.
//
//

LEETCODE_BEGIN_RESOLVING(1432, MaxDifferenceYouCanGetFromChangingAnInteger,
                         Solution);

class Solution {
public:
  int maxDiff(int num) {
    string str1 = to_string(num);
    string str2 = str1;
    int    n    = str1.size();
    int    i;
    for (i = 0; i < n; i++) {
      if (str1[i] != '9')
        break;
    }
    char ele1 = str1[i];
    for (int k = 0; k < n; k++) {
      if (str1[k] == ele1)
        str1[k] = '9';
    }
    char ele2    = str2[0];
    char replace = '1';
    if (ele2 == '1') {
      for (int k = 1; k < n; k++) {
        if (str2[k] != '0' && str2[k] != '1') {
          ele2    = str2[k];
          replace = '0';
          break;
        }
      }
    }
    for (int k = 0; k < n; k++) {
      if (str2[k] == ele2)
        str2[k] = replace;
    }

    return stoi(str1) - stoi(str2);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= num <= 10⁸|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: num = 555
// Output: 888
//

LEETCODE_SOLUTION_UNITTEST(1432, MaxDifferenceYouCanGetFromChangingAnInteger,
                           example_1) {
  auto solution = MakeSolution();
  int  num      = 555;
  int  expect   = 888;
  int  actual   = solution->maxDiff(num);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: num = 9
// Output: 8
//

LEETCODE_SOLUTION_UNITTEST(1432, MaxDifferenceYouCanGetFromChangingAnInteger,
                           example_2) {
  auto solution = MakeSolution();
  int  num      = 9;
  int  expect   = 8;
  int  actual   = solution->maxDiff(num);
  LCD_EXPECT_EQ(expect, actual);
}

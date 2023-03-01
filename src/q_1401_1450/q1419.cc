// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimum Number of Frogs Croaking
//
// https://leetcode.com/problems/minimum-number-of-frogs-croaking/
//
// Question ID: 1419
// Difficult  : Medium
// Solve Date : 2022/02/10 18:03

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1419. Minimum Number of Frogs Croaking|:
//
// You are given the string |croakOfFrogs|, which represents a combination of
// the string |"croak"| from different frogs, that is, multiple frogs can croak
// at the same time, so multiple |"croak"| are mixed. Return the minimum number
// of different frogs to finish all the croaks in the given string. A valid
// |"croak"| means a frog is printing five letters |'c'|, |'r'|, |'o'|, |'a'|,
// and |'k'| sequentially. The frogs have to print all five letters to finish a
// croak. If the given string is not a combination of a valid |"croak"| return
// |-1|.  
//

LEETCODE_BEGIN_RESOLVING(1419, MinimumNumberOfFrogsCroaking, Solution);

class Solution {
public:
  int minNumberOfFrogs(string croakOfFrogs) {
    if (croakOfFrogs.size() % 5 != 0 || croakOfFrogs.back() != 'k')
      return -1;
    vector<int> croak(5, 0);
    for (const auto &c : croakOfFrogs) {
      switch (c) {
      case 'c':
        ++croak[0];
        if (croak[4] != 0)
          --croak[4];
        break;
      case 'r':
        ++croak[1];
        if (croak[0] <= 0)
          return -1;
        --croak[0];
        break;
      case 'o':
        ++croak[2];
        if (croak[1] <= 0)
          return -1;
        --croak[1];
        break;
      case 'a':
        ++croak[3];
        if (croak[2] <= 0)
          return -1;
        --croak[2];
        break;
      case 'k':
        ++croak[4];
        if (croak[3] <= 0)
          return -1;
        --croak[3];
        break;
      default:
        return -1;
      }
    }
    for (int i = 0; i < 4; ++i)
      if (croak[i] != 0)
        return -1;
    return croak.back();
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= croakOfFrogs.length <= 10⁵|
// * |croakOfFrogs| is either |'c'|, |'r'|, |'o'|, |'a'|, or |'k'|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: croakOfFrogs = "croakcroak"
// Output: 1
//
// One frog yelling "croak" twice.

LEETCODE_SOLUTION_UNITTEST(1419, MinimumNumberOfFrogsCroaking, example_1) {
  auto   solution     = MakeSolution();
  string croakOfFrogs = "croakcroak";
  int    expect       = 1;
  int    actual       = solution->minNumberOfFrogs(croakOfFrogs);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: croakOfFrogs = "crcoakroak"
// Output: 2
//
// The minimum number of frogs is two.
// The first frog could yell "crcoakroak".
// The second frog could yell later "crcoakroak".

LEETCODE_SOLUTION_UNITTEST(1419, MinimumNumberOfFrogsCroaking, example_2) {
  auto   solution     = MakeSolution();
  string croakOfFrogs = "crcoakroak";
  int    expect       = 2;
  int    actual       = solution->minNumberOfFrogs(croakOfFrogs);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: croakOfFrogs = "croakcrook"
// Output: -1
//
// The given string is an invalid combination of "croak" from different frogs.

LEETCODE_SOLUTION_UNITTEST(1419, MinimumNumberOfFrogsCroaking, example_3) {
  auto   solution     = MakeSolution();
  string croakOfFrogs = "croakcrook";
  int    expect       = -1;
  int    actual       = solution->minNumberOfFrogs(croakOfFrogs);
  LCD_EXPECT_EQ(expect, actual);
}

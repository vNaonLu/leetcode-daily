// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Minimum Number of Chairs in a Waiting Room
//
// https://leetcode.com/problems/minimum-number-of-chairs-in-a-waiting-room/
//
// Question ID: 3168
// Difficult  : Easy
// Solve Date : 2024/06/02 12:47

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3168. Minimum Number of Chairs in a Waiting Room|:
//
// You are given a string |s|. Simulate events at each second |i|:
//
//  • If |s[i] == 'E'|, a person enters the waiting room and takes one of the
//  chairs in it.
//
//  • If |s[i] == 'L'|, a person leaves the waiting room, freeing up a chair.
// Return the minimum number of chairs needed so that a chair is available for
// every person who enters the waiting room given that it is initially empty.
//
//

LEETCODE_BEGIN_RESOLVING(3168, MinimumNumberOfChairsInAWaitingRoom, Solution);

class Solution {
public:
  int minimumChairs(string s) {
    int res = 0;
    int cur = 0;
    for (auto c : s) {
      if (c == 'L') {
        --cur;
      } else {
        ++cur;
        res = max(res, cur);
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 50|
// * |s| consists only of the letters |'E'| and |'L'|.
// * |s| represents a valid sequence of entries and exits.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "EEEEEEE"
// Output: 7
//

LEETCODE_SOLUTION_UNITTEST(3168, MinimumNumberOfChairsInAWaitingRoom,
                           example_1) {
  auto   solution = MakeSolution();
  string s        = "EEEEEEE";
  int    expect   = 7;
  int    actual   = solution->minimumChairs(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "ELELEEL"
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(3168, MinimumNumberOfChairsInAWaitingRoom,
                           example_2) {
  auto   solution = MakeSolution();
  string s        = "ELELEEL";
  int    expect   = 2;
  int    actual   = solution->minimumChairs(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "ELEELEELLL"
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(3168, MinimumNumberOfChairsInAWaitingRoom,
                           example_3) {
  auto   solution = MakeSolution();
  string s        = "ELEELEELLL";
  int    expect   = 3;
  int    actual   = solution->minimumChairs(s);
  LCD_EXPECT_EQ(expect, actual);
}

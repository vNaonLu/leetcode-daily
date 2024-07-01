// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Swap Adjacent in LR String
//
// https://leetcode.com/problems/swap-adjacent-in-lr-string/
//
// Question ID: 777
// Difficult  : Medium
// Solve Date : 2024/07/01 20:37

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |777. Swap Adjacent in LR String|:
//
// In a string composed of |'L'|, |'R'|, and |'X'| characters, like
// |"RXXLRXRXL"|, a move consists of either replacing one occurrence of |"XL"|
// with |"LX"|, or replacing one occurrence of |"RX"| with |"XR"|. Given the
// starting string |start| and the ending string |end|, return |True| if and
// only if there exists a sequence of moves to transform one string to the
// other.
//
//

LEETCODE_BEGIN_RESOLVING(777, SwapAdjacentInLRString, Solution);

class Solution {
public:
  bool canTransform(string start, string end) {
    int i = 0;
    int j = 0;
    while (i < start.size() && j < end.size()) {
      while (start[i] == 'X') {
        ++i;
      }
      while (end[j] == 'X') {
        ++j;
      }
      if (start[i] != end[j]) {
        return false;
      }

      if (start[i] == 'R' && i > j) {
        return false;
      }

      if (start[i] == 'L' && i < j) {
        return false;
      }

      ++i;
      ++j;
    }
    while (i < start.size() && start[i] == 'X') {
      ++i;
    }
    while (j < end.size() && end[j] == 'X') {
      ++j;
    }

    return i == j;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= start.length <= 10⁴|
// * |start.length == end.length|
// * Both |start| and |end| will only consist of characters in |'L'|, |'R'|, and
// |'X'|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: start = "RXXLRXRXL", end = "XRLXXRRLX"
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(777, SwapAdjacentInLRString, example_1) {
  auto   solution = MakeSolution();
  string start    = "RXXLRXRXL";
  string end      = "XRLXXRRLX";
  bool   expect   = true;
  bool   actual   = solution->canTransform(start, end);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: start = "X", end = "L"
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(777, SwapAdjacentInLRString, example_2) {
  auto   solution = MakeSolution();
  string start    = "X";
  string end      = "L";
  bool   expect   = false;
  bool   actual   = solution->canTransform(start, end);
  LCD_EXPECT_EQ(expect, actual);
}

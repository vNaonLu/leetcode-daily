// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Check if All A's Appears Before All B's
//
// https://leetcode.com/problems/check-if-all-as-appears-before-all-bs/
//
// Question ID: 2124
// Difficult  : Easy
// Solve Date : 2023/04/12 18:56

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2124. Check if All A's Appears Before All B's|:
//
// Given a string |s| consisting of only the characters |'a'| and |'b'|, return
// |true| if every |'a'| appears before every |'b'| in the string. Otherwise,
// return |false|.
//
//

LEETCODE_BEGIN_RESOLVING(2124, CheckIfAllASAppearsBeforeAllBS, Solution);

class Solution {
public:
  bool checkString(string s) {
    bool b_appeared = false;
    for (auto c : s) {
      if (c == 'b') {
        b_appeared = true;
      } else if (b_appeared) {
        return false;
      }
    }
    return true;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 100|
// * |s[i]| is either |'a'| or |'b'|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "aaabbb"
// Output: true
//
// The 'a's are at indices 0, 1, and 2, while the 'b's are at indices 3, 4,
// and 5. Hence, every 'a' appears before every 'b' and we return true.

LEETCODE_SOLUTION_UNITTEST(2124, CheckIfAllASAppearsBeforeAllBS, example_1) {
  auto   solution = MakeSolution();
  string s        = "aaabbb";
  bool   expect   = true;
  bool   actual   = solution->checkString(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "abab"
// Output: false
//
// There is an 'a' at index 2 and a 'b' at index 1.
// Hence, not every 'a' appears before every 'b' and we return false.

LEETCODE_SOLUTION_UNITTEST(2124, CheckIfAllASAppearsBeforeAllBS, example_2) {
  auto   solution = MakeSolution();
  string s        = "abab";
  bool   expect   = false;
  bool   actual   = solution->checkString(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "bbb"
// Output: true
//
// There are no 'a's, hence, every 'a' appears before every 'b' and we return
// true.

LEETCODE_SOLUTION_UNITTEST(2124, CheckIfAllASAppearsBeforeAllBS, example_3) {
  auto   solution = MakeSolution();
  string s        = "bbb";
  bool   expect   = true;
  bool   actual   = solution->checkString(s);
  LCD_EXPECT_EQ(expect, actual);
}

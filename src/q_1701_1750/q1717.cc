// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Maximum Score From Removing Substrings
//
// https://leetcode.com/problems/maximum-score-from-removing-substrings/
//
// Question ID: 1717
// Difficult  : Medium
// Solve Date : 2024/07/13 02:25

#include <iosfwd>
#include <stack>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1717. Maximum Score From Removing Substrings|:
//
// You are given a string |s| and two integers |x| and |y|. You can perform two
// types of operations any number of times.
//
//  • Remove substring |"ab"| and gain |x| points.
//
//
//    • For example, when removing |"ab"| from |"cabxbae"| it becomes |"cxbae"|.
//
//
//
//  • Remove substring |"ba"| and gain |y| points.
//
//
//    • For example, when removing |"ba"| from |"cabxbae"| it becomes |"cabxe"|.
//
//
// Return the maximum points you can gain after applying the above operations on
// |s|.
//
//

LEETCODE_BEGIN_RESOLVING(1717, MaximumScoreFromRemovingSubstrings, Solution);

class Solution {
public:
  int maximumGain(string s, int x, int y) {
    int mxab = 0;
    int mxba = 0;
    int mnab = 0;
    int mnba = 0;
    helper<'a', 'b'>(s, &mxab, &mnba);
    helper<'b', 'a'>(s, &mxba, &mnab);
    return max(mxab * x + mnba * y, mxba * y + mnab * x);
  }

private:
  template <char fst, char sec>
  void helper(string s, int *cnt1, int *cnt2) {
    int i = 1;
    while (i < s.size()) {
      if (i > 0 && s[i - 1] == fst && s[i] == sec) {
        ++(*cnt1);
        s.erase(i - 1, 2);
        --i;
      } else {
        ++i;
      }
    }
    i = 1;
    while (i < s.size()) {
      if (i > 0 && s[i - 1] == sec && s[i] == fst) {
        ++(*cnt2);
        s.erase(i - 1, 2);
        --i;
      } else {
        ++i;
      }
    }
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 10⁵|
// * |1 <= x, y <= 10⁴|
// * |s| consists of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "cdbcbbaaabab", x = 4, y = 5
// Output: 19
//

LEETCODE_SOLUTION_UNITTEST(1717, MaximumScoreFromRemovingSubstrings,
                           example_1) {
  auto   solution = MakeSolution();
  string s        = "cdbcbbaaabab";
  int    x        = 4;
  int    y        = 5;
  int    expect   = 19;
  int    actual   = solution->maximumGain(s, x, y);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "aabbaaxybbaabb", x = 5, y = 4
// Output: 20
//

LEETCODE_SOLUTION_UNITTEST(1717, MaximumScoreFromRemovingSubstrings,
                           example_2) {
  auto   solution = MakeSolution();
  string s        = "aabbaaxybbaabb";
  int    x        = 5;
  int    y        = 4;
  int    expect   = 20;
  int    actual   = solution->maximumGain(s, x, y);
  LCD_EXPECT_EQ(expect, actual);
}

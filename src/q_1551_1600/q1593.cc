// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Split a String Into the Max Number of Unique Substrings
//
// https://leetcode.com/problems/split-a-string-into-the-max-number-of-unique-substrings/
//
// Question ID: 1593
// Difficult  : Medium
// Solve Date : 2024/10/21 20:15

#include <iosfwd>
#include <set>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1593. Split a String Into the Max Number of Unique
// Substrings|:
//
// Given a string |s|, return the maximum number of unique substrings that the
// given string can be split into. You can split string |s| into any list of
// non-empty substrings, where the concatenation of the substrings forms the
// original string. However, you must split the substrings such that all of them
// are unique. A substring is a contiguous sequence of characters within a
// string.
//
//

LEETCODE_BEGIN_RESOLVING(1593, SplitAStringIntoTheMaxNumberOfUniqueSubstrings,
                         Solution);

class Solution {
public:
  int maxUniqueSplit(string s) {
    set<string> used;
    int         res = 0;
    solve(0, s, &used, 0, &res);
    return res;
  }

private:
  void solve(int ind, const string &s, set<string> *used, int curr, int *res) {
    if (ind == s.size()) {
      *res = max(*res, curr);
      return;
    }

    string tmp;
    for (int i = ind; i < s.size(); ++i) {
      tmp.push_back(s[i]);
      if (auto [_, ok] = used->insert(tmp); ok) {
        solve(i + 1, s, used, curr + 1, res);
        used->erase(tmp);
      }
    }
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * 1 <= s.length <= 16 |
// * | s | contains only lower case English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "ababccc"
// Output: 5
//

LEETCODE_SOLUTION_UNITTEST(1593, SplitAStringIntoTheMaxNumberOfUniqueSubstrings,
                           example_1) {
  auto   solution = MakeSolution();
  string s        = "ababccc";
  int    expect   = 5;
  int    actual   = solution->maxUniqueSplit(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "aba"
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(1593, SplitAStringIntoTheMaxNumberOfUniqueSubstrings,
                           example_2) {
  auto   solution = MakeSolution();
  string s        = "aba";
  int    expect   = 2;
  int    actual   = solution->maxUniqueSplit(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "aa"
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(1593, SplitAStringIntoTheMaxNumberOfUniqueSubstrings,
                           example_3) {
  auto   solution = MakeSolution();
  string s        = "aa";
  int    expect   = 1;
  int    actual   = solution->maxUniqueSplit(s);
  LCD_EXPECT_EQ(expect, actual);
}

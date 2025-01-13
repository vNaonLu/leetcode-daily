// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Minimum Length of String After Operations
//
// https://leetcode.com/problems/minimum-length-of-string-after-operations/
//
// Question ID: 3223
// Difficult  : Medium
// Solve Date : 2025/01/13 21:05

#include <iosfwd>
#include <string>
#include <unordered_map>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3223. Minimum Length of String After Operations|:
//
// You are given a string |s|.
// You can perform the following process on |s| any number of times:
//
//  • Choose an index |i| in the string such that there is at least one
//  character to the left of index |i| that is equal to |s[i]|, and at least one
//  character to the right that is also equal to |s[i]|.
//
//  • Delete the closest character to the left of index |i| that is equal to
//  |s[i]|.
//
//  • Delete the closest character to the right of index |i| that is equal to
//  |s[i]|.
// Return the minimum length of the final string |s| that you can achieve.
//
//

LEETCODE_BEGIN_RESOLVING(3223, MinimumLengthOfStringAfterOperations, Solution);

class Solution {
public:
  int minimumLength(string s) {
    unordered_map<char, int> mp;
    for (auto c : s) {
      ++mp[c];
    }

    int cnt = 0;
    for (auto &[_, freq] : mp) {
      if (freq & 1) {
        cnt += freq - 1;
      } else {
        cnt += freq - 2;
      }
    }
    return s.size() - cnt;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 2 * 10⁵|
// * |s| consists only of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "abaacbcbb"
// Output: 5
//

LEETCODE_SOLUTION_UNITTEST(3223, MinimumLengthOfStringAfterOperations,
                           example_1) {
  auto   solution = MakeSolution();
  string s        = "abaacbcbb";
  int    expect   = 5;
  int    actual   = solution->minimumLength(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "aa"
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(3223, MinimumLengthOfStringAfterOperations,
                           example_2) {
  auto   solution = MakeSolution();
  string s        = "aa";
  int    expect   = 2;
  int    actual   = solution->minimumLength(s);
  LCD_EXPECT_EQ(expect, actual);
}

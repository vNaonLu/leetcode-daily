// Copyright 2023 Naon Lu
//
// This file describes the solution of
// First Unique Character in a String
//
// https://leetcode.com/problems/first-unique-character-in-a-string/
//
// Question ID: 387
// Difficult  : Easy
// Solve Date : 2021/09/10 08:00

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |387. First Unique Character in a String|:
//
// Given a string |s|, find the first non-repeating character in it and return
// its index. If it does not exist, return |-1|.  
//

LEETCODE_BEGIN_RESOLVING(387, FirstUniqueCharacterinaString, Solution);

class Solution {
public:
  int firstUniqChar(string s) {
    vector<int> cnt(26, 0);
    for (const auto &c : s)
      ++cnt[c - 'a'];
    for (int i = 0; i < s.size(); ++i)
      if (cnt[s[i] - 'a'] == 1)
        return i;
    return -1;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 10⁵|
// * |s| consists of only lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "leetcode"
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(387, FirstUniqueCharacterinaString, example_1) {
  auto   solution = MakeSolution();
  string s        = "leetcode";
  int    expect   = 0;
  int    actual   = solution->firstUniqChar(s);
  EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "loveleetcode"
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(387, FirstUniqueCharacterinaString, example_2) {
  auto   solution = MakeSolution();
  string s        = "loveleetcode";
  int    expect   = 2;
  int    actual   = solution->firstUniqChar(s);
  EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "aabb"
// Output: -1
//

LEETCODE_SOLUTION_UNITTEST(387, FirstUniqueCharacterinaString, example_3) {
  auto   solution = MakeSolution();
  string s        = "aabb";
  int    expect   = -1;
  int    actual   = solution->firstUniqChar(s);
  EXPECT_EQ(expect, actual);
}

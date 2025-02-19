// Copyright 2025 Naon Lu
//
// This file describes the solution of
// The k-th Lexicographical String of All Happy Strings of Length n
//
// https://leetcode.com/problems/the-k-th-lexicographical-string-of-all-happy-strings-of-length-n/
//
// Question ID: 1415
// Difficult  : Medium
// Solve Date : 2025/02/19 19:05

#include <algorithm>
#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1415. The k-th Lexicographical String of All Happy Strings of
// Length n|:
//
// A happy string is a string that:
//
//  • consists only of letters of the set |['a', 'b', 'c']|.
//
//  • |s[i] != s[i + 1]| for all values of |i| from |1| to |s.length - 1|
//  (string is 1-indexed).
// For example, strings "abc", "ac", "b" and "abcbabcbcb" are all happy strings
// and strings "aa", "baa" and "ababbc" are not happy strings. Given two
// integers |n| and |k|, consider a list of all happy strings of length |n|
// sorted in lexicographical order. Return the kth string of this list or return
// an empty string if there are less than |k| happy strings of length |n|.
//
//

LEETCODE_BEGIN_RESOLVING(1415,
                         TheKThLexicographicalStringOfAllHappyStringsOfLengthN,
                         Solution);

class Solution {
public:
  string getHappyString(int n, int k) {
    string         curr;
    vector<string> happy;
    generate(n, curr, &happy);
    if (happy.size() < k) {
      return "";
    }
    sort(happy.begin(), happy.end());
    return happy[k - 1];
  }

private:
  void generate(int n, string curr, vector<string> *happy) {
    if (curr.size() == n) {
      happy->emplace_back(std::move(curr));
      return;
    }

    for (char c = 'a'; c <= 'c'; ++c) {
      if (curr.size() > 0 && curr.back() == c) {
        continue;
      }

      generate(n, curr + c, happy);
    }
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n <= 10|
// * |1 <= k <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 1, k = 3
// Output: "c"
//

LEETCODE_SOLUTION_UNITTEST(
    1415, TheKThLexicographicalStringOfAllHappyStringsOfLengthN, example_1) {
  auto   solution = MakeSolution();
  int    n        = 1;
  int    k        = 3;
  string expect   = "c";
  string actual   = solution->getHappyString(n, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 1, k = 4
// Output: ""
//

LEETCODE_SOLUTION_UNITTEST(
    1415, TheKThLexicographicalStringOfAllHappyStringsOfLengthN, example_2) {
  auto   solution = MakeSolution();
  int    n        = 1;
  int    k        = 4;
  string expect   = "";
  string actual   = solution->getHappyString(n, k);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: n = 3, k = 9
// Output: "cab"
//

LEETCODE_SOLUTION_UNITTEST(
    1415, TheKThLexicographicalStringOfAllHappyStringsOfLengthN, example_3) {
  auto   solution = MakeSolution();
  int    n        = 3;
  int    k        = 9;
  string expect   = "cab";
  string actual   = solution->getHappyString(n, k);
  LCD_EXPECT_EQ(expect, actual);
}

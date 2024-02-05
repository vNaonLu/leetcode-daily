// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Make Three Strings Equal
//
// https://leetcode.com/problems/make-three-strings-equal/
//
// Question ID: 2937
// Difficult  : Easy
// Solve Date : 2024/02/05 19:55

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2937. Make Three Strings Equal|:
//
// You are given three strings |s1|, |s2|, and |s3|. You have to perform the
// following operation on these three strings as many times as you want. In one
// operation you can choose one of these three strings such that its length is
// at least |2| and delete the rightmost character of it. Return the minimum
// number of operations you need to perform to make the three strings equal if
// there is a way to make them equal, otherwise, return |-1|.
//
//

LEETCODE_BEGIN_RESOLVING(2937, MakeThreeStringsEqual, Solution);

class Solution {
public:
  int findMinimumOperations(string s1, string s2, string s3) {
    int i   = 0;
    int cnt = 0;
    int len = min({s1.size(), s2.size(), s3.size()});
    while (i < len) {
      if (s1[i] == s2[i] && s2[i] == s3[i]) {
        ++i;
        ++cnt;
      } else {
        break;
      }
    }
    if (cnt == 0) {
      return -1;
    }
    return s1.size() + s2.size() + s3.size() - 3 * cnt;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= s1.length, s2.length, s3.length <= 100|
// * |s1|, |s2| and |s3| consist only of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s1 = "abc", s2 = "abb", s3 = "ab"
// Output: 2
//
// Performing operations on s1 and s2 once will lead to three equal strings.
// It can be shown that there is no way to make them equal with less than two
// operations.

LEETCODE_SOLUTION_UNITTEST(2937, MakeThreeStringsEqual, example_1) {
  auto   solution = MakeSolution();
  string s1       = "abc";
  string s2       = "abb";
  string s3       = "ab";
  int    expect   = 2;
  int    actual   = solution->findMinimumOperations(s1, s2, s3);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s1 = "dac", s2 = "bac", s3 = "cac"
// Output: -1
//
// Because the leftmost letters of s1 and s2 are not equal, they could not be
// equal after any number of operations. So the answer is -1.

LEETCODE_SOLUTION_UNITTEST(2937, MakeThreeStringsEqual, example_2) {
  auto   solution = MakeSolution();
  string s1       = "dac";
  string s2       = "bac";
  string s3       = "cac";
  int    expect   = -1;
  int    actual   = solution->findMinimumOperations(s1, s2, s3);
  LCD_EXPECT_EQ(expect, actual);
}

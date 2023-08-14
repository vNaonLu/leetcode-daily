// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Maximum Score After Splitting a String
//
// https://leetcode.com/problems/maximum-score-after-splitting-a-string/
//
// Question ID: 1422
// Difficult  : Easy
// Solve Date : 2023/08/14 22:30

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1422. Maximum Score After Splitting a String|:
//
// Given a string |s| of zeros and ones, return the maximum score after
// splitting the string into two non-empty substrings (i.e. left substring and
// right substring). The score after splitting a string is the number of zeros
// in the left substring plus the number of ones in the right substring.
//
//

LEETCODE_BEGIN_RESOLVING(1422, MaximumScoreAfterSplittingAString, Solution);

class Solution {
public:
  int maxScore(string s) {
    vector<int> ones(s.size() + 1, 0);
    vector<int> zeros(s.size() + 1, 0);
    for (int i = 0; i < s.size(); ++i) {
      ones[i + 1]  = ones[i];
      zeros[i + 1] = zeros[i];
      if (s[i] == '0') {
        ++zeros[i + 1];
      } else {
        ++ones[i + 1];
      }
    }
    int res = 0;
    for (int i = 1; i < s.size(); ++i) {
      res = max(res, (zeros[i] - zeros.front()) + (ones.back() - ones[i]));
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= s.length <= 500|
// * The string |s| consists of characters |'0'| and |'1'| only.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "011101"
// Output: 5
//
// All possible ways of splitting s into two non-empty substrings are:
// left = "0" and right = "11101", score = 1 + 4 = 5
// left = "01" and right = "1101", score = 1 + 3 = 4
// left = "011" and right = "101", score = 1 + 2 = 3
// left = "0111" and right = "01", score = 1 + 1 = 2
// left = "01110" and right = "1", score = 2 + 1 = 3

LEETCODE_SOLUTION_UNITTEST(1422, MaximumScoreAfterSplittingAString, example_1) {
  auto   solution = MakeSolution();
  string s        = "011101";
  int    expect   = 5;
  int    actual   = solution->maxScore(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "00111"
// Output: 5
//
// When left = "00" and right = "111", we get the maximum score = 2 + 3 = 5

LEETCODE_SOLUTION_UNITTEST(1422, MaximumScoreAfterSplittingAString, example_2) {
  auto   solution = MakeSolution();
  string s        = "00111";
  int    expect   = 5;
  int    actual   = solution->maxScore(s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "1111"
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(1422, MaximumScoreAfterSplittingAString, example_3) {
  auto   solution = MakeSolution();
  string s        = "1111";
  int    expect   = 3;
  int    actual   = solution->maxScore(s);
  LCD_EXPECT_EQ(expect, actual);
}

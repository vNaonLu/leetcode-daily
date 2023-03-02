// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Maximum Number of Balloons
//
// https://leetcode.com/problems/maximum-number-of-balloons/
//
// Question ID: 1189
// Difficult  : Easy
// Solve Date : 2021/09/13 08:00

#include <iosfwd>
#include <map>
#include <string>
#include <unordered_map>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1189. Maximum Number of Balloons|:
//
// Given a string |text|, you want to use the characters of |text| to form as
// many instances of the word "balloon" as possible. You can use each character
// in |text| at most once. Return the maximum number of instances that can be
// formed.  
//

LEETCODE_BEGIN_RESOLVING(1189, MaximumNumberOfBalloons, Solution);

class Solution {
public:
  int maxNumberOfBalloons(string text) {
    unordered_map<char, int> tar{
        {'b', 1},
        {'a', 1},
        {'l', 2},
        {'o', 2},
        {'n', 1}
    };
    unordered_map<char, int> cnt{
        {'b', 0},
        {'a', 0},
        {'l', 0},
        {'o', 0},
        {'n', 0}
    };
    for (const auto &c : text) {
      if (tar.count(c)) {
        ++cnt[c];
      }
    }
    int res = text.size();
    for (const auto &[a, b] : cnt) {
      res = min(b / tar[a], res);
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= text.length <= 10⁴|
// * |text| consists of lower case English letters only.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: text = "nlaebolko"
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(1189, MaximumNumberOfBalloons, example_1) {
  auto   solution = MakeSolution();
  string text     = "nlaebolko";
  int    expect   = 1;
  int    actual   = solution->maxNumberOfBalloons(text);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: text = "loonbalxballpoon"
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(1189, MaximumNumberOfBalloons, example_2) {
  auto   solution = MakeSolution();
  string text     = "loonbalxballpoon";
  int    expect   = 2;
  int    actual   = solution->maxNumberOfBalloons(text);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: text = "leetcode"
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(1189, MaximumNumberOfBalloons, example_3) {
  auto   solution = MakeSolution();
  string text     = "leetcode";
  int    expect   = 0;
  int    actual   = solution->maxNumberOfBalloons(text);
  LCD_EXPECT_EQ(expect, actual);
}

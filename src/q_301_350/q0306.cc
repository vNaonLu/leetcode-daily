// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Additive Number
//
// https://leetcode.com/problems/additive-number/
//
// Question ID: 306
// Difficult  : Medium
// Solve Date : 2024/03/08 21:05

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |306. Additive Number|:
//
// An additive number is a string whose digits can form an additive sequence.
// A valid additive sequence should contain at least three numbers. Except for
// the first two numbers, each subsequent number in the sequence must be the sum
// of the preceding two. Given a string containing only digits, return |true| if
// it is an additive number or |false| otherwise. Note: Numbers in the additive
// sequence cannot have leading zeros, so sequence |1, 2, 03| or |1, 02, 3| is
// invalid.
//
//

LEETCODE_BEGIN_RESOLVING(306, AdditiveNumber, Solution);

class Solution {
public:
  bool isAdditiveNumber(string num) {
    uint64_t fst = 0;
    int      n   = num.size();
    for (int i = 0; i < (num[0] == '0' ? 1 : n / 2); ++i) {
      fst          = fst * 10 + (num[i] - '0');
      uint64_t snd = 0;
      for (int j = i + 1;
           j < (num[i + 1] == '0' ? i + 2 : min(n, i + n / 2 + 1)); ++j) {
        snd = snd * 10 + (num[j] - '0');
        if (helper(fst, snd, j + 1, num)) {
          return true;
        }
      }
    }
    return false;
  }

private:
  bool helper(uint64_t fst, uint64_t snd, int beg, string const &num) {
    int n = num.size();
    if (beg >= n) {
      return false;
    }

    uint64_t tmp = fst;
    fst          = snd;
    snd += tmp;
    string cur = to_string(snd);
    int    p   = 0;
    int    i   = beg;
    while (i < n) {
      while (i < n && p < cur.size() && num[i] == cur[p]) {
        ++i;
        ++p;
      }
      if (p != cur.size()) {
        return false;
      }
      auto tmp = fst;
      fst      = snd;
      snd += tmp;
      cur = to_string(snd);
      p   = 0;
    }
    return !p;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= num.length <= 35|
// * |num| consists only of digits.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: "112358"
// Output: true
//
// The digits can form an additive sequence: 1, 1, 2, 3, 5, 8.
// 1 + 1 = 2, 1 + 2 = 3, 2 + 3 = 5, 3 + 5 = 8

LEETCODE_SOLUTION_UNITTEST(306, AdditiveNumber, example_1) {
  auto   solution = MakeSolution();
  string num      = "112358";
  bool   expect   = true;
  bool   actual   = solution->isAdditiveNumber(num);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: "199100199"
// Output: true
//
// The additive sequence is: 1, 99, 100, 199.
// 1 + 99 = 100, 99 + 100 = 199

LEETCODE_SOLUTION_UNITTEST(306, AdditiveNumber, example_2) {
  auto   solution = MakeSolution();
  string num      = "199100199";
  bool   expect   = true;
  bool   actual   = solution->isAdditiveNumber(num);
  LCD_EXPECT_EQ(expect, actual);
}

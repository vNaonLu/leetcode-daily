// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Number of Different Integers in a String
//
// https://leetcode.com/problems/number-of-different-integers-in-a-string/
//
// Question ID: 1805
// Difficult  : Easy
// Solve Date : 2022/06/22 18:14

#include <iosfwd>
#include <set>
#include <string>
#include <unordered_set>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1805. Number of Different Integers in a String|:
//
// You are given a string |word| that consists of digits and lowercase English
// letters. You will replace every non-digit character with a space. For
// example, |"a123bc34d8ef34"| will become |" 123 34 8 34"|. Notice that you are
// left with some integers that are separated by at least one space: |"123"|,
// |"34"|, |"8"|, and |"34"|. Return the number of different integers after
// performing the replacement operations on |word|. Two integers are considered
// different if their decimal representations without any leading zeros are
// different.
//

LEETCODE_BEGIN_RESOLVING(1805, NumberOfDifferentIntegersInAString, Solution);

class Solution {
private:
  template <typename iterator>
  bool is_integral(iterator it) {
    return *it >= '0' && *it <= '9';
  }

  template <typename iterator>
  void trim_left_zero(iterator &beg, iterator end) {
    while (beg != end) {
      if (*beg != '0') {
        break;
      }
      ++beg;
    }
  }

public:
  int numDifferentIntegers(string word) {
    unordered_set<string_view> memo;
    auto                       right = word.begin();
    auto                       left  = word.begin();

    for (; right != word.end(); ++right) {
      if (is_integral(right) && !is_integral(left)) {
        left = right;
      } else if (!is_integral(right) && is_integral(left)) {
        trim_left_zero(left, right);
        memo.emplace(&(*left), right - left);
        left = right;
      }
    }

    if (is_integral(left)) {
      trim_left_zero(left, right);
      memo.emplace(&(*left), right - left);
    }

    return memo.size();
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= word.length <= 1000|
// * |word| consists of digits and lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: word = "a123bc34d8ef34"
// Output: 3
//
// The three different integers are "123", "34", and "8". Notice that "34" is
// only counted once.

LEETCODE_SOLUTION_UNITTEST(1805, NumberOfDifferentIntegersInAString,
                           example_1) {
  auto   solution = MakeSolution();
  string word     = "a123bc34d8ef34";
  int    expect   = 3;
  int    actual   = solution->numDifferentIntegers(word);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: word = "leet1234code234"
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(1805, NumberOfDifferentIntegersInAString,
                           example_2) {
  auto   solution = MakeSolution();
  string word     = "leet1234code234";
  int    expect   = 2;
  int    actual   = solution->numDifferentIntegers(word);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: word = "a1b01c001"
// Output: 1
//
// The three integers "1", "01", and "001" all represent the same integer
// because the leading zeros are ignored when comparing their decimal values.

LEETCODE_SOLUTION_UNITTEST(1805, NumberOfDifferentIntegersInAString,
                           example_3) {
  auto   solution = MakeSolution();
  string word     = "a1b01c001";
  int    expect   = 1;
  int    actual   = solution->numDifferentIntegers(word);
  LCD_EXPECT_EQ(expect, actual);
}

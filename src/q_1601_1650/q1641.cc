// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Count Sorted Vowel Strings
//
// https://leetcode.com/problems/count-sorted-vowel-strings/
//
// Question ID: 1641
// Difficult  : Medium
// Solve Date : 2022/05/11 11:15

#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1641. Count Sorted Vowel Strings|:
//
// Given an integer |n|, return the number of strings of length |n| that consist
// only of vowels ( |a|, |e|, |i|, |o|, |u|) and are lexicographically sorted.
// A string |s| is lexicographically sorted if for all valid |i|, |s[i]| is the
// same as or comes before |s[i+1]| in the alphabet.  
//

LEETCODE_BEGIN_RESOLVING(1641, CountSortedVowelStrings, Solution);

class Solution {
public:
  int countVowelStrings(int n) {

    return (n + 4) * (n + 3) * (n + 2) * (n + 1) / 24;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n <= 50| 
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 1
// Output: 5
//
// The 5 sorted strings that consist of vowels only are |["a","e","i","o","u"].|

LEETCODE_SOLUTION_UNITTEST(1641, CountSortedVowelStrings, example_1) {
  auto solution = MakeSolution();
  int  n        = 1;
  int  expect   = 5;
  int  actual   = solution->countVowelStrings(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 2
// Output: 15
//
// The 15 sorted strings that consist of vowels only are
// ["aa","ae","ai","ao","au","ee","ei","eo","eu","ii","io","iu","oo","ou","uu"].
// Note that "ea" is not a valid string since 'e' comes after 'a' in the
// alphabet.

LEETCODE_SOLUTION_UNITTEST(1641, CountSortedVowelStrings, example_2) {
  auto solution = MakeSolution();
  int  n        = 2;
  int  expect   = 15;
  int  actual   = solution->countVowelStrings(n);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: n = 33
// Output: 66045
//

LEETCODE_SOLUTION_UNITTEST(1641, CountSortedVowelStrings, example_3) {
  auto solution = MakeSolution();
  int  n        = 33;
  int  expect   = 66045;
  int  actual   = solution->countVowelStrings(n);
  LCD_EXPECT_EQ(expect, actual);
}

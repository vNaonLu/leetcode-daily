// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Find First Palindromic String in the Array
//
// https://leetcode.com/problems/find-first-palindromic-string-in-the-array/
//
// Question ID: 2108
// Difficult  : Easy
// Solve Date : 2023/05/16 22:56

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2108. Find First Palindromic String in the Array|:
//
// Given an array of strings |words|, return the first palindromic string in the
// array. If there is no such string, return an empty string |""|. A string is
// palindromic if it reads the same forward and backward.
//
//

LEETCODE_BEGIN_RESOLVING(2108, FindFirstPalindromicStringInTheArray, Solution);

class Solution {
public:
  string firstPalindrome(vector<string> &words) {
    for (auto &s : words) {
      if (isPalindromic(s)) {
        return s;
      }
    }
    return "";
  }

private:
  bool isPalindromic(string &s) {
    auto b = s.begin();
    auto r = s.rbegin();
    while (b != s.end()) {
      if (*b++ != *r++) {
        return false;
      }
    }
    return true;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= words.length <= 100|
// * |1 <= words[i].length <= 100|
// * |words[i]| consists only of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: words = ["abc","car","ada","racecar","cool"]
// Output: "ada"
//
// The first string that is palindromic is "ada".
// Note that "racecar" is also palindromic, but it is not the first.

LEETCODE_SOLUTION_UNITTEST(2108, FindFirstPalindromicStringInTheArray,
                           example_1) {
  auto           solution = MakeSolution();
  vector<string> words    = {"abc", "car", "ada", "racecar", "cool"};
  string         expect   = "ada";
  string         actual   = solution->firstPalindrome(words);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: words = ["notapalindrome","racecar"]
// Output: "racecar"
//
// The first and only string that is palindromic is "racecar".

LEETCODE_SOLUTION_UNITTEST(2108, FindFirstPalindromicStringInTheArray,
                           example_2) {
  auto           solution = MakeSolution();
  vector<string> words    = {"notapalindrome", "racecar"};
  string         expect   = "racecar";
  string         actual   = solution->firstPalindrome(words);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: words = ["def","ghi"]
// Output: ""
//
// There are no palindromic strings, so the empty string is returned.

LEETCODE_SOLUTION_UNITTEST(2108, FindFirstPalindromicStringInTheArray,
                           example_3) {
  auto           solution = MakeSolution();
  vector<string> words    = {"def", "ghi"};
  string         expect   = "";
  string         actual   = solution->firstPalindrome(words);
  LCD_EXPECT_EQ(expect, actual);
}

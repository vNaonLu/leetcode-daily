// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Find Smallest Letter Greater Than Target
//
// https://leetcode.com/problems/find-smallest-letter-greater-than-target/
//
// Question ID: 744
// Difficult  : Easy
// Solve Date : 2022/04/06 19:12

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |744. Find Smallest Letter Greater Than Target|:
//
// You are given an array of characters |letters| that is sorted in
// non-decreasing order, and a character |target|. There are at least two
// different characters in |letters|. Return the smallest character in |letters|
// that is lexicographically greater than |target|. If such a character does not
// exist, return the first character in |letters|.  
//

LEETCODE_BEGIN_RESOLVING(744, FindSmallestLetterGreaterThanTarget, Solution);

class Solution {
public:
  char nextGreatestLetter(vector<char> &letters, char target) {
    int l = 0, r = letters.size();
    while (l < r) {
      int m = l + (r - l) / 2;
      if (letters[m] <= target) {
        l = m + 1;
      } else {
        r = m;
      }
    }
    return letters[l % letters.size()];
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |2 <= letters.length <= 10⁴|
// * |letters[i]| is a lowercase English letter.
// * |letters| is sorted in non-decreasing order.
// * |letters| contains at least two different characters.
// * |target| is a lowercase English letter.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: letters = ["c","f","j"], target = "a"
// Output: "c"
//
// The smallest character that is lexicographically greater than 'a' in letters
// is 'c'.

LEETCODE_SOLUTION_UNITTEST(744, FindSmallestLetterGreaterThanTarget,
                           example_1) {
  auto         solution = MakeSolution();
  vector<char> letters  = {'c', 'f', 'j'};
  char         target   = 'a';
  char         expect   = 'c';
  char         actual   = solution->nextGreatestLetter(letters, target);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: letters = ["c","f","j"], target = "c"
// Output: "f"
//
// The smallest character that is lexicographically greater than 'c' in letters
// is 'f'.

LEETCODE_SOLUTION_UNITTEST(744, FindSmallestLetterGreaterThanTarget,
                           example_2) {
  auto         solution = MakeSolution();
  vector<char> letters  = {'c', 'f', 'j'};
  char         target   = 'c';
  char         expect   = 'f';
  char         actual   = solution->nextGreatestLetter(letters, target);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: letters = ["x","x","y","y"], target = "z"
// Output: "x"
//
// There are no characters in letters that is lexicographically greater than 'z'
// so we return letters[0].

LEETCODE_SOLUTION_UNITTEST(744, FindSmallestLetterGreaterThanTarget,
                           example_3) {
  auto         solution = MakeSolution();
  vector<char> letters  = {'x', 'x', 'y', 'y'};
  char         target   = 'z';
  char         expect   = 'x';
  char         actual   = solution->nextGreatestLetter(letters, target);
  LCD_EXPECT_EQ(expect, actual);
}

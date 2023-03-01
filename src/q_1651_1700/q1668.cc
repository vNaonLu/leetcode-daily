// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Maximum Repeating Substring
//
// https://leetcode.com/problems/maximum-repeating-substring/
//
// Question ID: 1668
// Difficult  : Easy
// Solve Date : 2022/12/18 13:45

#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1668. Maximum Repeating Substring|:
//
// For a string |sequence|, a string |word| is |k|-repeating if |word|
// concatenated |k| times is a substring of |sequence|. The |word|'s maximum
// |k|-repeating value is the highest value |k| where |word| is |k|-repeating in
// |sequence|. If |word| is not a substring of |sequence|, |word|'s maximum
// |k|-repeating value is |0|. Given strings |sequence| and |word|, return the
// maximum |k|-repeating value of |word| in |sequence|.
//

LEETCODE_BEGIN_RESOLVING(1668, MaximumRepeatingSubstring, Solution);

class Solution {
public:
  int maxRepeating(string sequence, string word) {
    auto res  = (int)0;
    auto temp = word;
    while (sequence.find(temp) != string::npos) {
      ++res;
      temp += word;
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= sequence.length <= 100|
// * |1 <= word.length <= 100|
// * |sequence| and |word|contains only lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: sequence = "ababc", word = "ab"
// Output: 2
//
// "abab" is a substring in "ababc".

LEETCODE_SOLUTION_UNITTEST(1668, MaximumRepeatingSubstring, example_1) {
  auto   solution = MakeSolution();
  string sequence = "ababc";
  string word     = "ab";
  int    expect   = 2;
  int    actual   = solution->maxRepeating(sequence, word);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: sequence = "ababc", word = "ba"
// Output: 1
//
// "ba" is a substring in "ababc". "baba" is not a substring in "ababc".

LEETCODE_SOLUTION_UNITTEST(1668, MaximumRepeatingSubstring, example_2) {
  auto   solution = MakeSolution();
  string sequence = "ababc";
  string word     = "ba";
  int    expect   = 1;
  int    actual   = solution->maxRepeating(sequence, word);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: sequence = "ababc", word = "ac"
// Output: 0
//
// "ac" is not a substring in "ababc".

LEETCODE_SOLUTION_UNITTEST(1668, MaximumRepeatingSubstring, example_3) {
  auto   solution = MakeSolution();
  string sequence = "ababc";
  string word     = "ac";
  int    expect   = 0;
  int    actual   = solution->maxRepeating(sequence, word);
  LCD_EXPECT_EQ(expect, actual);
}

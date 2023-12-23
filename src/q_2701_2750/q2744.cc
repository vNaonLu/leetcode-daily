// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Find Maximum Number of String Pairs
//
// https://leetcode.com/problems/find-maximum-number-of-string-pairs/
//
// Question ID: 2744
// Difficult  : Easy
// Solve Date : 2023/12/23 15:34

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2744. Find Maximum Number of String Pairs|:
//
// You are given a 0-indexed array |words| consisting of distinct strings.
// The string |words[i]| can be paired with the string |words[j]| if:
//
//  • The string |words[i]| is equal to the reversed string of |words[j]|.
//
//  • |0 <= i < j < words.length|.
// Return the maximum number of pairs that can be formed from the array |words|.
// Note that each string can belong in at most one pair.
//
//

LEETCODE_BEGIN_RESOLVING(2744, FindMaximumNumberOfStringPairs, Solution);

class Solution {
public:
  int maximumNumberOfStringPairs(vector<string> &words) {
    int res = 0;
    for (int i = 0; i < words.size(); ++i) {
      for (int j = i + 1; j < words.size(); ++j) {
        string s = words[j];
        reverse(s.begin(), s.end());
        if (words[i] == s) {
          ++res;
        }
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= words.length <= 50|
// * |words[i].length == 2|
// * |words| consists of distinct strings.
// * |words[i]| contains only lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: words = ["cd","ac","dc","ca","zz"]
// Output: 2
//
// In this example, we can form 2 pair of strings in the following way:
// - We pair the 0ᵗʰ string with the 2ⁿᵈ string, as the reversed string of
// word[0] is "dc" and is equal to words[2].
// - We pair the 1ˢᵗ string with the 3ʳᵈ string, as the reversed string of
// word[1] is "ca" and is equal to words[3]. It can be proven that 2 is the
// maximum number of pairs that can be formed.

LEETCODE_SOLUTION_UNITTEST(2744, FindMaximumNumberOfStringPairs, example_1) {
  auto           solution = MakeSolution();
  vector<string> words    = {"cd", "ac", "dc", "ca", "zz"};
  int            expect   = 2;
  int            actual   = solution->maximumNumberOfStringPairs(words);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: words = ["ab","ba","cc"]
// Output: 1
//
// In this example, we can form 1 pair of strings in the following way:
// - We pair the 0ᵗʰ string with the 1ˢᵗ string, as the reversed string of
// words[1] is "ab" and is equal to words[0]. It can be proven that 1 is the
// maximum number of pairs that can be formed.

LEETCODE_SOLUTION_UNITTEST(2744, FindMaximumNumberOfStringPairs, example_2) {
  auto           solution = MakeSolution();
  vector<string> words    = {"ab", "ba", "cc"};
  int            expect   = 1;
  int            actual   = solution->maximumNumberOfStringPairs(words);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: words = ["aa","ab"]
// Output: 0
//
// In this example, we are unable to form any pair of strings.

LEETCODE_SOLUTION_UNITTEST(2744, FindMaximumNumberOfStringPairs, example_3) {
  auto           solution = MakeSolution();
  vector<string> words    = {"aa", "ab"};
  int            expect   = 0;
  int            actual   = solution->maximumNumberOfStringPairs(words);
  LCD_EXPECT_EQ(expect, actual);
}

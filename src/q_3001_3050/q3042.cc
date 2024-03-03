// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Count Prefix and Suffix Pairs I
//
// https://leetcode.com/problems/count-prefix-and-suffix-pairs-i/
//
// Question ID: 3042
// Difficult  : Easy
// Solve Date : 2024/03/03 21:42

#include <iosfwd>
#include <string>
#include <string_view>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |3042. Count Prefix and Suffix Pairs I|:
//
// You are given a 0-indexed string array |words|.
// Let's define a boolean function |isPrefixAndSuffix| that takes two strings,
// |str1| and |str2|:
//
//  • |isPrefixAndSuffix(str1, str2)| returns |true| if |str1| is both a prefix
//  and a suffix of |str2|, and |false| otherwise.
// For example, |isPrefixAndSuffix("aba", "ababa")| is |true| because |"aba"| is
// a prefix of |"ababa"| and also a suffix, but |isPrefixAndSuffix("abc",
// "abcd")| is |false|. Return an integer denoting the number of index pairs
// |(i, j)| such that |i < j|, and |isPrefixAndSuffix(words[i], words[j])| is
// |true|.
//
//

LEETCODE_BEGIN_RESOLVING(3042, CountPrefixAndSuffixPairsI, Solution);

class Solution {
public:
  int countPrefixSuffixPairs(vector<string> &words) {
    int res = 0;
    for (int i = 0; i < words.size(); ++i) {
      string_view s1 = words[i];
      for (int j = i + 1; j < words.size(); ++j) {
        string_view s2 = words[j];
        if (s1 == s2.substr(0, min(s1.size(), s2.size())) &&
            s1 == s2.substr(s2.size() - min(s1.size(), s2.size()))) {
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
// * |1 <= words[i].length <= 10|
// * |words[i]| consists only of lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: words = ["a","aba","ababa","aa"]
// Output: 4
//
// In this example, the counted index pairs are:
// i = 0 and j = 1 because isPrefixAndSuffix("a", "aba") is true.
// i = 0 and j = 2 because isPrefixAndSuffix("a", "ababa") is true.
// i = 0 and j = 3 because isPrefixAndSuffix("a", "aa") is true.
// i = 1 and j = 2 because isPrefixAndSuffix("aba", "ababa") is true.
// Therefore, the answer is 4.

LEETCODE_SOLUTION_UNITTEST(3042, CountPrefixAndSuffixPairsI, example_1) {
  auto           solution = MakeSolution();
  vector<string> words    = {"a", "aba", "ababa", "aa"};
  int            expect   = 4;
  int            actual   = solution->countPrefixSuffixPairs(words);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: words = ["pa","papa","ma","mama"]
// Output: 2
//
// In this example, the counted index pairs are:
// i = 0 and j = 1 because isPrefixAndSuffix("pa", "papa") is true.
// i = 2 and j = 3 because isPrefixAndSuffix("ma", "mama") is true.
// Therefore, the answer is 2.

LEETCODE_SOLUTION_UNITTEST(3042, CountPrefixAndSuffixPairsI, example_2) {
  auto           solution = MakeSolution();
  vector<string> words    = {"pa", "papa", "ma", "mama"};
  int            expect   = 2;
  int            actual   = solution->countPrefixSuffixPairs(words);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: words = ["abab","ab"]
// Output: 0
//
// In this example, the only valid index pair is i = 0 and j = 1, and
// isPrefixAndSuffix("abab", "ab") is false. Therefore, the answer is 0.

LEETCODE_SOLUTION_UNITTEST(3042, CountPrefixAndSuffixPairsI, example_3) {
  auto           solution = MakeSolution();
  vector<string> words    = {"abab", "ab"};
  int            expect   = 0;
  int            actual   = solution->countPrefixSuffixPairs(words);
  LCD_EXPECT_EQ(expect, actual);
}

// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Count Pairs Of Similar Strings
//
// https://leetcode.com/problems/count-pairs-of-similar-strings/
//
// Question ID: 2506
// Difficult  : Easy
// Solve Date : 2023/03/09 19:52

#include <iosfwd>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2506. Count Pairs Of Similar Strings|:
//
// You are given a 0-indexed string array |words|.
// Two strings are similar if they consist of the same characters.
//
//  • For example, |"abca"| and |"cba"| are similar since both consist of
//  characters |'a'|, |'b'|, and |'c'|.
//
//  • However, |"abacba"| and |"bcfd"| are not similar since they do not consist
//  of the same characters.
// Return the number of pairs |(i, j)| such that |0 <= i < j <= word.length - 1|
// and the two strings |words[i]| and |words[j]| are similar.
//

LEETCODE_BEGIN_RESOLVING(2506, CountPairsOfSimilarStrings, Solution);

class Solution {
private:
  string simplify(string const &s) {
    set<char> appear(s.begin(), s.end());
    return string(appear.begin(), appear.end());
  }

public:
  int similarPairs(vector<string> &words) {
    int                        res = 0;
    unordered_map<string, int> freq;
    for (auto &s : words) {
      auto simple = simplify(s);
      ++freq[simple];

      auto iter = freq.find(simple);
      if (iter->second > 1) {
        res += iter->second - 1;
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= words.length <= 100|
// * |1 <= words[i].length <= 100|
// * |words[i]| consist of only lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: words = ["aba","aabb","abcd","bac","aabc"]
// Output: 2
//
// There are 2 pairs that satisfy the conditions:
// - i = 0 and j = 1 : both words[0] and words[1] only consist of characters 'a'
// and 'b'.
// - i = 3 and j = 4 : both words[3] and words[4] only consist of characters
// 'a', 'b', and 'c'.

LEETCODE_SOLUTION_UNITTEST(2506, CountPairsOfSimilarStrings, example_1) {
  auto           solution = MakeSolution();
  vector<string> words    = {"aba", "aabb", "abcd", "bac", "aabc"};
  int            expect   = 2;
  int            actual   = solution->similarPairs(words);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: words = ["aabb","ab","ba"]
// Output: 3
//
// There are 3 pairs that satisfy the conditions:
// - i = 0 and j = 1 : both words[0] and words[1] only consist of characters 'a'
// and 'b'.
// - i = 0 and j = 2 : both words[0] and words[2] only consist of characters 'a'
// and 'b'.
// - i = 1 and j = 2 : both words[1] and words[2] only consist of characters 'a'
// and 'b'.

LEETCODE_SOLUTION_UNITTEST(2506, CountPairsOfSimilarStrings, example_2) {
  auto           solution = MakeSolution();
  vector<string> words    = {"aabb", "ab", "ba"};
  int            expect   = 3;
  int            actual   = solution->similarPairs(words);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: words = ["nba","cba","dba"]
// Output: 0
//
// Since there does not exist any pair that satisfies the conditions, we return
// 0.

LEETCODE_SOLUTION_UNITTEST(2506, CountPairsOfSimilarStrings, example_3) {
  auto           solution = MakeSolution();
  vector<string> words    = {"nba", "cba", "dba"};
  int            expect   = 0;
  int            actual   = solution->similarPairs(words);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Example #1]
//  Input: words = ["a", "b"]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(2506, CountPairsOfSimilarStrings, extra_example_1) {
  auto           solution = MakeSolution();
  vector<string> words    = {"a", "b"};
  int            expect   = 0;
  int            actual   = solution->similarPairs(words);
  LCD_EXPECT_EQ(expect, actual);
}

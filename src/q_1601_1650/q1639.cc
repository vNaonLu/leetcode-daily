// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Number of Ways to Form a Target String Given a Dictionary
//
// https://leetcode.com/problems/number-of-ways-to-form-a-target-string-given-a-dictionary/
//
// Question ID: 1639
// Difficult  : Hard
// Solve Date : 2023/04/16 15:33

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1639. Number of Ways to Form a Target String Given a
// Dictionary|:
//
// You are given a list of strings of the same length |words| and a string
// |target|. Your task is to form |target| using the given |words| under the
// following rules:
//
//  • |target| should be formed from left to right.
//
//  • To form the |iᵗʰ| character (0-indexed) of |target|, you can choose the
//  |kᵗʰ| character of the |jᵗʰ| string in |words| if |target[i] = words[j][k]|.
//
//  • Once you use the |kᵗʰ| character of the |jᵗʰ| string of |words|, you can
//  no longer use the |xᵗʰ| character of any string in |words| where |x <= k|.
//  In other words, all characters to the left of or at index |k| become
//  unusuable for every string.
//
//  • Repeat the process until you form the string |target|.
// Notice that you can use multiple characters from the same string in |words|
// provided the conditions above are met. Return the number of ways to form
// |target| from |words|. Since the answer may be too large, return it modulo
// |10⁹ + 7|.
//
//

LEETCODE_BEGIN_RESOLVING(1639, NumberOfWaysToFormATargetStringGivenADictionary,
                         Solution);

class Solution {
public:
  int numWays(vector<string> &words, string target) {
    int                 n = words.size();
    int                 E = words.front().size();
    int                 m = target.size();
    vector<vector<int>> freq(E, vector<int>(26));
    for (int i = 0; i < E; ++i) {
      for (int j = 0; j < n; ++j) {
        ++freq[i][words[j][i] - 'a'];
      }
    }
    vector<vector<int64_t>> dp(m + 1, vector<int64_t>(E + 1));
    for (int i = 0; i <= E; ++i) {
      dp[0][i] = 1;
    }
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < E; ++j) {
        int x            = freq[j][target[i] - 'a'];
        dp[i + 1][j + 1] = (dp[i + 1][j] + (dp[i][j] * x) % kMod) % kMod;
      }
    }
    return dp.back().back();
  }

private:
  constexpr static int kMod = 1e9 + 7;
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= words.length <= 1000|
// * |1 <= words[i].length <= 1000|
// * All strings in |words| have the same length.
// * |1 <= target.length <= 1000|
// * |words[i]| and |target| contain only lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: words = ["acca","bbbb","caca"], target = "aba"
// Output: 6
//
// There are 6 ways to form target.
// "aba" -> index 0 ("acca"), index 1 ("bbbb"), index 3 ("caca")
// "aba" -> index 0 ("acca"), index 2 ("bbbb"), index 3 ("caca")
// "aba" -> index 0 ("acca"), index 1 ("bbbb"), index 3 ("acca")
// "aba" -> index 0 ("acca"), index 2 ("bbbb"), index 3 ("acca")
// "aba" -> index 1 ("caca"), index 2 ("bbbb"), index 3 ("acca")
// "aba" -> index 1 ("caca"), index 2 ("bbbb"), index 3 ("caca")

LEETCODE_SOLUTION_UNITTEST(1639,
                           NumberOfWaysToFormATargetStringGivenADictionary,
                           example_1) {
  auto           solution = MakeSolution();
  vector<string> words    = {"acca", "bbbb", "caca"};
  string         target   = "aba";
  int            expect   = 6;
  int            actual   = solution->numWays(words, target);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: words = ["abba","baab"], target = "bab"
// Output: 4
//
// There are 4 ways to form target.
// "bab" -> index 0 ("baab"), index 1 ("baab"), index 2 ("abba")
// "bab" -> index 0 ("baab"), index 1 ("baab"), index 3 ("baab")
// "bab" -> index 0 ("baab"), index 2 ("baab"), index 3 ("baab")
// "bab" -> index 1 ("abba"), index 2 ("baab"), index 3 ("baab")

LEETCODE_SOLUTION_UNITTEST(1639,
                           NumberOfWaysToFormATargetStringGivenADictionary,
                           example_2) {
  auto           solution = MakeSolution();
  vector<string> words    = {"abba", "baab"};
  string         target   = "bab";
  int            expect   = 4;
  int            actual   = solution->numWays(words, target);
  LCD_EXPECT_EQ(expect, actual);
}

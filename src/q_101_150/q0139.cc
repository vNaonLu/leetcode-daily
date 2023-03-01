// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Word Break
//
// https://leetcode.com/problems/word-break/
//
// Question ID: 139
// Difficult  : Medium
// Solve Date : 2021/10/03 11:52

#include <iosfwd>
#include <set>
#include <string>
#include <unordered_set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |139. Word Break|:
//
// Given a string |s| and a dictionary of strings |wordDict|, return |true| if
// |s| can be segmented into a space-separated sequence of one or more
// dictionary words. Note that the same word in the dictionary may be reused
// multiple times in the segmentation.  
//

LEETCODE_BEGIN_RESOLVING(139, WordBreak, Solution);

class Solution {
public:
  bool wordBreak(string s, vector<string> &wordDict) {
    unordered_set<string> dict;
    int                   maxlength = 0;
    for (auto it = wordDict.begin(); it != wordDict.end(); ++it) {
      dict.insert(*it);
      maxlength = max(maxlength, (int)(*it).size());
    }
    vector<bool> dp(s.size() + 1, false);
    dp[0] = true;
    for (int i = 1; i <= s.size(); ++i)
      for (int j = i - 1; j >= max(i - maxlength, 0); --j) {
        if (dp[j] && dict.count(s.substr(j, i - j))) {
          dp[i] = true;
          break;
        }
      }
    return dp.back();
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 300|
// * |1 <= wordDict.length <= 1000|
// * |1 <= wordDict[i].length <= 20|
// * |s| and |wordDict[i]| consist of only lowercase English letters.
// * All the strings of |wordDict| are unique.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "leetcode", wordDict = ["leet","code"]
// Output: true
//
// Return true because "leetcode" can be segmented as "leet code".

LEETCODE_SOLUTION_UNITTEST(139, WordBreak, example_1) {
  auto           solution = MakeSolution();
  string         s        = "leetcode";
  vector<string> wordDict = {"leet", "code"};
  bool           expect   = true;
  bool           actual   = solution->wordBreak(s, wordDict);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "applepenapple", wordDict = ["apple","pen"]
// Output: true
//
// Return true because "applepenapple" can be segmented as "apple pen apple".
// Note that you are allowed to reuse a dictionary word.

LEETCODE_SOLUTION_UNITTEST(139, WordBreak, example_2) {
  auto           solution = MakeSolution();
  string         s        = "applepenapple";
  vector<string> wordDict = {"apple", "pen"};
  bool           expect   = true;
  bool           actual   = solution->wordBreak(s, wordDict);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "catsandog", wordDict = ["cats","dog","sand","and","cat"]
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(139, WordBreak, example_3) {
  auto           solution = MakeSolution();
  string         s        = "catsandog";
  vector<string> wordDict = {"cats", "dog", "sand", "and", "cat"};
  bool           expect   = false;
  bool           actual   = solution->wordBreak(s, wordDict);
  LCD_EXPECT_EQ(expect, actual);
}

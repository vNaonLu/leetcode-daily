#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

/**
 * This file is generated by leetcode_add.py v1.0
 *
 * 139.
 *      Word Break
 *
 * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
 *
 *   Given a string ‘s’ and a dictionary of strings ‘wordDict’ , return
 *   ‘true’ if ‘s’ can be segmented into a space-separated sequence of one
 *   or more dictionary
 *    “Note” that the same word in the dictionary may be reused multiple
 *   times in the segmentation.
 *
 * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
 *
 *   • ‘1 ≤ s.length ≤ 300’
 *   • ‘1 ≤ wordDict.length ≤ 1000’
 *   • ‘1 ≤ wordDict[i].length ≤ 20’
 *   • ‘s’ and ‘wordDict[i]’ consist of only lowercase English letters.
 *   • All the strings of ‘wordDict’ are “unique” .
 *
 */

struct q139 : public ::testing::Test {
  // Leetcode answer here
  class Solution {
   public:
    bool wordBreak(string s, vector<string>& wordDict) {
      unordered_set<string> dict;
      int maxlength = 0;
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

  class Solution *solution;
};

TEST_F(q139, sample_input01) {
  solution = new Solution();
  string s = "leetcode";
  vector<string> wordDict = {"leet", "code"};
  bool exp = true;
  EXPECT_EQ(solution->wordBreak(s, wordDict), exp);
  delete solution;
}

TEST_F(q139, sample_input02) {
  solution = new Solution();
  string s = "applepenapple";
  vector<string> wordDict = {"apple", "pen"};
  bool exp = true;
  EXPECT_EQ(solution->wordBreak(s, wordDict), exp);
  delete solution;
}

TEST_F(q139, sample_input03) {
  solution = new Solution();
  string s = "catsandog";
  vector<string> wordDict = {"cats", "dog", "sand", "and", "cat"};
  bool exp = false;
  EXPECT_EQ(solution->wordBreak(s, wordDict), exp);
  delete solution;
}
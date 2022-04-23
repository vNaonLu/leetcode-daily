#include <gtest/gtest.h>
#include <iostream>
#include <queue>
#include <string>

using namespace std;

/**
 * This file is generated by leetcode_add.py
 *
 * 767.
 *      Reorganize String
 *
 * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
 *
 *   Given a string ‘s’ , rearrange the characters of ‘s’ so that any two
 *   adjacent characters are not the
 *   Return “any possible rearrangement of” ‘s’ “or return” ‘''’ “if not
 *   possible” .
 *
 * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
 *
 *   • ‘1 ≤ s.length ≤ 500’
 *   • ‘s’ consists of lowercase English letters.
 *
 */

struct q767 : public ::testing::Test {
  // Leetcode answer here
  class Solution {
   public:
    string reorganizeString(string s) {
      vector<int> cnt(26, 0);
      auto comp = [](const pair<int, int> &x, const pair<int, int> &y) {
        return x.second < y.second;
      };
      priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(comp)> q(comp);
      for (const auto &c : s) ++cnt[c - 'a'];
      for (int i = 0; i < cnt.size(); ++i) {
        if (cnt[i] != 0) {
          q.emplace(i, cnt[i]);
        }
      }
      string res;
      while (!q.empty()) {
        auto [c, cnt] = q.top(); q.pop();
        if (c != res.back() - 'a') {
          res.push_back(c + 'a');
          if (--cnt != 0) q.emplace(c, cnt);
        } else {
          if (q.empty()) return "";
          auto [next, next_cnt] = q.top(); q.pop();
          res.push_back(next + 'a');
          if (--next_cnt != 0) q.emplace(next, next_cnt);
          q.emplace(c, cnt);
        }
      }
      return res;
    }
  };

  class Solution *solution;
};

TEST_F(q767, sample_input01) {
  solution = new Solution();
  string s = "aab";
  string exp = "aba";
  string act = solution->reorganizeString(s);
  EXPECT_EQ(act, exp);
  delete solution;
}

TEST_F(q767, sample_input02) {
  solution = new Solution();
  string s = "aaab";
  string exp = "";
  string act = solution->reorganizeString(s);
  EXPECT_EQ(act, exp);
  delete solution;
}
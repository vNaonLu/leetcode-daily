// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Similar String Groups
//
// https://leetcode.com/problems/similar-string-groups/
//
// Question ID: 839
// Difficult  : Hard
// Solve Date : 2023/04/28 11:33

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |839. Similar String Groups|:
//
// Two strings |X| and |Y| are similar if we can swap two letters (in different
// positions) of |X|, so that it equals |Y|. Also two strings |X| and |Y| are
// similar if they are equal. For example, |"tars"| and |"rats"| are similar
// (swapping at positions |0| and |2|), and |"rats"| and |"arts"| are similar,
// but |"star"| is not similar to |"tars"|, |"rats"|, or |"arts"|. Together,
// these form two connected groups by similarity: |{"tars", "rats", "arts"}| and
// |{"star"}|.  Notice that |"tars"| and |"arts"| are in the same group even
// though they are not similar.  Formally, each group is such that a word is in
// the group if and only if it is similar to at least one other word in the
// group. We are given a list |strs| of strings where every string in |strs| is
// an anagram of every other string in |strs|. How many groups are there?
//
//

LEETCODE_BEGIN_RESOLVING(839, SimilarStringGroups, Solution);

class Solution {
public:
  int numSimilarGroups(vector<string> &strs) {
    int                 n   = strs.size();
    int                 res = 0;
    vector<vector<int>> adj = createGraph(strs, n);
    vector<bool>        vis(n, false);
    for (int i = 0; i < n; ++i) {
      if (!vis[i]) {
        dfs(i, vis, adj);
        ++res;
      }
    }
    return res;
  }

private:
  void dfs(int i, vector<bool> &vis, vector<vector<int>> &adj) {
    vis[i] = true;
    for (int j : adj[i]) {
      if (!vis[j]) {
        dfs(j, vis, adj);
      }
    }
  }
  vector<vector<int>> createGraph(vector<string> &strs, int n) {
    vector<vector<int>> res(n);
    for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        if (isSimilar(strs[i], strs[j])) {
          res[i].emplace_back(j);
          res[j].emplace_back(i);
        }
      }
    }
    return res;
  }
  bool isSimilar(string &a, string &b) {
    int c = 0;
    for (int i = 0; i < a.size(); ++i) {
      if (a[i] != b[i]) {
        ++c;
      }
    }
    return c == 0 || c == 2;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= strs.length <= 300|
// * |1 <= strs[i].length <= 300|
// * |strs[i]| consists of lowercase letters only.
// * All words in |strs| have the same length and are anagrams of each other.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: strs = ["tars","rats","arts","star"]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(839, SimilarStringGroups, example_1) {
  auto           solution = MakeSolution();
  vector<string> strs     = {"tars", "rats", "arts", "star"};
  int            expect   = 2;
  int            actual   = solution->numSimilarGroups(strs);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: strs = ["omv","ovm"]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(839, SimilarStringGroups, example_2) {
  auto           solution = MakeSolution();
  vector<string> strs     = {"omv", "ovm"};
  int            expect   = 1;
  int            actual   = solution->numSimilarGroups(strs);
  LCD_EXPECT_EQ(expect, actual);
}

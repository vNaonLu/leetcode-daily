// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Longest Path With Different Adjacent Characters
//
// https://leetcode.com/problems/longest-path-with-different-adjacent-characters/
//
// Question ID: 2246
// Difficult  : Hard
// Solve Date : 2023/01/13 19:09

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2246. Longest Path With Different Adjacent Characters|:
//
// You are given a tree (i.e. a connected, undirected graph that has no cycles)
// rooted at node |0| consisting of |n| nodes numbered from |0| to |n - 1|. The
// tree is represented by a 0-indexed array |parent| of size |n|, where
// |parent[i]| is the parent of node |i|. Since node |0| is the root, |parent[0]
// == -1|. You are also given a string |s| of length |n|, where |s[i]| is the
// character assigned to node |i|. Return the length of the longest path in the
// tree such that no pair of adjacent nodes on the path have the same character
// assigned to them.
//

LEETCODE_BEGIN_RESOLVING(2246, LongestPathWithDifferentAdjacentCharacters,
                         Solution);

class Solution {
private:
  int dfs(vector<vector<int>> &x, int &res, int i, string &s) {
    if (x[i].size() == 0) {
      return 1;
    }
    vector<int> e;
    int         len1 = 0, len2 = 0;
    for (int j = 0; j < x[i].size(); ++j) {
      auto tmp = dfs(x, res, x[i][j], s);
      if (s[x[i][j]] == s[i]) {
        tmp = 0;
      }
      if (tmp > len1) {
        len2 = len1;
        len1 = tmp;
      } else if (tmp > len2) {
        len2 = tmp;
      }
    }
    res = max(res, len1 + len2 + 1);
    return len1 + 1;
  }

public:
  int longestPath(vector<int> &parent, string s) {
    auto                n = parent.size();
    vector<vector<int>> x(n);
    int                 res = 1;
    for (int i = 0; i < n; ++i) {
      if (parent[i] != -1) {
        x[parent[i]].emplace_back(i);
      }
    }
    dfs(x, res, 0, s);
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == parent.length == s.length|
// * |1 <= n <= 10⁵|
// * |0 <= parent[i] <= n - 1| for all |i >= 1|
// * |parent[0] == -1|
// * |parent| represents a valid tree.
// * |s| consists of only lowercase English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: parent = [-1,0,0,1,1,2], s = "abacbe"
// Output: 3
//
// The longest path where each two adjacent nodes have different characters in
// the tree is the path: 0 -> 1 -> 3. The length of this path is 3, so 3 is
// returned. It can be proven that there is no longer path that satisfies the
// conditions.

LEETCODE_SOLUTION_UNITTEST(2246, LongestPathWithDifferentAdjacentCharacters,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> parent   = {-1, 0, 0, 1, 1, 2};
  string      s        = "abacbe";
  int         expect   = 3;
  int         actual   = solution->longestPath(parent, s);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: parent = [-1,0,0,0], s = "aabc"
// Output: 3
//
// The longest path where each two adjacent nodes have different characters is
// the path: 2 -> 0 -> 3. The length of this path is 3, so 3 is returned.

LEETCODE_SOLUTION_UNITTEST(2246, LongestPathWithDifferentAdjacentCharacters,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> parent   = {-1, 0, 0, 0};
  string      s        = "aabc";
  int         expect   = 3;
  int         actual   = solution->longestPath(parent, s);
  LCD_EXPECT_EQ(expect, actual);
}

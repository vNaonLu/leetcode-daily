// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Smallest String With Swaps
//
// https://leetcode.com/problems/smallest-string-with-swaps/
//
// Question ID: 1202
// Difficult  : Medium
// Solve Date : 2022/04/27 18:21

#include <algorithm>
#include <array>
#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1202. Smallest String With Swaps|:
//
// You are given a string |s|, and an array of pairs of indices in the string 
// |pairs| where  |pairs[i] = [a, b]| indicates 2 indices(0-indexed) of the
// string. You can swap the characters at any pair of indices in the given 
// |pairs| any number of times. Return the lexicographically smallest string
// that |s| can be changed to after using the swaps.  
//

LEETCODE_BEGIN_RESOLVING(1202, SmallestStringWithSwaps, Solution);

class Solution {
private:
  static const int      N = 100001;
  array<vector<int>, N> adj;
  array<bool, N>        visited;

  void dfs(string &s, int v, vector<char> &ch, vector<int> &indices) {
    ch.emplace_back(s[v]);
    indices.emplace_back(v);

    visited[v] = true;
    for (int &a : adj[v]) {
      if (!visited[a]) {
        dfs(s, a, ch, indices);
      }
    }
  }

public:
  string smallestStringWithSwaps(string s, vector<vector<int>> &pairs) {
    for (auto &v : pairs) {
      int i = v[0], j = v[1];
      adj[i].emplace_back(j);
      adj[j].emplace_back(i);
    }

    for (int i = 0; i < s.size(); ++i) {
      if (!visited[i]) {
        vector<char> chs;
        vector<int>  ind;
        dfs(s, i, chs, ind);

        sort(chs.begin(), chs.end());
        sort(ind.begin(), ind.end());

        for (int j = 0; j < chs.size(); ++j) {
          s[ind[j]] = chs[j];
        }
      }
    }

    return s;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= s.length <= 10^5|
// * |0 <= pairs.length <= 10^5|
// * |0 <= pairs[i][0], pairs[i][1] < s.length|
// * |s| only contains lower case English letters.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: s = "dcab", pairs = [[0,3],[1,2]]
// Output: "bacd"
// Explaination:
// Swap s[0] and s[3], s = "bcad"
// Swap s[1] and s[2], s = "bacd"
//

LEETCODE_SOLUTION_UNITTEST(1202, SmallestStringWithSwaps, example_1) {
  auto                solution = MakeSolution();
  string              s        = "dcab";
  vector<vector<int>> pairs    = {
      {0, 3},
      {1, 2}
  };
  string expect = "bacd";
  string actual = solution->smallestStringWithSwaps(s, pairs);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: s = "dcab", pairs = [[0,3],[1,2],[0,2]]
// Output: "abcd"
// Explaination:
// Swap s[0] and s[3], s = "bcad"
// Swap s[0] and s[2], s = "acbd"
// Swap s[1] and s[2], s = "abcd"
//

LEETCODE_SOLUTION_UNITTEST(1202, SmallestStringWithSwaps, example_2) {
  auto                solution = MakeSolution();
  string              s        = "dcab";
  vector<vector<int>> pairs    = {
      {0, 3},
      {1, 2},
      {0, 2}
  };
  string expect = "abcd";
  string actual = solution->smallestStringWithSwaps(s, pairs);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: s = "cba", pairs = [[0,1],[1,2]]
// Output: "abc"
// Explaination:
// Swap s[0] and s[1], s = "bca"
// Swap s[1] and s[2], s = "bac"
// Swap s[0] and s[1], s = "abc"
//

LEETCODE_SOLUTION_UNITTEST(1202, SmallestStringWithSwaps, example_3) {
  auto                solution = MakeSolution();
  string              s        = "cba";
  vector<vector<int>> pairs    = {
      {0, 1},
      {1, 2}
  };
  string expect = "abc";
  string actual = solution->smallestStringWithSwaps(s, pairs);
  LCD_EXPECT_EQ(expect, actual);
}

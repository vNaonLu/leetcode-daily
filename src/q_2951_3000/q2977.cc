// Copyright 2026 Naon Lu
//
// This file describes the solution of
// Minimum Cost to Convert String II
//
// https://leetcode.com/problems/minimum-cost-to-convert-string-ii/
//
// Question ID: 2977
// Difficult  : Hard
// Solve Date : 2026/01/30 20:48

#include <iosfwd>
#include <string>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2977. Minimum Cost to Convert String II|:
//
// You are given two 0-indexed strings |source| and |target|, both of length |n|
// and consisting of lowercase English characters. You are also given two
// 0-indexed string arrays |original| and |changed|, and an integer array
// |cost|, where |cost[i]| represents the cost of converting the string
// |original[i]| to the string |changed[i]|. You start with the string |source|.
// In one operation, you can pick a substring |x| from the string, and change it
// to |y| at a cost of |z| if there exists any index |j| such that |cost[j] ==
// z|, |original[j] == x|, and |changed[j] == y|. You are allowed to do any
// number of operations, but any pair of operations must satisfy either of these
// two conditions:
//
//  • The substrings picked in the operations are |source[a..b]| and
//  |source[c..d]| with either |b < c| or |d < a|. In other words, the indices
//  picked in both operations are disjoint.
//
//  • The substrings picked in the operations are |source[a..b]| and
//  |source[c..d]| with |a == c| and |b == d|. In other words, the indices
//  picked in both operations are identical.
// Return the minimum cost to convert the string |source| to the string |target|
// using any number of operations. If it is impossible to convert |source| to
// |target|, return |-1|. Note that there may exist indices |i|, |j| such that
// |original[j] == original[i]| and |changed[j] == changed[i]|.
//
//

LEETCODE_BEGIN_RESOLVING(2977, MinimumCostToConvertStringII, Solution);

class Solution {
public:
  const long long INF = 1e18;

  unordered_map<string, int> mp;
  vector<vector<long long>>  dist;
  string                     src, tgt;
  int                        n;
  vector<long long>          dp;

  long long solve(int i) {
    if (i == n)
      return 0;
    if (dp[i] != -1)
      return dp[i];

    long long ans = INF;
    if (src[i] == tgt[i]) {
      ans = min(ans, solve(i + 1));
    }

    for (auto &p1 : mp) {

      const string &s1  = p1.first;
      int           u   = p1.second;
      int           len = s1.size();

      if (i + len > n)
        continue;
      if (src.compare(i, len, s1) != 0)
        continue;

      for (auto &p2 : mp) {
        const string &s2 = p2.first;
        int           v  = p2.second;

        if (tgt.compare(i, len, s2) != 0)
          continue;
        if (dist[u][v] == INF)
          continue;

        ans = min(ans, dist[u][v] + solve(i + len));
      }
    }

    return dp[i] = ans;
  }

  long long minimumCost(string source, string target, vector<string> &original,
                        vector<string> &changed, vector<int> &cost) {
    src = source;
    tgt = target;
    n   = source.size();

    int cnt = 0;
    for (int i = 0; i < original.size(); i++) {
      if (!mp.count(original[i]))
        mp[original[i]] = cnt++;
      if (!mp.count(changed[i]))
        mp[changed[i]] = cnt++;
    }

    dist.assign(cnt, vector<long long>(cnt, INF));

    for (int i = 0; i < cnt; i++)
      dist[i][i] = 0;

    for (int i = 0; i < original.size(); i++) {
      int u      = mp[original[i]];
      int v      = mp[changed[i]];
      dist[u][v] = min(dist[u][v], (long long)cost[i]);
    }

    for (int k = 0; k < cnt; k++)
      for (int i = 0; i < cnt; i++)
        for (int j = 0; j < cnt; j++)
          dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

    dp.assign(n, -1);
    long long ans = solve(0);

    if (ans >= INF)
      return -1;

    return ans;
  }
};
LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= source.length == target.length <= 1000|
// * |source|, |target| consist only of lowercase English characters.
// * |1 <= cost.length == original.length == changed.length <= 100|
// * |1 <= original[i].length == changed[i].length <= source.length|
// * |original[i]|, |changed[i]| consist only of lowercase English characters.
// * |original[i] != changed[i]|
// * |1 <= cost[i] <= 10⁶|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: source = "abcd", target = "acbe", original =
//  ["a","b","c","c","e","d"], changed = ["b","c","b","e","b","e"], cost =
//  [2,5,5,1,2,20]
// Output: 28
//

LEETCODE_SOLUTION_UNITTEST(2977, MinimumCostToConvertStringII, example_1) {
  auto           solution = MakeSolution();
  string         source   = "abcd";
  string         target   = "acbe";
  vector<string> original = {"a", "b", "c", "c", "e", "d"};
  vector<string> changed  = {"b", "c", "b", "e", "b", "e"};
  vector<int>    cost     = {2, 5, 5, 1, 2, 20};
  long long      expect   = 28;
  long long      actual =
      solution->minimumCost(source, target, original, changed, cost);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: source = "abcdefgh", target = "acdeeghh", original =
//  ["bcd","fgh","thh"], changed = ["cde","thh","ghh"], cost = [1,3,5]
// Output: 9
//

LEETCODE_SOLUTION_UNITTEST(2977, MinimumCostToConvertStringII, example_2) {
  auto           solution = MakeSolution();
  string         source   = "abcdefgh";
  string         target   = "acdeeghh";
  vector<string> original = {"bcd", "fgh", "thh"};
  vector<string> changed  = {"cde", "thh", "ghh"};
  vector<int>    cost     = {1, 3, 5};
  long long      expect   = 9;
  long long      actual =
      solution->minimumCost(source, target, original, changed, cost);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: source = "abcdefgh", target = "addddddd", original = ["bcd","defgh"],
//  changed = ["ddd","ddddd"], cost = [100,1578]
// Output: -1
//

LEETCODE_SOLUTION_UNITTEST(2977, MinimumCostToConvertStringII, example_3) {
  auto           solution = MakeSolution();
  string         source   = "abcdefgh";
  string         target   = "addddddd";
  vector<string> original = {"bcd", "defgh"};
  vector<string> changed  = {"ddd", "ddddd"};
  vector<int>    cost     = {100, 1578};
  long long      expect   = -1;
  long long      actual =
      solution->minimumCost(source, target, original, changed, cost);
  LCD_EXPECT_EQ(expect, actual);
}

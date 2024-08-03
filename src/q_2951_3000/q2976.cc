// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Minimum Cost to Convert String I
//
// https://leetcode.com/problems/minimum-cost-to-convert-string-i/
//
// Question ID: 2976
// Difficult  : Medium
// Solve Date : 2024/07/27 12:45

#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2976. Minimum Cost to Convert String I|:
//
// You are given two 0-indexed strings |source| and |target|, both of length |n|
// and consisting of lowercase English letters. You are also given two 0-indexed
// character arrays |original| and |changed|, and an integer array |cost|, where
// |cost[i]| represents the cost of changing the character |original[i]| to the
// character |changed[i]|. You start with the string |source|. In one operation,
// you can pick a character |x| from the string and change it to the character
// |y| at a cost of |z| if there exists any index |j| such that |cost[j] == z|,
// |original[j] == x|, and |changed[j] == y|. Return the minimum cost to convert
// the string |source| to the string |target| using any number of operations. If
// it is impossible to convert |source| to |target|, return |-1|. Note that
// there may exist indices |i|, |j| such that |original[j] == original[i]| and
// |changed[j] == changed[i]|.
//
//

LEETCODE_BEGIN_RESOLVING(2976, MinimumCostToConvertStringI, Solution);

class Solution {
public:
  long long minimumCost(string source, string target, vector<char> &original,
                        vector<char> &changed, vector<int> &cost) {
    auto conversion = buildConversionGraph(original, changed, cost);
    return computeTotalConversionCost(source, target, conversion);
  }

private:
  static constexpr int CHAR_COUNT = 26;
  static constexpr int INF        = 1e9;

  vector<vector<int>> buildConversionGraph(vector<char> const &ori,
                                           vector<char> const &changed,
                                           vector<int> const  &cost) {
    vector<vector<int>> graph(CHAR_COUNT, vector<int>(CHAR_COUNT, INF));
    for (int i = 0; i < CHAR_COUNT; ++i) {
      graph[i][i] = 0;
    }
    for (int i = 0; i < cost.size(); ++i) {
      int from        = ori[i] - 'a';
      int to          = changed[i] - 'a';
      graph[from][to] = min(graph[from][to], cost[i]);
    }
    optimize(&graph);
    return graph;
  }

  void optimize(vector<vector<int>> *graph) {
    for (int k = 0; k < CHAR_COUNT; ++k) {
      for (int i = 0; i < CHAR_COUNT; ++i) {
        if ((*graph)[i][k] < INF) {
          for (int j = 0; j < CHAR_COUNT; ++j) {
            if ((*graph)[k][j] < INF) {
              (*graph)[i][j] =
                  min((*graph)[i][j], (*graph)[i][k] + (*graph)[k][j]);
            }
          }
        }
      }
    }
  }

  int64_t computeTotalConversionCost(string const &source, string const &target,
                                     vector<vector<int>> const &graph) {
    int64_t res = 0;
    for (int i = 0; i < source.size(); ++i) {
      int s = source[i] - 'a';
      int t = target[i] - 'a';
      if (s != t) {
        if (graph[s][t] == INF) {
          return -1;
        }
        res += graph[s][t];
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= source.length == target.length <= 10⁵|
// * |source|, |target| consist of lowercase English letters.
// * |1 <= cost.length == original.length == changed.length <= 2000|
// * |original[i]|, |changed[i]| are lowercase English letters.
// * |1 <= cost[i] <= 10⁶|
// * |original[i] != changed[i]|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: source = "abcd", target = "acbe", original =
//  ["a","b","c","c","e","d"], changed = ["b","c","b","e","b","e"], cost =
//  [2,5,5,1,2,20]
// Output: 28
//

LEETCODE_SOLUTION_UNITTEST(2976, MinimumCostToConvertStringI, example_1) {
  auto         solution = MakeSolution();
  string       source   = "abcd";
  string       target   = "acbe";
  vector<char> original = {'a', 'b', 'c', 'c', 'e', 'd'};
  vector<char> changed  = {'b', 'c', 'b', 'e', 'b', 'e'};
  vector<int>  cost     = {2, 5, 5, 1, 2, 20};
  long long    expect   = 28;
  long long    actual =
      solution->minimumCost(source, target, original, changed, cost);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: source = "aaaa", target = "bbbb", original = ["a","c"], changed =
//  ["c","b"], cost = [1,2]
// Output: 12
//

LEETCODE_SOLUTION_UNITTEST(2976, MinimumCostToConvertStringI, example_2) {
  auto         solution = MakeSolution();
  string       source   = "aaaa";
  string       target   = "bbbb";
  vector<char> original = {'a', 'c'};
  vector<char> changed  = {'c', 'b'};
  vector<int>  cost     = {1, 2};
  long long    expect   = 12;
  long long    actual =
      solution->minimumCost(source, target, original, changed, cost);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: source = "abcd", target = "abce", original = ["a"], changed = ["e"],
//  cost = [10000]
// Output: -1
//

LEETCODE_SOLUTION_UNITTEST(2976, MinimumCostToConvertStringI, example_3) {
  auto         solution = MakeSolution();
  string       source   = "abcd";
  string       target   = "abce";
  vector<char> original = {'a'};
  vector<char> changed  = {'e'};
  vector<int>  cost     = {10000};
  long long    expect   = -1;
  long long    actual =
      solution->minimumCost(source, target, original, changed, cost);
  LCD_EXPECT_EQ(expect, actual);
}

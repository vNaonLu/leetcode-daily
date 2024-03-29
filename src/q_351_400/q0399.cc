// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Evaluate Division
//
// https://leetcode.com/problems/evaluate-division/
//
// Question ID: 399
// Difficult  : Medium
// Solve Date : 2022/04/30 10:39

#include <iosfwd>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |399. Evaluate Division|:
//
// You are given an array of variable pairs |equations| and an array of real
// numbers |values|, where |equations[i] = [Aᵢ, Bᵢ]| and |values[i]| represent
// the equation |Aᵢ / Bᵢ = values[i]|. Each |Aᵢ| or |Bᵢ| is a string that
// represents a single variable. You are also given some |queries|, where
// |queries[j] = [Cⱼ, Dⱼ]| represents the |jᵗʰ| query where you must find the
// answer for |Cⱼ / Dⱼ = ?|. Return the answers to all queries. If a single
// answer cannot be determined, return |-1.0|. Note: The input is always valid.
// You may assume that evaluating the queries will not result in division by
// zero and that there is no contradiction.  
//

LEETCODE_BEGIN_RESOLVING(399, EvaluateDivision, Solution);

class Solution {
private:
  void dfs(const string &start, const string &end,
           unordered_map<string, double>         &mp,
           unordered_map<string, vector<string>> &graph, double &val,
           unordered_map<string, int> &visited, bool &found) {
    visited[start] = 1;

    if (found == true) {
      return;
    }

    for (auto child : graph[start]) {
      if (visited[child] != 1) {
        val *= mp[start + "->" + child];
        if (end == child) {
          found = true;
          return;
        }
        dfs(child, end, mp, graph, val, visited, found);
        if (found == true) {
          return;
        } else {
          val /= mp[start + "->" + child];
        }
      }
    }
  }

public:
  vector<double> calcEquation(vector<vector<string>> &equations,
                              vector<double>         &values,
                              vector<vector<string>> &queries) {
    vector<double>                        ans;
    unordered_map<string, double>         mp;
    unordered_map<string, vector<string>> graph;
    for (int i = 0; i < equations.size(); i++) {
      string u         = equations[i][0];
      string v         = equations[i][1];
      mp[u + "->" + v] = values[i];
      mp[v + "->" + u] = 1 / values[i];
      graph[u].push_back(v);
      graph[v].push_back(u);
    }

    for (int i = 0; i < queries.size(); i++) {
      string start = queries[i][0];
      string end   = queries[i][1];
      if (graph.find(start) == graph.end() || graph.find(end) == graph.end()) {
        ans.push_back(-1);
      } else {
        double                     val = 1;
        unordered_map<string, int> visited;
        bool                       found = false;
        if (start == end) {
          found = true;
        } else
          dfs(start, end, mp, graph, val, visited, found);
        if (found == true)
          ans.push_back(val);
        else
          ans.push_back(-1);
      }
    }
    return ans;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= equations.length <= 20|
// * |equations[i].length == 2|
// * |1 <= Aᵢ.length, Bᵢ.length <= 5|
// * |values.length == equations.length|
// * |0.0 < values[i] <= 20.0|
// * |1 <= queries.length <= 20|
// * |queries[i].length == 2|
// * |1 <= Cⱼ.length, Dⱼ.length <= 5|
// * |Aᵢ, Bᵢ, Cⱼ, Dⱼ| consist of lower case English letters and digits.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: equations = [["a","b"],["b","c"]], values = [2.0,3.0], queries =
//  [["a","c"],["b","a"],["a","e"],["a","a"],["x","x"]]
// Output: [6.00000,0.50000,-1.00000,1.00000,-1.00000]
//
// Given: a / b = 2.0, b / c = 3.0
// queries are: a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ?
// return: [6.0, 0.5, -1.0, 1.0, -1.0 ]

LEETCODE_SOLUTION_UNITTEST(399, EvaluateDivision, example_1) {
  auto                   solution  = MakeSolution();
  vector<vector<string>> equations = {
      {"a", "b"},
      {"b", "c"}
  };
  vector<double>         values  = {2.0, 3.0};
  vector<vector<string>> queries = {
      {"a", "c"},
      {"b", "a"},
      {"a", "e"},
      {"a", "a"},
      {"x", "x"}
  };
  vector<double> expect = {6.00000, 0.50000, -1.00000, 1.00000, -1.00000};
  vector<double> actual = solution->calcEquation(equations, values, queries);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: equations = [["a","b"],["b","c"],["bc","cd"]], values =
//  [1.5,2.5,5.0], queries = [["a","c"],["c","b"],["bc","cd"],["cd","bc"]]
// Output: [3.75000,0.40000,5.00000,0.20000]
//

LEETCODE_SOLUTION_UNITTEST(399, EvaluateDivision, example_2) {
  auto                   solution  = MakeSolution();
  vector<vector<string>> equations = {
      { "a",  "b"},
      { "b",  "c"},
      {"bc", "cd"}
  };
  vector<double>         values  = {1.5, 2.5, 5.0};
  vector<vector<string>> queries = {
      { "a",  "c"},
      { "c",  "b"},
      {"bc", "cd"},
      {"cd", "bc"}
  };
  vector<double> expect = {3.75000, 0.40000, 5.00000, 0.20000};
  vector<double> actual = solution->calcEquation(equations, values, queries);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: equations = [["a","b"]], values = [0.5], queries =
//  [["a","b"],["b","a"],["a","c"],["x","y"]]
// Output: [0.50000,2.00000,-1.00000,-1.00000]
//

LEETCODE_SOLUTION_UNITTEST(399, EvaluateDivision, example_3) {
  auto                   solution  = MakeSolution();
  vector<vector<string>> equations = {
      {"a", "b"}
  };
  vector<double>         values  = {0.5};
  vector<vector<string>> queries = {
      {"a", "b"},
      {"b", "a"},
      {"a", "c"},
      {"x", "y"}
  };
  vector<double> expect = {0.50000, 2.00000, -1.00000, -1.00000};
  vector<double> actual = solution->calcEquation(equations, values, queries);
  LCD_EXPECT_EQ(expect, actual);
}

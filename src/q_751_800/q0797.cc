// Copyright 2023 Naon Lu
//
// This file describes the solution of
// All Paths From Source to Target
//
// https://leetcode.com/problems/all-paths-from-source-to-target/
//
// Question ID: 797
// Difficult  : Medium
// Solve Date : 2021/09/26 15:53

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |797. All Paths From Source to Target|:
//
// Given a directed acyclic graph (DAG) of |n| nodes labeled from |0| to |n -
// 1|, find all possible paths from node |0| to node |n - 1| and return them in
// any order. The graph is given as follows: |graph[i]| is a list of all nodes
// you can visit from node |i| (i.e., there is a directed edge from node |i| to
// node |graph[i][j]|).  
//

LEETCODE_BEGIN_RESOLVING(797, AllPathsFromSourceToTarget, Solution);

class Solution {
private:
  void helper(vector<vector<int>> &graph, vector<vector<int>> &r,
              vector<int> &path, int target = 0) {
    path.push_back(target);
    if (target == graph.size() - 1) {
      r.push_back(path);
    } else {
      for (const int &dest : graph[target]) {
        if (find(path.begin(), path.end(), dest) == path.end())
          helper(graph, r, path, dest);
      }
    }
    path.pop_back();
  }

public:
  vector<vector<int>> allPathsSourceTarget(vector<vector<int>> &graph) {
    vector<vector<int>> res;
    vector<int>         path;
    helper(graph, res, path);
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |n == graph.length|
// * |2 <= n <= 15|
// * |0 <= graph[i][j] < n|
// * |graph[i][j] != i| (i.e., there will be no self-loops).
// * All the elements of |graph[i]| are unique.
// * The input graph is guaranteed to be a DAG.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: graph = [[1,2],[3],[3],[]]
// Output: [[0,1,3],[0,2,3]]
//
// There are two paths: 0 -> 1 -> 3 and 0 -> 2 -> 3.

LEETCODE_SOLUTION_UNITTEST(797, AllPathsFromSourceToTarget, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> graph    = {
      {1, 2},
      {3},
      {3},
      {}
  };
  vector<vector<int>> expect = {
      {0, 1, 3},
      {0, 2, 3}
  };
  vector<vector<int>> actual = solution->allPathsSourceTarget(graph);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #2]
//  Input: graph = [[4,3,1],[3,2,4],[3],[4],[]]
// Output: [[0,4],[0,3,4],[0,1,3,4],[0,1,2,3,4],[0,1,4]]
//

LEETCODE_SOLUTION_UNITTEST(797, AllPathsFromSourceToTarget, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> graph    = {
      {4, 3, 1},
      {3, 2, 4},
      {3},
      {4},
      {}
  };
  vector<vector<int>> expect = {
      {0, 4},
      {0, 3, 4},
      {0, 1, 3, 4},
      {0, 1, 2, 3, 4},
      {0, 1, 4}
  };
  vector<vector<int>> actual = solution->allPathsSourceTarget(graph);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Find Center of Star Graph
//
// https://leetcode.com/problems/find-center-of-star-graph/
//
// Question ID: 1791
// Difficult  : Easy
// Solve Date : 2022/02/23 19:25

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1791. Find Center of Star Graph|:
//
// There is an undirected star graph consisting of |n| nodes labeled from |1| to
// |n|. A star graph is a graph where there is one center node and exactly |n -
// 1| edges that connect the center node with every other node. You are given a
// 2D integer array |edges| where each |edges[i] = [uᵢ, vᵢ]| indicates that
// there is an edge between the nodes |uᵢ| and |vᵢ|. Return the center of the
// given star graph.  
//

LEETCODE_BEGIN_RESOLVING(1791, FindCenterOfStarGraph, Solution);

class Solution {
public:
  int findCenter(vector<vector<int>> &edges) {
    return edges[0][0] == edges[1][0]
               ? edges[0][0]
               : (edges[0][0] == edges[1][1] ? edges[0][0] : edges[0][1]);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |3 <= n <= 10⁵|
// * |edges.length == n - 1|
// * |edges[i].length == 2|
// * |1 <= u^{i,} vᵢ <= n|
// * |uᵢ != vᵢ|
// * The given |edges| represent a valid star graph.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: edges = [[1,2],[2,3],[4,2]]
// Output: 2
//
// As shown in the figure above, node 2 is connected to every other node, so 2
// is the center.

LEETCODE_SOLUTION_UNITTEST(1791, FindCenterOfStarGraph, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> edges    = {
      {1, 2},
      {2, 3},
      {4, 2}
  };
  int expect = 2;
  int actual = solution->findCenter(edges);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: edges = [[1,2],[5,1],[1,3],[1,4]]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(1791, FindCenterOfStarGraph, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> edges    = {
      {1, 2},
      {5, 1},
      {1, 3},
      {1, 4}
  };
  int expect = 1;
  int actual = solution->findCenter(edges);
  LCD_EXPECT_EQ(expect, actual);
}

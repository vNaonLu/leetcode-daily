// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Path with Maximum Probability
//
// https://leetcode.com/problems/path-with-maximum-probability/
//
// Question ID: 1514
// Difficult  : Medium
// Solve Date : 2023/06/28 21:18

#include <iosfwd>
#include <queue>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1514. Path with Maximum Probability|:
//
// You are given an undirected weighted graph of |n| nodes (0-indexed),
// represented by an edge list where |edges[i] = [a, b]| is an undirected edge
// connecting the nodes |a| and |b| with a probability of success of traversing
// that edge |succProb[i]|. Given two nodes |start| and |end|, find the path
// with the maximum probability of success to go from |start| to |end| and
// return its success probability. If there is no path from |start| to |end|,
// return 0. Your answer will be accepted if it differs from the correct answer
// by at most 1e-5.
//
//

LEETCODE_BEGIN_RESOLVING(1514, PathWithMaximumProbability, Solution);

class Solution {
public:
  struct ProbNode {
    int    curr;
    double prob;

    bool operator<(const ProbNode &rhs) const { return prob < rhs.prob; }
  };

  double maxProbability(int n, vector<vector<int>> &edges,
                        vector<double> &succProb, int start, int end) {
    vector<vector<pair<int, double>>> graph(n);
    for (int i = 0; i < edges.size(); ++i) {
      graph[edges[i][0]].emplace_back(edges[i][1], succProb[i]);
      graph[edges[i][1]].emplace_back(edges[i][0], succProb[i]);
    }
    vector<double>           probs(n, 0);
    priority_queue<ProbNode> pq;
    pq.emplace(ProbNode{start, 1.0});
    probs[start] = 1.0;
    while (!pq.empty()) {
      auto node = std::move(pq.top());
      pq.pop();
      if (node.curr == end) {
        return node.prob;
      }

      if (probs[node.curr] > node.prob) {
        continue;
      }

      for (auto &nxt : graph[node.curr]) {
        double nxt_prob = node.prob * nxt.second;
        if (nxt_prob > probs[nxt.first]) {
          probs[nxt.first] = nxt_prob;
          pq.emplace(ProbNode{nxt.first, nxt_prob});
        }
      }
    }
    return 0.0;
  }

private:
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |2 <= n <= 10^4|
// * |0 <= start, end < n|
// * |start != end|
// * |0 <= a, b < n|
// * |a != b|
// * |0 <= succProb.length == edges.length <= 2*10^4|
// * |0 <= succProb[i] <= 1|
// * There is at most one edge between every two nodes.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 3, edges = [[0,1],[1,2],[0,2]], succProb = [0.5,0.5,0.2], start =
//  0, end = 2
// Output: 0.25000
//
//  There are two paths from start to end, one having a probability of success =
//  0.2 and the other has 0.5 * 0.5 = 0.25.

LEETCODE_SOLUTION_UNITTEST(1514, PathWithMaximumProbability, example_1) {
  auto                solution = MakeSolution();
  int                 n        = 3;
  vector<vector<int>> edges    = {
      {0, 1},
      {1, 2},
      {0, 2}
  };
  vector<double> succProb = {0.5, 0.5, 0.2};
  int            start    = 0;
  int            end      = 2;
  double         expect   = 0.25000;
  double actual = solution->maxProbability(n, edges, succProb, start, end);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 3, edges = [[0,1],[1,2],[0,2]], succProb = [0.5,0.5,0.3], start =
//  0, end = 2
// Output: 0.30000
//

LEETCODE_SOLUTION_UNITTEST(1514, PathWithMaximumProbability, example_2) {
  auto                solution = MakeSolution();
  int                 n        = 3;
  vector<vector<int>> edges    = {
      {0, 1},
      {1, 2},
      {0, 2}
  };
  vector<double> succProb = {0.5, 0.5, 0.3};
  int            start    = 0;
  int            end      = 2;
  double         expect   = 0.30000;
  double actual = solution->maxProbability(n, edges, succProb, start, end);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #3]
//  Input: n = 3, edges = [[0,1]], succProb = [0.5], start = 0, end = 2
// Output: 0.00000
//
//  There is no path between 0 and 2.

LEETCODE_SOLUTION_UNITTEST(1514, PathWithMaximumProbability, example_3) {
  auto                solution = MakeSolution();
  int                 n        = 3;
  vector<vector<int>> edges    = {
      {0, 1}
  };
  vector<double> succProb = {0.5};
  int            start    = 0;
  int            end      = 2;
  double         expect   = 0.00000;
  double actual = solution->maxProbability(n, edges, succProb, start, end);
  LCD_EXPECT_EQ(expect, actual);
}

// [Extra Testcase #1]
//  Input: 5
// [[2,3],[1,2],[3,4],[1,3],[1,4],[0,1],[2,4],[0,4],[0,2]]
// [0.06,0.26,0.49,0.25,0.2,0.64,0.23,0.21,0.77]
// 0
// 3
// Output: 0.16000
//

LEETCODE_SOLUTION_UNITTEST(1514, PathWithMaximumProbability, extra_testcase_1) {
  auto                solution = MakeSolution();
  int                 n        = 5;
  vector<vector<int>> edges    = {
      {2, 3},
      {1, 2},
      {3, 4},
      {1, 3},
      {1, 4},
      {0, 1},
      {2, 4},
      {0, 4},
      {0, 2}
  };
  vector<double> succProb = {0.06, 0.26, 0.49, 0.25, 0.2,
                             0.64, 0.23, 0.21, 0.77};
  int            start    = 0;
  int            end      = 3;
  double         expect   = 0.16000;
  double actual = solution->maxProbability(n, edges, succProb, start, end);
  LCD_EXPECT_EQ(expect, actual);
}

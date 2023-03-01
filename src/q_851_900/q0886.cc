// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Possible Bipartition
//
// https://leetcode.com/problems/possible-bipartition/
//
// Question ID: 886
// Difficult  : Medium
// Solve Date : 2022/03/23 18:42

#include <iosfwd>
#include <queue>
#include <set>
#include <unordered_set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |886. Possible Bipartition|:
//
// We want to split a group of |n| people (labeled from |1| to |n|) into two
// groups of any size. Each person may dislike some other people, and they
// should not go into the same group. Given the integer |n| and the array
// |dislikes| where |dislikes[i] = [aᵢ, bᵢ]| indicates that the person labeled
// |aᵢ| does not like the person labeled |bᵢ|, return |true| if it is possible
// to split everyone into two groups in this way.  
//

LEETCODE_BEGIN_RESOLVING(886, PossibleBipartition, Solution);

class Solution {
public:
  bool possibleBipartition(int n, vector<vector<int>> &dislikes) {
    vector<unordered_set<int>> graph(n + 1);

    for (auto &v : dislikes) {
      graph[v[0]].emplace(v[1]);
      graph[v[1]].emplace(v[0]);
    }

    vector<bool> grouped(n + 1, false), visited(n + 1, false);

    for (int i = 1; i <= n; ++i) {
      if (visited[i])
        continue;
      queue<int> q;
      q.emplace(i);
      visited[i] = true;

      while (!q.empty()) {
        auto x = q.front();
        q.pop();

        for (auto &y : graph[x]) {
          if (!visited[y]) {
            visited[y] = true;
            grouped[y] = !grouped[x];
            q.emplace(y);
          } else {
            if (grouped[x] == grouped[y]) {
              return false;
            }
          }
        }
      }
    }

    return true;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= n <= 2000|
// * |0 <= dislikes.length <= 10⁴|
// * |dislikes[i].length == 2|
// * |1 <= aᵢ < bᵢ <= n|
// * All the pairs of |dislikes| are unique.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 4, dislikes = [[1,2],[1,3],[2,4]]
// Output: true
//
// The first group has [1,4], and the second group has [2,3].

LEETCODE_SOLUTION_UNITTEST(886, PossibleBipartition, example_1) {
  auto                solution = MakeSolution();
  int                 n        = 4;
  vector<vector<int>> dislikes = {
      {1, 2},
      {1, 3},
      {2, 4}
  };
  bool expect = true;
  bool actual = solution->possibleBipartition(n, dislikes);
  LCD_EXPECT_EQ(expect, actual);
}

// [Example #2]
//  Input: n = 3, dislikes = [[1,2],[1,3],[2,3]]
// Output: false
//
// We need at least 3 groups to divide them. We cannot put them in two groups.

LEETCODE_SOLUTION_UNITTEST(886, PossibleBipartition, example_2) {
  auto                solution = MakeSolution();
  int                 n        = 3;
  vector<vector<int>> dislikes = {
      {1, 2},
      {1, 3},
      {2, 3}
  };
  bool expect = false;
  bool actual = solution->possibleBipartition(n, dislikes);
  LCD_EXPECT_EQ(expect, actual);
}

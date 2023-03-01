// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Erect the Fence
//
// https://leetcode.com/problems/erect-the-fence/
//
// Question ID: 587
// Difficult  : Hard
// Solve Date : 2022/11/19 14:27

#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |587. Erect the Fence|:
//
// You are given an array |trees| where |trees[i] = [xᵢ, yᵢ]| represents the
// location of a tree in the garden. Fence the entire garden using the minimum
// length of rope, as it is expensive. The garden is well-fenced only if all the
// trees are enclosed. Return the coordinates of trees that are exactly located
// on the fence perimeter. You may return the answer in any order.
//

LEETCODE_BEGIN_RESOLVING(587, ErectTheFence, Solution);

class Solution {
private:
  bool isClockwiseTrun(vector<int> &a, vector<int> &b, vector<int> &c) {
    return (((c[1] - b[1]) * (b[0] - a[0])) -
            ((b[1] - a[1]) * (c[0] - b[0]))) >= 0;
  }

public:
  vector<vector<int>> outerTrees(vector<vector<int>> &trees) {
    auto res = vector<vector<int>>();
    auto n   = trees.size();
    auto cmp = [&](auto &a, auto &b) {
      return a[0] == b[0] ? a[1] < b[1] : a[0] < b[0];
    };

    sort(trees.begin(), trees.end(), cmp);

    for (int i = 0; i < n; ++i) {
      while (res.size() > 1 &&
             !isClockwiseTrun(*(res.rbegin() + 1), *(res.rbegin()), trees[i])) {
        res.pop_back();
      }
      res.emplace_back(trees[i]);
    }

    for (int i = n - 1; i >= 0; --i) {
      while (res.size() > 1 &&
             !isClockwiseTrun(*(res.rbegin() + 1), *(res.rbegin()), trees[i])) {
        res.pop_back();
      }
      res.emplace_back(trees[i]);
    }

    res.pop_back();
    sort(res.begin(), res.end(), cmp);
    res.erase(unique(res.begin(), res.end()), res.end());
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= trees.length <= 3000|
// * |trees[i].length == 2|
// * |0 <= xᵢ, yᵢ <= 100|
// * All the given positions are unique.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: trees = [[1,1],[2,2],[2,0],[2,4],[3,3],[4,2]]
// Output: [[1,1],[2,0],[4,2],[3,3],[2,4]]
//
// All the trees will be on the perimeter of the fence except the tree at [2,
// 2], which will be inside the fence.

LEETCODE_SOLUTION_UNITTEST(587, ErectTheFence, example_1) {
  auto                solution = MakeSolution();
  vector<vector<int>> trees    = {
      {1, 1},
      {2, 2},
      {2, 0},
      {2, 4},
      {3, 3},
      {4, 2}
  };
  vector<vector<int>> expect = {
      {1, 1},
      {2, 0},
      {4, 2},
      {3, 3},
      {2, 4}
  };
  vector<vector<int>> actual = solution->outerTrees(trees);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// [Example #2]
//  Input: trees = [[1,2],[2,2],[4,2]]
// Output: [[4,2],[2,2],[1,2]]
//
// The fence forms a line that passes through all the trees.

LEETCODE_SOLUTION_UNITTEST(587, ErectTheFence, example_2) {
  auto                solution = MakeSolution();
  vector<vector<int>> trees    = {
      {1, 2},
      {2, 2},
      {4, 2}
  };
  vector<vector<int>> expect = {
      {4, 2},
      {2, 2},
      {1, 2}
  };
  vector<vector<int>> actual = solution->outerTrees(trees);
  EXPECT_ANYORDER_EQ(expect, actual);
}

// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Minimum Number of Operations to Sort a Binary Tree by Level
//
// https://leetcode.com/problems/minimum-number-of-operations-to-sort-a-binary-tree-by-level/
//
// Question ID: 2471
// Difficult  : Medium
// Solve Date : 2024/12/23 19:07

#include "leetcode/tree_node.h"
#include <algorithm>
#include <iosfwd>
#include <queue>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2471. Minimum Number of Operations to Sort a Binary Tree by
// Level|:
//
// You are given the |root| of a binary tree with unique values.
// In one operation, you can choose any two nodes at the same level and swap
// their values. Return the minimum number of operations needed to make the
// values at each level sorted in a strictly increasing order. The level of a
// node is the number of edges along the path between it and the root node.
//
//

LEETCODE_BEGIN_RESOLVING(2471,
                         MinimumNumberOfOperationsToSortABinaryTreeByLevel,
                         Solution);

class Solution {
public:
  int minimumOperations(TreeNode *root) {
    queue<TreeNode *> q;
    q.push(root);
    int res = 0;
    while (!q.empty()) {
      auto        cq = std::move(q);
      vector<int> t;
      t.reserve(cq.size());
      while (!cq.empty()) {
        auto *p = cq.front();
        cq.pop();
        t.emplace_back(p->val);

        if (p->left) {
          q.emplace(p->left);
        }
        if (p->right) {
          q.emplace(p->right);
        }
      }

      res += getMinSwap(t);
    }
    return res;
  }

private:
  int getMinSwap(vector<int> &origin) {
    int         swap   = 0;
    vector<int> target = origin;
    sort(target.begin(), target.end());
    unordered_map<int, int> pos;
    for (int i = 0; i < origin.size(); ++i) {
      pos[origin[i]] = i;
    }

    for (int i = 0; i < origin.size(); ++i) {
      if (origin[i] != target[i]) {
        ++swap;

        int cur        = pos[target[i]];
        pos[origin[i]] = cur;
        std::swap(origin[cur], origin[i]);
      }
    }
    return swap;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is in the range |[1, 10⁵]|.
// * |1 <= Node.val <= 10⁵|
// * All the values of the tree are unique.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [1,4,3,7,6,8,5,null,null,null,null,9,null,10]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(2471,
                           MinimumNumberOfOperationsToSortABinaryTreeByLevel,
                           example_1) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector(
      {1, 4, 3, 7, 6, 8, 5, null, null, null, null, 9, null, 10});
  int expect = 3;
  int actual = solution->minimumOperations(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #2]
//  Input: root = [1,3,2,7,6,5,4]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(2471,
                           MinimumNumberOfOperationsToSortABinaryTreeByLevel,
                           example_2) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({1, 3, 2, 7, 6, 5, 4});
  int       expect   = 3;
  int       actual   = solution->minimumOperations(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #3]
//  Input: root = [1,2,3,4,5,6]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(2471,
                           MinimumNumberOfOperationsToSortABinaryTreeByLevel,
                           example_3) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({1, 2, 3, 4, 5, 6});
  int       expect   = 0;
  int       actual   = solution->minimumOperations(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Amount of Time for Binary Tree to Be Infected
//
// https://leetcode.com/problems/amount-of-time-for-binary-tree-to-be-infected/
//
// Question ID: 2385
// Difficult  : Medium
// Solve Date : 2024/01/10 19:01

#include "leetcode/tree_node.h"
#include <iosfwd>
#include <queue>
#include <unordered_map>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2385. Amount of Time for Binary Tree to Be Infected|:
//
// You are given the |root| of a binary tree with unique values, and an integer
// |start|. At minute |0|, an infection starts from the node with value |start|.
// Each minute, a node becomes infected if:
//
//  • The node is currently uninfected.
//
//  • The node is adjacent to an infected node.
// Return the number of minutes needed for the entire tree to be infected.
//
//

LEETCODE_BEGIN_RESOLVING(2385, AmountOfTimeForBinaryTreeToBeInfected, Solution);

class Solution {
public:
  int amountOfTime(TreeNode *root, int start) {
    unordered_map<int, unordered_set<int>> g;
    unordered_set<int>                     infected;
    traval(root, &g);

    int        res = 0;
    queue<int> q;
    q.emplace(start);
    infected.emplace(start);
    while (!q.empty()) {
      auto tmp = std::move(q);
      while (!tmp.empty()) {
        auto p = tmp.front();
        tmp.pop();

        for (auto x : g[p]) {
          if (infected.emplace(x).second) {
            q.emplace(x);
          }
        }
      }
      if (!q.empty()) {
        ++res;
      }
    }
    return res;
  }

private:
  void traval(TreeNode *p, unordered_map<int, unordered_set<int>> *g) {
    if (!p) {
      return;
    }

    if (p->left) {
      traval(p->left, g);
      (*g)[p->val].emplace(p->left->val);
      (*g)[p->left->val].emplace(p->val);
    }
    if (p->right) {
      traval(p->right, g);
      (*g)[p->val].emplace(p->right->val);
      (*g)[p->right->val].emplace(p->val);
    }
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is in the range |[1, 10⁵]|.
// * |1 <= Node.val <= 10⁵|
// * Each node has a unique value.
// * A node with a value of |start| exists in the tree.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [1,5,3,null,4,10,6,9,2], start = 3
// Output: 4
//
// The following nodes are infected during:
// - Minute 0: Node 3
// - Minute 1: Nodes 1, 10 and 6
// - Minute 2: Node 5
// - Minute 3: Node 4
// - Minute 4: Nodes 9 and 2
// It takes 4 minutes for the whole tree to be infected so we return 4.

LEETCODE_SOLUTION_UNITTEST(2385, AmountOfTimeForBinaryTreeToBeInfected,
                           example_1) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({1, 5, 3, null, 4, 10, 6, 9, 2});
  int       start    = 3;
  int       expect   = 4;
  int       actual   = solution->amountOfTime(root, start);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #2]
//  Input: root = [1], start = 1
// Output: 0
//
// At minute 0, the only node in the tree is infected so we return 0.

LEETCODE_SOLUTION_UNITTEST(2385, AmountOfTimeForBinaryTreeToBeInfected,
                           example_2) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({1});
  int       start    = 1;
  int       expect   = 0;
  int       actual   = solution->amountOfTime(root, start);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

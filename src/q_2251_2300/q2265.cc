// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Count Nodes Equal to Average of Subtree
//
// https://leetcode.com/problems/count-nodes-equal-to-average-of-subtree/
//
// Question ID: 2265
// Difficult  : Medium
// Solve Date : 2023/11/02 19:36

#include "leetcode/tree_node.h"
#include <iosfwd>
#include <unordered_map>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2265. Count Nodes Equal to Average of Subtree|:
//
// Given the |root| of a binary tree, return the number of nodes where the value
// of the node is equal to the average of the values in its subtree. Note:
//
//  • The average of |n| elements is the sum of the |n| elements divided by |n|
//  and rounded down to the nearest integer.
//
//  • A subtree of |root| is a tree consisting of |root| and all of its
//  descendants.
//
//

LEETCODE_BEGIN_RESOLVING(2265, CountNodesEqualToAverageOfSubtree, Solution);

class Solution {
public:
  int averageOfSubtree(TreeNode *root) {
    unordered_map<TreeNode *, pair<int, int>> memo;
    int                                       ret = 0;
    doCalculateTrees(root, &memo);
    for (auto &[p, r] : memo) {
      if (p->val == r.first / r.second) {
        ++ret;
      }
    }
    return ret;
  }

private:
  pair<int, int>
  doCalculateTrees(TreeNode                                  *root,
                   unordered_map<TreeNode *, pair<int, int>> *memo) {
    if (!root) {
      return make_pair(0, 0);
    }

    auto left  = doCalculateTrees(root->left, memo);
    auto right = doCalculateTrees(root->right, memo);

    auto ret = memo->emplace(
        root, make_pair<int, int>(left.first + right.first + root->val,
                                  left.second + right.second + 1));

    return (ret.first)->second;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is in the range |[1, 1000]|.
// * |0 <= Node.val <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [4,8,5,0,1,null,6]
// Output: 5
//
// For the node with value 4: The average of its subtree is (4 + 8 + 5 + 0 + 1 +
// 6) / 6 = 24 / 6 = 4. For the node with value 5: The average of its subtree is
// (5 + 6) / 2 = 11 / 2 = 5. For the node with value 0: The average of its
// subtree is 0 / 1 = 0. For the node with value 1: The average of its subtree
// is 1 / 1 = 1. For the node with value 6: The average of its subtree is 6 / 1
// = 6.

LEETCODE_SOLUTION_UNITTEST(2265, CountNodesEqualToAverageOfSubtree, example_1) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({4, 8, 5, 0, 1, null, 6});
  int       expect   = 5;
  int       actual   = solution->averageOfSubtree(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #2]
//  Input: root = [1]
// Output: 1
//
// For the node with value 1: The average of its subtree is 1 / 1 = 1.

LEETCODE_SOLUTION_UNITTEST(2265, CountNodesEqualToAverageOfSubtree, example_2) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({1});
  int       expect   = 1;
  int       actual   = solution->averageOfSubtree(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

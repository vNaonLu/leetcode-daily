// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Lowest Common Ancestor of Deepest Leaves
//
// https://leetcode.com/problems/lowest-common-ancestor-of-deepest-leaves/
//
// Question ID: 1123
// Difficult  : Medium
// Solve Date : 2025/04/04 12:10

#include "leetcode/tree_node.h"
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1123. Lowest Common Ancestor of Deepest Leaves|:
//
// Given the |root| of a binary tree, return the lowest common ancestor of its
// deepest leaves. Recall that:
//
//  • The node of a binary tree is a leaf if and only if it has no children
//
//  • The depth of the root of the tree is |0|. if the depth of a node is |d|,
//  the depth of each of its children is |d + 1|.
//
//  • The lowest common ancestor of a set |S| of nodes, is the node |A| with the
//  largest depth such that every node in |S| is in the subtree with root |A|.
//
//

LEETCODE_BEGIN_RESOLVING(1123, LowestCommonAncestorOfDeepestLeaves, Solution);

class Solution {
public:
  TreeNode *lcaDeepestLeaves(TreeNode *root) {
    int mx = maxDepth(root);
    return dfs(root, mx, 0);
  }

private:
  TreeNode *dfs(auto *root, int mx, int len) {
    if (!root) {
      return nullptr;
    }
    if (mx - 1 == len) {
      return root;
    }

    auto *left  = dfs(root->left, mx, len + 1);
    auto *right = dfs(root->right, mx, len + 1);

    if (left && right) {
      return root;
    }
    return left ? left : right;
  }

  int maxDepth(auto *root) {
    if (!root) {
      return 0;
    }
    return 1 + max(maxDepth(root->left), maxDepth(root->right));
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree will be in the range |[1, 1000]|.
// * |0 <= Node.val <= 1000|
// * The values of the nodes in the tree are unique.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [3,5,1,6,2,0,8,null,null,7,4]
// Output: [2,7,4]
//

LEETCODE_SOLUTION_UNITTEST(1123, LowestCommonAncestorOfDeepestLeaves,
                           example_1) {
  auto      solution = MakeSolution();
  TreeNode *root =
      TreeNode::FromVector({3, 5, 1, 6, 2, 0, 8, null, null, 7, 4});
  TreeNode *expect = TreeNode::FromVector({2, 7, 4});
  TreeNode *actual = solution->lcaDeepestLeaves(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root, expect, actual);
}

// [Example #2]
//  Input: root = [1]
// Output: [1]
//

LEETCODE_SOLUTION_UNITTEST(1123, LowestCommonAncestorOfDeepestLeaves,
                           example_2) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({1});
  TreeNode *expect   = TreeNode::FromVector({1});
  TreeNode *actual   = solution->lcaDeepestLeaves(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root, expect, actual);
}

// [Example #3]
//  Input: root = [0,1,3,null,2]
// Output: [2]
//

LEETCODE_SOLUTION_UNITTEST(1123, LowestCommonAncestorOfDeepestLeaves,
                           example_3) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({0, 1, 3, null, 2});
  TreeNode *expect   = TreeNode::FromVector({2});
  TreeNode *actual   = solution->lcaDeepestLeaves(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root, expect, actual);
}

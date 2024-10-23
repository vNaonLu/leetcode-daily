// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Cousins in Binary Tree II
//
// https://leetcode.com/problems/cousins-in-binary-tree-ii/
//
// Question ID: 2641
// Difficult  : Medium
// Solve Date : 2024/10/23 23:33

#include "leetcode/tree_node.h"
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2641. Cousins in Binary Tree II|:
//
// Given the |root| of a binary tree, replace the value of each node in the tree
// with the sum of all its cousins' values. Two nodes of a binary tree are
// cousins if they have the same depth with different parents. Return the |root|
// of the modified tree. Note that the depth of a node is the number of edges in
// the path from the root node to it.
//
//

LEETCODE_BEGIN_RESOLVING(2641, CousinsInBinaryTreeII, Solution);

class Solution {
public:
  TreeNode *replaceValueInTree(TreeNode *root) {
    vector<int> res(100001);
    int         h = 0;
    helper(root, 0, &h, &res);
    root->val = 0;
    dfs(root, 0, &h, &res);
    return root;
  }

private:
  void helper(TreeNode *p, int level, int *height, vector<int> *out) {
    if (!p) {
      return;
    }

    if (level >= *height) {
      ++*height;
    }
    (*out)[level] += p->val;
    helper(p->left, level + 1, height, out);
    helper(p->right, level + 1, height, out);
  }

  void dfs(TreeNode *p, int level, int *height, vector<int> *out) {
    if (!p) {
      return;
    }

    if (level + 1 < *height) {
      int x = (*out)[level + 1];
      if (p->left) {
        x -= p->left->val;
      }
      if (p->right) {
        x -= p->right->val;
      }
      if (p->left) {
        p->left->val = x;
      }
      if (p->right) {
        p->right->val = x;
      }
    }

    dfs(p->left, level + 1, height, out);
    dfs(p->right, level + 1, height, out);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is in the range |[1, 10⁵]|.
// * |1 <= Node.val <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [5,4,9,1,10,null,7]
// Output: [0,0,0,7,7,null,11]
//

LEETCODE_SOLUTION_UNITTEST(2641, CousinsInBinaryTreeII, example_1) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({5, 4, 9, 1, 10, null, 7});
  TreeNode *expect   = TreeNode::FromVector({0, 0, 0, 7, 7, null, 11});
  TreeNode *actual   = solution->replaceValueInTree(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root, expect, actual);
}

// [Example #2]
//  Input: root = [3,1,2]
// Output: [0,0,0]
//

LEETCODE_SOLUTION_UNITTEST(2641, CousinsInBinaryTreeII, example_2) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({3, 1, 2});
  TreeNode *expect   = TreeNode::FromVector({0, 0, 0});
  TreeNode *actual   = solution->replaceValueInTree(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root, expect, actual);
}

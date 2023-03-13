// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Binary Tree Pruning
//
// https://leetcode.com/problems/binary-tree-pruning/
//
// Question ID: 814
// Difficult  : Medium
// Solve Date : 2022/09/06 18:11

#include "leetcode/tree_node.h"
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |814. Binary Tree Pruning|:
//
// Given the |root| of a binary tree, return the same tree where every subtree
// (of the given tree) not containing a |1| has been removed. A subtree of a
// node |node| is |node| plus every node that is a descendant of |node|.
//

LEETCODE_BEGIN_RESOLVING(814, BinaryTreePruning, Solution);

class Solution {
private:
  void deleteTree(TreeNode *p) {
    if (p) {
      deleteTree(p->left);
      deleteTree(p->right);
      delete p;
    }
  }

  bool isPivotalNode(TreeNode *p) {
    if (nullptr == p) {
      return false;
    } else if (p->val == 0) {
      return isPivotalNode(p->left) || isPivotalNode(p->right);
    } else {
      return true;
    }
  }

public:
  TreeNode *pruneTree(TreeNode *root) {
    if (!isPivotalNode(root)) {
      deleteTree(root);
      root = nullptr;
    } else {
      root->left  = pruneTree(root->left);
      root->right = pruneTree(root->right);
    }
    return root;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is in the range |[1, 200]|.
// * |Node.val| is either |0| or |1|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [1,null,0,0,1]
// Output: [1,null,0,null,1]
//
// Only the red nodes satisfy the property "every subtree not containing a 1".
// The diagram on the right represents the answer.

LEETCODE_SOLUTION_UNITTEST(814, BinaryTreePruning, example_1) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({1, null, 0, 0, 1});
  TreeNode *expect   = TreeNode::FromVector({1, null, 0, null, 1});
  TreeNode *actual   = solution->pruneTree(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root, expect, actual);
}

// [Example #2]
//  Input: root = [1,0,1,0,0,0,1]
// Output: [1,null,1,null,1]
//

LEETCODE_SOLUTION_UNITTEST(814, BinaryTreePruning, example_2) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({1, 0, 1, 0, 0, 0, 1});
  TreeNode *expect   = TreeNode::FromVector({1, null, 1, null, 1});
  TreeNode *actual   = solution->pruneTree(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root, expect, actual);
}

// [Example #3]
//  Input: root = [1,1,0,1,1,0,1,0]
// Output: [1,1,0,1,1,null,1]
//

LEETCODE_SOLUTION_UNITTEST(814, BinaryTreePruning, example_3) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({1, 1, 0, 1, 1, 0, 1, 0});
  TreeNode *expect   = TreeNode::FromVector({1, 1, 0, 1, 1, null, 1});
  TreeNode *actual   = solution->pruneTree(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root, expect, actual);
}

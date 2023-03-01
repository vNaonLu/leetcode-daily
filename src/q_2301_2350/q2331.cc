// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Evaluate Boolean Binary Tree
//
// https://leetcode.com/problems/evaluate-boolean-binary-tree/
//
// Question ID: 2331
// Difficult  : Easy
// Solve Date : 2022/10/18 14:13

#include "leetcode/tree_node.h"
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2331. Evaluate Boolean Binary Tree|:
//
// You are given the |root| of a full binary tree with the following properties:
//
//  • Leaf nodes have either the value |0| or |1|, where |0| represents |False|
//  and |1| represents |True|.
//
//  • Non-leaf nodes have either the value |2| or |3|, where |2| represents the
//  boolean |OR| and |3| represents the boolean |AND|.
// The evaluation of a node is as follows:
//
//  • If the node is a leaf node, the evaluation is the value of the node, i.e.
//  |True| or |False|.
//
//  • Otherwise, evaluate the node's two children and apply the boolean
//  operation of its value with the children's evaluations.
// Return the boolean result of evaluating the |root| node.
// A full binary tree is a binary tree where each node has either |0| or |2|
// children. A leaf node is a node that has zero children.
//

LEETCODE_BEGIN_RESOLVING(2331, EvaluateBooleanBinaryTree, Solution);

class Solution {
public:
  bool evaluateTree(TreeNode *root) {
    if (nullptr == root) {
      return false;
    }

    switch (root->val) {
    case 0:
      return false;
    case 1:
      return true;
    case 2:
      return evaluateTree(root->left) || evaluateTree(root->right);
    case 3:
      return evaluateTree(root->left) && evaluateTree(root->right);
    default:
      return false;
    }
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is in the range |[1, 1000]|.
// * |0 <= Node.val <= 3|
// * Every node has either |0| or |2| children.
// * Leaf nodes have a value of |0| or |1|.
// * Non-leaf nodes have a value of |2| or |3|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [2,1,3,null,null,0,1]
// Output: true
//
// The above diagram illustrates the evaluation process.
// The AND node evaluates to False AND True = False.
// The OR node evaluates to True OR False = True.
// The root node evaluates to True, so we return true.

LEETCODE_SOLUTION_UNITTEST(2331, EvaluateBooleanBinaryTree, example_1) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({2, 1, 3, null, null, 0, 1});
  bool      expect   = true;
  bool      actual   = solution->evaluateTree(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #2]
//  Input: root = [0]
// Output: false
//
// The root node is a leaf node and it evaluates to false, so we return false.

LEETCODE_SOLUTION_UNITTEST(2331, EvaluateBooleanBinaryTree, example_2) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({0});
  bool      expect   = false;
  bool      actual   = solution->evaluateTree(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Flatten Binary Tree to Linked List
//
// https://leetcode.com/problems/flatten-binary-tree-to-linked-list/
//
// Question ID: 114
// Difficult  : Medium
// Solve Date : 2021/10/11 17:49

#include "leetcode/tree_node.h"
#include <iosfwd>
#include <stack>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |114. Flatten Binary Tree to Linked List|:
//
// Given the |root| of a binary tree, flatten the tree into a "linked list":
//
//  • The "linked list" should use the same |TreeNode| class where the |right|
//  child pointer points to the next node in the list and the |left| child
//  pointer is always |null|.
//
//  • The "linked list" should be in the same order as a pre-order traversal of
//  the binary tree.
//  
//

LEETCODE_BEGIN_RESOLVING(114, FlattenBinaryTreeToLinkedList, Solution);

class Solution {
public:
  void flatten(TreeNode *root) {
    if (root == nullptr)
      return;
    stack<TreeNode *> s;
    s.push(root);
    while (!s.empty()) {
      auto node = s.top();
      s.pop();
      if (node->right != nullptr)
        s.push(node->right);
      if (node->left != nullptr)
        s.push(node->left);
      node->left = nullptr;
      if (!s.empty())
        node->right = s.top();
    }
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is in the range |[0, 2000]|.
// * |-100 <= Node.val <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [1,2,5,3,4,null,6]
// Output: [1,null,2,null,3,null,4,null,5,null,6]
//

LEETCODE_SOLUTION_UNITTEST(114, FlattenBinaryTreeToLinkedList, example_1) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({1, 2, 5, 3, 4, null, 6});
  TreeNode *expect =
      TreeNode::FromVector({1, null, 2, null, 3, null, 4, null, 5, null, 6});
  solution->flatten(root);
  LCD_EXPECT_EQ(expect, root);
  TreeNode::Release(root, expect);
}

// [Example #2]
//  Input: root = []
// Output: []
//

LEETCODE_SOLUTION_UNITTEST(114, FlattenBinaryTreeToLinkedList, example_2) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({});
  TreeNode *expect   = TreeNode::FromVector({});
  solution->flatten(root);
  LCD_EXPECT_EQ(expect, root);
  TreeNode::Release(root, expect);
}

// [Example #3]
//  Input: root = [0]
// Output: [0]
//

LEETCODE_SOLUTION_UNITTEST(114, FlattenBinaryTreeToLinkedList, example_3) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({0});
  TreeNode *expect   = TreeNode::FromVector({0});
  solution->flatten(root);
  LCD_EXPECT_EQ(expect, root);
  TreeNode::Release(root, expect);
}

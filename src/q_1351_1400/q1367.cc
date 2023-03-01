// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Linked List in Binary Tree
//
// https://leetcode.com/problems/linked-list-in-binary-tree/
//
// Question ID: 1367
// Difficult  : Medium
// Solve Date : 2022/04/29 15:24

#include "leetcode/list_node.h"
#include "leetcode/tree_node.h"
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1367. Linked List in Binary Tree|:
//
// Given a binary tree |root| and a linked list with  |head| as the first node. 
// Return True if all the elements in the linked list starting from the |head|
// correspond to some downward path connected in the binary tree otherwise
// return False. In this context downward path means a path that starts at some
// node and goes downwards.  
//

LEETCODE_BEGIN_RESOLVING(1367, LinkedListInBinaryTree, Solution);

class Solution {
private:
  bool match(ListNode *head, TreeNode *root) {
    if (head == nullptr)
      return true;
    if (root == nullptr || root->val != head->val)
      return false;
    return match(head->next, root->left) || match(head->next, root->right);
  }
  bool dfs(ListNode *head, TreeNode *root) {
    if (root == nullptr)
      return false;
    if (match(head, root))
      return true;
    return dfs(head, root->left) || dfs(head, root->right);
  }

public:
  bool isSubPath(ListNode *head, TreeNode *root) { return dfs(head, root); }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree will be in the range |[1, 2500]|.
// * The number of nodes in the list will be in the range |[1, 100]|.
// * |1 <= Node.val <= 100| for each node in the linked list and binary tree.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: head = [4,2,8], root =
//  [1,4,4,null,2,2,null,1,null,6,8,null,null,null,null,1,3]
// Output: true
//
// Nodes in blue form a subpath in the binary Tree.

LEETCODE_SOLUTION_UNITTEST(1367, LinkedListInBinaryTree, example_1) {
  auto      solution = MakeSolution();
  ListNode *head     = ListNode::FromVector({4, 2, 8} /*, looped_index*/);
  TreeNode *root     = TreeNode::FromVector(
      {1, 4, 4, null, 2, 2, null, 1, null, 6, 8, null, null, null, null, 1, 3});
  bool expect = true;
  bool actual = solution->isSubPath(head, root);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head);
  TreeNode::Release(root);
}

// [Example #2]
//  Input: head = [1,4,2,6], root =
//  [1,4,4,null,2,2,null,1,null,6,8,null,null,null,null,1,3]
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(1367, LinkedListInBinaryTree, example_2) {
  auto      solution = MakeSolution();
  ListNode *head     = ListNode::FromVector({1, 4, 2, 6} /*, looped_index*/);
  TreeNode *root     = TreeNode::FromVector(
      {1, 4, 4, null, 2, 2, null, 1, null, 6, 8, null, null, null, null, 1, 3});
  bool expect = true;
  bool actual = solution->isSubPath(head, root);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head);
  TreeNode::Release(root);
}

// [Example #3]
//  Input: head = [1,4,2,6,8], root =
//  [1,4,4,null,2,2,null,1,null,6,8,null,null,null,null,1,3]
// Output: false
//
// There is no path in the binary tree that contains all the elements of the
// linked list from |head|.

LEETCODE_SOLUTION_UNITTEST(1367, LinkedListInBinaryTree, example_3) {
  auto      solution = MakeSolution();
  ListNode *head     = ListNode::FromVector({1, 4, 2, 6, 8} /*, looped_index*/);
  TreeNode *root     = TreeNode::FromVector(
      {1, 4, 4, null, 2, 2, null, 1, null, 6, 8, null, null, null, null, 1, 3});
  bool expect = false;
  bool actual = solution->isSubPath(head, root);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head);
  TreeNode::Release(root);
}

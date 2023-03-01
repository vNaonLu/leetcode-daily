// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Delete Node in a BST
//
// https://leetcode.com/problems/delete-node-in-a-bst/
//
// Question ID: 450
// Difficult  : Medium
// Solve Date : 2021/10/04 13:11

#include "leetcode/tree_node.h"
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |450. Delete Node in a BST|:
//
// Given a root node reference of a BST and a key, delete the node with the
// given key in the BST. Return the root node reference (possibly updated) of
// the BST. Basically, the deletion can be divided into two stages:
//
//  1. Search for a node to remove.
//
//  2. If the node is found, delete the node.
//  
//

LEETCODE_BEGIN_RESOLVING(450, DeleteNodeInABST, Solution);

class Solution {
private:
  TreeNode *remove(TreeNode *p) {
    TreeNode *min = p->right;
    while (min != nullptr && min->left != nullptr) {
      if (min->left->left == nullptr) {
        TreeNode *pre = min;
        min           = min->left;
        pre->left     = min->right;
        break;
      }
      min = min->left;
    }
    if (min == nullptr) {
      auto left = p->left;
      delete p;
      return left;
    } else if (p->right == min) {
      min->left = p->left;
      delete p;
      return min;
    } else {
      min->left  = p->left;
      min->right = p->right;
      delete p;
      return min;
    }
  }

public:
  TreeNode *deleteNode(TreeNode *root, int key) {
    TreeNode *p = root, *pre = nullptr;
    while (p != nullptr) {
      if (p->val > key) {
        pre = p;
        p   = p->left;
      } else if (p->val < key) {
        pre = p;
        p   = p->right;
      } else {
        if (pre == nullptr) {
          root = remove(p);
        } else {
          if (pre->left == p) {
            pre->left = remove(p);
          } else {
            pre->right = remove(p);
          }
        }
        break;
      }
    }
    return root;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is in the range |[0, 10⁴]|.
// * |-10⁵ <= Node.val <= 10⁵|
// * Each node has a unique value.
// * |root| is a valid binary search tree.
// * |-10⁵ <= key <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [5,3,6,2,4,null,7], key = 3
// Output: [5,4,6,2,null,null,7]
//
// Given key to delete is 3. So we find the node with value 3 and delete it.
// One valid answer is [5,4,6,2,null,null,7], shown in the above BST.
// Please notice that another valid answer is [5,2,6,null,4,null,7] and it's
// also accepted.
// ![img](https://assets.leetcode.com/uploads/2020/09/04/del_node_supp.jpg)

LEETCODE_SOLUTION_UNITTEST(450, DeleteNodeInABST, example_1) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({5, 3, 6, 2, 4, null, 7});
  int       key      = 3;
  TreeNode *expect   = TreeNode::FromVector({5, 4, 6, 2, null, null, 7});
  TreeNode *actual   = solution->deleteNode(root, key);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root, expect);
}

// [Example #2]
//  Input: root = [5,3,6,2,4,null,7], key = 0
// Output: [5,3,6,2,4,null,7]
//
// The tree does not contain a node with value = 0.

LEETCODE_SOLUTION_UNITTEST(450, DeleteNodeInABST, example_2) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({5, 3, 6, 2, 4, null, 7});
  int       key      = 0;
  TreeNode *expect   = TreeNode::FromVector({5, 3, 6, 2, 4, null, 7});
  TreeNode *actual   = solution->deleteNode(root, key);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root, expect);
}

// [Example #3]
//  Input: root = [], key = 0
// Output: []
//

LEETCODE_SOLUTION_UNITTEST(450, DeleteNodeInABST, example_3) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({});
  int       key      = 0;
  TreeNode *expect   = TreeNode::FromVector({});
  TreeNode *actual   = solution->deleteNode(root, key);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root, expect);
}

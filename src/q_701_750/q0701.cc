// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Insert into a Binary Search Tree
//
// https://leetcode.com/problems/insert-into-a-binary-search-tree/
//
// Question ID: 701
// Difficult  : Medium
// Solve Date : 2021/09/17 08:00

#include "leetcode/tree_node.h"
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |701. Insert into a Binary Search Tree|:
//
// You are given the |root| node of a binary search tree (BST) and a |value| to
// insert into the tree. Return the root node of the BST after the insertion. It
// is guaranteed that the new value does not exist in the original BST.
// Notice that there may exist multiple valid ways for the insertion, as long as
// the tree remains a BST after insertion. You can return any of them.  
//

LEETCODE_BEGIN_RESOLVING(701, InsertIntoABinarySearchTree, Solution);

class Solution {
public:
  TreeNode *insertIntoBST(TreeNode *root, int val) {
    TreeNode *p = root, *pre = nullptr;
    while (p != nullptr) {
      pre = p;
      if (p->val > val) {
        p = p->left;
      } else {
        p = p->right;
      }
    }
    if (pre == nullptr) {
      root = new TreeNode(val);
    } else {
      if (pre->val > val) {
        pre->left = new TreeNode(val);
      } else {
        pre->right = new TreeNode(val);
      }
    }
    return root;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree will be in the range |[0, 10⁴]|.
// * |-10⁸ <= Node.val <= 10⁸|
// * All the values |Node.val| are unique.
// * |-10⁸ <= val <= 10⁸|
// * It's guaranteed that |val| does not exist in the original BST.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [4,2,7,1,3], val = 5
// Output: [4,2,7,1,3,5]
//
// Another accepted tree is:
// ![img](https://assets.leetcode.com/uploads/2020/10/05/bst.jpg)

LEETCODE_SOLUTION_UNITTEST(701, InsertIntoABinarySearchTree, example_1) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({4, 2, 7, 1, 3});
  int       val      = 5;
  TreeNode *expect   = TreeNode::FromVector({4, 2, 7, 1, 3, 5});
  TreeNode *actual   = solution->insertIntoBST(root, val);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root, expect);
}

// [Example #2]
//  Input: root = [40,20,60,10,30,50,70], val = 25
// Output: [40,20,60,10,30,50,70,null,null,25]
//

LEETCODE_SOLUTION_UNITTEST(701, InsertIntoABinarySearchTree, example_2) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({40, 20, 60, 10, 30, 50, 70});
  int       val      = 25;
  TreeNode *expect =
      TreeNode::FromVector({40, 20, 60, 10, 30, 50, 70, null, null, 25});
  TreeNode *actual = solution->insertIntoBST(root, val);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root, expect);
}

// [Example #3]
//  Input: root = [4,2,7,1,3,null,null,null,null,null,null], val = 5
// Output: [4,2,7,1,3,5]
//

LEETCODE_SOLUTION_UNITTEST(701, InsertIntoABinarySearchTree, example_3) {
  auto      solution = MakeSolution();
  TreeNode *root =
      TreeNode::FromVector({4, 2, 7, 1, 3, null, null, null, null, null, null});
  int       val    = 5;
  TreeNode *expect = TreeNode::FromVector({4, 2, 7, 1, 3, 5});
  TreeNode *actual = solution->insertIntoBST(root, val);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root, expect);
}

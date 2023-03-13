// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Recover Binary Search Tree
//
// https://leetcode.com/problems/recover-binary-search-tree/
//
// Question ID: 99
// Difficult  : Medium
// Solve Date : 2022/04/19 11:44

#include "leetcode/tree_node.h"
#include <iosfwd>
#include <limits>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |99. Recover Binary Search Tree|:
//
// You are given the |root| of a binary search tree (BST), where the values of
// exactly two nodes of the tree were swapped by mistake. Recover the tree
// without changing its structure.  
//

LEETCODE_BEGIN_RESOLVING(99, RecoverBinarySearchTree, Solution);

class Solution {
private:
  void find(TreeNode *p, TreeNode *&pre, TreeNode *&first, TreeNode *&second) {
    if (nullptr == p) {
      return;
    }

    find(p->left, pre, first, second);

    if (first == nullptr && p->val < pre->val) {
      first = pre;
    }

    if (first != nullptr && p->val < pre->val) {
      second = p;
    }

    pre = p;

    find(p->right, pre, first, second);
  }

public:
  void recoverTree(TreeNode *root) {
    TreeNode  dummy(numeric_limits<int>::min());
    TreeNode *p      = &dummy;
    TreeNode *miss_1 = nullptr;
    TreeNode *miss_2 = nullptr;
    find(root, p, miss_1, miss_2);
    swap(miss_1->val, miss_2->val);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is in the range |[2, 1000]|.
// * |-2³¹ <= Node.val <= 2³¹ - 1|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [1,3,null,null,2]
// Output: [3,1,null,null,2]
//
// 3 cannot be a left child of 1 because 3 > 1. Swapping 1 and 3 makes the BST
// valid.

LEETCODE_SOLUTION_UNITTEST(99, RecoverBinarySearchTree, example_1) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({1, 3, null, null, 2});
  TreeNode *expect   = TreeNode::FromVector({3, 1, null, null, 2});
  solution->recoverTree(root);
  LCD_EXPECT_EQ(expect, root);
  TreeNode::Release(root, expect);
}

// [Example #2]
//  Input: root = [3,1,4,null,null,2]
// Output: [2,1,4,null,null,3]
//
// 2 cannot be in the right subtree of 3 because 2 < 3. Swapping 2 and 3 makes
// the BST valid.

LEETCODE_SOLUTION_UNITTEST(99, RecoverBinarySearchTree, example_2) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({3, 1, 4, null, null, 2});
  TreeNode *expect   = TreeNode::FromVector({2, 1, 4, null, null, 3});
  solution->recoverTree(root);
  LCD_EXPECT_EQ(expect, root);
  TreeNode::Release(root, expect);
}

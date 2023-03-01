// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Balance a Binary Search Tree
//
// https://leetcode.com/problems/balance-a-binary-search-tree/
//
// Question ID: 1382
// Difficult  : Medium
// Solve Date : 2022/06/14 18:26

#include "leetcode/tree_node.h"
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1382. Balance a Binary Search Tree|:
//
// Given the |root| of a binary search tree, return a balanced binary search
// tree with the same node values. If there is more than one answer, return any
// of them. A binary search tree is balanced if the depth of the two subtrees of
// every node never differs by more than |1|.
//

LEETCODE_BEGIN_RESOLVING(1382, BalanceABinarySearchTree, Solution);

class Solution {
private:
  void build_inorder(TreeNode *p, vector<TreeNode *> &inorder) {
    if (p == nullptr) {
      return;
    }

    build_inorder(p->left, inorder);
    inorder.emplace_back(p);
    build_inorder(p->right, inorder);
  }

  template <typename iterator>
  TreeNode *build_tree_from_inorder(iterator beg, iterator end) {
    if (beg == end) {
      return nullptr;
    }

    auto mid      = beg + (end - beg) / 2;
    (*mid)->left  = build_tree_from_inorder(beg, mid);
    (*mid)->right = build_tree_from_inorder(mid + 1, end);

    return *mid;
  }

public:
  TreeNode *balanceBST(TreeNode *root) {
    vector<TreeNode *> order;
    build_inorder(root, order);

    return build_tree_from_inorder(order.begin(), order.end());
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is in the range |[1, 10⁴]|.
// * |1 <= Node.val <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [1,null,2,null,3,null,4,null,null]
// Output: [2,1,3,null,null,null,4]
// Explanation: This is not the only correct answer, [3,1,4,null,2] is also
// correct.
//

LEETCODE_SOLUTION_UNITTEST(1382, BalanceABinarySearchTree, example_1) {
  auto      solution = MakeSolution();
  TreeNode *root =
      TreeNode::FromVector({1, null, 2, null, 3, null, 4, null, null});
  TreeNode *expect = TreeNode::FromVector({3, 2, 4, 1});
  TreeNode *actual = solution->balanceBST(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root, expect, actual);
}

// [Example #2]
//  Input: root = [2,1,3]
// Output: [2,1,3]
//

LEETCODE_SOLUTION_UNITTEST(1382, BalanceABinarySearchTree, example_2) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({2, 1, 3});
  TreeNode *expect   = TreeNode::FromVector({2, 1, 3});
  TreeNode *actual   = solution->balanceBST(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root, expect, actual);
}

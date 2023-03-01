// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Construct Binary Search Tree from Preorder Traversal
//
// https://leetcode.com/problems/construct-binary-search-tree-from-preorder-traversal/
//
// Question ID: 1008
// Difficult  : Medium
// Solve Date : 2021/10/13 12:11

#include "leetcode/tree_node.h"
#include <iosfwd>
#include <limits>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1008. Construct Binary Search Tree from Preorder Traversal|:
//
// Given an array of integers preorder, which represents the preorder traversal
// of a BST (i.e., binary search tree), construct the tree and return its root.
// It is guaranteed that there is always possible to find a binary search tree
// with the given requirements for the given test cases. A binary search tree is
// a binary tree where for every node, any descendant of |Node.left| has a value
// strictly less than |Node.val|, and any descendant of |Node.right| has a value
// strictly greater than |Node.val|. A preorder traversal of a binary tree
// displays the value of the node first, then traverses |Node.left|, then
// traverses |Node.right|.  
//

LEETCODE_BEGIN_RESOLVING(1008, ConstructBinarySearchTreeFromPreorderTraversal,
                         Solution);

class Solution {
private:
  TreeNode *build_tree(vector<int> &v, int &idx,
                       int bound = numeric_limits<int>::max()) {
    if (idx == v.size() || v[idx] > bound)
      return nullptr;
    TreeNode *p = new TreeNode(v[idx++]);
    p->left     = build_tree(v, idx, p->val);
    p->right    = build_tree(v, idx, bound);
    return p;
  }

public:
  TreeNode *bstFromPreorder(vector<int> &preorder) {
    int i = 0;
    return build_tree(preorder, i);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= preorder.length <= 100|
// * |1 <= preorder[i] <= 1000|
// * All the values of |preorder| are unique.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: preorder = [8,5,1,7,10,12]
// Output: [8,5,10,1,7,null,12]
//

LEETCODE_SOLUTION_UNITTEST(1008, ConstructBinarySearchTreeFromPreorderTraversal,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> preorder = {8, 5, 1, 7, 10, 12};
  TreeNode   *expect   = TreeNode::FromVector({8, 5, 10, 1, 7, null, 12});
  TreeNode   *actual   = solution->bstFromPreorder(preorder);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(expect, actual);
}

// [Example #2]
//  Input: preorder = [1,3]
// Output: [1,null,3]
//

LEETCODE_SOLUTION_UNITTEST(1008, ConstructBinarySearchTreeFromPreorderTraversal,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> preorder = {1, 3};
  TreeNode   *expect   = TreeNode::FromVector({1, null, 3});
  TreeNode   *actual   = solution->bstFromPreorder(preorder);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(expect, actual);
}

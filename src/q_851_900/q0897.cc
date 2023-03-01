// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Increasing Order Search Tree
//
// https://leetcode.com/problems/increasing-order-search-tree/
//
// Question ID: 897
// Difficult  : Easy
// Solve Date : 2022/04/17 12:10

#include "leetcode/tree_node.h"
#include <iosfwd>
#include <queue>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |897. Increasing Order Search Tree|:
//
// Given the |root| of a binary search tree, rearrange the tree in in-order so
// that the leftmost node in the tree is now the root of the tree, and every
// node has no left child and only one right child.  
//

LEETCODE_BEGIN_RESOLVING(897, IncreasingOrderSearchTree, Solution);

class Solution {
private:
  void fill_queue(queue<TreeNode *> &q, TreeNode *p) {
    if (nullptr == p) {
      return;
    }
    fill_queue(q, p->left);
    q.emplace(p);
    fill_queue(q, p->right);
  }

public:
  TreeNode *increasingBST(TreeNode *root) {
    queue<TreeNode *> q;
    fill_queue(q, root);
    TreeNode *res = q.front();
    q.pop();
    TreeNode *p = res;
    while (!q.empty()) {
      p->left  = nullptr;
      p->right = q.front();
      q.pop();
      p = p->right;
    }
    p->left  = nullptr;
    p->right = nullptr;

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the given tree will be in the range |[1, 100]|.
// * |0 <= Node.val <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [5,3,6,2,4,null,8,1,null,null,null,7,9]
// Output: [1,null,2,null,3,null,4,null,5,null,6,null,7,null,8,null,9]
//

LEETCODE_SOLUTION_UNITTEST(897, IncreasingOrderSearchTree, example_1) {
  auto      solution = MakeSolution();
  TreeNode *root =
      TreeNode::FromVector({5, 3, 6, 2, 4, null, 8, 1, null, null, null, 7, 9});
  TreeNode *expect =
      TreeNode::FromVector({1, null, 2, null, 3, null, 4, null, 5, null, 6,
                            null, 7, null, 8, null, 9});
  TreeNode *actual = solution->increasingBST(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root, expect, actual);
}

// [Example #2]
//  Input: root = [5,1,7]
// Output: [1,null,5,null,7]
//

LEETCODE_SOLUTION_UNITTEST(897, IncreasingOrderSearchTree, example_2) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({5, 1, 7});
  TreeNode *expect   = TreeNode::FromVector({1, null, 5, null, 7});
  TreeNode *actual   = solution->increasingBST(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root, expect, actual);
}

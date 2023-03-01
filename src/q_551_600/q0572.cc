// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Subtree of Another Tree
//
// https://leetcode.com/problems/subtree-of-another-tree/
//
// Question ID: 572
// Difficult  : Easy
// Solve Date : 2021/09/25 16:06

#include "leetcode/tree_node.h"
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |572. Subtree of Another Tree|:
//
// Given the roots of two binary trees |root| and |subRoot|, return |true| if
// there is a subtree of |root| with the same structure and node values of |
// subRoot| and |false| otherwise. A subtree of a binary tree |tree| is a tree
// that consists of a node in |tree| and all of this node's descendants. The
// tree |tree| could also be considered as a subtree of itself.  
//

LEETCODE_BEGIN_RESOLVING(572, SubtreeOfAnotherTree, Solution);

class Solution {
private:
  bool helper(TreeNode *p, TreeNode *q) {
    if (p != nullptr && q != nullptr) {
      return p->val == q->val && helper(p->left, q->left) &&
             helper(p->right, q->right);
    } else if (p == nullptr && q == nullptr) {
      return true;
    } else {
      return false;
    }
  }

public:
  bool isSubtree(TreeNode *root, TreeNode *subRoot) {
    if (root == nullptr && subRoot == nullptr)
      return true;
    else if (root == nullptr)
      return false;
    else if (subRoot == nullptr)
      return true;
    if (helper(root, subRoot))
      return true;
    return isSubtree(root->left, subRoot) || isSubtree(root->right, subRoot);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the |root| tree is in the range |[1, 2000]|.
// * The number of nodes in the |subRoot| tree is in the range |[1, 1000]|.
// * |-10⁴ <= root.val <= 10⁴|
// * |-10⁴ <= subRoot.val <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [3,4,5,1,2], subRoot = [4,1,2]
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(572, SubtreeOfAnotherTree, example_1) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({3, 4, 5, 1, 2});
  TreeNode *subRoot  = TreeNode::FromVector({4, 1, 2});
  bool      expect   = true;
  bool      actual   = solution->isSubtree(root, subRoot);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root, subRoot);
}

// [Example #2]
//  Input: root = [3,4,5,1,2,null,null,null,null,0], subRoot = [4,1,2]
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(572, SubtreeOfAnotherTree, example_2) {
  auto      solution = MakeSolution();
  TreeNode *root =
      TreeNode::FromVector({3, 4, 5, 1, 2, null, null, null, null, 0});
  TreeNode *subRoot = TreeNode::FromVector({4, 1, 2});
  bool      expect  = false;
  bool      actual  = solution->isSubtree(root, subRoot);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root, subRoot);
}

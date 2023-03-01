// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Binary Tree Cameras
//
// https://leetcode.com/problems/binary-tree-cameras/
//
// Question ID: 968
// Difficult  : Hard
// Solve Date : 2022/06/17 22:09

#include "leetcode/tree_node.h"
#include <iosfwd>
#include <set>
#include <unordered_set>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |968. Binary Tree Cameras|:
//
// You are given the |root| of a binary tree. We install cameras on the tree
// nodes where each camera at a node can monitor its parent, itself, and its
// immediate children. Return the minimum number of cameras needed to monitor
// all nodes of the tree.
//

LEETCODE_BEGIN_RESOLVING(968, BinaryTreeCameras, Solution);

class Solution {
private:
  void helper(TreeNode *p, TreeNode *prev, unordered_set<TreeNode *> &memo,
              int &res) {
    if (nullptr != p) {
      helper(p->left, p, memo, res);
      helper(p->right, p, memo, res);

      if (nullptr == prev && !memo.count(p) || !memo.count(p->left) ||
          !memo.count(p->right)) {
        ++res;
        memo.insert(p);
        memo.insert(prev);
        memo.insert(p->left);
        memo.insert(p->right);
      }
    }
  }

public:
  int minCameraCover(TreeNode *root) {
    int                       res = 0;
    unordered_set<TreeNode *> memo;
    memo.insert(nullptr);

    helper(root, nullptr, memo, res);

    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is in the range |[1, 1000]|.
// * |Node.val == 0|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [0,0,null,0,0]
// Output: 1
//
// One camera is enough to monitor all nodes if placed as shown.

LEETCODE_SOLUTION_UNITTEST(968, BinaryTreeCameras, example_1) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({0, 0, null, 0, 0});
  int       expect   = 1;
  int       actual   = solution->minCameraCover(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #2]
//  Input: root = [0,0,null,0,null,0,null,null,0]
// Output: 2
//
// At least two cameras are needed to monitor all nodes of the tree. The above
// image shows one of the valid configurations of camera placement.

LEETCODE_SOLUTION_UNITTEST(968, BinaryTreeCameras, example_2) {
  auto      solution = MakeSolution();
  TreeNode *root =
      TreeNode::FromVector({0, 0, null, 0, null, 0, null, null, 0});
  int expect = 2;
  int actual = solution->minCameraCover(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

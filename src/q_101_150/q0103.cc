// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Binary Tree Zigzag Level Order Traversal
//
// https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/
//
// Question ID: 103
// Difficult  : Medium
// Solve Date : 2021/10/03 13:42

#include "leetcode/tree_node.h"
#include <deque>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |103. Binary Tree Zigzag Level Order Traversal|:
//
// Given the |root| of a binary tree, return the zigzag level order traversal of
// its nodes' values. (i.e., from left to right, then right to left for the next
// level and alternate between).  
//

LEETCODE_BEGIN_RESOLVING(103, BinaryTreeZigzagLevelOrderTraversal, Solution);

class Solution {
public:
  vector<vector<int>> zigzagLevelOrder(TreeNode *root) {
    vector<vector<int>> res;
    if (root == nullptr)
      return res;
    deque<TreeNode *> dq;
    dq.push_back(root);
    int       i    = 0;
    TreeNode *temp = nullptr;
    while (!dq.empty()) {
      int         s = dq.size();
      vector<int> ll;
      if (i % 2 == 0) {
        while (s--) {
          temp = dq.front();
          dq.pop_front();
          ll.push_back(temp->val);
          if (temp->left != NULL)
            dq.push_back(temp->left);
          if (temp->right != NULL)
            dq.push_back(temp->right);
        }
      } else {
        while (s--) {
          temp = dq.back();
          dq.pop_back();
          ll.push_back(temp->val);
          if (temp->right != NULL)
            dq.push_front(temp->right);
          if (temp->left != NULL)
            dq.push_front(temp->left);
        }
      }
      res.push_back(ll);
      i++;
    }
    return res;
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
//  Input: root = [3,9,20,null,null,15,7]
// Output: [[3],[20,9],[15,7]]
//

LEETCODE_SOLUTION_UNITTEST(103, BinaryTreeZigzagLevelOrderTraversal,
                           example_1) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({3, 9, 20, null, null, 15, 7});
  vector<vector<int>> expect = {
      {3},
      {20, 9},
      {15, 7}
  };
  vector<vector<int>> actual = solution->zigzagLevelOrder(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #2]
//  Input: root = [1]
// Output: [[1]]
//

LEETCODE_SOLUTION_UNITTEST(103, BinaryTreeZigzagLevelOrderTraversal,
                           example_2) {
  auto                solution = MakeSolution();
  TreeNode           *root     = TreeNode::FromVector({1});
  vector<vector<int>> expect   = {{1}};
  vector<vector<int>> actual   = solution->zigzagLevelOrder(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #3]
//  Input: root = []
// Output: []
//

LEETCODE_SOLUTION_UNITTEST(103, BinaryTreeZigzagLevelOrderTraversal,
                           example_3) {
  auto                solution = MakeSolution();
  TreeNode           *root     = TreeNode::FromVector({});
  vector<vector<int>> expect   = {};
  vector<vector<int>> actual   = solution->zigzagLevelOrder(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

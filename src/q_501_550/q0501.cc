// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Find Mode in Binary Search Tree
//
// https://leetcode.com/problems/find-mode-in-binary-search-tree/
//
// Question ID: 501
// Difficult  : Easy
// Solve Date : 2021/10/05 12:58

#include "leetcode/tree_node.h"
#include <iosfwd>
#include <map>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |501. Find Mode in Binary Search Tree|:
//
// Given the |root| of a binary search tree (BST) with duplicates, return all
// the [mode(s)] (i.e., the most frequently occurred element) in it. If the tree
// has more than one mode, return them in any order. Assume a BST is defined as
// follows:
//
//  • The left subtree of a node contains only nodes with keys less than or
//  equal to the node's key.
//
//  • The right subtree of a node contains only nodes with keys greater than or
//  equal to the node's key.
//
//  • Both the left and right subtrees must also be binary search trees.
//  
//

LEETCODE_BEGIN_RESOLVING(501, FindModeInBinarySearchTree, Solution);

class Solution {
private:
  unordered_map<int, int> mapping;
  int                     helper(TreeNode *p) {
    if (p == nullptr)
      return 0;
    int res = helper(p->left);
    res     = max(res, ++mapping[p->val]);
    res     = max(res, helper(p->right));
    return res;
  }

public:
  vector<int> findMode(TreeNode *root) {
    vector<int> res;
    int         maxmod = helper(root);
    for (auto it = mapping.begin(); it != mapping.end(); ++it) {
      if (it->second == maxmod) {
        res.push_back(it->first);
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is in the range |[1, 10⁴]|.
// * |-10⁵ <= Node.val <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [1,null,2,2]
// Output: [2]
//

LEETCODE_SOLUTION_UNITTEST(501, FindModeInBinarySearchTree, example_1) {
  auto        solution = MakeSolution();
  TreeNode   *root     = TreeNode::FromVector({1, null, 2, 2});
  vector<int> expect   = {2};
  vector<int> actual   = solution->findMode(root);
  EXPECT_ANYORDER_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #2]
//  Input: root = [0]
// Output: [0]
//

LEETCODE_SOLUTION_UNITTEST(501, FindModeInBinarySearchTree, example_2) {
  auto        solution = MakeSolution();
  TreeNode   *root     = TreeNode::FromVector({0});
  vector<int> expect   = {0};
  vector<int> actual   = solution->findMode(root);
  EXPECT_ANYORDER_EQ(expect, actual);
  TreeNode::Release(root);
}

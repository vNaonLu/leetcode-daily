// Copyright 2023 Naon Lu
//
// This file describes the solution of
// House Robber III
//
// https://leetcode.com/problems/house-robber-iii/
//
// Question ID: 337
// Difficult  : Medium
// Solve Date : 2021/12/05 14:08

#include "leetcode/tree_node.h"
#include <iosfwd>
#include <map>
#include <unordered_map>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |337. House Robber III|:
//
// The thief has found himself a new place for his thievery again. There is only
// one entrance to this area, called |root|. Besides the |root|, each house has
// one and only one parent house. After a tour, the smart thief realized that
// all houses in this place form a binary tree. It will automatically contact
// the police if two directly-linked houses were broken into on the same night.
// Given the |root| of the binary tree, return the maximum amount of money the
// thief can rob without alerting the police.  
//

LEETCODE_BEGIN_RESOLVING(337, HouseRobberIII, Solution);

class Solution {
private:
  int robRec(TreeNode *node, unordered_map<TreeNode *, int> &mem) {
    if (node == nullptr) {
      return 0;
    }
    if (mem.count(node) != 0) {
      return mem[node];
    }
    int maxWithNode = node->val;
    if (node->left != nullptr) {
      maxWithNode +=
          robRec(node->left->left, mem) + robRec(node->left->right, mem);
    }
    if (node->right != nullptr) {
      maxWithNode +=
          robRec(node->right->left, mem) + robRec(node->right->right, mem);
    }
    int maxWithoutNode = robRec(node->left, mem) + robRec(node->right, mem);
    return mem[node]   = max(maxWithNode, maxWithoutNode);
  }

public:
  int rob(TreeNode *root) {
    unordered_map<TreeNode *, int> mem;
    return robRec(root, mem);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is in the range |[1, 10⁴]|.
// * |0 <= Node.val <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [3,2,3,null,3,null,1]
// Output: 7
//
// Maximum amount of money the thief can rob = 3 + 3 + 1 = 7.

LEETCODE_SOLUTION_UNITTEST(337, HouseRobberIII, example_1) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({3, 2, 3, null, 3, null, 1});
  int       expect   = 7;
  int       actual   = solution->rob(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #2]
//  Input: root = [3,4,5,1,3,null,1]
// Output: 9
//
// Maximum amount of money the thief can rob = 4 + 5 = 9.

LEETCODE_SOLUTION_UNITTEST(337, HouseRobberIII, example_2) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({3, 4, 5, 1, 3, null, 1});
  int       expect   = 9;
  int       actual   = solution->rob(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

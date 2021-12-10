#include <gtest/gtest.h>
#include <iostream>
#include <leetcode/treenode.hpp>

using namespace std;

/**
 * This file is generated by leetcode_add.py v1.0
 *
 * 572.
 *      Subtree of Another Tree
 *
 * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
 *
 *   Given the roots of two binary trees ‘root’ and ‘subRoot’ , return
 *   ‘true’ if there is a subtree of ‘root’ with the same structure and
 *   node values of ‘ subRoot’ and ‘false’
 *   A subtree of a binary tree ‘tree’ is a tree that consists of a node in
 *   ‘tree’ and all of this node's descendants. The tree ‘tree’ could also
 *   be considered as a subtree of itself.
 *
 * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
 *
 *   • The number of nodes in the ‘root’ tree is in the range ‘[1, 2000]’ .
 *   • The number of nodes in the ‘subRoot’ tree is in the range ‘[1, 1000]’ .
 *   • ‘-10⁴ ≤ root.val ≤ 10⁴’
 *   • ‘-10⁴ ≤ subRoot.val ≤ 10⁴’
 *
 */

struct q572 : public ::testing::Test {
  // Leetcode answer here
  class Solution {
   private:
    bool helper(TreeNode* p, TreeNode* q) {
      if (p != nullptr && q != nullptr) {
        return p->val == q->val &&
               helper(p->left, q->left) &&
               helper(p->right, q->right);
      } else if (p == nullptr && q == nullptr) {
        return true;
      } else {
        return false;
      }
    }
   public:
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
      if (root == nullptr && subRoot == nullptr)
        return true;
      else if (root == nullptr)
        return false;
      else if (subRoot == nullptr)
        return true;
      if (helper(root, subRoot)) return true;
      return isSubtree(root->left, subRoot) ||
             isSubtree(root->right, subRoot);
    }
  };

  class Solution *solution;
};

TEST_F(q572, sample_input01) {
  solution = new Solution();
  TreeNode* root = TreeNode::generate({3, 4, 5, 1, 2});
  TreeNode* subRoot = TreeNode::generate({4, 1, 2});
  bool exp = true;
  EXPECT_EQ(solution->isSubtree(root, subRoot), exp);
  delete solution;
}

TEST_F(q572, sample_input02) {
  solution = new Solution();
  TreeNode* root = TreeNode::generate({3, 4, 5, 1, 2, NULL_TREENODE, NULL_TREENODE, NULL_TREENODE, NULL_TREENODE, 0});
  TreeNode* subRoot = TreeNode::generate({4, 1, 2});
  bool exp = false;
  EXPECT_EQ(solution->isSubtree(root, subRoot), exp);
  delete solution;
}
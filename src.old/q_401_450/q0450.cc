#include <gtest/gtest.h>
#include <iostream>
#include <leetcode/treenode.hpp>

using namespace std;

/**
 * This file is generated by leetcode_add.py v1.0
 *
 * 450.
 *      Delete Node in a BST
 *
 * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
 *
 *   Given a root node reference of a BST and a key, delete the node with
 *   the given key in the BST. Return the root node reference (possibly
 *   updated) of the
 *   Basically, the deletion can be divided into two
 *       1. Search for a node to
 *       2. If the node is found, delete the node.
 *
 * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
 *
 *   • The number of nodes in the tree is in the range ‘[0, 10⁴]’ .
 *   • ‘-10⁵ ≤ Node.val ≤ 10⁵’
 *   • Each node has a “unique” value.
 *   • ‘root’ is a valid binary search tree.
 *   • ‘-10⁵ ≤ key ≤ 10⁵’
 *
 */

struct q450 : public ::testing::Test {
  // Leetcode answer here
  class Solution {
   private:
    TreeNode *remove(TreeNode *p) {
      TreeNode *min = p->right;
      while (min != nullptr && min->left != nullptr) {
        if (min->left->left == nullptr) {
          TreeNode *pre = min;
          min = min->left;
          pre->left = min->right;
          break;
        }
        min = min->left;
      }
      if (min == nullptr) {
        return p->left;
      } else if (p->right == min) {
        min->left = p->left;
        return min;
      } else {
        min->left = p->left;
        min->right = p->right;
        return min;
      }
    }
   public:
    TreeNode *deleteNode(TreeNode *root, int key) {
      TreeNode *p = root, *pre = nullptr;
      while (p != nullptr) {
        if (p->val > key) {
          pre = p;
          p = p->left;
        } else if (p->val < key) {
          pre = p;
          p = p->right;
        } else {
          if (pre == nullptr) {
            root = remove(p);
          } else {
            if (pre->left == p) {
              pre->left = remove(p);
            } else {
              pre->right = remove(p);
            }
          }
          break;
        }
      }
      return root;
    }
  };

  class Solution *solution;
};

TEST_F(q450, sample_input01) {
  solution = new Solution();
  TreeNode* root = TreeNode::generate({5, 3, 6, 2, 4, NULL_TREENODE, 7});
  int key = 3;
  TreeNode* exp = TreeNode::generate({5, 4, 6, 2, NULL_TREENODE, NULL_TREENODE, 7});
  TreeNode *act = solution->deleteNode(root, key);
  EXPECT_TREENODE_EQ(act, exp);
  TreeNode::release(root, exp, act);
  delete solution;
}

TEST_F(q450, sample_input02) {
  solution = new Solution();
  TreeNode* root = TreeNode::generate({5, 3, 6, 2, 4, NULL_TREENODE, 7});
  int key = 0;
  TreeNode *exp = TreeNode::generate({5, 3, 6, 2, 4, NULL_TREENODE, 7});
  TreeNode *act = solution->deleteNode(root, key);
  EXPECT_TREENODE_EQ(act, exp);
  TreeNode::release(root, exp, act);
  delete solution;
}

TEST_F(q450, sample_input03) {
  solution = new Solution();
  TreeNode* root = TreeNode::generate({});
  int key = 0;
  TreeNode *exp = TreeNode::generate({});
  TreeNode *act = solution->deleteNode(root, key);
  EXPECT_TREENODE_EQ(act, exp);
  TreeNode::release(root, exp, act);
  delete solution;
}
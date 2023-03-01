#include <gtest/gtest.h>
#include <iostream>
#include <leetcode/treenode.hpp>
#include <unordered_set>

using namespace std;

/**
 * This file is generated by leetcode_add.py
 *
 * 968.
 *      Binary Tree Cameras
 *
 * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
 *
 *   You are given the ‘root’ of a binary tree. We install cameras on the
 *   tree nodes where each camera at a node can monitor its parent, itself,
 *   and its immediate
 *   Return “the minimum number of cameras needed to monitor all nodes of
 *   the tree” .
 *
 * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
 *
 *   • The number of nodes in the tree is in the range ‘[1, 1000]’ .
 *   • ‘Node.val = 0’
 *
 */

struct q968 : public ::testing::Test {
  // Leetcode answer here
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
private:
    void helper(TreeNode *p, TreeNode *prev,
                unordered_set<TreeNode*> &memo, int &res) {
        if (nullptr != p) {
            helper(p->left, p, memo, res);
            helper(p->right, p, memo, res);
            
            if (nullptr == prev && !memo.count(p) ||
                                   !memo.count(p->left) ||
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
    int minCameraCover(TreeNode* root) {
        int res = 0;
        unordered_set<TreeNode*> memo;
        memo.insert(nullptr);
        
        helper(root, nullptr, memo, res);
        
        return res;
    }
};

  class Solution *solution;
};

TEST_F(q968, sample_input01) {
  solution = new Solution();
  TreeNode* root = TreeNode::generate({0, 0, NULL_TREENODE, 0, 0});
  int exp = 1;
  int act = solution->minCameraCover(root);
  EXPECT_EQ(act, exp);
  TreeNode::release(root);
  delete solution;
}

TEST_F(q968, sample_input02) {
  solution = new Solution();
  TreeNode* root = TreeNode::generate({0, 0, NULL_TREENODE, 0, NULL_TREENODE, 0, NULL_TREENODE, NULL_TREENODE, 0});
  int exp = 2;
  int act = solution->minCameraCover(root);
  EXPECT_EQ(act, exp);
  TreeNode::release(root);
  delete solution;
}
#include <gtest/gtest.h>
#include <iostream>
#include <leetcode/treenode.hpp>
#include <vector>

using namespace std;

/**
 * The file is generated by LeetCodeDailyTools
 *
 * 107.
 *      Binary Tree Level Order Traversal II
 *
 * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
 *
 *   Given the ‘root’ of a binary tree, return “the bottom-up level order
 *   traversal of its nodes' values” . (i.e., from left to right, level by
 *   level from leaf to root).
 *
 * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
 *
 *   • The number of nodes in the tree is in the range ‘[0, 2000]’ .
 *   • ‘-1000 ≤ Node.val ≤ 1000’
 *
 * see more details:
 * https://leetcode.com/problems/binary-tree-level-order-traversal-ii/
 */

struct q107 : public ::testing::Test {
  // Leetcode answer here
  class Solution {
  private:
    void helper(vector<vector<int>> &res, TreeNode *p, int level = 0) {
      if (p) {
        if (res.size() <= level) {
          res.resize(level + 1);
        }
        res[level].emplace_back(p->val);
        helper(res, p->left, level + 1);
        helper(res, p->right, level + 1);
      }
    }

  public:
    vector<vector<int>> levelOrderBottom(TreeNode *root) {
      vector<vector<int>> res;
      helper(res, root);
      reverse(res.begin(), res.end());
      return res;
    }
  };

  class Solution *solution;
};

TEST_F(q107, sample_input01) {
  solution = new Solution();
  TreeNode *root =
      TreeNode::generate({3, 9, 20, NULL_TREENODE, NULL_TREENODE, 15, 7});
  vector<vector<int>> exp = {
      {15, 7},
      {9, 20},
      {3}
  };
  vector<vector<int>> act = solution->levelOrderBottom(root);
  EXPECT_EQ(act, exp);
  TreeNode::release(root);
  delete solution;
}

TEST_F(q107, sample_input02) {
  solution                 = new Solution();
  TreeNode           *root = TreeNode::generate({1});
  vector<vector<int>> exp  = {{1}};
  vector<vector<int>> act  = solution->levelOrderBottom(root);
  EXPECT_EQ(act, exp);
  TreeNode::release(root);
  delete solution;
}

TEST_F(q107, sample_input03) {
  solution                 = new Solution();
  TreeNode           *root = TreeNode::generate({});
  vector<vector<int>> exp  = {};
  vector<vector<int>> act  = solution->levelOrderBottom(root);
  EXPECT_EQ(act, exp);
  TreeNode::release(root);
  delete solution;
}

TEST_F(q107, input01) {
  solution                 = new Solution();
  TreeNode           *root = TreeNode::generate({1, 2, 3, 4, 5});
  vector<vector<int>> exp  = {
      {4, 5},
      {2, 3},
      {1}
  };
  vector<vector<int>> act = solution->levelOrderBottom(root);
  EXPECT_EQ(act, exp);
  TreeNode::release(root);
  delete solution;
}
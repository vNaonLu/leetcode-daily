#include <gtest/gtest.h>
#include <iostream>
#include <leetcode/anyorder.hpp>
#include <leetcode/treenode.hpp>
#include <unordered_map>
#include <vector>

using namespace std;

/**
 * This file is generated by leetcode_add.py v1.0
 *
 * 501.
 *      Find Mode in Binary Search Tree
 *
 * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
 *
 *   Given the ‘root’ of a binary search tree (BST) with duplicates, return
 *   “all the <a href="https://en.wikipedia.org/wiki/Mode_(statistics)"
 *   target="_blank">mode(s)</a> (i.e., the most frequently occurred
 *   element) in it”
 *   If the tree has more than one mode, return them in “any order”
 *   Assume a BST is defined as
 *       - The left subtree of a node contains only nodes with keys “less
 *   than or equal to” the node's
 *       - The right subtree of a node contains only nodes with keys
 *   “greater than or equal to” the node's
 *       - Both the left and right subtrees must also be binary search
 *   trees.
 *
 * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
 *
 *   • The number of nodes in the tree is in the range ‘[1, 10⁴]’ .
 *   • ‘-10⁵ ≤ Node.val ≤ 10⁵’
 *
 */

struct q501 : public ::testing::Test {
  // Leetcode answer here
  class Solution {
   private:
    unordered_map<int, int> mapping;
    int helper(TreeNode* p) {
      if (p == nullptr) return 0;
      int res = helper(p->left);
      res = max(res, ++mapping[p->val]);
      res = max(res, helper(p->right));
      return res;
    }
   public:
    vector<int> findMode(TreeNode* root) {
      vector<int> res;
      int maxmod = helper(root);
      for (auto it = mapping.begin(); it != mapping.end(); ++it) {
        if (it->second == maxmod) {
          res.push_back(it->first);
        }
      }
      return res;
    }
  };

  class Solution *solution;
};

TEST_F(q501, sample_input01) {
  solution = new Solution();
  TreeNode* root = TreeNode::generate({1, NULL_TREENODE, 2, 2});
  vector<int> exp = {2};
  // Try EXPECT_EQ_ANY_ORDER_RECURSIVE
  // if the element is also matched in any order.
  EXPECT_EQ_ANY_ORDER(solution->findMode(root), exp);
  delete solution;
}

TEST_F(q501, sample_input02) {
  solution = new Solution();
  TreeNode* root = TreeNode::generate({0});
  vector<int> exp = {0};
  // Try EXPECT_EQ_ANY_ORDER_RECURSIVE
  // if the element is also matched in any order.
  EXPECT_EQ_ANY_ORDER(solution->findMode(root), exp);
  delete solution;
}
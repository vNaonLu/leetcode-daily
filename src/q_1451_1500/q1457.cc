#include <gtest/gtest.h>
#include <iostream>
#include <leetcode/treenode.hpp>
#include <vector>

using namespace std;

/**
 * This file is generated by leetcode_add.py
 *
 * 1457.
 *       Pseudo-Palindromic Paths in a Binary Tree
 *
 * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
 *
 *   Given a binary tree where node values are digits from 1 to 9. A path
 *   in the binary tree is said to be “pseudo-palindromic” if at least one
 *   permutation of the node values in the path is a
 *    “Return the number of “pseudo-palindromic” paths going from the root
 *   node to leaf nodes.”
 *
 * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
 *
 *   • The number of nodes in the tree is in the range ‘[1, 10⁵]’ .
 *   • ‘1 ≤ Node.val ≤ 9’
 *
 */

struct q1457 : public ::testing::Test {
  // Leetcode answer here
  class Solution {
  private:
    bool isLeaf(TreeNode *p) {
      if (nullptr == p) {
        return false;
      }
      return nullptr == p->left && nullptr == p->right;
    }

    template <typename Iterator>
    bool isPseudoPalindromic(Iterator beg, Iterator end) {
      auto single = false;
      while (beg != end) {
        if (*beg++ & 1) {
          if (single) {
            return false;
          }
          single = true;
        }
      }
      return true;
    }

    void dfs(TreeNode *p, vector<int> &cnt, int &res) {
      if (nullptr != p) {
        ++cnt[p->val];
        if (isLeaf(p)) {
          if (isPseudoPalindromic(cnt.begin(), cnt.end())) {
            ++res;
          }
        } else {
          dfs(p->left, cnt, res);
          dfs(p->right, cnt, res);
        }
        --cnt[p->val];
      }
    }

  public:
    int pseudoPalindromicPaths(TreeNode *root) {
      auto cnt = vector<int>(10);
      auto res = (int)0;
      dfs(root, cnt, res);
      return res;
    }
  };

  class Solution *solution;
};

TEST_F(q1457, sample_input01) {
  solution       = new Solution();
  TreeNode *root = TreeNode::generate({2, 3, 1, 3, 1, NULL_TREENODE, 1});
  int       exp  = 2;
  int       act  = solution->pseudoPalindromicPaths(root);
  EXPECT_EQ(act, exp);
  TreeNode::release(root);
  delete solution;
}

TEST_F(q1457, sample_input02) {
  solution = new Solution();
  TreeNode *root =
      TreeNode::generate({2, 1, 1, 1, 3, NULL_TREENODE, NULL_TREENODE,
                          NULL_TREENODE, NULL_TREENODE, NULL_TREENODE, 1});
  int exp = 1;
  int act = solution->pseudoPalindromicPaths(root);
  EXPECT_EQ(act, exp);
  TreeNode::release(root);
  delete solution;
}

TEST_F(q1457, sample_input03) {
  solution       = new Solution();
  TreeNode *root = TreeNode::generate({9});
  int       exp  = 1;
  int       act  = solution->pseudoPalindromicPaths(root);
  EXPECT_EQ(act, exp);
  TreeNode::release(root);
  delete solution;
}
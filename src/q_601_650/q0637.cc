#include <gtest/gtest.h>
#include <iostream>
#include <leetcode/treenode.hpp>
#include <numeric>
#include <vector>

using namespace std;

/**
 * This file is generated by leetcode_add.py
 *
 * 637.
 *      Average of Levels in Binary Tree
 *
 * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
 *
 *   Given the ‘root’ of a binary tree, return “the average value of the
 *   nodes on each level in the form of an array” . Answers within ‘10⁻⁵’
 *   of the actual answer will be accepted.
 *
 * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
 *
 *   • The number of nodes in the tree is in the range ‘[1, 10⁴]’ .
 *   • ‘-2³¹ ≤ Node.val ≤ 2³¹ - 1’
 *
 */

struct q637 : public ::testing::Test {
  // Leetcode answer here
  class Solution {
  private:
    void solve(TreeNode *p, vector<vector<int64_t>> &vals, int lvl = 0) {
      if (nullptr == p) {
        return;
      }

      if (lvl >= vals.size()) {
        vals.resize(lvl + 1);
      }

      vals[lvl].emplace_back(p->val);
      solve(p->left, vals, lvl + 1);
      solve(p->right, vals, lvl + 1);
    }

  public:
    vector<double> averageOfLevels(TreeNode *root) {
      auto res = vector<double>();
      auto cnt = vector<vector<int64_t>>();
      solve(root, cnt);
      for (auto &v : cnt) {
        res.emplace_back(accumulate(v.begin(), v.end(), 0.0) /
                         static_cast<double>(v.size()));
      }
      return res;
    }
  };

  class Solution *solution;
};

TEST_F(q637, sample_input01) {
  solution = new Solution();
  TreeNode *root =
      TreeNode::generate({3, 9, 20, NULL_TREENODE, NULL_TREENODE, 15, 7});
  vector<double> exp = {3.00000, 14.50000, 11.00000};
  vector<double> act = solution->averageOfLevels(root);
  EXPECT_EQ(act, exp);
  TreeNode::release(root);
  delete solution;
}

TEST_F(q637, sample_input02) {
  solution            = new Solution();
  TreeNode      *root = TreeNode::generate({3, 9, 20, 15, 7});
  vector<double> exp  = {3.00000, 14.50000, 11.00000};
  vector<double> act  = solution->averageOfLevels(root);
  EXPECT_EQ(act, exp);
  TreeNode::release(root);
  delete solution;
}

#ifndef Q108_UNITTEST_H__
#define Q108_UNITTEST_H__
#include <gtest/gtest.h>

#include <cmath>

#include "q0108.hpp"
using namespace std;

/**
  * This file is generated by leetcode_add.py
  *
  * 108.
  *      Convert Sorted Array to Binary Search Tree
  *
  * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
  *
  *   Given an integer array ‘nums’ where the elements are sorted in
  *   “ascending order” , convert “it to a “height-balanced” binary search
  *   tree”.
  *   
  *   A “height-balanced” binary tree is a binary tree in which the depth of
  *   the two subtrees of every node never differs by more than one.
  *
  * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
  *
  *   • ‘1 ≤ nums.length ≤ 10⁴’
  *   • ‘-10⁴ ≤ nums[i] ≤ 10⁴’
  *   • ‘nums’ is sorted in a “strictly increasing” order.
  *
*/

bool expect(TreeNode* p, const int max_level, int level = 0) {
  if (p == nullptr) return true;
  if (level > max_level) return false;
  return (p->left ? p->val >= p->left->val && expect(p->left, max_level, level + 1) : true) &&
         (p->right ? p->val <= p->right->val && expect(p->right, max_level, level + 1) : true);
};

TEST(q108, sample_input01) {
  l108::Solution solver;
  vector<int> nums = {-10, -3, 0, 5, 9};
  EXPECT_TRUE(expect(solver.sortedArrayToBST(nums),
                     log2(nums.size())));
}

TEST(q108, sample_input02) {
  l108::Solution solver;
  vector<int> nums = {1, 3};
  EXPECT_TRUE(expect(solver.sortedArrayToBST(nums),
                     log2(nums.size())));
}

#endif
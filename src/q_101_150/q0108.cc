#include <cmath>
#include <gtest/gtest.h>
#include <iostream>
#include <leetcode/treenode.hpp>
#include <vector>

using namespace std;

/**
 * This file is generated by leetcode_add.py v1.0
 *
 * 108.
 *      Convert Sorted Array to Binary Search Tree
 *
 * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
 *
 *   Given an integer array ‘nums’ where the elements are sorted in
 *   “ascending order” , convert “it to a “height-balanced” binary search
 *   tree”
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

struct q108 : public ::testing::Test {
  // Leetcode answer here
  class Solution {
  private:
    template <typename Iterator> TreeNode *build(Iterator beg, Iterator end) {
      if (beg == end) {
        return nullptr;
      } else if (beg + 1 == end) {
        return new TreeNode(*beg);
      } else {
        auto mid = beg + distance(beg, end) / 2;
        return new TreeNode(*mid, build(beg, mid), build(mid + 1, end));
      }
    }

  public:
    TreeNode *sortedArrayToBST(vector<int> &nums) {
      return build(nums.begin(), nums.end());
    }
  };

  class Solution *solution;
};

bool expect(TreeNode *p, const int max_level, int level = 0) {
  if (p == nullptr)
    return true;
  if (level > max_level)
    return false;
  return (p->left
              ? p->val >= p->left->val && expect(p->left, max_level, level + 1)
              : true) &&
         (p->right ? p->val <= p->right->val &&
                         expect(p->right, max_level, level + 1)
                   : true);
};

TEST_F(q108, sample_input01) {
  solution         = new Solution();
  vector<int> nums = {-10, -3, 0, 5, 9};
  TreeNode   *exp  = TreeNode::generate({0, -3, 9, -10, NULL_TREENODE, 5});
  EXPECT_TRUE(expect(solution->sortedArrayToBST(nums), log2(nums.size())));
  delete solution;
}

TEST_F(q108, sample_input02) {
  solution         = new Solution();
  vector<int> nums = {1, 3};
  TreeNode   *exp  = TreeNode::generate({3, 1});
  EXPECT_TRUE(expect(solution->sortedArrayToBST(nums), log2(nums.size())));
  delete solution;
}
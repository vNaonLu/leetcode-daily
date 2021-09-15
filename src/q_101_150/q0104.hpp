
#ifndef LEETCODE_Q104_H__
#define LEETCODE_Q104_H__
#include <iostream>
#include <leetcode/tree_node.hpp>
#include <vector>

namespace l104 {
using namespace std;

/**
  * this file is generated by gquestion.py
  *
  * 104. Maximum Depth of Binary Tree
  *
  * Given the root of a binary tree, return its
  * maximum depth .
  * A binary tree';s “maximum depth“ is the number of
  * nodes along the longest path from the root node
  * down to the farthest leaf node.
  *
  * Constraints:
  * - The number of nodes in the tree is in the range [0, 10^(4)] .
  * -  -100 <= Node.val <= 100 
  *
*/
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
  int helper(TreeNode* p, int h = 0) {
    if (p == nullptr) return h;

    return max({h, helper(p->left, h + 1), helper(p->right, h + 1)});
  }

 public:
  int maxDepth(TreeNode* root) {
    int res = helper(root);
    return res;
  }
};
}  // namespace l104
#endif
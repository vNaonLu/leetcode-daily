
#ifndef LEETCODE_Q145_H__
#define LEETCODE_Q145_H__
#include <iostream>
#include <vector>

#include "leetcode_struct/tree_node.hpp"

namespace l145 {
using namespace std;

/**
  * this file is generated by gquestion.py
  *
  * 145. Binary Tree Postorder Traversal
  *
  * Given the root of abinary tree, return the
  * postorder traversal of its nodes'; values .
  *
  * Constraints:
  * - The number of the nodes in the tree is in the range [0, 100] .
  * -  -100 <= Node.val <= 100 
  *  “Follow up:“ Recursive solution is trivial, could you do it iteratively?
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
  void helper(TreeNode *p, vector<int> &re) {
    if (p == nullptr) return;
    helper(p->left, re);
    helper(p->right, re);
    re.push_back(p->val);
  }

 public:
  vector<int> postorderTraversal(TreeNode *root) {
    vector<int> res;
    helper(root, res);
    return res;
  }
};
}  // namespace l145
#endif
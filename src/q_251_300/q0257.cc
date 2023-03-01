// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Binary Tree Paths
//
// https://leetcode.com/problems/binary-tree-paths/
//
// Question ID: 257
// Difficult  : Easy
// Solve Date : 2021/10/08 15:55

#include "leetcode/tree_node.h"
#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |257. Binary Tree Paths|:
//
// Given the |root| of a binary tree, return all root-to-leaf paths in any
// order. A leaf is a node with no children.  
//

LEETCODE_BEGIN_RESOLVING(257, BinaryTreePaths, Solution);

class Solution {
private:
  void helper(TreeNode *p, vector<string> &res, vector<int> &cur) {
    if (p == nullptr)
      return;
    cur.push_back(p->val);
    if (p->left == nullptr && p->right == nullptr) {
      string path = to_string(cur.front());
      for (int i = 1; i < cur.size(); ++i)
        path += "->" + to_string(cur[i]);
      res.push_back(path);
    } else {
      helper(p->left, res, cur);
      helper(p->right, res, cur);
    }
    cur.pop_back();
  }

public:
  vector<string> binaryTreePaths(TreeNode *root) {
    vector<string> res;
    vector<int>    tmp;
    helper(root, res, tmp);
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is in the range |[1, 100]|.
// * |-100 <= Node.val <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [1,2,3,null,5]
// Output: ["1->2->5","1->3"]
//

LEETCODE_SOLUTION_UNITTEST(257, BinaryTreePaths, example_1) {
  auto           solution = MakeSolution();
  TreeNode      *root     = TreeNode::FromVector({1, 2, 3, null, 5});
  vector<string> expect   = {"1->2->5", "1->3"};
  vector<string> actual   = solution->binaryTreePaths(root);
  EXPECT_ANYORDER_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #2]
//  Input: root = [1]
// Output: ["1"]
//

LEETCODE_SOLUTION_UNITTEST(257, BinaryTreePaths, example_2) {
  auto           solution = MakeSolution();
  TreeNode      *root     = TreeNode::FromVector({1});
  vector<string> expect   = {"1"};
  vector<string> actual   = solution->binaryTreePaths(root);
  EXPECT_ANYORDER_EQ(expect, actual);
  TreeNode::Release(root);
}

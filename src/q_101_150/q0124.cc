// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Binary Tree Maximum Path Sum
//
// https://leetcode.com/problems/binary-tree-maximum-path-sum/
//
// Question ID: 124
// Difficult  : Hard
// Solve Date : 2022/02/10 21:05

#include "leetcode/tree_node.h"
#include <iosfwd>
#include <map>
#include <unordered_map>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |124. Binary Tree Maximum Path Sum|:
//
// A path in a binary tree is a sequence of nodes where each pair of adjacent
// nodes in the sequence has an edge connecting them. A node can only appear in
// the sequence at most once. Note that the path does not need to pass through
// the root. The path sum of a path is the sum of the node's values in the path.
// Given the |root| of a binary tree, return the maximum path sum of any
// non-empty path.  
//

LEETCODE_BEGIN_RESOLVING(124, BinaryTreeMaximumPathSum, Solution);

class Solution {
private:
  unordered_map<TreeNode *, int> memo{
      {nullptr, 0}
  };
  int findMaxSum(TreeNode *p) {
    if (!memo.count(p)) {
      memo[p] = p->val + max({findMaxSum(p->left), findMaxSum(p->right), 0});
    }
    return memo[p];
  }

public:
  int maxPathSum(TreeNode *root) {
    if (nullptr == root)
      return 0;
    int res = root->val + max(findMaxSum(root->left), 0) +
              max(findMaxSum(root->right), 0);
    if (nullptr != root->left)
      res = max(res, maxPathSum(root->left));
    if (nullptr != root->right)
      res = max(res, maxPathSum(root->right));
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is in the range |[1, 3 * 10⁴]|.
// * |-1000 <= Node.val <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [1,2,3]
// Output: 6
//
// The optimal path is 2 -> 1 -> 3 with a path sum of 2 + 1 + 3 = 6.

LEETCODE_SOLUTION_UNITTEST(124, BinaryTreeMaximumPathSum, example_1) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({1, 2, 3});
  int       expect   = 6;
  int       actual   = solution->maxPathSum(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #2]
//  Input: root = [-10,9,20,null,null,15,7]
// Output: 42
//
// The optimal path is 15 -> 20 -> 7 with a path sum of 15 + 20 + 7 = 42.

LEETCODE_SOLUTION_UNITTEST(124, BinaryTreeMaximumPathSum, example_2) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({-10, 9, 20, null, null, 15, 7});
  int       expect   = 42;
  int       actual   = solution->maxPathSum(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

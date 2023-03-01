// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Maximum Width of Binary Tree
//
// https://leetcode.com/problems/maximum-width-of-binary-tree/
//
// Question ID: 662
// Difficult  : Medium
// Solve Date : 2022/02/27 11:27

#include "leetcode/tree_node.h"
#include <iosfwd>
#include <queue>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |662. Maximum Width of Binary Tree|:
//
// Given the |root| of a binary tree, return the maximum width of the given
// tree. The maximum width of a tree is the maximum width among all levels. The
// width of one level is defined as the length between the end-nodes (the
// leftmost and rightmost non-null nodes), where the null nodes between the
// end-nodes that would be present in a complete binary tree extending down to
// that level are also counted into the length calculation. It is guaranteed
// that the answer will in the range of a 32-bit signed integer.  
//

LEETCODE_BEGIN_RESOLVING(662, MaximumWidthOfBinaryTree, Solution);

class Solution {
private:
  using ull = unsigned long long;

public:
  int widthOfBinaryTree(TreeNode *root) {
    if (nullptr == root)
      return 0;
    ull                          res = 1;
    queue<pair<TreeNode *, ull>> q;
    q.emplace(root, 0);
    while (!q.empty()) {
      queue<pair<TreeNode *, ull>> temp = move(q);
      ull                          left = -1;
      while (!temp.empty()) {
        auto [p, index] = temp.front();
        temp.pop();
        index <<= 1;
        if (nullptr != p->left) {
          if (left == -1) {
            left = index;
          } else {
            res = max(res, index - left + 1);
          }
          q.emplace(p->left, index);
        }
        if (nullptr != p->right) {
          if (left == -1) {
            left = index + 1;
          } else {
            res = max(res, index - left + 2);
          }
          q.emplace(p->right, index + 1);
        }
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is in the range |[1, 3000]|.
// * |-100 <= Node.val <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [1,3,2,5,3,null,9]
// Output: 4
//
// The maximum width exists in the third level with length 4 (5,3,null,9).

LEETCODE_SOLUTION_UNITTEST(662, MaximumWidthOfBinaryTree, example_1) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({1, 3, 2, 5, 3, null, 9});
  int       expect   = 4;
  int       actual   = solution->widthOfBinaryTree(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #2]
//  Input: root = [1,3,2,5,null,null,9,6,null,7]
// Output: 7
//
// The maximum width exists in the fourth level with length 7
// (6,null,null,null,null,null,7).

LEETCODE_SOLUTION_UNITTEST(662, MaximumWidthOfBinaryTree, example_2) {
  auto      solution = MakeSolution();
  TreeNode *root =
      TreeNode::FromVector({1, 3, 2, 5, null, null, 9, 6, null, 7});
  int expect = 7;
  int actual = solution->widthOfBinaryTree(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #3]
//  Input: root = [1,3,2,5]
// Output: 2
//
// The maximum width exists in the second level with length 2 (3,2).

LEETCODE_SOLUTION_UNITTEST(662, MaximumWidthOfBinaryTree, example_3) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({1, 3, 2, 5});
  int       expect   = 2;
  int       actual   = solution->widthOfBinaryTree(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

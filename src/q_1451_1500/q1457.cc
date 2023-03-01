// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Pseudo-Palindromic Paths in a Binary Tree
//
// https://leetcode.com/problems/pseudo-palindromic-paths-in-a-binary-tree/
//
// Question ID: 1457
// Difficult  : Medium
// Solve Date : 2022/09/14 15:01

#include "leetcode/tree_node.h"
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1457. Pseudo-Palindromic Paths in a Binary Tree|:
//
// Given a binary tree where node values are digits from 1 to 9. A path in the
// binary tree is said to be pseudo-palindromic if at least one permutation of
// the node values in the path is a palindrome. Return the number of
// pseudo-palindromic paths going from the root node to leaf nodes.
//

LEETCODE_BEGIN_RESOLVING(1457, PseudoPalindromicPathsInABinaryTree, Solution);

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

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is in the range |[1, 10⁵]|.
// * |1 <= Node.val <= 9|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [2,3,1,3,1,null,1]
// Output: 2
//
// The figure above represents the given binary tree. There are three paths
// going from the root node to leaf nodes: the red path [2,3,3], the green path
// [2,1,1], and the path [2,3,1]. Among these paths only red path and green path
// are pseudo-palindromic paths since the red path [2,3,3] can be rearranged in
// [3,2,3] (palindrome) and the green path [2,1,1] can be rearranged in [1,2,1]
// (palindrome).

LEETCODE_SOLUTION_UNITTEST(1457, PseudoPalindromicPathsInABinaryTree,
                           example_1) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({2, 3, 1, 3, 1, null, 1});
  int       expect   = 2;
  int       actual   = solution->pseudoPalindromicPaths(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #2]
//  Input: root = [2,1,1,1,3,null,null,null,null,null,1]
// Output: 1
//
// The figure above represents the given binary tree. There are three paths
// going from the root node to leaf nodes: the green path [2,1,1], the path
// [2,1,3,1], and the path [2,1]. Among these paths only the green path is
// pseudo-palindromic since [2,1,1] can be rearranged in [1,2,1] (palindrome).

LEETCODE_SOLUTION_UNITTEST(1457, PseudoPalindromicPathsInABinaryTree,
                           example_2) {
  auto      solution = MakeSolution();
  TreeNode *root =
      TreeNode::FromVector({2, 1, 1, 1, 3, null, null, null, null, null, 1});
  int expect = 1;
  int actual = solution->pseudoPalindromicPaths(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #3]
//  Input: root = [9]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(1457, PseudoPalindromicPathsInABinaryTree,
                           example_3) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({9});
  int       expect   = 1;
  int       actual   = solution->pseudoPalindromicPaths(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

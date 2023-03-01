// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Check Completeness of a Binary Tree
//
// https://leetcode.com/problems/check-completeness-of-a-binary-tree/
//
// Question ID: 958
// Difficult  : Medium
// Solve Date : 2022/08/10 20:36

#include "leetcode/tree_node.h"
#include <iosfwd>
#include <queue>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |958. Check Completeness of a Binary Tree|:
//
// Given the |root| of a binary tree, determine if it is a complete binary tree.
// In a [complete binary tree], every level, except possibly the last, is
// completely filled, and all nodes in the last level are as far left as
// possible. It can have between |1| and |2ʰ| nodes inclusive at the last level
// |h|.
//

LEETCODE_BEGIN_RESOLVING(958, CheckCompletenessOfABinaryTree, Solution);

class Solution {
private:
  int count(TreeNode *p) {
    if (nullptr == p) {
      return 0;
    } else {
      return 1 + count(p->left) + count(p->right);
    }
  }

public:
  bool isCompleteTree(TreeNode *root) {
    auto total    = count(root);
    auto traveled = 0;
    auto q        = queue<TreeNode *>();

    q.emplace(root);
    while (!q.empty()) {
      auto curr = q.front();
      q.pop();

      if (curr == nullptr) {
        break;
      }

      ++traveled;
      q.emplace(curr->left);
      q.emplace(curr->right);
    }

    return traveled == total;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is in the range |[1, 100]|.
// * |1 <= Node.val <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [1,2,3,4,5,6]
// Output: true
//
// Every level before the last is full (ie. levels with node-values {1} and {2,
// 3}), and all nodes in the last level ({4, 5, 6}) are as far left as possible.

LEETCODE_SOLUTION_UNITTEST(958, CheckCompletenessOfABinaryTree, example_1) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({1, 2, 3, 4, 5, 6});
  bool      expect   = true;
  bool      actual   = solution->isCompleteTree(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #2]
//  Input: root = [1,2,3,4,5,null,7]
// Output: false
//
// The node with value 7 isn't as far left as possible.

LEETCODE_SOLUTION_UNITTEST(958, CheckCompletenessOfABinaryTree, example_2) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({1, 2, 3, 4, 5, null, 7});
  bool      expect   = false;
  bool      actual   = solution->isCompleteTree(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

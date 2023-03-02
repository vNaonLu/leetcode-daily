// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Count Complete Tree Nodes
//
// https://leetcode.com/problems/count-complete-tree-nodes/
//
// Question ID: 222
// Difficult  : Medium
// Solve Date : 2021/10/24 22:03

#include "leetcode/tree_node.h"
#include <cmath>
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |222. Count Complete Tree Nodes|:
//
// Given the |root| of a complete binary tree, return the number of the nodes in
// the tree. According to [Wikipedia], every level, except possibly the last, is
// completely filled in a complete binary tree, and all nodes in the last level
// are as far left as possible. It can have between |1| and |2ʰ| nodes inclusive
// at the last level |h|. Design an algorithm that runs in less than 
// |O(n)| time complexity.  
//

LEETCODE_BEGIN_RESOLVING(222, CountCompleteTreeNodes, Solution);

class Solution {
private:
  template <typename Op>
  int calcHeight(TreeNode *p, Op f) {
    if (p == nullptr) {
      return 0;
    } else {
      return 1 + calcHeight(f(p), f);
    }
  }

public:
  int countNodes(TreeNode *root) {
    int lh = calcHeight(root, [](TreeNode *p) { return p->left; }),
        rh = calcHeight(root, [](TreeNode *p) { return p->right; });

    if (lh == rh) {
      return pow(2, lh) - 1;
    } else {
      return 1 + countNodes(root->left) + countNodes(root->right);
    }
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is in the range |[0, 5 * 10⁴]|.
// * |0 <= Node.val <= 5 * 10⁴|
// * The tree is guaranteed to be complete.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [1,2,3,4,5,6]
// Output: 6
//

LEETCODE_SOLUTION_UNITTEST(222, CountCompleteTreeNodes, example_1) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({1, 2, 3, 4, 5, 6});
  int       expect   = 6;
  int       actual   = solution->countNodes(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #2]
//  Input: root = []
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(222, CountCompleteTreeNodes, example_2) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({});
  int       expect   = 0;
  int       actual   = solution->countNodes(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #3]
//  Input: root = [1]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(222, CountCompleteTreeNodes, example_3) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({1});
  int       expect   = 1;
  int       actual   = solution->countNodes(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

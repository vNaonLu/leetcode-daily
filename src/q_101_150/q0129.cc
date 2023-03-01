// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Sum Root to Leaf Numbers
//
// https://leetcode.com/problems/sum-root-to-leaf-numbers/
//
// Question ID: 129
// Difficult  : Medium
// Solve Date : 2021/11/03 18:16

#include "leetcode/tree_node.h"
#include <iosfwd>
#include <numeric>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |129. Sum Root to Leaf Numbers|:
//
// You are given the |root| of a binary tree containing digits from |0| to |9|
// only. Each root-to-leaf path in the tree represents a number.
//
//  • For example, the root-to-leaf path |1 -> 2 -> 3| represents the number
//  |123|.
// Return the total sum of all root-to-leaf numbers. Test cases are generated so
// that the answer will fit in a 32-bit integer. A leaf node is a node with no
// children.  
//

LEETCODE_BEGIN_RESOLVING(129, SumRootToLeafNumbers, Solution);

class Solution {
private:
  void helper(TreeNode *p, vector<int> &nums, int current = 0) {
    if (p != nullptr) {
      current = current * 10 + p->val;
      if (p->left == nullptr && p->right == nullptr) {
        nums.push_back(current);
      } else {
        helper(p->left, nums, current);
        helper(p->right, nums, current);
      }
    }
  }

public:
  int sumNumbers(TreeNode *root) {
    vector<int> leavesSum;
    helper(root, leavesSum);
    return accumulate(leavesSum.begin(), leavesSum.end(), 0);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is in the range |[1, 1000]|.
// * |0 <= Node.val <= 9|
// * The depth of the tree will not exceed |10|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [1,2,3]
// Output: 25
//
// The root-to-leaf path |1->2| represents the number |12|.
// The root-to-leaf path |1->3| represents the number |13|.
// Therefore, sum = 12 + 13 = |25|.

LEETCODE_SOLUTION_UNITTEST(129, SumRootToLeafNumbers, example_1) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({1, 2, 3});
  int       expect   = 25;
  int       actual   = solution->sumNumbers(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #2]
//  Input: root = [4,9,0,5,1]
// Output: 1026
//
// The root-to-leaf path |4->9->5| represents the number 495.
// The root-to-leaf path |4->9->1| represents the number 491.
// The root-to-leaf path |4->0| represents the number 40.
// Therefore, sum = 495 + 491 + 40 = |1026|.

LEETCODE_SOLUTION_UNITTEST(129, SumRootToLeafNumbers, example_2) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({4, 9, 0, 5, 1});
  int       expect   = 1026;
  int       actual   = solution->sumNumbers(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

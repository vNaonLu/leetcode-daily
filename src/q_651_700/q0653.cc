// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Two Sum IV - Input is a BST
//
// https://leetcode.com/problems/two-sum-iv-input-is-a-bst/
//
// Question ID: 653
// Difficult  : Easy
// Solve Date : 2021/09/18 08:00

#include "leetcode/tree_node.h"
#include <iosfwd>
#include <set>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |653. Two Sum IV - Input is a BST|:
//
// Given the |root| of a binary search tree and an integer |k|, return |true| if
// there exist two elements in the BST such that their sum is equal to |k|, or
// |false| otherwise.  
//

LEETCODE_BEGIN_RESOLVING(653, TwoSumIVInputIsABST, Solution);

class Solution {
private:
  set<int> nums;

public:
  bool findTarget(TreeNode *root, int k) {
    if (root == nullptr) {
      return false;
    } else {
      if (nums.count(k - root->val)) {
        return true;
      } else {
        nums.insert(root->val);
        return findTarget(root->left, k) || findTarget(root->right, k);
      }
    }
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is in the range |[1, 10⁴]|.
// * |-10⁴ <= Node.val <= 10⁴|
// * |root| is guaranteed to be a valid binary search tree.
// * |-10⁵ <= k <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [5,3,6,2,4,null,7], k = 9
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(653, TwoSumIVInputIsABST, example_1) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({5, 3, 6, 2, 4, null, 7});
  int       k        = 9;
  bool      expect   = true;
  bool      actual   = solution->findTarget(root, k);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #2]
//  Input: root = [5,3,6,2,4,null,7], k = 28
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(653, TwoSumIVInputIsABST, example_2) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({5, 3, 6, 2, 4, null, 7});
  int       k        = 28;
  bool      expect   = false;
  bool      actual   = solution->findTarget(root, k);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

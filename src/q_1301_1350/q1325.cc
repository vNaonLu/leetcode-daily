// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Delete Leaves With a Given Value
//
// https://leetcode.com/problems/delete-leaves-with-a-given-value/
//
// Question ID: 1325
// Difficult  : Medium
// Solve Date : 2024/05/17 11:44

#include "leetcode/tree_node.h"
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1325. Delete Leaves With a Given Value|:
//
// Given a binary tree |root| and an integer |target|, delete all the leaf nodes
// with value |target|. Note that once you delete a leaf node with value
// |target|, if its parent node becomes a leaf node and has the value |target|,
// it should also be deleted (you need to continue doing that until you cannot).
//
//

LEETCODE_BEGIN_RESOLVING(1325, DeleteLeavesWithAGivenValue, Solution);

class Solution {
public:
  TreeNode *removeLeafNodes(TreeNode *root, int target) {
    if (!root) {
      return root;
    }

    root->left  = removeLeafNodes(root->left, target);
    root->right = removeLeafNodes(root->right, target);

    if (!root->left && !root->right && root->val == target) {
      // LeetCode will use root instead of return value,
      // hence there wil be a SEGV if the root is deleted.
      // delete root;
      root = nullptr;
    }
    return root;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is in the range |[1, 3000]|.
// * |1 <= Node.val, target <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [1,2,3,2,null,2,4], target = 2
// Output: [1,null,3,null,4]
//

LEETCODE_SOLUTION_UNITTEST(1325, DeleteLeavesWithAGivenValue, example_1) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({1, 2, 3, 2, null, 2, 4});
  int       target   = 2;
  TreeNode *expect   = TreeNode::FromVector({1, null, 3, null, 4});
  TreeNode *actual   = solution->removeLeafNodes(root, target);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::ReleaseAll();
}

// [Example #2]
//  Input: root = [1,3,3,3,2], target = 3
// Output: [1,3,null,null,2]
//

LEETCODE_SOLUTION_UNITTEST(1325, DeleteLeavesWithAGivenValue, example_2) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({1, 3, 3, 3, 2});
  int       target   = 3;
  TreeNode *expect   = TreeNode::FromVector({1, 3, null, null, 2});
  TreeNode *actual   = solution->removeLeafNodes(root, target);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::ReleaseAll();
}

// [Example #3]
//  Input: root = [1,2,null,2,null,2], target = 2
// Output: [1]
//

LEETCODE_SOLUTION_UNITTEST(1325, DeleteLeavesWithAGivenValue, example_3) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({1, 2, null, 2, null, 2});
  int       target   = 2;
  TreeNode *expect   = TreeNode::FromVector({1});
  TreeNode *actual   = solution->removeLeafNodes(root, target);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::ReleaseAll();
}

// [Extra Testcase #1]
//  Input: [1,1,1]
// 1
// Output: []
//

LEETCODE_SOLUTION_UNITTEST(1325, DeleteLeavesWithAGivenValue,
                           extra_testcase_1) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({1, 1, 1});
  int       target   = 1;
  TreeNode *expect   = TreeNode::FromVector({});
  TreeNode *actual   = solution->removeLeafNodes(root, target);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::ReleaseAll();
}

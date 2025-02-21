// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Find Elements in a Contaminated Binary Tree
//
// https://leetcode.com/problems/find-elements-in-a-contaminated-binary-tree/
//
// Question ID: 1261
// Difficult  : Medium
// Solve Date : 2025/02/21 18:54

#include "leetcode/tree_node.h"
#include <iosfwd>
#include <set>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1261. Find Elements in a Contaminated Binary Tree|:
//
// Given a binary tree with the following rules:
//
//  1. |root.val == 0|
//
//  2. For any |treeNode|:
//
//
//    1. If |treeNode.val| has a value |x| and |treeNode.left != null|, then
//    |treeNode.left.val == 2 * x + 1|
//
//    2. If |treeNode.val| has a value |x| and |treeNode.right != null|, then
//    |treeNode.right.val == 2 * x + 2|
//
//
// Now the binary tree is contaminated, which means all |treeNode.val| have been
// changed to |-1|. Implement the |FindElements| class:
//
//  • |FindElements(TreeNode* root)| Initializes the object with a contaminated
//  binary tree and recovers it.
//
//  • |bool find(int target)| Returns |true| if the |target| value exists in the
//  recovered binary tree.
//
//

LEETCODE_BEGIN_RESOLVING(1261, FindElementsInAContaminatedBinaryTree,
                         FindElements);

class FindElements {
public:
  FindElements(TreeNode *root) { traverse(root); }

  bool find(int target) { return has_.find(target) != has_.end(); }

private:
  void traverse(auto *node, int val = 0) {
    if (!node) {
      return;
    }

    has_.insert(val);
    traverse(node->left, 2 * val + 1);
    traverse(node->right, 2 * val + 2);
  }

  set<int> has_;
};

LEETCODE_END_RESOLVING(FindElements);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |TreeNode.val == -1|
// * The height of the binary tree is less than or equal to |20|
// * The total number of nodes is between |[1, 10⁴]|
// * Total calls of |find()| is between |[1, 10⁴]|
// * |0 <= target <= 10⁶|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: ["FindElements","find","find"]
// [[[-1,null,-1]],[1],[2]]
// Output: [null,false,true]
//

LEETCODE_SOLUTION_UNITTEST(1261, FindElementsInAContaminatedBinaryTree,
                           example_1) {
  TreeNode *s0_root       = TreeNode::FromVector({-1, null, -1});
  auto      find_elements = MakeFindElements(s0_root);
  int       s1_target     = 1;
  bool      s1_expect     = false;
  bool      s1_actual     = find_elements->find(s1_target);
  LCD_EXPECT_EQ(s1_expect, s1_actual);
  int  s2_target = 2;
  bool s2_expect = true;
  bool s2_actual = find_elements->find(s2_target);
  LCD_EXPECT_EQ(s2_expect, s2_actual);
  TreeNode::Release(s0_root);
}

// [Example #2]
//  Input: ["FindElements","find","find","find"]
// [[[-1,-1,-1,-1,-1]],[1],[3],[5]]
// Output: [null,true,true,false]
//

LEETCODE_SOLUTION_UNITTEST(1261, FindElementsInAContaminatedBinaryTree,
                           example_2) {
  TreeNode *s0_root       = TreeNode::FromVector({-1, -1, -1, -1, -1});
  auto      find_elements = MakeFindElements(s0_root);
  int       s1_target     = 1;
  bool      s1_expect     = true;
  bool      s1_actual     = find_elements->find(s1_target);
  LCD_EXPECT_EQ(s1_expect, s1_actual);
  int  s2_target = 3;
  bool s2_expect = true;
  bool s2_actual = find_elements->find(s2_target);
  LCD_EXPECT_EQ(s2_expect, s2_actual);
  int  s3_target = 5;
  bool s3_expect = false;
  bool s3_actual = find_elements->find(s3_target);
  LCD_EXPECT_EQ(s3_expect, s3_actual);
  TreeNode::Release(s0_root);
}

// [Example #3]
//  Input: ["FindElements","find","find","find","find"]
// [[[-1,null,-1,-1,null,-1]],[2],[3],[4],[5]]
// Output: [null,true,false,false,true]
//

LEETCODE_SOLUTION_UNITTEST(1261, FindElementsInAContaminatedBinaryTree,
                           example_3) {
  TreeNode *s0_root       = TreeNode::FromVector({-1, null, -1, -1, null, -1});
  auto      find_elements = MakeFindElements(s0_root);
  int       s1_target     = 2;
  bool      s1_expect     = true;
  bool      s1_actual     = find_elements->find(s1_target);
  LCD_EXPECT_EQ(s1_expect, s1_actual);
  int  s2_target = 3;
  bool s2_expect = false;
  bool s2_actual = find_elements->find(s2_target);
  LCD_EXPECT_EQ(s2_expect, s2_actual);
  int  s3_target = 4;
  bool s3_expect = false;
  bool s3_actual = find_elements->find(s3_target);
  LCD_EXPECT_EQ(s3_expect, s3_actual);
  int  s4_target = 5;
  bool s4_expect = true;
  bool s4_actual = find_elements->find(s4_target);
  LCD_EXPECT_EQ(s4_expect, s4_actual);
  TreeNode::Release(s0_root);
}

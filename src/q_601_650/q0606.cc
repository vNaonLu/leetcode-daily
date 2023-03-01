// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Construct String from Binary Tree
//
// https://leetcode.com/problems/construct-string-from-binary-tree/
//
// Question ID: 606
// Difficult  : Easy
// Solve Date : 2022/09/07 17:52

#include "leetcode/tree_node.h"
#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |606. Construct String from Binary Tree|:
//
// Given the |root| of a binary tree, construct a string consisting of
// parenthesis and integers from a binary tree with the preorder traversal way,
// and return it. Omit all the empty parenthesis pairs that do not affect the
// one-to-one mapping relationship between the string and the original binary
// tree.
//

LEETCODE_BEGIN_RESOLVING(606, ConstructStringFromBinaryTree, Solution);

class Solution {
public:
  string tree2str(TreeNode *root) {
    if (nullptr == root) {
      return "";
    }
    auto res   = to_string(root->val);
    auto left  = tree2str(root->left);
    auto right = tree2str(root->right);
    if (!right.empty()) {
      res += string("(") + left + string(")");
      res += string("(") + right + string(")");
    } else if (!left.empty()) {
      res += string("(") + left + string(")");
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is in the range |[1, 10⁴]|.
// * |-1000 <= Node.val <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [1,2,3,4]
// Output: "1(2(4))(3)"
//
// Originally, it needs to be "1(2(4)())(3()())", but you need to omit all the
// unnecessary empty parenthesis pairs. And it will be "1(2(4))(3)"

LEETCODE_SOLUTION_UNITTEST(606, ConstructStringFromBinaryTree, example_1) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({1, 2, 3, 4});
  string    expect   = "1(2(4))(3)";
  string    actual   = solution->tree2str(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #2]
//  Input: root = [1,2,3,null,4]
// Output: "1(2()(4))(3)"
//
// Almost the same as the first example, except we cannot omit the first
// parenthesis pair to break the one-to-one mapping relationship between the
// input and the output.

LEETCODE_SOLUTION_UNITTEST(606, ConstructStringFromBinaryTree, example_2) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({1, 2, 3, null, 4});
  string    expect   = "1(2()(4))(3)";
  string    actual   = solution->tree2str(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

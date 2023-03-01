// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Leaf-Similar Trees
//
// https://leetcode.com/problems/leaf-similar-trees/
//
// Question ID: 872
// Difficult  : Easy
// Solve Date : 2022/10/20 07:19

#include "leetcode/tree_node.h"
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |872. Leaf-Similar Trees|:
//
// Consider all the leaves of a binary tree, fromleft to right order, the values
// of thoseleaves form a leaf value sequence.
// ![img](https://s3-lc-upload.s3.amazonaws.com/uploads/2018/07/16/tree.png)
// For example, in the given tree above, the leaf value sequence is |(6, 7, 4,
// 9, 8)|. Two binary trees are considered leaf-similarif their leaf value
// sequence is the same. Return |true| if and only if the two given trees with
// head nodes |root1| and |root2| are leaf-similar.
//

LEETCODE_BEGIN_RESOLVING(872, LeafSimilarTrees, Solution);

class Solution {
private:
  void helper(TreeNode *p, vector<int> &res) {
    if (nullptr != p) {
      if (nullptr == p->left && nullptr == p->right) {
        res.emplace_back(p->val);
      } else {
        helper(p->left, res);
        helper(p->right, res);
      }
    }
  }

  vector<int> extractLeaf(TreeNode *p) {
    auto res = vector<int>();
    helper(p, res);
    return res;
  }

public:
  bool leafSimilar(TreeNode *root1, TreeNode *root2) {
    auto leaf1 = extractLeaf(root1);
    auto leaf2 = extractLeaf(root2);
    return leaf1 == leaf2;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in each tree will be in the range |[1, 200]|.
// * Both of the given trees will have values in the range |[0, 200]|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root1 = [3,5,1,6,2,9,8,null,null,7,4], root2 =
//  [3,5,1,6,7,4,2,null,null,null,null,null,null,9,8]
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(872, LeafSimilarTrees, example_1) {
  auto      solution = MakeSolution();
  TreeNode *root1 =
      TreeNode::FromVector({3, 5, 1, 6, 2, 9, 8, null, null, 7, 4});
  TreeNode *root2 = TreeNode::FromVector(
      {3, 5, 1, 6, 7, 4, 2, null, null, null, null, null, null, 9, 8});
  bool expect = true;
  bool actual = solution->leafSimilar(root1, root2);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root1, root2);
}

// [Example #2]
//  Input: root1 = [1,2,3], root2 = [1,3,2]
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(872, LeafSimilarTrees, example_2) {
  auto      solution = MakeSolution();
  TreeNode *root1    = TreeNode::FromVector({1, 2, 3});
  TreeNode *root2    = TreeNode::FromVector({1, 3, 2});
  bool      expect   = false;
  bool      actual   = solution->leafSimilar(root1, root2);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root1, root2);
}

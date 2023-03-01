// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Find a Corresponding Node of a Binary Tree in a Clone of That Tree
//
// https://leetcode.com/problems/find-a-corresponding-node-of-a-binary-tree-in-a-clone-of-that-tree/
//
// Question ID: 1379
// Difficult  : Easy
// Solve Date : 2022/05/17 18:15

#include "leetcode/tree_node.h"
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1379. Find a Corresponding Node of a Binary Tree in a Clone
// of That Tree|:
//
// Given two binary trees |original| and |cloned| and given a reference to a
// node |target| in the original tree. The |cloned| tree is a copy of the
// |original| tree. Return a reference to the same node in the |cloned| tree.
// Note that you are not allowed to change any of the two trees or the |target|
// node and the answer must be a reference to a node in the |cloned| tree.
//

LEETCODE_BEGIN_RESOLVING(1379,
                         FindACorrespondingNodeOfABinaryTreeInACloneOfThatTree,
                         Solution);

class Solution {
public:
  TreeNode *getTargetCopy(TreeNode *original, TreeNode *cloned,
                          TreeNode *target) {
    if (original == nullptr) {
      return nullptr;
    }

    if (original == target) {
      return cloned;
    }

    if (auto l = getTargetCopy(original->left, cloned->left, target);
        nullptr != l) {
      return l;
    } else if (auto r = getTargetCopy(original->right, cloned->right, target);
               nullptr != r) {
      return r;
    }

    return nullptr;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the |tree| is in the range |[1, 10⁴]|.
// * The values of the nodes of the |tree| are unique.
// * |target| node is a node from the |original| tree and is not |null|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: tree = [7,4,3,null,null,6,19], target = 3
// Output: 3
//
// In all examples the original and cloned trees are shown. The target node is a
// green node from the original tree. The answer is the yellow node from the
// cloned tree.

LEETCODE_SOLUTION_UNITTEST(
    1379, FindACorrespondingNodeOfABinaryTreeInACloneOfThatTree, example_1) {
  auto solution = MakeSolution();
  TreeNode* original = TreeNode::FromVector({7, 4, 3, null, null, 6, 19});
  TreeNode* cloned = TreeNode::FromVector({7, 4, 3, null, null, 6, 19});
  TreeNode* target = original->left;
  TreeNode* exp = cloned->left;
  TreeNode* act = solution->getTargetCopy(original, cloned, target);
  EXPECT_EQ(act, exp);
  TreeNode::Release(original, cloned, target, exp, act);
}

// [Example #2]
//  Input: tree = [7], target = 7
// Output: 7
//

LEETCODE_SOLUTION_UNITTEST(
    1379, FindACorrespondingNodeOfABinaryTreeInACloneOfThatTree, example_2) {
  auto solution = MakeSolution();
  TreeNode* original = TreeNode::FromVector({7});
  TreeNode* cloned = TreeNode::FromVector({7});
  TreeNode* target = original;
  TreeNode* exp = cloned;
  TreeNode* act = solution->getTargetCopy(original, cloned, target);
  EXPECT_EQ(act, exp);
  TreeNode::Release(original, cloned, target, exp, act);
}

// [Example #3]
//  Input: tree = [8,null,6,null,5,null,4,null,3,null,2,null,1], target = 4
// Output: 4
//

LEETCODE_SOLUTION_UNITTEST(
    1379, FindACorrespondingNodeOfABinaryTreeInACloneOfThatTree, example_3) {
  auto solution = MakeSolution();
  TreeNode* original = TreeNode::FromVector({8, null, 6, null, 5, null, 4, null, 3, null, 2, null, 1});
  TreeNode* cloned = TreeNode::FromVector({8, null, 6, null, 5, null, 4, null, 3, null, 2, null, 1});
  TreeNode* target = original->right->right->right;
  TreeNode* exp = cloned->right->right->right;
  TreeNode* act = solution->getTargetCopy(original, cloned, target);
  EXPECT_EQ(act, exp);
  TreeNode::Release(original, cloned, target, exp, act);
}

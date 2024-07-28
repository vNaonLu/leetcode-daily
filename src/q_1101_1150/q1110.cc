// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Delete Nodes And Return Forest
//
// https://leetcode.com/problems/delete-nodes-and-return-forest/
//
// Question ID: 1110
// Difficult  : Medium
// Solve Date : 2024/07/17 19:16

#include "leetcode/tree_node.h"
#include <iosfwd>
#include <set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1110. Delete Nodes And Return Forest|:
//
// Given the |root| of a binary tree, each node in the tree has a distinct
// value. After deleting all nodes with a value in |to_delete|, we are left with
// a forest (a disjoint union of trees). Return the roots of the trees in the
// remaining forest. You may return the result in any order.
//
//

LEETCODE_BEGIN_RESOLVING(1110, DeleteNodesAndReturnForest, Solution);

class Solution {
public:
  vector<TreeNode *> delNodes(TreeNode *root, vector<int> &to_delete) {
    set<int>           rm(to_delete.begin(), to_delete.end());
    vector<TreeNode *> ret;
    dfs(&root, rm, true, &ret);
    return ret;
  }

private:
  void dfs(TreeNode **p, set<int> const &rm, bool f, vector<TreeNode *> *ret) {
    if (!*p) {
      return;
    }

    dfs(&(*p)->left, rm, !!rm.count((*p)->val), ret);
    dfs(&(*p)->right, rm, !!rm.count((*p)->val), ret);

    if (!rm.count((*p)->val) && f) {
      ret->emplace_back(*p);
    }
    if (!!rm.count((*p)->val)) {
      delete *p;
      *p = nullptr;
    }
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * The number of nodes in the given tree is at most |1000|.
// * Each node has a distinct value between |1| and |1000|.
// * |to_delete.length <= 1000|
// * |to_delete| contains distinct values between |1| and |1000|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [1,2,3,4,5,6,7], to_delete = [3,5]
// Output: [[1,2,null,4],[6],[7]]
//

LEETCODE_SOLUTION_UNITTEST(1110, DeleteNodesAndReturnForest, example_1) {
  auto               solution  = MakeSolution();
  TreeNode          *root      = TreeNode::FromVector({1, 2, 3, 4, 5, 6, 7});
  vector<int>        to_delete = {3, 5};
  vector<TreeNode *> expect    = {TreeNode::FromVector({1, 2, null, 4}),
                                  TreeNode::FromVector({6}),
                                  TreeNode::FromVector({7})};
  vector<TreeNode *> actual    = solution->delNodes(root, to_delete);
  EXPECT_ANYORDER_EQ(expect, actual);
  TreeNode::ReleaseAll();
}

// [Example #2]
//  Input: root = [1,2,4,null,3], to_delete = [3]
// Output: [[1,2,4]]
//

LEETCODE_SOLUTION_UNITTEST(1110, DeleteNodesAndReturnForest, example_2) {
  auto               solution  = MakeSolution();
  TreeNode          *root      = TreeNode::FromVector({1, 2, 4, null, 3});
  vector<int>        to_delete = {3};
  vector<TreeNode *> expect    = {TreeNode::FromVector({1, 2, 4})};
  vector<TreeNode *> actual    = solution->delNodes(root, to_delete);
  EXPECT_ANYORDER_EQ(expect, actual);
  TreeNode::ReleaseAll();
}

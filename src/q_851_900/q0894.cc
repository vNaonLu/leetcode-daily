// Copyright 2023 Naon Lu
//
// This file describes the solution of
// All Possible Full Binary Trees
//
// https://leetcode.com/problems/all-possible-full-binary-trees/
//
// Question ID: 894
// Difficult  : Medium
// Solve Date : 2023/07/23 10:49

#include "leetcode/tree_node.h"
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |894. All Possible Full Binary Trees|:
//
// Given an integer |n|, return a list of all possible full binary trees with
// |n| nodes. Each node of each tree in the answer must have |Node.val == 0|.
// Each element of the answer is the root node of one possible tree. You may
// return the final list of trees in any order. A full binary tree is a binary
// tree where each node has exactly |0| or |2| children.
//
//

LEETCODE_BEGIN_RESOLVING(894, AllPossibleFullBinaryTrees, Solution);

class Solution {
public:
  vector<TreeNode *> allPossibleFBT(int n) {
    vector<vector<TreeNode *>> dp(n + 1, vector<TreeNode *>{});
    return FBT(&dp, n);
  }

private:
  vector<TreeNode *> FBT(vector<vector<TreeNode *>> *dp, int n) {
    if ((n % 2) == 0) {
      return {};
    }

    if (n == 1) {
      return (*dp)[1] = {new TreeNode(0)};
    }

    if ((*dp)[n].size() > 0) {
      return (*dp)[n];
    }

    vector<TreeNode *> res;
    for (int i = 1; i < n; ++i) {
      vector<TreeNode *> left  = FBT(dp, i);
      vector<TreeNode *> right = FBT(dp, n - 1 - i);
      for (auto *lp : left) {
        for (auto *rp : right) {
          TreeNode *root = new TreeNode(0);
          root->left     = lp;
          root->right    = rp;
          res.emplace_back(root);
        }
      }
    }
    return (*dp)[n] = std::move(res);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= n <= 20|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: n = 7
// Output:
// [[0,0,0,null,null,0,0,null,null,0,0],[0,0,0,null,null,0,0,0,0],[0,0,0,0,0,0,0],[0,0,0,0,0,null,null,null,null,0,0],[0,0,0,0,0,null,null,0,0]]
//

LEETCODE_SOLUTION_UNITTEST(894, AllPossibleFullBinaryTrees, example_1) {
  auto               solution = MakeSolution();
  int                n        = 7;
  vector<TreeNode *> expect   = {
      TreeNode::FromVector({0, 0, 0, null, null, 0, 0, null, null, 0, 0}),
      TreeNode::FromVector({0, 0, 0, null, null, 0, 0, 0, 0}),
      TreeNode::FromVector({0, 0, 0, 0, 0, 0, 0}),
      TreeNode::FromVector({0, 0, 0, 0, 0, null, null, null, null, 0, 0}),
      TreeNode::FromVector({0, 0, 0, 0, 0, null, null, 0, 0})};
  vector<TreeNode *> actual = solution->allPossibleFBT(n);
  EXPECT_ANYORDER_EQ(expect, actual);
  TreeNode::ReleaseAll();
}

// [Example #2]
//  Input: n = 3
// Output: [[0,0,0]]
//

LEETCODE_SOLUTION_UNITTEST(894, AllPossibleFullBinaryTrees, example_2) {
  auto               solution = MakeSolution();
  int                n        = 3;
  vector<TreeNode *> expect   = {TreeNode::FromVector({0, 0, 0})};
  vector<TreeNode *> actual   = solution->allPossibleFBT(n);
  EXPECT_ANYORDER_EQ(expect, actual);
  TreeNode::ReleaseAll();
}

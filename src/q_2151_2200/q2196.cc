// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Create Binary Tree From Descriptions
//
// https://leetcode.com/problems/create-binary-tree-from-descriptions/
//
// Question ID: 2196
// Difficult  : Medium
// Solve Date : 2024/07/15 19:21

#include "leetcode/tree_node.h"
#include <iosfwd>
#include <map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2196. Create Binary Tree From Descriptions|:
//
// You are given a 2D integer array |descriptions| where |descriptions[i] =
// [parentᵢ, childᵢ, isLeftᵢ]| indicates that |parentᵢ| is the parent of
// |childᵢ| in a binary tree of unique values. Furthermore,
//
//  • If |isLeftᵢ == 1|, then |childᵢ| is the left child of |parentᵢ|.
//
//  • If |isLeftᵢ == 0|, then |childᵢ| is the right child of |parentᵢ|.
// Construct the binary tree described by |descriptions| and return its root.
// The test cases will be generated such that the binary tree is valid.
//
//

LEETCODE_BEGIN_RESOLVING(2196, CreateBinaryTreeFromDescriptions, Solution);

class Solution {
public:
  TreeNode *createBinaryTree(vector<vector<int>> &descriptions) {
    map<int, TreeNode *> memo;
    map<TreeNode *, int> degree;
    for (auto &v : descriptions) {
      auto **p      = &memo[v[0]];
      auto **child  = &memo[v[1]];
      int    isleft = v[2];

      if (!*p) {
        *p = new TreeNode(v[0]);
      }
      if (!*child) {
        *child = new TreeNode(v[1]);
      }

      ++degree[*child];
      degree[*p]; // create if not exist

      if (isleft) {
        (*p)->left = *child;
      } else {
        (*p)->right = *child;
      }
    }

    for (auto [p, deg] : degree) {
      if (deg == 0) {
        return p;
      }
    }

    return nullptr;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= descriptions.length <= 10⁴|
// * |descriptions[i].length == 3|
// * |1 <= parentᵢ, childᵢ <= 10⁵|
// * |0 <= isLeftᵢ <= 1|
// * The binary tree described by |descriptions| is valid.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: descriptions = [[20,15,1],[20,17,0],[50,20,1],[50,80,0],[80,19,1]]
// Output: [50,20,80,15,17,19]
//

LEETCODE_SOLUTION_UNITTEST(2196, CreateBinaryTreeFromDescriptions, example_1) {
  auto                solution     = MakeSolution();
  vector<vector<int>> descriptions = {
      {20, 15, 1},
      {20, 17, 0},
      {50, 20, 1},
      {50, 80, 0},
      {80, 19, 1}
  };
  TreeNode *expect = TreeNode::FromVector({50, 20, 80, 15, 17, 19});
  TreeNode *actual = solution->createBinaryTree(descriptions);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(expect, actual);
}

// [Example #2]
//  Input: descriptions = [[1,2,1],[2,3,0],[3,4,1]]
// Output: [1,2,null,null,3,4]
//

LEETCODE_SOLUTION_UNITTEST(2196, CreateBinaryTreeFromDescriptions, example_2) {
  auto                solution     = MakeSolution();
  vector<vector<int>> descriptions = {
      {1, 2, 1},
      {2, 3, 0},
      {3, 4, 1}
  };
  TreeNode *expect = TreeNode::FromVector({1, 2, null, null, 3, 4});
  TreeNode *actual = solution->createBinaryTree(descriptions);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(expect, actual);
}

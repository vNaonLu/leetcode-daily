// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Vertical Order Traversal of a Binary Tree
//
// https://leetcode.com/problems/vertical-order-traversal-of-a-binary-tree/
//
// Question ID: 987
// Difficult  : Hard
// Solve Date : 2022/09/04 15:59

#include "leetcode/tree_node.h"
#include <algorithm>
#include <iosfwd>
#include <map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |987. Vertical Order Traversal of a Binary Tree|:
//
// Given the |root| of a binary tree, calculate the vertical order traversal of
// the binary tree. For each node at position |(row, col)|, its left and right
// children will be at positions |(row + 1, col - 1)| and |(row + 1, col + 1)|
// respectively. The root of the tree is at |(0, 0)|. The vertical order
// traversal of a binary tree is a list of top-to-bottom orderings for each
// column index starting from the leftmost column and ending on the rightmost
// column. There may be multiple nodes in the same row and same column. In such
// a case, sort these nodes by their values. Return the vertical order traversal
// of the binary tree.
//

LEETCODE_BEGIN_RESOLVING(987, VerticalOrderTraversalOfABinaryTree, Solution);

class Solution {
private:
  void travel(TreeNode *p, int row, int col,
              map<int, vector<pair<int, pair<int, int>>>> &res) {
    if (nullptr == p) {
      return;
    }
    res[col].emplace_back(p->val, make_pair(row, col));
    travel(p->left, row + 1, col - 1, res);
    travel(p->right, row + 1, col + 1, res);
  }

public:
  vector<vector<int>> verticalTraversal(TreeNode *root) {
    auto mp  = map<int, vector<pair<int, pair<int, int>>>>();
    auto res = vector<vector<int>>();
    travel(root, 0, 0, mp);
    for (auto &[k, v] : mp) {
      sort(v.begin(), v.end(), [](auto &x, auto &y) {
        auto &rc_x = x.second;
        auto &rc_y = y.second;
        return rc_x.first == rc_y.first
                   ? (rc_x.second == rc_y.second ? x.first < y.first
                                                 : rc_x.second < rc_y.second)
                   : rc_x.first < rc_y.first;
      });
      res.emplace_back();
      auto &rv = res.back();
      for (auto x : v) {
        rv.emplace_back(x.first);
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is in the range |[1, 1000]|.
// * |0 <= Node.val <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [3,9,20,null,null,15,7]
// Output: [[9],[3,15],[20],[7]]
//
// Column -1: Only node 9 is in this column.
// Column 0: Nodes 3 and 15 are in this column in that order from top to bottom.
// Column 1: Only node 20 is in this column.
// Column 2: Only node 7 is in this column.

LEETCODE_SOLUTION_UNITTEST(987, VerticalOrderTraversalOfABinaryTree,
                           example_1) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({3, 9, 20, null, null, 15, 7});
  vector<vector<int>> expect = {
      {9},
      {3, 15},
      {20},
      {7}
  };
  vector<vector<int>> actual = solution->verticalTraversal(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #2]
//  Input: root = [1,2,3,4,5,6,7]
// Output: [[4],[2],[1,5,6],[3],[7]]
//
// Column -2: Only node 4 is in this column.
// Column -1: Only node 2 is in this column.
// Column 0: Nodes 1, 5, and 6 are in this column.
//  1 is at the top, so it comes first.
//  5 and 6 are at the same position (2, 0), so we order them by their value, 5
//  before 6.
// Column 1: Only node 3 is in this column.
// Column 2: Only node 7 is in this column.

LEETCODE_SOLUTION_UNITTEST(987, VerticalOrderTraversalOfABinaryTree,
                           example_2) {
  auto                solution = MakeSolution();
  TreeNode           *root     = TreeNode::FromVector({1, 2, 3, 4, 5, 6, 7});
  vector<vector<int>> expect   = {
      {4},
      {2},
      {1, 5, 6},
      {3},
      {7}
  };
  vector<vector<int>> actual = solution->verticalTraversal(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #3]
//  Input: root = [1,2,3,4,6,5,7]
// Output: [[4],[2],[1,5,6],[3],[7]]
//
// This case is the exact same as example 2, but with nodes 5 and 6 swapped.
// Note that the solution remains the same since 5 and 6 are in the same
// location and should be ordered by their values.

LEETCODE_SOLUTION_UNITTEST(987, VerticalOrderTraversalOfABinaryTree,
                           example_3) {
  auto                solution = MakeSolution();
  TreeNode           *root     = TreeNode::FromVector({1, 2, 3, 4, 6, 5, 7});
  vector<vector<int>> expect   = {
      {4},
      {2},
      {1, 5, 6},
      {3},
      {7}
  };
  vector<vector<int>> actual = solution->verticalTraversal(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Print Binary Tree
//
// https://leetcode.com/problems/print-binary-tree/
//
// Question ID: 655
// Difficult  : Medium
// Solve Date : 2022/10/10 13:39

#include "leetcode/tree_node.h"
#include <iosfwd>
#include <string>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |655. Print Binary Tree|:
//
// Given the |root| of a binary tree, construct a 0-indexed |m x n| string
// matrix |res| that represents a formatted layout of the tree. The formatted
// layout matrix should be constructed using the following rules:
//
//  • The height of the tree is |height|and the number of rows |m| should be
//  equal to |height + 1|.
//
//  • The number of columns |n| should be equal to |2ʰᵉⁱᵍʰᵗ⁺¹ - 1|.
//
//  • Place the root node in the middle of the top row (more formally, at
//  location |res[0][(n-1)/2]|).
//
//  • For each node that has been placed in the matrix at position |res[r][c]|,
//  place its left child at |res[r+1][c-2ʰᵉⁱᵍʰᵗ⁻ʳ⁻¹]| and its right child at
//  |res[r+1][c+2ʰᵉⁱᵍʰᵗ⁻ʳ⁻¹]|.
//
//  • Continue this process until all the nodes in the tree have been placed.
//
//  • Any empty cells should contain the empty string |""|.
// Return the constructed matrix |res|.
//

LEETCODE_BEGIN_RESOLVING(655, PrintBinaryTree, Solution);

class Solution {
private:
  int findDepth(TreeNode *p) {
    if (nullptr == p) {
      return 0;
    }
    return 1 + max(findDepth(p->left), findDepth(p->right));
  }

  void layout(vector<vector<string>> &res, TreeNode *p, int r, int c) {
    if (nullptr != p) {
      auto h    = (int)res.size();
      res[r][c] = to_string(p->val);
      if (r + 1 < h) {
        layout(res, p->left, r + 1, c - (1 << (h - r - 2)));
        layout(res, p->right, r + 1, c + (1 << (h - r - 2)));
      }
    }
  }

public:
  vector<vector<string>> printTree(TreeNode *root) {
    auto h   = findDepth(root);
    auto w   = (1 << h) - 1;
    auto res = vector<vector<string>>(h, vector<string>(w, ""));
    layout(res, root, 0, (w - 1) / 2);
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is in the range |[1, 2¹⁰]|.
// * |-99 <= Node.val <= 99|
// * The depth of the tree will be in the range |[1, 10]|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [1,2]
// Output: [["","1",""],
// ["2","",""]]
//

LEETCODE_SOLUTION_UNITTEST(655, PrintBinaryTree, example_1) {
  auto                   solution = MakeSolution();
  TreeNode              *root     = TreeNode::FromVector({1, 2});
  vector<vector<string>> expect   = {
      { "", "1", ""},
      {"2",  "", ""}
  };
  vector<vector<string>> actual = solution->printTree(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #2]
//  Input: root = [1,2,3,null,4]
// Output: [["","","","1","","",""],
// ["","2","","","","3",""],
// ["","","4","","","",""]]
//

LEETCODE_SOLUTION_UNITTEST(655, PrintBinaryTree, example_2) {
  auto                   solution = MakeSolution();
  TreeNode              *root     = TreeNode::FromVector({1, 2, 3, null, 4});
  vector<vector<string>> expect   = {
      {"",  "",  "", "1", "",  "", ""},
      {"", "2",  "",  "", "", "3", ""},
      {"",  "", "4",  "", "",  "", ""}
  };
  vector<vector<string>> actual = solution->printTree(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

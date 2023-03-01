// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Even Odd Tree
//
// https://leetcode.com/problems/even-odd-tree/
//
// Question ID: 1609
// Difficult  : Medium
// Solve Date : 2022/06/16 18:22

#include "leetcode/tree_node.h"
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1609. Even Odd Tree|:
//
// A binary tree is named Even-Odd if it meets the following conditions:
//
//  • The root of the binary tree is at level index |0|, its children are at
//  level index |1|, their children are at level index |2|, etc.
//
//  • For every even-indexed level, all nodes at the level have odd integer
//  values in strictly increasing order (from left to right).
//
//  • For every odd-indexed level, all nodes at the level have even integer
//  values in strictly decreasing order (from left to right).
// Given the |root| of a binary tree, return |true| if the binary tree is
// Even-Odd, otherwise return |false|.
//

LEETCODE_BEGIN_RESOLVING(1609, EvenOddTree, Solution);

class Solution {
private:
  void evaluate_tree(TreeNode *p, int level, vector<vector<int>> &memo) {
    if (p != nullptr) {
      if (level >= memo.size()) {
        memo.resize(level + 1);
      }

      memo[level].emplace_back(p->val);
      evaluate_tree(p->left, level + 1, memo);
      evaluate_tree(p->right, level + 1, memo);
    }
  }

  template <typename iterator>
  bool is_odd_increasing(iterator beg, iterator end) {
    if (beg != end) {
      auto next = beg + 1;
      if ((*beg & 1) == 0) {
        return false;
      }

      while (next != end) {
        if ((*next & 1) == 0 || *next <= *beg) {
          return false;
        }
        next = ++beg + 1;
      }
    }

    return true;
  }

  template <typename iterator>
  bool is_even_decreasing(iterator beg, iterator end) {
    if (beg != end) {
      auto next = beg + 1;
      if ((*beg & 1) == 1) {
        return false;
      }

      while (next != end) {
        if ((*next & 1) == 1 || *next >= *beg) {
          return false;
        }
        next = ++beg + 1;
      }
    }

    return true;
  }

public:
  bool isEvenOddTree(TreeNode *root) {
    vector<vector<int>> levels;
    evaluate_tree(root, 0, levels);

    for (int i = 0; i < levels.size(); ++i) {
      auto &v = levels[i];
      if ((i & 1) == 0) {
        if (!is_odd_increasing(v.begin(), v.end())) {

          return false;
        }
      } else {
        if (!is_even_decreasing(v.begin(), v.end())) {

          return false;
        }
      }
    }

    return true;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is in the range |[1, 10⁵]|.
// * |1 <= Node.val <= 10⁶|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [1,10,4,3,null,7,9,12,8,6,null,null,2]
// Output: true
//
// The node values on each level are:
// Level 0: [1]
// Level 1: [10,4]
// Level 2: [3,7,9]
// Level 3: [12,8,6,2]
// Since levels 0 and 2 are all odd and increasing and levels 1 and 3 are all
// even and decreasing, the tree is Even-Odd.

LEETCODE_SOLUTION_UNITTEST(1609, EvenOddTree, example_1) {
  auto      solution = MakeSolution();
  TreeNode *root =
      TreeNode::FromVector({1, 10, 4, 3, null, 7, 9, 12, 8, 6, null, null, 2});
  bool expect = true;
  bool actual = solution->isEvenOddTree(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #2]
//  Input: root = [5,4,2,3,3,7]
// Output: false
//
// The node values on each level are:
// Level 0: [5]
// Level 1: [4,2]
// Level 2: [3,3,7]
// Node values in level 2 must be in strictly increasing order, so the tree is
// not Even-Odd.

LEETCODE_SOLUTION_UNITTEST(1609, EvenOddTree, example_2) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({5, 4, 2, 3, 3, 7});
  bool      expect   = false;
  bool      actual   = solution->isEvenOddTree(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #3]
//  Input: root = [5,9,1,3,5,7]
// Output: false
//
// Node values in the level 1 should be even integers.

LEETCODE_SOLUTION_UNITTEST(1609, EvenOddTree, example_3) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({5, 9, 1, 3, 5, 7});
  bool      expect   = false;
  bool      actual   = solution->isEvenOddTree(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Binary Tree Coloring Game
//
// https://leetcode.com/problems/binary-tree-coloring-game/
//
// Question ID: 1145
// Difficult  : Medium
// Solve Date : 2022/02/18 18:39

#include "leetcode/tree_node.h"
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1145. Binary Tree Coloring Game|:
//
// Two players play a turn based game on a binary tree. We are given the |root|
// of this binary tree, and the number of nodes |n| in the tree. |n| is odd, and
// each node has a distinct value from |1| to |n|. Initially, the first player
// names a value |x| with |1 <= x <= n|, and the second player names a value |y|
// with |1 <= y <= n| and |y != x|. The first player colors the node with value
// |x| red, and the second player colors the node with value |y| blue. Then, the
// players take turns starting with the first player. In each turn, that player
// chooses a node of their color (red if player 1, blue if player 2) and colors
// an uncolored neighbor of the chosen node (either the left child, right child,
// or parent of the chosen node.) If (and only if) a player cannot choose such a
// node in this way, they must pass their turn. If both players pass their turn,
// the game ends, and the winner is the player that colored more nodes. You are
// the second player. If it is possible to choose such a |y| to ensure you win
// the game, return |true|. If it is not possible, return |false|.  
//

LEETCODE_BEGIN_RESOLVING(1145, BinaryTreeColoringGame, Solution);

class Solution {
private:
  inline int count(TreeNode *p, int x, int &max_nodes) noexcept {
    if (nullptr == p)
      return 0;
    int total =
        count(p->left, x, max_nodes) + count(p->right, x, max_nodes) + 1;
    if (p->val == x)
      return 0;
    max_nodes = max(max_nodes, total);
    return total;
  }

public:
  bool btreeGameWinningMove(TreeNode *root, int n, int x) {
    int max_nodes = 0;
    count(root, x, max_nodes);
    return max_nodes > n - max_nodes;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is |n|.
// * |1 <= x <= n <= 100|
// * |n| is odd.
// * 1 <= Node.val <= n
// * All the values of the tree are unique.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [1,2,3,4,5,6,7,8,9,10,11], n = 11, x = 3
// Output: true
//
// The second player can choose the node with value 2.

LEETCODE_SOLUTION_UNITTEST(1145, BinaryTreeColoringGame, example_1) {
  auto      solution = MakeSolution();
  TreeNode *root   = TreeNode::FromVector({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11});
  int       n      = 11;
  int       x      = 3;
  bool      expect = true;
  bool      actual = solution->btreeGameWinningMove(root, n, x);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #2]
//  Input: root = [1,2,3], n = 3, x = 1
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(1145, BinaryTreeColoringGame, example_2) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({1, 2, 3});
  int       n        = 3;
  int       x        = 1;
  bool      expect   = false;
  bool      actual   = solution->btreeGameWinningMove(root, n, x);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

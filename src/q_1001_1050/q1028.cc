// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Recover a Tree From Preorder Traversal
//
// https://leetcode.com/problems/recover-a-tree-from-preorder-traversal/
//
// Question ID: 1028
// Difficult  : Hard
// Solve Date : 2025/02/22 14:06

#include "leetcode/tree_node.h"
#include <iosfwd>
#include <string>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1028. Recover a Tree From Preorder Traversal|:
//
// We run a preorder depth-first search (DFS) on the |root| of a binary tree.
// At each node in this traversal, we output |D| dashes (where |D| is the depth
// of this node), then we output the value of this node.  If the depth of a node
// is |D|, the depth of its immediate child is |D + 1|.  The depth of the |root|
// node is |0|. If a node has only one child, that child is guaranteed to be the
// left child. Given the output |traversal| of this traversal, recover the tree
// and return its |root|.
//
//

LEETCODE_BEGIN_RESOLVING(1028, RecoverATreeFromPreorderTraversal, Solution);

class Solution {
public:
  int       i = 0;
  TreeNode *recoverFromPreorder(string &T, int depth = 0) {
    if (i >= T.size())
      return NULL; // base case
    int D = 0;

    while (T[i] == '-')
      D++, i++; // D dashes

    // If the current depth is less than expected, reset i
    if (D < depth) {
      i -= D; // Reset i
      return NULL;
    }

    // Read the node value
    int x = 0;
    while (isdigit(T[i])) {
      x = x * 10 + T[i] - '0';
      i++;
    }

    // Create node
    TreeNode *node = new TreeNode(x);

    // recover left and right children
    node->left  = recoverFromPreorder(T, depth + 1);
    node->right = recoverFromPreorder(T, depth + 1);

    return node;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * The number of nodes in the original tree is in the range |[1, 1000]|.
// * |1 <= Node.val <= 10⁹|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: traversal = "1-2--3--4-5--6--7"
// Output: [1,2,5,3,4,6,7]
//

LEETCODE_SOLUTION_UNITTEST(1028, RecoverATreeFromPreorderTraversal, example_1) {
  auto      solution  = MakeSolution();
  string    traversal = "1-2--3--4-5--6--7";
  TreeNode *expect    = TreeNode::FromVector({1, 2, 5, 3, 4, 6, 7});
  TreeNode *actual    = solution->recoverFromPreorder(traversal);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(expect, actual);
}

// [Example #2]
//  Input: traversal = "1-2--3---4-5--6---7"
// Output: [1,2,5,3,null,6,null,4,null,7]
//

LEETCODE_SOLUTION_UNITTEST(1028, RecoverATreeFromPreorderTraversal, example_2) {
  auto      solution  = MakeSolution();
  string    traversal = "1-2--3---4-5--6---7";
  TreeNode *expect =
      TreeNode::FromVector({1, 2, 5, 3, null, 6, null, 4, null, 7});
  TreeNode *actual = solution->recoverFromPreorder(traversal);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(expect, actual);
}

// [Example #3]
//  Input: traversal = "1-401--349---90--88"
// Output: [1,401,null,349,88,90]
//

LEETCODE_SOLUTION_UNITTEST(1028, RecoverATreeFromPreorderTraversal, example_3) {
  auto      solution  = MakeSolution();
  string    traversal = "1-401--349---90--88";
  TreeNode *expect    = TreeNode::FromVector({1, 401, null, 349, 88, 90});
  TreeNode *actual    = solution->recoverFromPreorder(traversal);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(expect, actual);
}

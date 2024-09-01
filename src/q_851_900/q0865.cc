// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Smallest Subtree with all the Deepest Nodes
//
// https://leetcode.com/problems/smallest-subtree-with-all-the-deepest-nodes/
//
// Question ID: 865
// Difficult  : Medium
// Solve Date : 2024/09/01 10:48

#include "leetcode/tree_node.h"
#include <iosfwd>
#include <unordered_map>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |865. Smallest Subtree with all the Deepest Nodes|:
//
// Given the |root| of a binary tree, the depth of each node is the shortest
// distance to the root. Return the smallest subtree such that it contains all
// the deepest nodes in the original tree. A node is called the deepest if it
// has the largest depth possible among any node in the entire tree. The subtree
// of a node is a tree consisting of that node, plus the set of all descendants
// of that node.
//
//

LEETCODE_BEGIN_RESOLVING(865, SmallestSubtreeWithAllTheDeepestNodes, Solution);

class Solution {
public:
  TreeNode *subtreeWithAllDeepest(TreeNode *root) {
    unordered_map<TreeNode *, int> ds;
    TreeNode                      *res;
    depth(root, &ds);
    findNode(&res, root, ds);
    return res;
  }

private:
  int depth(auto *p, auto *mp) {
    if (!p) {
      return 0;
    }

    return (*mp)[p] = max(depth(p->left, mp), depth(p->right, mp)) + 1;
  }

  void findNode(auto **res, auto *p, auto &mp) {
    int left  = mp[p->left];
    int right = mp[p->right];

    if (left > right) {
      findNode(res, p->left, mp);
    } else if (left < right) {
      findNode(res, p->right, mp);
    } else {
      *res = p;
    }
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree will be in the range |[1, 500]|.
// * |0 <= Node.val <= 500|
// * The values of the nodes in the tree are unique.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [3,5,1,6,2,0,8,null,null,7,4]
// Output: [2,7,4]
//

LEETCODE_SOLUTION_UNITTEST(865, SmallestSubtreeWithAllTheDeepestNodes,
                           example_1) {
  auto      solution = MakeSolution();
  TreeNode *root =
      TreeNode::FromVector({3, 5, 1, 6, 2, 0, 8, null, null, 7, 4});
  TreeNode *expect = TreeNode::FromVector({2, 7, 4});
  TreeNode *actual = solution->subtreeWithAllDeepest(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root, expect, actual);
}

// [Example #2]
//  Input: root = [1]
// Output: [1]
//

LEETCODE_SOLUTION_UNITTEST(865, SmallestSubtreeWithAllTheDeepestNodes,
                           example_2) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({1});
  TreeNode *expect   = TreeNode::FromVector({1});
  TreeNode *actual   = solution->subtreeWithAllDeepest(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root, expect, actual);
}

// [Example #3]
//  Input: root = [0,1,3,null,2]
// Output: [2]
//

LEETCODE_SOLUTION_UNITTEST(865, SmallestSubtreeWithAllTheDeepestNodes,
                           example_3) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({0, 1, 3, null, 2});
  TreeNode *expect   = TreeNode::FromVector({2});
  TreeNode *actual   = solution->subtreeWithAllDeepest(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root, expect, actual);
}

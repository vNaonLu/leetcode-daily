// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Longest Univalue Path
//
// https://leetcode.com/problems/longest-univalue-path/
//
// Question ID: 687
// Difficult  : Medium
// Solve Date : 2022/09/01 00:35

#include "leetcode/tree_node.h"
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |687. Longest Univalue Path|:
//
// Given the |root| of a binary tree, return the length of the longest path,
// where each node in the path has the same value. This path may or may not pass
// through the root. The length of the path between two nodes is represented by
// the number of edges between them.
//

LEETCODE_BEGIN_RESOLVING(687, LongestUnivaluePath, Solution);

class Solution {
private:
  int findLength(TreeNode *prev, TreeNode *p, int &res) {
    if (p == nullptr || (prev != nullptr && prev->val != p->val)) {
      return 0;
    }
    auto left_v = findLength(p, p->left, res);
    if (left_v == 0) {
      findLength(nullptr, p->left, res);
    }

    auto right_v = findLength(p, p->right, res);
    if (right_v == 0) {
      findLength(nullptr, p->right, res);
    }

    res = max(res, left_v + right_v + 1);
    return max(right_v, left_v) + 1;
  }

public:
  int longestUnivaluePath(TreeNode *root) {
    int res = 0;
    findLength(nullptr, root, res);
    return max(res - 1, 0);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is in the range |[0, 10⁴]|.
// * |-1000 <= Node.val <= 1000|
// * The depth of the tree will not exceed |1000|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [5,4,5,1,1,null,5]
// Output: 2
//
// The shown image shows that the longest path of the same value (i.e. 5).

LEETCODE_SOLUTION_UNITTEST(687, LongestUnivaluePath, example_1) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({5, 4, 5, 1, 1, null, 5});
  int       expect   = 2;
  int       actual   = solution->longestUnivaluePath(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #2]
//  Input: root = [1,4,5,4,4,null,5]
// Output: 2
//
// The shown image shows that the longest path of the same value (i.e. 4).

LEETCODE_SOLUTION_UNITTEST(687, LongestUnivaluePath, example_2) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({1, 4, 5, 4, 4, null, 5});
  int       expect   = 2;
  int       actual   = solution->longestUnivaluePath(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

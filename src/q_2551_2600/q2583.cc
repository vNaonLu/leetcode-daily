// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Kth Largest Sum in a Binary Tree
//
// https://leetcode.com/problems/kth-largest-sum-in-a-binary-tree/
//
// Question ID: 2583
// Difficult  : Medium
// Solve Date : 2024/10/22 18:59

#include "leetcode/tree_node.h"
#include <algorithm>
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2583. Kth Largest Sum in a Binary Tree|:
//
// You are given the |root| of a binary tree and a positive integer |k|.
// The level sum in the tree is the sum of the values of the nodes that are on
// the same level. Return the |kᵗʰ| largest level sum in the tree (not
// necessarily distinct). If there are fewer than |k| levels in the tree, return
// |-1|. Note that two nodes are on the same level if they have the same
// distance from the root.
//
//

LEETCODE_BEGIN_RESOLVING(2583, KthLargestSumInABinaryTree, Solution);

class Solution {
public:
  long long kthLargestLevelSum(TreeNode *root, int k) {
    vector<int64_t> mp;
    sum(root, 0, &mp);
    if (mp.size() < k) {
      return -1;
    }
    nth_element(mp.begin(), mp.begin() + k - 1, mp.end(), greater<int64_t>{});
    return *(mp.begin() + k - 1);
  }

private:
  void sum(auto *p, int d, auto *out) {
    if (!p) {
      return;
    }
    if (out->size() < d + 1) {
      out->resize(d + 1);
    }
    (*out)[d] += p->val;
    sum(p->left, d + 1, out);
    sum(p->right, d + 1, out);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is |n|.
// * |2 <= n <= 10⁵|
// * |1 <= Node.val <= 10⁶|
// * |1 <= k <= n|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [5,8,9,2,1,3,7,4,6], k = 2
// Output: 13
//

LEETCODE_SOLUTION_UNITTEST(2583, KthLargestSumInABinaryTree, example_1) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({5, 8, 9, 2, 1, 3, 7, 4, 6});
  int       k        = 2;
  long long expect   = 13;
  long long actual   = solution->kthLargestLevelSum(root, k);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #2]
//  Input: root = [1,2,null,3], k = 1
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(2583, KthLargestSumInABinaryTree, example_2) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({1, 2, null, 3});
  int       k        = 1;
  long long expect   = 3;
  long long actual   = solution->kthLargestLevelSum(root, k);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Extra Testcase #1]
//  Input: [5,8,9,2,1,3,7]
// 4
// Output: -1
//

LEETCODE_SOLUTION_UNITTEST(2583, KthLargestSumInABinaryTree, extra_testcase_1) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({5, 8, 9, 2, 1, 3, 7});
  int       k        = 4;
  long long expect   = -1;
  long long actual   = solution->kthLargestLevelSum(root, k);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

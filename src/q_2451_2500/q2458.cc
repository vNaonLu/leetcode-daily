// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Height of Binary Tree After Subtree Removal Queries
//
// https://leetcode.com/problems/height-of-binary-tree-after-subtree-removal-queries/
//
// Question ID: 2458
// Difficult  : Hard
// Solve Date : 2024/10/26 13:06

#include "leetcode/tree_node.h"
#include <iosfwd>
#include <queue>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2458. Height of Binary Tree After Subtree Removal Queries|:
//
// You are given the |root| of a binary tree with |n| nodes. Each node is
// assigned a unique value from |1| to |n|. You are also given an array
// |queries| of size |m|. You have to perform |m| independent queries on the
// tree where in the |iᵗʰ| query you do the following:
//
//  • Remove the subtree rooted at the node with the value |queries[i]| from the
//  tree. It is guaranteed that |queries[i]| will not be equal to the value of
//  the root.
// Return an array |answer| of size |m| where |answer[i]| is the height of the
// tree after performing the |iᵗʰ| query. Note:
//
//  • The queries are independent, so the tree returns to its initial state
//  after each query.
//
//  • The height of a tree is the number of edges in the longest simple path
//  from the root to some node in the tree.
//
//

LEETCODE_BEGIN_RESOLVING(2458, HeightOfBinaryTreeAfterSubtreeRemovalQueries,
                         Solution);

class Solution {
public:
  vector<int> treeQueries(TreeNode *root, vector<int> &queries) {
    vector<int> res;
    vector<int> v2h(100001, -1);
    vector<int> removal(100001, -1);
    dfs(root, 0, 0, &removal, &v2h);

    res.reserve(queries.size());
    for (auto i : queries) {
      res.emplace_back(removal[i]);
    }
    return res;
  }

private:
  int h(auto *p, auto *v) {
    if (!p) {
      return -1;
    }
    auto x = p->val;
    if ((*v)[x] != -1) {
      return (*v)[x];
    }
    return (*v)[x] = 1 + max(h(p->left, v), h(p->right, v));
  }

  void dfs(auto *p, int lvl, int mxlvl, auto *v, auto *hs) {
    if (!p) {
      return;
    }

    auto x  = p->val;
    (*v)[x] = mxlvl;
    dfs(p->left, lvl + 1, max(mxlvl, 1 + lvl + h(p->right, hs)), v, hs);
    dfs(p->right, lvl + 1, max(mxlvl, 1 + lvl + h(p->left, hs)), v, hs);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is |n|.
// * |2 <= n <= 10⁵|
// * |1 <= Node.val <= n|
// * All the values in the tree are unique.
// * |m == queries.length|
// * |1 <= m <= min(n, 10⁴)|
// * |1 <= queries[i] <= n|
// * |queries[i] != root.val|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [1,3,4,2,null,6,5,null,null,null,null,null,7], queries = [4]
// Output: [2]
//

LEETCODE_SOLUTION_UNITTEST(2458, HeightOfBinaryTreeAfterSubtreeRemovalQueries,
                           example_1) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector(
      {1, 3, 4, 2, null, 6, 5, null, null, null, null, null, 7});
  vector<int> queries = {4};
  vector<int> expect  = {2};
  vector<int> actual  = solution->treeQueries(root, queries);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #2]
//  Input: root = [5,8,9,2,1,3,7,4,6], queries = [3,2,4,8]
// Output: [3,2,3,2]
//

LEETCODE_SOLUTION_UNITTEST(2458, HeightOfBinaryTreeAfterSubtreeRemovalQueries,
                           example_2) {
  auto        solution = MakeSolution();
  TreeNode   *root     = TreeNode::FromVector({5, 8, 9, 2, 1, 3, 7, 4, 6});
  vector<int> queries  = {3, 2, 4, 8};
  vector<int> expect   = {3, 2, 3, 2};
  vector<int> actual   = solution->treeQueries(root, queries);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// Copyright 2023 Naon Lu
//
// This file describes the solution of
// All Nodes Distance K in Binary Tree
//
// https://leetcode.com/problems/all-nodes-distance-k-in-binary-tree/
//
// Question ID: 863
// Difficult  : Medium
// Solve Date : 2023/07/11 21:17

#include "leetcode/tree_node.h"
#include <iosfwd>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |863. All Nodes Distance K in Binary Tree|:
//
// Given the |root| of a binary tree, the value of a target node |target|, and
// an integer |k|, return an array of the values of all nodes that have a
// distance |k| from the target node. You can return the answer in any order.
//
//

LEETCODE_BEGIN_RESOLVING(863, AllNodesDistanceKInBinaryTree, Solution);

class Solution {
public:
  vector<int> distanceK(TreeNode *root, TreeNode *target, int k) {
    vector<int>               res;
    unordered_set<TreeNode *> visited;
    auto                      mp = buildMap(root);
    queue<TreeNode *>         q;
    visited.emplace(target);
    q.emplace(target);
    while (!q.empty() && k > 0) {
      auto tmp = std::move(q);
      while (!tmp.empty()) {
        for (auto *nxt : mp[tmp.front()]) {
          if (!visited.count(nxt)) {
            q.emplace(nxt);
            visited.emplace(nxt);
          }
        }
        tmp.pop();
      }
      --k;
    }
    while (!q.empty()) {
      res.emplace_back(q.front()->val);
      q.pop();
    }
    return res;
  }

private:
  unordered_map<TreeNode *, vector<TreeNode *>> buildMap(TreeNode *p) {
    unordered_map<TreeNode *, vector<TreeNode *>> res;
    traval(nullptr, p, &res);
    return res;
  }

  void traval(TreeNode *prev, TreeNode *cur,
              unordered_map<TreeNode *, vector<TreeNode *>> *out) {
    if (!cur) {
      return;
    }
    if (prev) {
      (*out)[prev].emplace_back(cur);
      (*out)[cur].emplace_back(prev);
    }
    traval(cur, cur->left, out);
    traval(cur, cur->right, out);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is in the range |[1, 500]|.
// * |0 <= Node.val <= 500|
// * All the values |Node.val| are unique.
// * |target| is the value of one of the nodes in the tree.
// * |0 <= k <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [3,5,1,6,2,0,8,null,null,7,4], target = 5, k = 2
// Output: [7,4,1]
// Explanation: The nodes that are a distance 2 from the target node (with value
// 5) have values 7, 4, and 1.
//

LEETCODE_SOLUTION_UNITTEST(863, AllNodesDistanceKInBinaryTree, example_1) {
  auto      solution = MakeSolution();
  TreeNode *root =
      TreeNode::FromVector({3, 5, 1, 6, 2, 0, 8, null, null, 7, 4});
  TreeNode   *target = root->GetChild(1);
  int         k      = 2;
  vector<int> expect = {7, 4, 1};
  vector<int> actual = solution->distanceK(root, target, k);
  EXPECT_ANYORDER_EQ(expect, actual);
  TreeNode::Release(root, target);
}

// [Example #2]
//  Input: root = [1], target = 1, k = 3
// Output: []
//

LEETCODE_SOLUTION_UNITTEST(863, AllNodesDistanceKInBinaryTree, example_2) {
  auto        solution = MakeSolution();
  TreeNode   *root     = TreeNode::FromVector({1});
  TreeNode   *target   = root->GetChild(0);
  int         k        = 3;
  vector<int> expect   = {};
  vector<int> actual   = solution->distanceK(root, target, k);
  EXPECT_ANYORDER_EQ(expect, actual);
  TreeNode::Release(root, target);
}

// Copyright 2023 Naon Lu
//
// This file describes the solution of
// N-ary Tree Level Order Traversal
//
// https://leetcode.com/problems/n-ary-tree-level-order-traversal/
//
// Question ID: 429
// Difficult  : Medium
// Solve Date : 2022/05/04 18:14

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |429. N-ary Tree Level Order Traversal|:
//
// Given an n-ary tree, return the level order traversal of its nodes' values.
// Nary-Tree input serialization is represented in their level order traversal,
// each group of children is separated by the null value (See examples).  
//

LEETCODE_BEGIN_RESOLVING(429, NAryTreeLevelOrderTraversal, Solution);

class Node {
public:
  int            val;
  vector<Node *> children;

  Node() {}

  Node(int _val) { val = _val; }

  Node(int _val, vector<Node *> _children) {
    val      = _val;
    children = _children;
  }
};

class Solution {
private:
  void helper(vector<vector<int>> &res, Node *p, int depth) {
    if (nullptr == p) {
      return;
    }

    if (depth >= res.size()) {
      res.resize(depth + 1);
    }

    res[depth].push_back(p->val);
    for (auto node : p->children) {
      helper(res, node, depth + 1);
    }
  }

public:
  vector<vector<int>> levelOrder(Node *root) {
    vector<vector<int>> res;
    helper(res, root, 0);
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The height of the n-ary tree is less than or equal to |1000|
// * The total number of nodes is between |[0, 10⁴]|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [1,null,3,2,4,null,5,6]
// Output: [[1],[3,2,4],[5,6]]
//

LEETCODE_SOLUTION_UNITTEST(429, NAryTreeLevelOrderTraversal, example_1) {
  GTEST_SKIP() << "Unittest Not Implemented";
}

// [Example #2]
//  Input: root =
//  [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14]
// Output: [[1],[2,3,4,5],[6,7,8,9,10],[11,12,13],[14]]
//

LEETCODE_SOLUTION_UNITTEST(429, NAryTreeLevelOrderTraversal, example_2) {
  GTEST_SKIP() << "Unittest Not Implemented";
}

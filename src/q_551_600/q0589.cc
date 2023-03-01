// Copyright 2023 Naon Lu
//
// This file describes the solution of
// N-ary Tree Preorder Traversal
//
// https://leetcode.com/problems/n-ary-tree-preorder-traversal/
//
// Question ID: 589
// Difficult  : Easy
// Solve Date : 2022/04/18 18:14

#include <iosfwd>
#include <stack>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |589. N-ary Tree Preorder Traversal|:
//
// Given the |root| of an n-ary tree, return the preorder traversal of its
// nodes' values. Nary-Tree input serialization is represented in their level
// order traversal. Each group of children is separated by the null value (See
// examples)  
//

LEETCODE_BEGIN_RESOLVING(589, NAryTreePreorderTraversal, Solution);

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
public:
  vector<int> preorder(Node *root) {
    auto res = vector<int>();
    auto stk = stack<Node *>();
    stk.emplace(root);
    while (!stk.empty()) {
      auto p = stk.top();
      stk.pop();

      if (p == nullptr) {
        continue;
      }

      res.emplace_back(p->val);
      for (auto it = p->children.rbegin(); it != p->children.rend(); ++it) {
        stk.emplace(*it);
      }
    }
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is in the range |[0, 10⁴]|.
// * |0 <= Node.val <= 10⁴|
// * The height of the n-ary tree is less than or equal to |1000|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [1,null,3,2,4,null,5,6]
// Output: [1,3,5,6,2,4]
//

LEETCODE_SOLUTION_UNITTEST(589, NAryTreePreorderTraversal, example_1) {
  GTEST_SKIP() << "Unittest Not Implemented";
}

// [Example #2]
//  Input: root =
//  [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14]
// Output: [1,2,3,6,7,11,14,4,8,12,5,9,13,10]
//

LEETCODE_SOLUTION_UNITTEST(589, NAryTreePreorderTraversal, example_2) {
  GTEST_SKIP() << "Unittest Not Implemented";
}

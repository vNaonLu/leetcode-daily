// Copyright 2023 Naon Lu
//
// This file describes the solution of
// N-ary Tree Postorder Traversal
//
// https://leetcode.com/problems/n-ary-tree-postorder-traversal/
//
// Question ID: 590
// Difficult  : Easy
// Solve Date : 2022/09/24 12:55

#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |590. N-ary Tree Postorder Traversal|:
//
// Given the |root| of an n-ary tree, return the postorder traversal of its
// nodes' values. Nary-Tree input serialization is represented in their level
// order traversal. Each group of children is separated by the null value (See
// examples)
//

LEETCODE_BEGIN_RESOLVING(590, NAryTreePostorderTraversal, Solution);

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
  void travel(vector<int> &res, Node *p) {
    if (nullptr != p) {
      for (auto n : p->children) {
        travel(res, n);
      }
      res.emplace_back(p->val);
    }
  }

public:
  vector<int> postorder(Node *root) {
    auto res = vector<int>();
    travel(res, root);
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
// Output: [5,6,3,2,4,1]
//

LEETCODE_SOLUTION_UNITTEST(590, NAryTreePostorderTraversal, example_1) {
  GTEST_SKIP() << "Unittest Not Implemented";
}

// [Example #2]
//  Input: root =
//  [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14]
// Output: [2,6,14,11,7,3,12,8,4,13,9,10,5,1]
//

LEETCODE_SOLUTION_UNITTEST(590, NAryTreePostorderTraversal, example_2) {
  GTEST_SKIP() << "Unittest Not Implemented";
}

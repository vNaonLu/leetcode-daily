// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Populating Next Right Pointers in Each Node II
//
// https://leetcode.com/problems/populating-next-right-pointers-in-each-node-ii/
//
// Question ID: 117
// Difficult  : Medium
// Solve Date : 2021/09/25 15:55

#include <iosfwd>
#include <map>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

namespace {
class Node {
public:
  int   val;
  Node *left;
  Node *right;
  Node *next;
  Node() : val(0), left(NULL), right(NULL), next(NULL) {}
  Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}
  Node(int _val, Node *_left, Node *_right, Node *_next)
      : val(_val), left(_left), right(_right), next(_next) {}
};
} // namespace

// Description of |117. Populating Next Right Pointers in Each Node II|:
//
// Given a binary tree
// struct Node {
//   int val;
//   Node *left;
//   Node *right;
//   Node *next;
// }
// Populate each next pointer to point to its next right node. If there is no
// next right node, the next pointer should be set to |NULL|. Initially, all
// next pointers are set to |NULL|.  
//

LEETCODE_BEGIN_RESOLVING(117, PopulatingNextRightPointersInEachNodeII,
                         Solution);
class Solution {
private:
  void helper(vector<vector<Node *>> &r, Node *p, int level = 0) {
    if (p == nullptr)
      return;
    if (level >= r.size())
      r.resize(level + 1);
    r[level].push_back(p);
    helper(r, p->left, level + 1);
    helper(r, p->right, level + 1);
  }

public:
  Node *connect(Node *root) {
    vector<vector<Node *>> level_map;
    helper(level_map, root);
    for (auto levels : level_map) {
      for (int i = 0; i < levels.size() - 1; ++i) {
        levels[i]->next = levels[i + 1];
      }
    }
    return root;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is in the range |[0, 6000]|.
// * |-100 <= Node.val <= 100|
// * You may only use constant extra space.
// * The recursive approach is fine. You may assume implicit stack space does
// not count as extra space for this problem.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [1,2,3,4,5,null,7]
// Output: [1,#,2,3,#,4,5,7,#]
//
// Given the above binary tree (Figure A), your function should populate each
// next pointer to point to its next right node, just like in Figure B. The
// serialized output is in level order as connected by the next pointers, with
// '#' signifying the end of each level.

LEETCODE_SOLUTION_UNITTEST(117, PopulatingNextRightPointersInEachNodeII,
                           example_1) {
  auto solution = MakeSolution();
  Node n4(4);
  Node n5(5);
  Node n7(7);

  Node  n2(2, &n4, &n5, nullptr);
  Node  n3(3, nullptr, &n7, nullptr);
  Node  root(1, &n2, &n3, nullptr);
  Node *actual = solution->connect(&root);
  ASSERT_EQ(actual, &root);
  ASSERT_EQ(actual->left, &n2);
  ASSERT_EQ(actual->right, &n3);
  ASSERT_EQ(actual->next, nullptr);
  ASSERT_EQ(n2.next, &n3);
  ASSERT_EQ(n3.next, nullptr);
  ASSERT_EQ(n4.next, &n5);
  ASSERT_EQ(n5.next, &n7);
  ASSERT_EQ(n7.next, nullptr);
}

// [Example #2]
//  Input: root = []
// Output: []
//

LEETCODE_SOLUTION_UNITTEST(117, PopulatingNextRightPointersInEachNodeII,
                           example_2) {
  auto  solution = MakeSolution();
  Node *root     = nullptr;
  Node *expect   = nullptr;
  Node *actual   = solution->connect(root);
  EXPECT_EQ(actual, expect);
}

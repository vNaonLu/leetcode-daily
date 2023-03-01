// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Flatten a Multilevel Doubly Linked List
//
// https://leetcode.com/problems/flatten-a-multilevel-doubly-linked-list/
//
// Question ID: 430
// Difficult  : Medium
// Solve Date : 2021/10/31 13:12

#include <iosfwd>
#include <stack>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |430. Flatten a Multilevel Doubly Linked List|:
//
// You are given a doubly linked list, which contains nodes that have a next
// pointer, a previous pointer, and an additional child pointer. This child
// pointer may or may not point to a separate doubly linked list, also
// containing these special nodes. These child lists may have one or more
// children of their own, and so on, to produce a multilevel data structure as
// shown in the example below. Given the |head| of the first level of the list,
// flatten the list so that all the nodes appear in a single-level, doubly
// linked list. Let |curr| be a node with a child list. The nodes in the child
// list should appear after |curr| and before |curr.next| in the flattened list.
// Return the |head| of the flattened list. The nodes in the list must have all
// of their child pointers set to |null|.  
//

LEETCODE_BEGIN_RESOLVING(430, FlattenAMultilevelDoublyLinkedList, Solution);

class Node {
public:
  int   val;
  Node *prev;
  Node *next;
  Node *child;
};

class Solution {
public:
  Node *flatten(Node *head) {
    if (head == nullptr)
      return nullptr;
    Node          dummy{0, nullptr, nullptr, nullptr};
    Node         *p = &dummy;
    stack<Node *> path;
    path.push(head);
    while (!path.empty()) {
      auto node = path.top();
      path.pop();
      if (node->next != nullptr)
        path.push(node->next);
      if (node->child != nullptr)
        path.push(node->child);
      p->next = node;
      if (p != &dummy) {
        node->prev = p;
      } else {
        node->prev = nullptr;
      }
      node->child = nullptr;
      p           = p->next;
    }
    return dummy.next;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of Nodes will not exceed |1000|.
// * |1 <= Node.val <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: head = [1,2,3,4,5,6,null,null,null,7,8,9,10,null,null,11,12]
// Output: [1,2,3,7,8,11,12,9,10,4,5,6]
//
// The multilevel linked list in the input is shown.
// After flattening the multilevel linked list it becomes:
// ![img](https://assets.leetcode.com/uploads/2021/11/09/flatten12.jpg)

LEETCODE_SOLUTION_UNITTEST(430, FlattenAMultilevelDoublyLinkedList, example_1) {
  GTEST_SKIP() << "Unittest Not Implemented";
}

// [Example #2]
//  Input: head = [1,2,null,3]
// Output: [1,3,2]
//
// The multilevel linked list in the input is shown.
// After flattening the multilevel linked list it becomes:
// ![img](https://assets.leetcode.com/uploads/2021/11/24/list.jpg)

LEETCODE_SOLUTION_UNITTEST(430, FlattenAMultilevelDoublyLinkedList, example_2) {
  GTEST_SKIP() << "Unittest Not Implemented";
}

// [Example #3]
//  Input: head = []
// Output: []
//
// There could be empty list in the input.

LEETCODE_SOLUTION_UNITTEST(430, FlattenAMultilevelDoublyLinkedList, example_3) {
  GTEST_SKIP() << "Unittest Not Implemented";
}

// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Remove Nodes From Linked List
//
// https://leetcode.com/problems/remove-nodes-from-linked-list/
//
// Question ID: 2487
// Difficult  : Medium
// Solve Date : 2024/05/06 22:07

#include "leetcode/list_node.h"
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2487. Remove Nodes From Linked List|:
//
// You are given the |head| of a linked list.
// Remove every node which has a node with a greater value anywhere to the right
// side of it. Return the |head| of the modified linked list.
//
//

LEETCODE_BEGIN_RESOLVING(2487, RemoveNodesFromLinkedList, Solution);

class Solution {
public:
  ListNode *removeNodes(ListNode *head) {
    ListNode           dummy;
    vector<ListNode *> stk;
    for (auto *p = head; p; p = p->next) {
      while (!stk.empty() && stk.back()->val < p->val) {
        delete stk.back();
        stk.pop_back();
      }
      stk.emplace_back(p);
    }
    auto *p = &dummy;
    for (auto *q : stk) {
      p->next = q;
      p       = q;
      p->next = nullptr;
    }
    return dummy.next;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * The number of the nodes in the given list is in the range |[1, 10⁵]|.
// * |1 <= Node.val <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: head = [5,2,13,3,8]
// Output: [13,8]
//

LEETCODE_SOLUTION_UNITTEST(2487, RemoveNodesFromLinkedList, example_1) {
  auto      solution = MakeSolution();
  ListNode *head   = ListNode::FromVector({5, 2, 13, 3, 8} /*, looped_index*/);
  ListNode *expect = ListNode::FromVector({13, 8} /*, looped_index*/);
  ListNode *actual = solution->removeNodes(head);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head, expect, actual);
}

// [Example #2]
//  Input: head = [1,1,1,1]
// Output: [1,1,1,1]
//

LEETCODE_SOLUTION_UNITTEST(2487, RemoveNodesFromLinkedList, example_2) {
  auto      solution = MakeSolution();
  ListNode *head     = ListNode::FromVector({1, 1, 1, 1} /*, looped_index*/);
  ListNode *expect   = ListNode::FromVector({1, 1, 1, 1} /*, looped_index*/);
  ListNode *actual   = solution->removeNodes(head);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head, expect, actual);
}

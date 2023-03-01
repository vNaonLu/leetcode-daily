// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Reverse Linked List II
//
// https://leetcode.com/problems/reverse-linked-list-ii/
//
// Question ID: 92
// Difficult  : Medium
// Solve Date : 2021/12/29 18:13

#include "leetcode/list_node.h"
#include <iosfwd>
#include <stack>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |92. Reverse Linked List II|:
//
// Given the |head| of a singly linked list and two integers |left| and |right|
// where |left <= right|, reverse the nodes of the list from position |left| to
// position |right|, and return the reversed list.  
//

LEETCODE_BEGIN_RESOLVING(92, ReverseLinkedListII, Solution);

class Solution {
public:
  ListNode *reverseBetween(ListNode *head, int left, int right) {
    stack<ListNode *> stk;
    ListNode          dummy(0, head), *p = &dummy;

    int idx = 1;
    while (idx <= right) {
      if (idx < left)
        p = p->next;
      else
        stk.emplace(head);
      ++idx;
      head = head->next;
    }

    ListNode *R = stk.top()->next;
    while (!stk.empty()) {
      p->next = stk.top();
      p       = p->next;
      stk.pop();
    }
    p->next = R;

    return dummy.next;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the list is |n|.
// * |1 <= n <= 500|
// * |-500 <= Node.val <= 500|
// * |1 <= left <= right <= n|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: head = [1,2,3,4,5], left = 2, right = 4
// Output: [1,4,3,2,5]
//

LEETCODE_SOLUTION_UNITTEST(92, ReverseLinkedListII, example_1) {
  auto      solution = MakeSolution();
  ListNode *head     = ListNode::FromVector({1, 2, 3, 4, 5} /*, looped_index*/);
  int       left     = 2;
  int       right    = 4;
  ListNode *expect   = ListNode::FromVector({1, 4, 3, 2, 5} /*, looped_index*/);
  ListNode *actual   = solution->reverseBetween(head, left, right);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head, expect, actual);
}

// [Example #2]
//  Input: head = [5], left = 1, right = 1
// Output: [5]
//

LEETCODE_SOLUTION_UNITTEST(92, ReverseLinkedListII, example_2) {
  auto      solution = MakeSolution();
  ListNode *head     = ListNode::FromVector({5} /*, looped_index*/);
  int       left     = 1;
  int       right    = 1;
  ListNode *expect   = ListNode::FromVector({5} /*, looped_index*/);
  ListNode *actual   = solution->reverseBetween(head, left, right);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head, expect, actual);
}

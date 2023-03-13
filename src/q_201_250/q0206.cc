// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Reverse Linked List
//
// https://leetcode.com/problems/reverse-linked-list/
//
// Question ID: 206
// Difficult  : Easy
// Solve Date : 2021/09/07 08:00

#include "leetcode/list_node.h"
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |206. Reverse Linked List|:
//
// Given the |head| of a singly linked list, reverse the list, and return the
// reversed list.  
//

LEETCODE_BEGIN_RESOLVING(206, ReverseLinkedList, Solution);

class Solution {
public:
  ListNode *reverseList(ListNode *head) {
    auto prev = (ListNode *)nullptr;
    auto tmp  = (ListNode *)nullptr;
    while (nullptr != head) {
      tmp        = head->next;
      head->next = prev;
      prev       = head;
      head       = tmp;
    }
    return prev;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the list is the range |[0, 5000]|.
// * |-5000 <= Node.val <= 5000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: head = [1,2,3,4,5]
// Output: [5,4,3,2,1]
//

LEETCODE_SOLUTION_UNITTEST(206, ReverseLinkedList, example_1) {
  auto      solution = MakeSolution();
  ListNode *head     = ListNode::FromVector({1, 2, 3, 4, 5} /*, looped_index*/);
  ListNode *expect   = ListNode::FromVector({5, 4, 3, 2, 1} /*, looped_index*/);
  ListNode *actual   = solution->reverseList(head);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head, expect, actual);
}

// [Example #2]
//  Input: head = [1,2]
// Output: [2,1]
//

LEETCODE_SOLUTION_UNITTEST(206, ReverseLinkedList, example_2) {
  auto      solution = MakeSolution();
  ListNode *head     = ListNode::FromVector({1, 2} /*, looped_index*/);
  ListNode *expect   = ListNode::FromVector({2, 1} /*, looped_index*/);
  ListNode *actual   = solution->reverseList(head);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head, expect, actual);
}

// [Example #3]
//  Input: head = []
// Output: []
//

LEETCODE_SOLUTION_UNITTEST(206, ReverseLinkedList, example_3) {
  auto      solution = MakeSolution();
  ListNode *head     = ListNode::FromVector({} /*, looped_index*/);
  ListNode *expect   = ListNode::FromVector({} /*, looped_index*/);
  ListNode *actual   = solution->reverseList(head);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head, expect, actual);
}

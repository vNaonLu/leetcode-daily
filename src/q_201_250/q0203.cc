// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Remove Linked List Elements
//
// https://leetcode.com/problems/remove-linked-list-elements/
//
// Question ID: 203
// Difficult  : Easy
// Solve Date : 2021/09/11 08:00

#include "leetcode/list_node.h"
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |203. Remove Linked List Elements|:
//
// Given the |head| of a linked list and an integer |val|, remove all the nodes
// of the linked list that has |Node.val == val|, and return the new head.  
//

LEETCODE_BEGIN_RESOLVING(203, RemoveLinkedListElements, Solution);

class Solution {
public:
  ListNode *removeElements(ListNode *head, int val) {
    ListNode  dummy(-1, head);
    ListNode *p = head, *pre = &dummy;
    while (p != nullptr) {
      ListNode *rm = nullptr;
      if (p->val == val) {
        rm        = p;
        pre->next = p->next;
      } else {
        pre = p;
      }
      p = p->next;
      if (rm) {
        delete rm;
      }
    }
    return dummy.next;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the list is in the range |[0, 10⁴]|.
// * |1 <= Node.val <= 50|
// * |0 <= val <= 50|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: head = [1,2,6,3,4,5,6], val = 6
// Output: [1,2,3,4,5]
//

LEETCODE_SOLUTION_UNITTEST(203, RemoveLinkedListElements, example_1) {
  auto      solution = MakeSolution();
  ListNode *head =
      ListNode::FromVector({1, 2, 6, 3, 4, 5, 6} /*, looped_index*/);
  int       val    = 6;
  ListNode *expect = ListNode::FromVector({1, 2, 3, 4, 5} /*, looped_index*/);
  ListNode *actual = solution->removeElements(head, val);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head, expect, actual);
}

// [Example #2]
//  Input: head = [], val = 1
// Output: []
//

LEETCODE_SOLUTION_UNITTEST(203, RemoveLinkedListElements, example_2) {
  auto      solution = MakeSolution();
  ListNode *head     = ListNode::FromVector({} /*, looped_index*/);
  int       val      = 1;
  ListNode *expect   = ListNode::FromVector({} /*, looped_index*/);
  ListNode *actual   = solution->removeElements(head, val);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head, expect, actual);
}

// [Example #3]
//  Input: head = [7,7,7,7], val = 7
// Output: []
//

LEETCODE_SOLUTION_UNITTEST(203, RemoveLinkedListElements, example_3) {
  auto      solution = MakeSolution();
  ListNode *head     = ListNode::FromVector({7, 7, 7, 7} /*, looped_index*/);
  int       val      = 7;
  ListNode *expect   = ListNode::FromVector({} /*, looped_index*/);
  ListNode *actual   = solution->removeElements(head, val);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head, expect, actual);
}

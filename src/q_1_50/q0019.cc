// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Remove Nth Node From End of List
//
// https://leetcode.com/problems/remove-nth-node-from-end-of-list/
//
// Question ID: 19
// Difficult  : Medium
// Solve Date : 2021/09/09 08:00

#include "leetcode/list_node.h"
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |19. Remove Nth Node From End of List|:
//
// Given the |head| of a linked list, remove the |nᵗʰ| node from the end of the
// list and return its head.  
//

LEETCODE_BEGIN_RESOLVING(19, RemoveNthNodeFromEndofList, Solution);

class Solution {
public:
  ListNode *removeNthFromEnd(ListNode *head, int n) {
    auto dummy = ListNode{0, head};
    auto slow  = &dummy;
    auto fast  = &dummy;
    while (n--) {
      fast = fast->next;
    }
    while (nullptr != fast && nullptr != fast->next) {
      fast = fast->next;
      slow = slow->next;
    }
    slow->next = slow->next->next;
    return dummy.next;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the list is |sz|.
// * |1 <= sz <= 30|
// * |0 <= Node.val <= 100|
// * |1 <= n <= sz|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: head = [1,2,3,4,5], n = 2
// Output: [1,2,3,5]
//

LEETCODE_SOLUTION_UNITTEST(19, RemoveNthNodeFromEndofList, example_1) {
  auto      solution = MakeSolution();
  ListNode *head     = ListNode::FromVector({1, 2, 3, 4, 5} /*, looped_index*/);
  int       n        = 2;
  ListNode *expect   = ListNode::FromVector({1, 2, 3, 5} /*, looped_index*/);
  ListNode *actual   = solution->removeNthFromEnd(head, n);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head);
}

// [Example #2]
//  Input: head = [1], n = 1
// Output: []
//

LEETCODE_SOLUTION_UNITTEST(19, RemoveNthNodeFromEndofList, example_2) {
  auto      solution = MakeSolution();
  ListNode *head     = ListNode::FromVector({1} /*, looped_index*/);
  int       n        = 1;
  ListNode *expect   = ListNode::FromVector({} /*, looped_index*/);
  ListNode *actual   = solution->removeNthFromEnd(head, n);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head);
}

// [Example #3]
//  Input: head = [1,2], n = 1
// Output: [1]
//

LEETCODE_SOLUTION_UNITTEST(19, RemoveNthNodeFromEndofList, example_3) {
  auto      solution = MakeSolution();
  ListNode *head     = ListNode::FromVector({1, 2} /*, looped_index*/);
  int       n        = 1;
  ListNode *expect   = ListNode::FromVector({1} /*, looped_index*/);
  ListNode *actual   = solution->removeNthFromEnd(head, n);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head);
}

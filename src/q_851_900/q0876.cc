// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Middle of the Linked List
//
// https://leetcode.com/problems/middle-of-the-linked-list/
//
// Question ID: 876
// Difficult  : Easy
// Solve Date : 2021/09/09 08:00

#include "leetcode/list_node.h"
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |876. Middle of the Linked List|:
//
// Given the |head| of a singly linked list, return the middle node of the
// linked list. If there are two middle nodes, return the second middle node.  
//

LEETCODE_BEGIN_RESOLVING(876, MiddleoftheLinkedList, Solution);

class Solution {
public:
  ListNode *middleNode(ListNode *head) {
    auto faster = head;

    while (faster != nullptr && faster->next != nullptr) {
      faster = faster->next->next;
      head   = head->next;
    }

    return head;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the list is in the range |[1, 100]|.
// * |1 <= Node.val <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: head = [1,2,3,4,5]
// Output: [3,4,5]
//
// The middle node of the list is node 3.

LEETCODE_SOLUTION_UNITTEST(876, MiddleoftheLinkedList, example_1) {
  auto      solution = MakeSolution();
  ListNode *head     = ListNode::FromVector({1, 2, 3, 4, 5} /*, looped_index*/);
  ListNode *expect   = ListNode::FromVector({3, 4, 5} /*, looped_index*/);
  ListNode *actual   = solution->middleNode(head);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head, expect, actual);
}

// [Example #2]
//  Input: head = [1,2,3,4,5,6]
// Output: [4,5,6]
//
// Since the list has two middle nodes with values 3 and 4, we return the second
// one.

LEETCODE_SOLUTION_UNITTEST(876, MiddleoftheLinkedList, example_2) {
  auto      solution = MakeSolution();
  ListNode *head = ListNode::FromVector({1, 2, 3, 4, 5, 6} /*, looped_index*/);
  ListNode *expect = ListNode::FromVector({4, 5, 6} /*, looped_index*/);
  ListNode *actual = solution->middleNode(head);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head, expect, actual);
}

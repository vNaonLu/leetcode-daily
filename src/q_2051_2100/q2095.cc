// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Delete the Middle Node of a Linked List
//
// https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/
//
// Question ID: 2095
// Difficult  : Medium
// Solve Date : 2022/10/14 10:08

#include "leetcode/list_node.h"
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2095. Delete the Middle Node of a Linked List|:
//
// You are given the |head| of a linked list. Delete the middle node, and return
// the |head| of the modified linked list. The middle node of a linked list of
// size |n| is the |⌊n / 2⌋ᵗʰ| node from the start using 0-based indexing, where
// |⌊x⌋| denotes the largest integer less than or equal to |x|.
//
//  • For |n| = |1|, |2|, |3|, |4|, and |5|, the middle nodes are |0|, |1|, |1|,
//  |2|, and |2|, respectively.
//

LEETCODE_BEGIN_RESOLVING(2095, DeleteTheMiddleNodeOfALinkedList, Solution);

class Solution {
public:
  ListNode *deleteMiddle(ListNode *head) {
    auto dummy = ListNode(0, head);
    auto lo    = &dummy;
    auto hi    = dummy.next;
    while (nullptr != hi && nullptr != hi->next) {
      hi = hi->next->next;
      lo = lo->next;
    }
    lo->next = lo->next->next;
    return dummy.next;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the list is in the range |[1, 10⁵]|.
// * |1 <= Node.val <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: head = [1,3,4,7,1,2,6]
// Output: [1,3,4,1,2,6]
//
// The above figure represents the given linked list. The indices of the nodes
// are written below. Since n = 7, node 3 with value 7 is the middle node, which
// is marked in red. We return the new list after removing this node.

LEETCODE_SOLUTION_UNITTEST(2095, DeleteTheMiddleNodeOfALinkedList, example_1) {
  auto      solution = MakeSolution();
  ListNode *head =
      ListNode::FromVector({1, 3, 4, 7, 1, 2, 6} /*, looped_index*/);
  ListNode *expect =
      ListNode::FromVector({1, 3, 4, 1, 2, 6} /*, looped_index*/);
  ListNode *actual = solution->deleteMiddle(head);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head, expect, actual);
}

// [Example #2]
//  Input: head = [1,2,3,4]
// Output: [1,2,4]
//
// The above figure represents the given linked list.
// For n = 4, node 2 with value 3 is the middle node, which is marked in red.

LEETCODE_SOLUTION_UNITTEST(2095, DeleteTheMiddleNodeOfALinkedList, example_2) {
  auto      solution = MakeSolution();
  ListNode *head     = ListNode::FromVector({1, 2, 3, 4} /*, looped_index*/);
  ListNode *expect   = ListNode::FromVector({1, 2, 4} /*, looped_index*/);
  ListNode *actual   = solution->deleteMiddle(head);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head, expect, actual);
}

// [Example #3]
//  Input: head = [2,1]
// Output: [2]
//
// The above figure represents the given linked list.
// For n = 2, node 1 with value 1 is the middle node, which is marked in red.
// Node 0 with value 2 is the only node remaining after removing node 1.

LEETCODE_SOLUTION_UNITTEST(2095, DeleteTheMiddleNodeOfALinkedList, example_3) {
  auto      solution = MakeSolution();
  ListNode *head     = ListNode::FromVector({2, 1} /*, looped_index*/);
  ListNode *expect   = ListNode::FromVector({2} /*, looped_index*/);
  ListNode *actual   = solution->deleteMiddle(head);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head, expect, actual);
}

// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Linked List Cycle
//
// https://leetcode.com/problems/linked-list-cycle/
//
// Question ID: 141
// Difficult  : Easy
// Solve Date : 2021/09/11 08:00

#include "leetcode/list_node.h"
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |141. Linked List Cycle|:
//
// Given |head|, the head of a linked list, determine if the linked list has a
// cycle in it. There is a cycle in a linked list if there is some node in the
// list that can be reached again by continuously following the  |next| pointer.
// Internally, |pos| is used to denote the index of the node that tail's 
// |next| pointer is connected to. Note that  |pos| is not passed as a
// parameter. Return  |true| if there is a cycle in the linked list. Otherwise,
// return |false|.  
//

LEETCODE_BEGIN_RESOLVING(141, LinkedListCycle, Solution);

class Solution {
public:
  bool hasCycle(ListNode *head) {
    ListNode *fast = head, *slow = head;
    while (fast != nullptr && fast->next != nullptr) {
      slow = slow->next;
      fast = fast->next->next;
      if (slow == fast)
        return true;
    }
    return false;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of the nodes in the list is in the range |[0, 10⁴]|.
// * |-10⁵ <= Node.val <= 10⁵|
// * |pos| is |-1| or a valid index in the linked-list.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: head = [3,2,0,-4], pos = 1
// Output: true
//
// There is a cycle in the linked list, where the tail connects to the 1st node
// (0-indexed).

LEETCODE_SOLUTION_UNITTEST(141, LinkedListCycle, example_1) {
  auto      solution = MakeSolution();
  ListNode *head     = ListNode::FromVector({3, 2, 0, -4}, 1);
  bool      expect   = true;
  bool      actual   = solution->hasCycle(head);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head);
}

// [Example #2]
//  Input: head = [1,2], pos = 0
// Output: true
//
// There is a cycle in the linked list, where the tail connects to the 0th node.

LEETCODE_SOLUTION_UNITTEST(141, LinkedListCycle, example_2) {
  auto      solution = MakeSolution();
  ListNode *head     = ListNode::FromVector({1, 2}, 0);
  bool      expect   = true;
  bool      actual   = solution->hasCycle(head);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head);
}

// [Example #3]
//  Input: head = [1], pos = -1
// Output: false
//
// There is no cycle in the linked list.

LEETCODE_SOLUTION_UNITTEST(141, LinkedListCycle, example_3) {
  auto      solution = MakeSolution();
  ListNode *head     = ListNode::FromVector({1} /*, looped_index*/);
  bool      expect   = false;
  bool      actual   = solution->hasCycle(head);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head);
}

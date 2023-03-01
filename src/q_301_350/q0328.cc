// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Odd Even Linked List
//
// https://leetcode.com/problems/odd-even-linked-list/
//
// Question ID: 328
// Difficult  : Medium
// Solve Date : 2021/12/02 13:04

#include "leetcode/list_node.h"
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |328. Odd Even Linked List|:
//
// Given the |head| of a singly linked list, group all the nodes with odd
// indices together followed by the nodes with even indices, and return the
// reordered list. The first node is considered odd, and the second node is
// even, and so on. Note that the relative order inside both the even and odd
// groups should remain as it was in the input. You must solve the problem in
// |O(1)| extra space complexity and |O(n)| time complexity.  
//

LEETCODE_BEGIN_RESOLVING(328, OddEvenLinkedList, Solution);

class Solution {
public:
  ListNode *oddEvenList(ListNode *head) {
    if (head == nullptr)
      return nullptr;
    ListNode *odd = head, *even = head->next, *even_head = even;
    while (even != nullptr && even->next != nullptr) {
      odd->next  = even->next;
      odd        = odd->next;
      even->next = odd->next;
      even       = even->next;
    }
    odd->next = even_head;
    return head;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the linked list is in the range |[0, 10⁴]|.
// * |-10⁶ <= Node.val <= 10⁶|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: head = [1,2,3,4,5]
// Output: [1,3,5,2,4]
//

LEETCODE_SOLUTION_UNITTEST(328, OddEvenLinkedList, example_1) {
  auto      solution = MakeSolution();
  ListNode *head     = ListNode::FromVector({1, 2, 3, 4, 5} /*, looped_index*/);
  ListNode *expect   = ListNode::FromVector({1, 3, 5, 2, 4} /*, looped_index*/);
  ListNode *actual   = solution->oddEvenList(head);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head, expect, actual);
}

// [Example #2]
//  Input: head = [2,1,3,5,6,4,7]
// Output: [2,3,6,7,1,5,4]
//

LEETCODE_SOLUTION_UNITTEST(328, OddEvenLinkedList, example_2) {
  auto      solution = MakeSolution();
  ListNode *head =
      ListNode::FromVector({2, 1, 3, 5, 6, 4, 7} /*, looped_index*/);
  ListNode *expect =
      ListNode::FromVector({2, 3, 6, 7, 1, 5, 4} /*, looped_index*/);
  ListNode *actual = solution->oddEvenList(head);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head, expect, actual);
}

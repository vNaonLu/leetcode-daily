// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Remove Duplicates from Sorted List II
//
// https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/
//
// Question ID: 82
// Difficult  : Medium
// Solve Date : 2021/09/21 08:00

#include "leetcode/list_node.h"
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |82. Remove Duplicates from Sorted List II|:
//
// Given the |head| of a sorted linked list, delete all nodes that have
// duplicate numbers, leaving only distinct numbers from the original list.
// Return the linked list sorted as well.  
//

LEETCODE_BEGIN_RESOLVING(82, RemoveDuplicatesFromSortedListII, Solution);

class Solution {
public:
  ListNode *deleteDuplicates(ListNode *head) {
    ListNode  dummy(-101, head);
    ListNode *p = &dummy;
    while (head != nullptr) {
      if (head->next != nullptr && head->val == head->next->val) {
        while (head->next != nullptr && head->val == head->next->val) {
          head = head->next;
        }
        p->next = head->next;
      } else {
        p = p->next;
      }
      head = head->next;
    }
    return dummy.next;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the list is in the range |[0, 300]|.
// * |-100 <= Node.val <= 100|
// * The list is guaranteed to be sorted in ascending order.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: head = [1,2,3,3,4,4,5]
// Output: [1,2,5]
//

LEETCODE_SOLUTION_UNITTEST(82, RemoveDuplicatesFromSortedListII, example_1) {
  auto      solution = MakeSolution();
  ListNode *head =
      ListNode::FromVector({1, 2, 3, 3, 4, 4, 5} /*, looped_index*/);
  ListNode *expect = ListNode::FromVector({1, 2, 5} /*, looped_index*/);
  ListNode *actual = solution->deleteDuplicates(head);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head, expect);
}

// [Example #2]
//  Input: head = [1,1,1,2,3]
// Output: [2,3]
//

LEETCODE_SOLUTION_UNITTEST(82, RemoveDuplicatesFromSortedListII, example_2) {
  auto      solution = MakeSolution();
  ListNode *head     = ListNode::FromVector({1, 1, 1, 2, 3} /*, looped_index*/);
  ListNode *expect   = ListNode::FromVector({2, 3} /*, looped_index*/);
  ListNode *actual   = solution->deleteDuplicates(head);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head, expect);
}

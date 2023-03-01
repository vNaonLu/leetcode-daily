// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Remove Duplicates from Sorted List
//
// https://leetcode.com/problems/remove-duplicates-from-sorted-list/
//
// Question ID: 83
// Difficult  : Easy
// Solve Date : 2021/09/12 08:00

#include "leetcode/list_node.h"
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |83. Remove Duplicates from Sorted List|:
//
// Given the |head| of a sorted linked list, delete all duplicates such that
// each element appears only once. Return the linked list sorted as well.  
//

LEETCODE_BEGIN_RESOLVING(83, RemoveDuplicatesFromSortedList, Solution);

class Solution {
public:
  ListNode *deleteDuplicates(ListNode *head) {
    ListNode  dummy(101, head);
    ListNode *p = head, *pre = &dummy;
    while (p != nullptr) {
      if (pre->val != p->val) {
        pre->next = p;
        pre       = p;
      } else {
        pre->next = nullptr;
      }
      p = p->next;
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
//  Input: head = [1,1,2]
// Output: [1,2]
//

LEETCODE_SOLUTION_UNITTEST(83, RemoveDuplicatesFromSortedList, example_1) {
  auto      solution = MakeSolution();
  ListNode *head     = ListNode::FromVector({1, 1, 2} /*, looped_index*/);
  ListNode *expect   = ListNode::FromVector({1, 2} /*, looped_index*/);
  ListNode *actual   = solution->deleteDuplicates(head);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head);
}

// [Example #2]
//  Input: head = [1,1,2,3,3]
// Output: [1,2,3]
//

LEETCODE_SOLUTION_UNITTEST(83, RemoveDuplicatesFromSortedList, example_2) {
  auto      solution = MakeSolution();
  ListNode *head     = ListNode::FromVector({1, 1, 2, 3, 3} /*, looped_index*/);
  ListNode *expect   = ListNode::FromVector({1, 2, 3} /*, looped_index*/);
  ListNode *actual   = solution->deleteDuplicates(head);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head);
}

// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Insert Greatest Common Divisors in Linked List
//
// https://leetcode.com/problems/insert-greatest-common-divisors-in-linked-list/
//
// Question ID: 2807
// Difficult  : Medium
// Solve Date : 2024/09/10 20:47

#include "leetcode/list_node.h"
#include <iosfwd>
#include <numeric>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2807. Insert Greatest Common Divisors in Linked List|:
//
// Given the head of a linked list |head|, in which each node contains an
// integer value. Between every pair of adjacent nodes, insert a new node with a
// value equal to the greatest common divisor of them. Return the linked list
// after insertion. The greatest common divisor of two numbers is the largest
// positive integer that evenly divides both numbers.
//
//

LEETCODE_BEGIN_RESOLVING(2807, InsertGreatestCommonDivisorsInLinkedList,
                         Solution);

class Solution {
public:
  ListNode *insertGreatestCommonDivisors(ListNode *head) {
    ListNode res;
    auto    *p = &res;
    while (head) {
      auto *nxt = head->next;
      p->next   = new ListNode(head->val);
      p         = p->next;
      if (nxt) {
        p->next = new ListNode(gcd(head->val, nxt->val));
        p       = p->next;
      }
      head = nxt;
    }
    return res.next;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * The number of nodes in the list is in the range |[1, 5000]|.
// * |1 <= Node.val <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: head = [18,6,10,3]
// Output: [18,6,6,2,10,1,3]
//

LEETCODE_SOLUTION_UNITTEST(2807, InsertGreatestCommonDivisorsInLinkedList,
                           example_1) {
  auto      solution = MakeSolution();
  ListNode *head     = ListNode::FromVector({18, 6, 10, 3} /*, looped_index*/);
  ListNode *expect =
      ListNode::FromVector({18, 6, 6, 2, 10, 1, 3} /*, looped_index*/);
  ListNode *actual = solution->insertGreatestCommonDivisors(head);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head, expect, actual);
}

// [Example #2]
//  Input: head = [7]
// Output: [7]
//

LEETCODE_SOLUTION_UNITTEST(2807, InsertGreatestCommonDivisorsInLinkedList,
                           example_2) {
  auto      solution = MakeSolution();
  ListNode *head     = ListNode::FromVector({7} /*, looped_index*/);
  ListNode *expect   = ListNode::FromVector({7} /*, looped_index*/);
  ListNode *actual   = solution->insertGreatestCommonDivisors(head);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head, expect, actual);
}

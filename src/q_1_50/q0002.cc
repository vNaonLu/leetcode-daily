// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Add Two Numbers
//
// https://leetcode.com/problems/add-two-numbers/
//
// Question ID: 2
// Difficult  : Medium
// Solve Date : 2021/09/28 10:52

#include "leetcode/list_node.h"
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2. Add Two Numbers|:
//
// You are given two non-empty linked lists representing two non-negative
// integers. The digits are stored in reverse order, and each of their nodes
// contains a single digit. Add the two numbers and return the sum as a linked
// list. You may assume the two numbers do not contain any leading zero, except
// the number 0 itself.  
//

LEETCODE_BEGIN_RESOLVING(2, AddTwoNumbers, Solution);

class Solution {
public:
  ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
    ListNode  dummy(0);
    ListNode *res = &dummy;
    ListNode *p = l1, *q = l2;
    int       carry = 0;
    while (p != nullptr || q != nullptr) {
      int x     = p == nullptr ? 0 : p->val;
      int y     = q == nullptr ? 0 : q->val;
      int sum   = x + y + carry;
      carry     = sum / 10;
      res->next = new ListNode(sum % 10);
      res       = res->next;
      if (p != nullptr)
        p = p->next;
      if (q != nullptr)
        q = q->next;
    }
    if (carry != 0)
      res->next = new ListNode(carry);
    return dummy.next;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in each linked list is in the range |[1, 100]|.
// * |0 <= Node.val <= 9|
// * It is guaranteed that the list represents a number that does not have
// leading zeros.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: l1 = [2,4,3], l2 = [5,6,4]
// Output: [7,0,8]
//
// 342 + 465 = 807.

LEETCODE_SOLUTION_UNITTEST(2, AddTwoNumbers, example_1) {
  auto      solution = MakeSolution();
  ListNode *l1       = ListNode::FromVector({2, 4, 3} /*, looped_index*/);
  ListNode *l2       = ListNode::FromVector({5, 6, 4} /*, looped_index*/);
  ListNode *expect   = ListNode::FromVector({7, 0, 8} /*, looped_index*/);
  ListNode *actual   = solution->addTwoNumbers(l1, l2);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(l1, l2, expect);
}

// [Example #2]
//  Input: l1 = [0], l2 = [0]
// Output: [0]
//

LEETCODE_SOLUTION_UNITTEST(2, AddTwoNumbers, example_2) {
  auto      solution = MakeSolution();
  ListNode *l1       = ListNode::FromVector({0} /*, looped_index*/);
  ListNode *l2       = ListNode::FromVector({0} /*, looped_index*/);
  ListNode *expect   = ListNode::FromVector({0} /*, looped_index*/);
  ListNode *actual   = solution->addTwoNumbers(l1, l2);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(l1, l2, expect);
}

// [Example #3]
//  Input: l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
// Output: [8,9,9,9,0,0,0,1]
//

LEETCODE_SOLUTION_UNITTEST(2, AddTwoNumbers, example_3) {
  auto      solution = MakeSolution();
  ListNode *l1 = ListNode::FromVector({9, 9, 9, 9, 9, 9, 9} /*, looped_index*/);
  ListNode *l2 = ListNode::FromVector({9, 9, 9, 9} /*, looped_index*/);
  ListNode *expect =
      ListNode::FromVector({8, 9, 9, 9, 0, 0, 0, 1} /*, looped_index*/);
  ListNode *actual = solution->addTwoNumbers(l1, l2);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(l1, l2, expect);
}

// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Swap Nodes in Pairs
//
// https://leetcode.com/problems/swap-nodes-in-pairs/
//
// Question ID: 24
// Difficult  : Medium
// Solve Date : 2021/09/30 13:48

#include "leetcode/list_node.h"
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |24. Swap Nodes in Pairs|:
//
// Given a linked list, swap every two adjacent nodes and return its head. You
// must solve the problem without modifying the values in the list's nodes
// (i.e., only nodes themselves may be changed.)  
//

LEETCODE_BEGIN_RESOLVING(24, SwapNodesInPairs, Solution);

class Solution {
public:
  ListNode *swapPairs(ListNode *head) {
    ListNode  dummy(0, head);
    ListNode *p = &dummy;
    while (p != nullptr && p->next != nullptr && p->next->next != nullptr) {
      ListNode *q = p->next->next, *next = p->next;
      next->next = q->next;
      p->next    = q;
      q->next    = next;
      p          = next;
    }
    return dummy.next;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the list is in the range |[0, 100]|.
// * |0 <= Node.val <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: head = [1,2,3,4]
// Output: [2,1,4,3]
//

LEETCODE_SOLUTION_UNITTEST(24, SwapNodesInPairs, example_1) {
  auto      solution = MakeSolution();
  ListNode *head     = ListNode::FromVector({1, 2, 3, 4} /*, looped_index*/);
  ListNode *expect   = ListNode::FromVector({2, 1, 4, 3} /*, looped_index*/);
  ListNode *actual   = solution->swapPairs(head);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head, expect, actual);
}

// [Example #2]
//  Input: head = []
// Output: []
//

LEETCODE_SOLUTION_UNITTEST(24, SwapNodesInPairs, example_2) {
  auto      solution = MakeSolution();
  ListNode *head     = ListNode::FromVector({} /*, looped_index*/);
  ListNode *expect   = ListNode::FromVector({} /*, looped_index*/);
  ListNode *actual   = solution->swapPairs(head);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head, expect, actual);
}

// [Example #3]
//  Input: head = [1]
// Output: [1]
//

LEETCODE_SOLUTION_UNITTEST(24, SwapNodesInPairs, example_3) {
  auto      solution = MakeSolution();
  ListNode *head     = ListNode::FromVector({1} /*, looped_index*/);
  ListNode *expect   = ListNode::FromVector({1} /*, looped_index*/);
  ListNode *actual   = solution->swapPairs(head);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head, expect, actual);
}

// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Swapping Nodes in a Linked List
//
// https://leetcode.com/problems/swapping-nodes-in-a-linked-list/
//
// Question ID: 1721
// Difficult  : Medium
// Solve Date : 2022/04/04 13:28

#include "leetcode/list_node.h"
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1721. Swapping Nodes in a Linked List|:
//
// You are given the |head| of a linked list, and an integer |k|.
// Return the head of the linked list after swapping the values of the |kᵗʰ|
// node from the beginning and the |kᵗʰ| node from the end (the list is
// 1-indexed).  
//

LEETCODE_BEGIN_RESOLVING(1721, SwappingNodesInALinkedList, Solution);

class Solution {
public:
  ListNode *swapNodes(ListNode *head, int k) {
    ListNode *left = head, *right = head, *curr = head;

    int counter = 1;
    while (nullptr != curr) {
      if (counter < k) {
        left = left->next;
      }
      if (counter > k) {
        right = right->next;
      }
      curr = curr->next;
      counter++;
    }

    swap(left->val, right->val);

    return head;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the list is |n|.
// * |1 <= k <= n <= 10⁵|
// * |0 <= Node.val <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: head = [1,2,3,4,5], k = 2
// Output: [1,4,3,2,5]
//

LEETCODE_SOLUTION_UNITTEST(1721, SwappingNodesInALinkedList, example_1) {
  auto      solution = MakeSolution();
  ListNode *head     = ListNode::FromVector({1, 2, 3, 4, 5} /*, looped_index*/);
  int       k        = 2;
  ListNode *expect   = ListNode::FromVector({1, 4, 3, 2, 5} /*, looped_index*/);
  ListNode *actual   = solution->swapNodes(head, k);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head, expect, actual);
}

// [Example #2]
//  Input: head = [7,9,6,6,7,8,3,0,9,5], k = 5
// Output: [7,9,6,6,8,7,3,0,9,5]
//

LEETCODE_SOLUTION_UNITTEST(1721, SwappingNodesInALinkedList, example_2) {
  auto      solution = MakeSolution();
  ListNode *head =
      ListNode::FromVector({7, 9, 6, 6, 7, 8, 3, 0, 9, 5} /*, looped_index*/);
  int       k = 5;
  ListNode *expect =
      ListNode::FromVector({7, 9, 6, 6, 8, 7, 3, 0, 9, 5} /*, looped_index*/);
  ListNode *actual = solution->swapNodes(head, k);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head, expect, actual);
}

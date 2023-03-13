// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Linked List Cycle II
//
// https://leetcode.com/problems/linked-list-cycle-ii/
//
// Question ID: 142
// Difficult  : Medium
// Solve Date : 2021/09/28 11:22

#include "leetcode/list_node.h"
#include <iosfwd>
#include <optional>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |142. Linked List Cycle II|:
//
// Given the |head| of a linked list, return the node where the cycle begins. If
// there is no cycle, return |null|. There is a cycle in a linked list if there
// is some node in the list that can be reached again by continuously following
// the |next| pointer. Internally, |pos| is used to denote the index of the node
// that tail's |next| pointer is connected to (0-indexed). It is |-1| if there
// is no cycle. Note that |pos| is not passed as a parameter. Do not modify the
// linked list.  
//

LEETCODE_BEGIN_RESOLVING(142, LinkedListCycleII, Solution);

class Solution {
public:
  ListNode *detectCycle(ListNode *head) {
    auto p = head, tmp = head;
    while (p != nullptr) {
      p   = p->next;
      tmp = tmp->next;
      if (p) {
        p = p->next;
        if (tmp == p) {
          tmp = head;
          break;
        }
      }
    }
    while (p != nullptr && p != tmp) {
      p   = p->next;
      tmp = tmp->next;
    }
    return p;
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
// Output: tail connects to node index 1
//
// There is a cycle in the linked list, where tail connects to the second node.

LEETCODE_SOLUTION_UNITTEST(142, LinkedListCycleII, example_1) {
  auto      solution = MakeSolution();
  ListNode *head     = ListNode::FromVector({3, 2, 0, -4}, 1);
  ListNode *expect   = head->GetChild(1);
  ListNode *actual   = solution->detectCycle(head);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head, expect, actual);
}

// [Example #2]
//  Input: head = [1,2], pos = 0
// Output: tail connects to node index 0
//
// There is a cycle in the linked list, where tail connects to the first node.

LEETCODE_SOLUTION_UNITTEST(142, LinkedListCycleII, example_2) {
  auto      solution = MakeSolution();
  ListNode *head     = ListNode::FromVector({1, 2}, 0);
  ListNode *expect   = head->GetChild(0);
  ListNode *actual   = solution->detectCycle(head);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head, expect, actual);
}

// [Example #3]
//  Input: head = [1], pos = -1
// Output: no cycle
//
// There is no cycle in the linked list.

LEETCODE_SOLUTION_UNITTEST(142, LinkedListCycleII, example_3) {
  auto      solution = MakeSolution();
  ListNode *head     = ListNode::FromVector({1}, nullopt);
  ListNode *expect   = nullptr;
  ListNode *actual   = solution->detectCycle(head);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head, expect, actual);
}

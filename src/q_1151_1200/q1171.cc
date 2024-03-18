// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Remove Zero Sum Consecutive Nodes from Linked List
//
// https://leetcode.com/problems/remove-zero-sum-consecutive-nodes-from-linked-list/
//
// Question ID: 1171
// Difficult  : Medium
// Solve Date : 2024/03/12 22:23

#include "leetcode/list_node.h"
#include <iosfwd>
#include <unordered_map>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1171. Remove Zero Sum Consecutive Nodes from Linked List|:
//
// Given the |head| of a linked list, we repeatedly delete consecutive sequences
// of nodes that sum to |0| until there are no such sequences.
//
// After doing so, return the head of the final linked list.  You may return any
// such answer.
//
// (Note that in the examples below, all sequences are serializations of
// |ListNode| objects.)
//

LEETCODE_BEGIN_RESOLVING(1171, RemoveZeroSumConsecutiveNodesFromLinkedList,
                         Solution);

class Solution {
public:
  ListNode *removeZeroSumSublists(ListNode *head) {
    ListNode                       dummy(0, head);
    unordered_map<int, ListNode *> mp;
    int                            prefix = 0;
    for (auto *p = &dummy; p; p = p->next) {
      prefix += p->val;
      mp[prefix] = p;
    }
    prefix = 0;
    for (auto *p = &dummy; p; p = p->next) {
      prefix += p->val;
      p->next = mp[prefix]->next;
    }
    return dummy.next;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * The given linked list will contain between |1| and |1000| nodes.
// * Each node in the linked list has |-1000 <= node.val <= 1000|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: head = [1,2,-3,3,1]
// Output: [3,1]
// Note: The answer [1,2,1] would also be accepted.
//

LEETCODE_SOLUTION_UNITTEST(1171, RemoveZeroSumConsecutiveNodesFromLinkedList,
                           example_1) {
  auto      solution = MakeSolution();
  ListNode *head   = ListNode::FromVector({1, 2, -3, 3, 1} /*, looped_index*/);
  ListNode *expect = ListNode::FromVector({3, 1} /*, looped_index*/);
  ListNode *actual = solution->removeZeroSumSublists(head);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::ReleaseAll();
}

// [Example #2]
//  Input: head = [1,2,3,-3,4]
// Output: [1,2,4]
//

LEETCODE_SOLUTION_UNITTEST(1171, RemoveZeroSumConsecutiveNodesFromLinkedList,
                           example_2) {
  auto      solution = MakeSolution();
  ListNode *head   = ListNode::FromVector({1, 2, 3, -3, 4} /*, looped_index*/);
  ListNode *expect = ListNode::FromVector({1, 2, 4} /*, looped_index*/);
  ListNode *actual = solution->removeZeroSumSublists(head);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::ReleaseAll();
}

// [Example #3]
//  Input: head = [1,2,3,-3,-2]
// Output: [1]
//

LEETCODE_SOLUTION_UNITTEST(1171, RemoveZeroSumConsecutiveNodesFromLinkedList,
                           example_3) {
  auto      solution = MakeSolution();
  ListNode *head   = ListNode::FromVector({1, 2, 3, -3, -2} /*, looped_index*/);
  ListNode *expect = ListNode::FromVector({1} /*, looped_index*/);
  ListNode *actual = solution->removeZeroSumSublists(head);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::ReleaseAll();
}

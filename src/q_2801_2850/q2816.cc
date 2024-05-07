// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Double a Number Represented as a Linked List
//
// https://leetcode.com/problems/double-a-number-represented-as-a-linked-list/
//
// Question ID: 2816
// Difficult  : Medium
// Solve Date : 2024/05/07 22:48

#include "leetcode/list_node.h"
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2816. Double a Number Represented as a Linked List|:
//
// You are given the |head| of a non-empty linked list representing a
// non-negative integer without leading zeroes. Return the |head| of the linked
// list after doubling it.
//
//

LEETCODE_BEGIN_RESOLVING(2816, DoubleANumberRepresentedAsALinkedList, Solution);

class Solution {
public:
  ListNode *doubleIt(ListNode *head) {
    vector<ListNode *> v;
    for (auto *p = head; p; p = p->next) {
      v.emplace_back(p);
    }
    int inc = 0;
    reverse(v.begin(), v.end());
    for (auto *p : v) {
      p->val *= 2;
      p->val += inc;
      inc = p->val / 10;
      p->val %= 10;
    }
    if (inc > 0) {
      head = new ListNode(inc, head);
    }
    return head;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * The number of nodes in the list is in the range |[1, 10⁴]|
// * |0 <= Node.val <= 9|
// * The input is generated such that the list represents a number that does not
// have leading zeros, except the number |0| itself.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: head = [1,8,9]
// Output: [3,7,8]
//

LEETCODE_SOLUTION_UNITTEST(2816, DoubleANumberRepresentedAsALinkedList,
                           example_1) {
  auto      solution = MakeSolution();
  ListNode *head     = ListNode::FromVector({1, 8, 9} /*, looped_index*/);
  ListNode *expect   = ListNode::FromVector({3, 7, 8} /*, looped_index*/);
  ListNode *actual   = solution->doubleIt(head);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head, expect, actual);
}

// [Example #2]
//  Input: head = [9,9,9]
// Output: [1,9,9,8]
//

LEETCODE_SOLUTION_UNITTEST(2816, DoubleANumberRepresentedAsALinkedList,
                           example_2) {
  auto      solution = MakeSolution();
  ListNode *head     = ListNode::FromVector({9, 9, 9} /*, looped_index*/);
  ListNode *expect   = ListNode::FromVector({1, 9, 9, 8} /*, looped_index*/);
  ListNode *actual   = solution->doubleIt(head);
  LCD_EXPECT_EQ(expect, actual);
  ListNode::Release(head, expect, actual);
}
